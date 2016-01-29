import fnmatch
import os
import glob
# Usage: from previous directory, simply do `python extra-tests/regression.py`

success = '\033[92m'
fail = '\033[91m'

def run_test(file, status):
	cmd = "./minic < %s 2>/dev/null" % file
	print "> %s : " % file
	os.system(cmd)

print "Running tests that should return VALID..."
for root, dirnames, filenames in os.walk('TEST_PROGRAMS/VALID'):
        for filename in fnmatch.filter(filenames, '*.min'):
            run_test(os.path.join(root, filename), success)
print

print "Running tests that should return INVALID..."
for root, dirnames, filenames in os.walk('TEST_PROGRAMS/INVALID'):
        for filename in fnmatch.filter(filenames, '*.min'):
            run_test(os.path.join(root, filename), fail)
