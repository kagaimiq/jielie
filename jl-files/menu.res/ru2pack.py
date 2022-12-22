from PIL import Image, ImageFont, ImageDraw
import sys, yaml, struct, os.path, io

print("JIE LI Files -- menu.res Packer [R2]")

if len(sys.argv) < 3:
    print("Usage: %s <input yaml file> <output menu.res>" % sys.argv[0])
    sys.exit(1)

with open(sys.argv[1], 'r') as ru2i:
    try:
        ru2_info = yaml.load(ru2i, Loader=yaml.FullLoader)
    except Exception as e:
        print("Error while reading ru2info!", e)
        sys.exit(2)
    
    ############################################################################################
    
    if ru2_info.get('type', '') != 'jieli-ru2':
        print("The type of the input yaml is not the 'jieli-ru2'!")
        sys.exit(2)
    
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
        'unk-22',
        'unk-23',
        'unk-24',
        'unk-25',
        'unk-26',
        'unk-27',
        'unk-28',
        'unk-29',
        'unk-30',
        'unk-31'
    )
    
    if not 'palettes' in ru2_info: ru2_info['palettes'] = {}
    if not 'pictures' in ru2_info: ru2_info['pictures'] = {}
    if not 'strings' in ru2_info: ru2_info['strings'] = {}
    
    #######################################################
    
    def getFnRelToYaml(path):
        return os.path.dirname(os.path.realpath(sys.argv[1])) + '/' + path
    
    palettes = []
    pictures = []
    strings = []
    picture_names = b''
    strings_count = 0
    ru2_lang = 0
    
    ### Parse Palettes ###
    try:
        print(">>> Palettes... <<<")
        for n, elm in enumerate(ru2_info['palettes'].get('entries', []), 1):
            palentry = {
                'count': 0,
                'data': b''
            }
            
            for color in elm.get('colors', []):
                cR, cG, cB = int(color[1:3],16),int(color[3:5],16),int(color[5:7],16)
                
                color = [
                    max(0, min(255, int(128 + (0.5     * cR) - (0.41869 * cG) - (0.08131 * cB)))),
                    max(0, min(255, int(128 - (0.16874 * cR) - (0.33126 * cG) + (0.5     * cB)))),
                    max(0, min(255, int(      0.299    * cR  +  0.587   * cG +   0.114   * cB))),
                    0
                ]
                
                palentry['data'] += bytes(color)
            
            palettes.append(palentry)
            
            print("    [%5d] %5d bytes, %d colors" % (n, len(palentry['data']), len(palentry['data']) // 4))
            
    except Exception as e:
        print("Failed to parse palettes!", e)
        sys.exit(3)
    
    ### Parse Pictures ###
    try:
        print(">>> Pictures... <<<")
        for n, elm in enumerate(ru2_info['pictures'].get('entries', []), 1):
            if not elm.get('type') in ('mono','rgb323','rgb565','rgb888','yuv420','jpeg','pal8'):
                print("unknown pic type [%s]" % elm.get('type'))
                continue
            
            if not 'filename' in elm:
                print("missing filename!")
                continue
            
            if not 'name' in elm:
                elm['name'] = os.path.splitext(os.path.basename(elm['filename']))[0]
            
            picentry = {
                'width': 0,
                'height': 0,
                'type': {'mono':0, 'pal8':1, 'rgb565':2, 'rgb888':3, 'yuv420':4, 'jpeg':5}[elm['type']],
                'data': b''
            }
            
            with Image.open(getFnRelToYaml(elm['filename'])) as pic:
                picentry['width'] = pic.width
                picentry['height'] = pic.height
                
                if elm['type'] == 'mono':
                    pic = pic.convert('1')
                    for py in range(0, pic.height, 8):
                        for px in range(pic.width):
                            byte = 0
                            
                            for pb in range(8):
                                if (py + pb) >= pic.height: break
                                
                                if pic.getpixel((px, py+pb)) != 0:
                                    byte |= 0x01 << pb
                            
                            picentry['data'] += bytes([byte])
                
                elif elm['type'] == 'jpeg':
                    bio = io.BytesIO(b'')
                    pic.save(bio, 'JPEG', quality=elm.get('quality', 75))
                    bio.seek(0)
                    picentry['data'] += bio.read()
                    
                else:
                    print("--- Image type %s is TODO ---" % elm['type'])
                    continue
            
            picture_names += bytes(elm['name'] + ':', 'ascii')
            pictures.append(picentry)
            
            print("    [%5d] %5d bytes, %dx%d" % (n, len(picentry['data']), picentry['width'], picentry['height']))
            
    except Exception as e:
        print("Failed to parse pictures!", e)
        sys.exit(3)
    
    ### Parse Strings ###
    try:
        print(">>> Strings... <<<")
        
        slangid = -1
        lastfont = ''
        lastsize = 12
        font = ImageFont.load_default()
        
        for langid in range(len(lang_names)):
            lang = lang_names[langid]
            
            if lang in ru2_info['strings']:
                ru2_lang |= (1 << langid)
                print("  (%s)" % lang)
                
                nstrings = 0
                for elm in ru2_info['strings'][lang]:
                    if not elm.get('source') in ('file','render'):
                        print("unknown string source [%s]" % elm.get('source'))
                        continue
                    
                    strentry = {
                        'width': 0,
                        'height': 0,
                        'data': b''
                    }
                    
                    if elm['source'] == 'file':
                        if not 'filename' in elm:
                            print("missing filename!")
                            continue
                        
                        with Image.open(getFnRelToYaml(elm['filename'])) as pic:
                            pic = pic.convert('1')
                            
                            strentry['width'] = pic.width
                            strentry['height'] = pic.height

                            for py in range(0, pic.height, 8):
                                for px in range(pic.width):
                                    byte = 0
                                    
                                    for pb in range(8):
                                        if (py + pb) >= pic.height: break
                                        
                                        if pic.getpixel((px, py+pb)) == 0:
                                            byte |= 0x01 << pb
                                    
                                    strentry['data'] += bytes([byte])
                    
                    elif elm['source'] == 'render':
                        lastfont = elm.get('font', lastfont)
                        lastsize = elm.get('size', lastsize)
                        
                        #If we have no text then we don't render this string entry
                        #as it may change the font or text size...
                        if not 'text' in elm:
                            continue
                        
                        try:
                            font = ImageFont.truetype(lastfont, size=lastsize)
                        except Exception as e:
                            print("couldn't load font [%s] (%s)!" % (lastfont, e))
                        
                        try:
                            with Image.new('1', font.getsize(elm['text']), color=255) as pic:
                                strentry['width'] = pic.width
                                strentry['height'] = pic.height
                                
                                ImageDraw.Draw(pic).text((0,0), elm['text'], font=font)

                                for py in range(0, pic.height, 8):
                                    for px in range(pic.width):
                                        byte = 0
                                        
                                        for pb in range(8):
                                            if (py + pb) >= pic.height: break
                                            
                                            if pic.getpixel((px, py+pb)) == 0:
                                                byte |= 0x01 << pb
                                        
                                        strentry['data'] += bytes([byte])
                            
                        except Exception as e:
                            print("couldn't render string (%s)" % e)
            
                    strings.append(strentry)
                    nstrings += 1
                    
                    print("    [%5d] %5d bytes, %dx%d" % (nstrings, len(strentry['data']), strentry['width'], strentry['height']))
                
                if slangid < 0:
                    slangid = langid
                    strings_count = nstrings
                else:
                    if nstrings != strings_count:
                        raise Exception("Count of strings in [%s] does not match the count in [%s]!" % (lang_names[langid], lang_names[slangid]))

    except Exception as e:
        print("Failed to parse strings!", e)
        sys.exit(3)
    
    ### Write Out ###
    with open(sys.argv[2], 'wb') as ru2f:
        ru2f.write(struct.pack('<4sHIH',
            b'RU2\x19',
            ru2_info.get('counts', len(palettes)+len(pictures)+len(strings)),  #"Number of resources temporarily reserved" --> Just assume this
            ru2_lang,
            len(pictures)
        ))
        
        entries_pos  = ru2f.tell()
        palettes_pos = entries_pos  + 8 * 3
        pictures_pos = palettes_pos + 10 * len(palettes)
        strings_pos  = pictures_pos + 13 * len(pictures)
        data_pos     = strings_pos  + 12 * len(strings)
        
        #--- entries ---
        ru2f.write(struct.pack('<IHBB', palettes_pos, len(palettes), 0x43, ru2_info['palettes'].get('panel-type', 0)))
        ru2f.write(struct.pack('<IHBB', pictures_pos, len(pictures), 0x50, ru2_info['pictures'].get('panel-type', 0)))
        ru2f.write(struct.pack('<IHBB', strings_pos,  strings_count, 0x53, ru2_info['strings'].get('panel-type', 0)))
        
        #--- infos ---
        for elm in palettes:
            ru2f.write(struct.pack('<HII', len(elm['data']) // 4, data_pos, len(elm['data'])))
            data_pos += len(elm['data'])
        
        for elm in pictures:
            ru2f.write(struct.pack('<BHHII', elm['type'], elm['width'], elm['height'], data_pos, len(elm['data'])))
            data_pos += len(elm['data'])
        
        for elm in strings:
            ru2f.write(struct.pack('<HHII', elm['width'], elm['height'], data_pos, len(elm['data'])))
            data_pos += len(elm['data'])

        #--- datas ---
        for elm in palettes: ru2f.write(elm['data'])
        for elm in pictures: ru2f.write(elm['data'])
        for elm in strings: ru2f.write(elm['data'])
        
        ru2f.write(picture_names)
        
        print("Pack done!")
