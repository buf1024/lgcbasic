#!/usr/bin/env python
#coding: utf-8
import sys

gAndroidVer = [
    ['1.5',   '3', 'Cupcake'],
    ['1.6',   '4', 'Donut'],
    ['2.1',   '7', '¨¦clair'],
    ['2.2',   '8', 'Froyo'],
    ['2.3',   '9', 'Gingerbread'],
    ['2.3.3', '10', 'Gingerbread'],
    ['3.0',   '11', 'Ice Cream']
]        

def gethelper(key, field):
    for v in gAndroidVer:
        if v[field] == key:
            return v
    return []

def get(key):
    if len(key) == 0:
        return gAndroidVer 
    val = None
    try:
        val = int(key[0])
        return [gethelper(key[0], 1)]
    except ValueError:
        val = None  
    try:
        val = float(key[0])
        return [gethelper(key[0], 0)]
    except ValueError:
        val = None
    return [gethelper(key[0], 2)]
def usage():
    print 'androidver [version number]'
    
def main():
    argv = sys.argv[1:]
    ver = get(argv)
    if len(ver[0]) != 0:
        print 'Version\tAPI Level\tCode'
    else:
        print 'Not found!'
    for v in ver:
        if len(v) != 0:
            print '%s\t%s\t\t%s' % (v[0], v[1], v[2])
    
if __name__ == '__main__':
    main()
