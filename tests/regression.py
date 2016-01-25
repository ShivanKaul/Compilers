import os
import glob

def run_test(file):
	cmd = "./minic < %s 2>/dev/null" % file
	print "> %s : " % file
	os.system(cmd)

print "Running tests that should return VALID..."
for file in glob.glob("tests/*.pass"):
	run_test(file)

print

print "Running tests that should return INVALID..."
for file in glob.glob("tests/*.fail"):
	run_test(file)


