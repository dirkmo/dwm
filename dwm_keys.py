#! /usr/bin/env python3

# stupid script that collects key shortcut comments and prints a summary on stdout.
# it assumes config.h in the same directory.

lines = []

with open("config.h") as f:
    start = False
    for l in f.readlines():
        if start:
            if l.find("};") == 0:
                break
            l = l.strip()
            if l.find("{") == 0:
                l = l[1:]
                secondcomma = l.find(",", l.find(",")+1)
                key = l[:secondcomma]
                key = key.replace(",", "+")
                key = key.replace("|", "+")
                key = key.replace(" ", "")
                key = key.replace("XK_", "")
                key = key.replace("MODKEY", "Super")
                key = key.replace("ShiftMask", "Shift")
                key = key.replace("ControlMask", "Ctrl")
                key = key.replace("Mod1Mask", "Alt")
                commentpos = l.find("//")
                comment = ""
                if commentpos > 0:
                    comment = ": " + l[commentpos+2:].strip()
                    print(f"{key:20} {comment}")
                else:
                    print(key)
        elif l.find("static const Key keys[] = {") == 0:
            start = True
