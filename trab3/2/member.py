import xmlrpclib
import os
import signal
import time

EXEC_LIMIT = 100
pid = os.getpid()

# signal handler
def wake_up(signum, frame):
	return 0

# set handler for "wake up" signal
signal.signal(30, wake_up)

# RPC server information
coord = xmlrpclib.ServerProxy("http://localhost:3000")
coord.check_in()

for i in range(1, EXEC_LIMIT) :
	# subscribe to waiting queue
	while(not coord.acquire(pid)):
		print("ERROR")
		time.sleep(1)

	# wait for access grant
	#while (not coord.check(pid)):
	signal.pause() # wait until signal is received

	print("PASSOU!")

	# open file
	file = open("output.txt", "a")
	# write
	file.write("INPUT FROM PROCCESS \t" + str(pid) + "\t ENTRY NUMBER " + str(i) + "AT \t" + time.ctime() +"\n")
	# close file
	file.close()

	while(not coord.release(pid)):
		print "ERROR"
		time.sleep(1)

coord.check_out()