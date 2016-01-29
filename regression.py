import fnmatch
import os
import glob
import sys

success = '\033[92m'
fail = '\033[91m'

def run_test(file):
	cmd = "./minic < %s 2>/dev/null" % file
	print "> %s : " % file
	os.system(cmd)

def valid():
	print "Running tests that should return VALID..."
	for root, dirnames, filenames in os.walk('TEST_PROGRAMS/VALID'):
	        for filename in fnmatch.filter(filenames, '*.min'):
	            run_test(os.path.join(root, filename))
	print

def invalid():
	print "Running tests that should return INVALID..."
	for root, dirnames, filenames in os.walk('TEST_PROGRAMS/INVALID'):
	        for filename in fnmatch.filter(filenames, '*.min'):
	            run_test(os.path.join(root, filename))

if (len(sys.argv) == 1):
	valid()
	invalid()
else:
	if (sys.argv[1] == "-i"):
		invalid()
	elif (sys.argv[1] == "-v"):
		valid()
	else:
		print "Script failed, man."
		sys.exit()