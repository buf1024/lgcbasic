#!/usr/bin/env python

import sys
import os
import os.path
import logging

g_IgnoreDirs = ['res', 'test', '.svn']
g_FileExt = '.h'

g_LinkDir = 'E:\\code\\SVN\\GCBasic\\CmmHdr\\'
g_TargetDir = 'E:\\code\\SVN\\GCBasic\\gclib\\'

def processmodule(dir):
    logging.info('Begin processing %s ...' % dir)
    
    files = os.listdir(dir)
    for file in files:
        if file.endswith(g_FileExt):
            cmd = 'mklink %s %s' % (g_LinkDir + file, dir + file)
            os.popen(cmd)
    
def process():
    logging.info('Begin processing %s ...' % g_TargetDir)
    
    if not os.path.exists(g_TargetDir) or os.path.isfile(g_TargetDir):
        logging.error('%s is not exist or is normal file, ignore ...' % g_TargetDir)
    else:
        subdirs = os.listdir(g_TargetDir)
        for subdir in subdirs:
            if os.path.isdir(g_TargetDir + subdir):
                if subdir.lower() in g_IgnoreDirs:
                    continue
                if subdir == '.' or subdir == '..':
                    continue
                processDir = g_TargetDir + subdir + os.sep
                processmodule(processDir)
    
    logging.info('End processing %s ...' % g_TargetDir)

def main():
    logging.basicConfig(level=logging.DEBUG,
			format='%(asctime)s %(levelname)-8s %(message)s',
			datefmt='%H:%M:S')
    logging.info('Begin processing...')
    process()
    logging.info('End processing...')
    
if __name__ == '__main__':
    main()



