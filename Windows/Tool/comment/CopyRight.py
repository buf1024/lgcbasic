#!/usr/bin/env python

import os
import os.path
import sys
import logging
from fnmatch import fnmatch


gHeadCopy = []
gTailCopy = []

def exactCopy(filepath):
	global gHeadCopy
	global gTailCopy
	f = open(filepath)
	lines = f.readlines()
	f.close()
	bHead = True
	for line in lines:
		if line.endswith('\n'):
			line = line[:-1]
		else:
			if line.endswith('\r\n'):
				line = line[:-2]
		if line.strip().startswith('[[[[[HEAD]]]]]'):
			bHead = True
			continue
		if line.strip().startswith('[[[[[TAIL]]]]]'):
			bHead = False
			continue
		if bHead:
			gHeadCopy.append(line)
		else:
			gTailCopy.append(line)


def buildCHeadOrTail(bHead):
	Num = 80
	cmt = '//'
	ret = cmt*(Num/2) + '\n'
	global gHeadCopy
	global gTailCopy
	copyinfo = gTailCopy
	if bHead:
		copyinfo = gHeadCopy
	for copy in copyinfo:
		tmp = cmt + ' ' + copy
		nLen = len(tmp)
		if nLen < Num:
			tmp = tmp + ' '*(Num-nLen-len(cmt)) + cmt + '\n'
		else:
			tmp = tmp + '\n'
		ret = ret + tmp
	ret = ret + cmt*(Num/2) + '\n'
	if bHead:
		ret = ret + '\n\n'
	else:
		ret = '\n\n' + ret
	return ret

def match(file, filepattern):
	for pattern in filepattern:
		if fnmatch(file, pattern):
			return True
	return False

def processfile(filepath):
	logging.info('processing file ' + filepath)
	copyHead = ''
	copyTail = ''
	if filepath.endswith('.h'):
		copyHead = buildCHeadOrTail(True)
		copyTail = buildCHeadOrTail(True)
	elif filepath.endswith('.hpp'):
		copyHead = buildCHeadOrTail(True)
		copyTail = buildCHeadOrTail(True)
	elif filepath.endswith('.c'):
		copyHead = buildCHeadOrTail(True)
		copyTail = buildCHeadOrTail(True)
	elif filepath.endswith('.cpp'):
		copyHead = buildCHeadOrTail(True)
		copyTail = buildCHeadOrTail(True)
	else:
		pass

	if len(copyHead) > 0 or len(copyTail) > 0:
		f = open(filepath)
		lines = f.readlines()
		f.close()

		content = copyHead
		for line in lines:
			content = content + line
		content = content + copyTail

		f = open(filepath, 'w')
		f.write(content)
		f.close()
		
def process(srcDir, filePattern):
	logging.info('processing dir ' + srcDir)
	files = os.listdir(srcDir)
	for file in files:
		tmpfile = srcDir + file
		if os.path.isfile(tmpfile):
			if match(tmpfile, filePattern):
				logging.info('change info for ' + tmpfile)
				processfile(tmpfile)
	for file in files:
		if file != '.' and file != '..' and file != '.svn' and file != '.git' and file != '.hg' and file != '.cvs':
			tmpfile = srcDir + file + os.sep
			if os.path.isdir(tmpfile):
				process(tmpfile, filePattern)

def usage():
	logging.error('Usage: ' + sys.argv[0] + ' CopyRight_File SRC_Dir File_Pattern [File_Pattern] ...')

def main():
	logging.basicConfig(level=logging.DEBUG,
			format='%(asctime)s %(levelname)-8s %(message)s',
			datefmt='%H:%M:S')

	logging.info('begin validate arguments')
	nLen = len(sys.argv)
	if nLen < 4:
		usage()
	else:
		copyFile = sys.argv[1]
		if not os.path.exists(copyFile):
			logging.error('CopyRight file ' + copyFile + ' does not exists')
			sys.exit(-1)
		
		srcDir = sys.argv[2]
		srcDir.replace('/', os.sep)
		srcDir.replace('\\', os.sep)
		if not srcDir.endswith(os.sep):
			srcDir = srcDir + os.sep
		if not os.path.exists(srcDir):
			logging.error('SRC_DIR ' + srcDir + ' does not exists')
			sys.exit(-2)
		
		filePattern = sys.argv[3:]
		if len(filePattern) == 0:
			logging.error('File_Pattern not specifify')
			sys.exits(-3)

		logging.info('read CopyRight file ' + copyFile + ' into memory')
		exactCopy(copyFile)

		process(srcDir, filePattern)

if __name__ == '__main__':
	main()


