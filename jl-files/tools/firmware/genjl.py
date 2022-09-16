import struct, crcmod, sys, yaml, os

if len(sys.argv) < 3:
    print("Usage: %s <input yaml layout> <output bin>" % sys.argv[0])
    sys.exit(1)

jl_crc16 = crcmod.mkCrcFun(0x11021, rev=False, initCrc=0x0000, xorOut=0x0000)

def jl_crypt(data, key=0xffff):
    data = bytearray(data)

    for i in range(len(data)):
        data[i] ^= key & 0xff
        key = ((key << 1) ^ (0x1021 if (key >> 15) else 0)) & 0xffff

    return bytes(data)

def jl_bcrypt(data, key=0xffff, bsize=32, dynkey=True):
    fdata = b''

    for i in range(0, len(data), bsize):
        if dynkey: xkey = key ^ (i >> 2)
        else:      xkey = key

        fdata += jl_crypt(data[i:i+bsize], xkey)

    return fdata

'''
00: ui.apu, res.res, audlogo.res        <misc>
01: uboot.boot                          <uboot.boot -- bootloader>
02: user.app                            <user.app   -- uncompressed app?>
03: cmd_zone, __zone2.zon, _____.____2  <zones>
04: sdram.apu                           <sdram.apu  -- compressed app?>
05: ver.bin                             <version file>
06: sys.cfg                             <system config>
07: spc.aer                             <special area definitions>
08: chip_key.bin                        <chip key>
'''

with open(sys.argv[1], 'r') as layf:
    try:
        layout = yaml.load(layf, Loader=yaml.FullLoader)
    except Exception as e:
        print("Error while reading layout!", e)
        sys.exit(2)

    def gensyd(lay, align, filler):
        def nalign(n):
            if (align > 0) and (n % align):
                n += align - (n % align)
            return n

        def n4align(n):
            if (align > 0) and (n % align):
                return align - (n % align)
            return 0

        hdrpos = lay.get('hdrpos', 'begin')
        assert(hdrpos in ('begin', 'end'))

        #>>> Make files <<<#
        files = []

        for fil in lay['files']:
            xfil = {\
                'type': fil.get('type', 0), \
                'name': fil.get('name', os.path.basename(fil.get('filename', ''))),\
            }

            ctype = fil.get('crypt', 'none')
            assert(ctype in ('none', 'whole', 'block'))

            ftype = fil.get('content', 'data')
            assert(ftype in ('data', 'bankcb', 'syd'))

            #>>> Make file contents <<<#
            if ftype == 'bankcb': # bootloader
                slices = []

                with open(fil['filename'], 'rb') as f:
                    while True:
                        rd = f.read(65535)
                        if len(rd) < 1: break
                        slices.append(rd)

                hdrs = []

                off = 0x10 * len(slices)
                addr = fil.get('load_addr', 0)

                for fslice in slices:
                    hdr = struct.pack('<HHIIH', len(slices), len(fslice), addr, off, jl_crc16(fslice))
                    hdr += jl_crc16(hdr).to_bytes(2, 'little')
                    hdrs.append(hdr)

                    off += len(fslice)
                    addr += len(fslice)

                xfil['data'] = b''
                rawdata = b''

                for hdr in hdrs:
                    xfil['data'] += jl_crypt(hdr)
                    rawdata += hdr

                for fslice in slices:
                    xfil['data'] += jl_crypt(fslice)
                    rawdata += fslice

                xfil['crc16'] = jl_crc16(rawdata)

            elif ftype == 'syd':
                xfil['data'] = gensyd(fil, fil.get('align', align), fil.get('filler', filler))

            else: # normal file
                with open(fil['filename'], 'rb') as f:
                    xfil['data'] = f.read()

            #>>> Encrypt if needed <<<#
            if ctype == 'whole':
                xfil['data'] = jl_crypt(xfil['data'], fil.get('key', 0xffff))

            elif ctype == 'block':
                xfil['data'] = jl_bcrypt(xfil['data'], fil.get('key', 0xffff), \
                                         fil.get('block_size', 32), fil.get('dynamic_key', True))

            files.append(xfil)

        #>>> Make entries <<<#
        syd_e = b''

        if hdrpos == 'end': off = 0
        else:               off = 0x20 + 0x20 * len(files) # {syd hdr len} + {syd ent len} * nfiles

        for i, fil in enumerate(files):
            off = nalign(off)

            ent = struct.pack('<BBHIII16s', fil['type'], 0, fil.get('crc16', jl_crc16(fil['data'])), \
                                            off, len(fil['data']), i, \
                                            bytes(fil['name'][:16], 'ascii'))

            if lay.get('hdrencrypt', True): ent = jl_crypt(ent)
            syd_e += ent

            off += len(fil['data'])

        #>>> Make header <<<#
        syd_h = struct.pack('<HIIIIIII', jl_crc16(syd_e),  0x696b6172,0x61747573, \
                                         len(syd_e)//0x20, 0x616e6f6b,0x21216174, \
                                                           0x6167616b,0x2121696d)
        syd_h = jl_crc16(syd_h).to_bytes(2, 'little') + syd_h
        if lay.get('hdrencrypt', True): syd_h = jl_crypt(syd_h)

        #>>> Put data <<<#
        data = b''

        if hdrpos == 'begin':
            data += syd_h + syd_e
            data += filler * n4align(len(data))

        for fil in files:
            data += fil['data']
            data += filler * n4align(len(data))

        if hdrpos == 'end':
            data += syd_h + syd_e
            data += filler * n4align(len(data))

        return data

    with open(sys.argv[2], 'wb') as outf:
        outf.write(gensyd(layout, align=layout.get('align', 512), filler=layout.get('filler', b'\xff')))
