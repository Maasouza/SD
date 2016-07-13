import xmlrpclib
import os
import signal
import time

EXEC_LIMIT = 100
pid = os.getpid()
myTurn = False

# signal handler
def wake_up(signum, frame):
	global myTurn
	myTurn = True
	return

# set handler for "wake up" signal
signal.signal(30, wake_up)

# RPC server information
coord = xmlrpclib.ServerProxy("http://localhost:3000")
coord.check_in()

for i in range(1, EXEC_LIMIT) :
	myTurn = False
	# subscribe to waiting queue
	while(not coord.acquire(pid)):
		print("ERROR")
		time.sleep(1)

	# wait for access grant
	while (not myTurn):
		signal.pause() # wait until signal is received

	#print("PASSOU!")

	# open file
	file = open("output.txt", "a")
	# write
	file.write("INPUT FROM PROCCESS \t" + str(pid) + "\t ENTRY NUMBER \t" + str(i) + "\t AT \t" + time.ctime() +"\n")
	# close file
	file.close()

	while(not coord.release(pid)):
		print "ERROR"
		time.sleep(1)

coord.check_out()