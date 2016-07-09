import xmlrpclib
import os
import time

EXEC_LIMIT = 1000

coord = xmlrpclib.ServerProxy("http://localhost:3000")
pid = os.getpid()

for i in range(1, EXEC_LIMIT) :
	# subscribe to waiting queue
	while(not coord.acquire(pid)):
		time.sleep(1)

	# wait for access grant
	while (not coord.check(pid)):
		time.sleep(1)

	# open file
	file = open("output.txt", "a")
	# write
	file.write("INPUT FROM PROCCESS \t" + str(pid) + "\t ENTRY #" + str(i) + "\n")
	# close file
	file.close()

	while(not coord.release(pid)):
		print "bug 3"
		time.sleep(1)