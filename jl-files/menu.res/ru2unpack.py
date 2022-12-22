from PIL import Image
import sys, yaml, struct, os, io

print("JIE LI Files -- menu.res Unpacker [R2]")

if len(sys.argv) < 3:
    print("Usage: %s <input menu.res> <output yaml file>" % sys.argv[0])
    sys.exit(1)

with open(sys.argv[1], 'rb') as ru2f:
    try:
        ru2_magic, ru2_counts, ru2_lang, ru2_sindex = struct.unpack('<4sHIH', ru2f.read(12))
        
        if ru2_magic != b'RU2\x19':
            raise Exception('bad magic ' + str(ru2_magic))
    except Exception as e:
        print("Error while reading header!", e)
        sys.exit(2)
    
    ############################################################################################
    def getFnRelToYaml(path):
        path = os.path.dirname(os.path.realpath(sys.argv[2])) + '/' + path
        
        pathd = os.path.dirname(path)
        if not os.path.exists(pathd): os.makedirs(pathd)
        
        return path
    
    ru2_info = {
        'type': 'jieli-ru2',
        'counts': ru2_counts,
        'palettes': {},
        'pictures': {},
        'strings': {},
    }
    
    lang_names = (
        'chinese_simp',
        'chinese_trad',
        'japaneese',
        'korean',
        'english',
        'french',
        'german',
        'italian',
        'dutch',
        'portugese',
        'spanish',
        'swedish',
        'czech',
        'danish',
        'polish',
        'russian',
        'turkish',
        'hebrew',
        'thai',
        'hungarian',
        'romanian',
        'arabic',
        'unk22',
        'unk23',
        'unk24',
        'unk25',
        'unk26',
        'unk27',
        'unk28',
        'unk29',
        'unk30',
        'unk31'
    )
    
    langs = []
    for i in range(len(lang_names)):
        if ru2_lang & (1 << i):
            langs.append(lang_names[i])
    
    print("languages:", ", ".join(langs))
    
    ######### Read Entries #########
    entries = []
    picture_names = []
    
    try:
        for i in range(3):
            entries.append(struct.unpack('<IHBB', ru2f.read(8)))
        
        ru2f.seek(0, 2)
        endpos = ru2f.tell()
        
        scnt = 0
        slen = 0
        
        while True:
            ru2f.seek(endpos-1)
            byte = ru2f.read(1)
            if (len(byte) == 0) or (byte[0] < 0x20) or (byte[0] >= 0x7f): break
            endpos -= 1
            
            if byte == b':':
                slen = 0
                
                # limit it by the possible count value #
                scnt += 1
            else:
                # limit the string length to 32 chars #
                slen += 1
                if slen > 32: break
        
        strbuild = ''
        while True:
            byte = ru2f.read(1)
            if (len(byte) == 0) or (byte[0] < 0x20) or (byte[0] >= 0x7f): break
            
            if byte == b':':
                picture_names.append(strbuild)
                strbuild = ''
            else:
                strbuild += chr(byte[0])
    
    except Exception as e:
        print("Error while reading entries!", e)
        sys.exit(2)
    
    ######### Parse Entries ########
    try:
        for off, cnt, type, ptype in entries:
            ru2f.seek(off)
            print("--- Entry type %02x, OFF=%08x, CNT=%d, Panel_Type=%d" % (type, off, cnt, ptype))
            
            if type == ord('C'):
                print(">>Palettes (%d)" % cnt)
                ru2_info['palettes']['panel-type'] = ptype
                ru2_info['palettes']['entries'] = []
                
                entries2 = []
                for i in range(cnt):
                    entries2.append(struct.unpack('<HII', ru2f.read(10)))
                
                for n, (ecnt, eoff, elen) in enumerate(entries2):
                    ru2f.seek(eoff)
                    data = ru2f.read(elen)
                    print("    [%5d] @%08x - %5d bytes, %d colors" % (n, eoff, elen, ecnt))
                    
                    entry = {'colors': []}
                    for n in range(ecnt):
                        cV, cU, cY, cX = tuple(data[n*4:n*4+4])
                        
                        color = (
                            max(0, min(255, int(cY + 1.402                          * (cV - 128)))),
                            max(0, min(255, int(cY - 0.34414 * (cU - 128) - 0.71414 * (cV - 128)))),
                            max(0, min(255, int(cY + 1.1772  * (cU - 128)                       )))
                        )
                        
                        entry['colors'].append('#%02x%02x%02x' % color)
                    
                    ru2_info['palettes']['entries'].append(entry)
            
            elif type == ord('P'):
                print(">>Pictures (%d)" % cnt)
                ru2_info['pictures']['panel-type'] = ptype
                ru2_info['pictures']['entries'] = []
                
                entries2 = []
                for i in range(cnt):
                    entries2.append(struct.unpack('<BHHII', ru2f.read(13)))
                
                for n, (etype, ewidth, eheight, eoff, elen) in enumerate(entries2):
                    ru2f.seek(eoff)
                    data = ru2f.read(elen)
                    
                    entry = {
                        'type': ['mono','pal8','rgb565','rgb888','yuv420','jpeg'][etype],
                        'filename': '%s-Pic/%s.png' % (os.path.basename(sys.argv[2]), picture_names[n] if n < len(picture_names) else ('%05d' % n))
                    }
                    
                    if n < len(picture_names): entry['name'] = picture_names[n]
                    
                    print("    [%5d] @%08x - %5d bytes, %dx%d, Type %d(%s), Name \"%s\""
                        % (n, eoff, elen, ewidth, eheight, etype, entry['type'], entry.get('name', '<unknown>')))
                    
                    if entry['type'] == 'mono':
                        with Image.new('1', (ewidth, eheight)) as pic:
                            for py in range(eheight):
                                for px in range(ewidth):
                                    pic.putpixel((px, py), 255 if data[px + (py >> 3) * ewidth] & (0x01 << (py & 7)) else 0)
                            
                            pic.save(getFnRelToYaml(entry['filename']))
                    
                    elif entry['type'] == 'pal8':
                        with Image.new('RGBA', (ewidth, eheight)) as pic:
                            pixno = 0
                            pielen = 0
                            
                            for byte in data:
                                #Decoding of the Most Sophsticated Compreession EVER
                                
                                #TODO: support the variation where there's no RLE compression
                                if byte > 0xc0 and pielen == 0 and True:
                                    pielen = byte - 0xc0
                                else:
                                    if pielen == 0: pielen = 1
                                    
                                    color = (0,0,0,0)
                                    
                                    if byte > 0:
                                        try:
                                            # Get PAL
                                            color = ru2_info['palettes']['entries'][0]['colors'][byte]
                                            color = (int(color[1:3],16),int(color[3:5],16),int(color[5:7],16),255)
                                        except:
                                            color = (255,0,0,127)
                                    
                                    for i in range(pielen):
                                        if pixno >= (ewidth * eheight): break
                                        pic.putpixel((pixno % ewidth, pixno // ewidth), color)
                                        pixno += 1
                                    
                                    pielen = 0
                            
                            pic.save(getFnRelToYaml(entry['filename']))
                    
                    elif entry['type'] == 'jpeg':
                        with Image.open(io.BytesIO(data)) as pic:
                            pic.save(getFnRelToYaml(entry['filename']))
            
                    ru2_info['pictures']['entries'].append(entry)
            
            elif type == ord('S'):
                ru2_info['strings']['panel-type'] = ptype
                print(">>Strings (%d - %d total)" % (cnt, cnt * len(langs)))
            
                entries2 = {}
                for lang in langs:
                    entries2[lang] = []
                    for i in range(cnt):
                        entries2[lang].append(struct.unpack('<HHII', ru2f.read(12)))
                
                for lang in entries2:
                    ru2_info['strings'][lang] = []
                    print("  (%s)" % lang)
                    
                    for n, (ewidth, eheight, eoff, elen) in enumerate(entries2[lang]):
                        ru2f.seek(eoff)
                        data = ru2f.read(elen)
                        print("    [%5d] @%08x - %5d bytes, %dx%d" % (n, eoff, elen, ewidth, eheight))
                        
                        entry = {
                            'source': 'file',
                            'filename': '%s-Str/%s/%05d.png' % (os.path.basename(sys.argv[2]), lang, n)
                        }
                        
                        if ewidth > 0 and eheight > 0:
                            with Image.new('1', (ewidth, eheight)) as pic:
                                for py in range(eheight):
                                    for px in range(ewidth):
                                        pic.putpixel((px, py), 0 if data[px + (py >> 3) * ewidth] & (0x01 << (py & 7)) else 255)
                                
                                pic.save(getFnRelToYaml(entry['filename']))
                    
                        ru2_info['strings'][lang].append(entry)
    except Exception as e:
        print("Error while parsing entries!", e)
        sys.exit(2)
    
    print("Unpack done!")
    
    with open(sys.argv[2], 'w') as ru2if:
        yaml.dump(ru2_info, ru2if)
