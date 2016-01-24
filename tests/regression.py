import os
import glob
os.chdir("tests/")
for file in glob.glob("*.fail"):
	cmd = "./minic < %s 2>/dev/null" % file
	print file
	output = os.system(cmd)
	print output
	if (output):
		print "%s was supposed to fail." % file
		quit() 

for file in glob.glob("*.pass"):
	cmd = "./minic < %s 2>/dev/null" % file
	print file
	output = os.system(cmd)
	#output = (os.system(cmd) / 256) - 1
	print output
	if (output):
		print "%s was supposed to pass." % file
		quit() 

print "All pass!"
