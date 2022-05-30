import sys
for line in sys.stdin: 
    a = line.strip("\n")
    if "$$" in a and a != "$$":
        print(a.replace("$$", "$"))
    else:
        if "html>" in a:
            continue
        elif "img style=" in a:
            src = a.split('src="')[1].split('"')[0]
            style = a.split('style="')[1].split('"')[0].replace(":", "=")
            style_key = style.split("=")[0]
            style_val = style.split("=")[1]
            new_style = style_key + '="' + style_val + '"'
            #print('![](%s){:%s}' % ("./" + src, new_style))
            print('![](%s)' % ("./" + src))
        else:
            print(a)
