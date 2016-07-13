from SimpleXMLRPCServer import SimpleXMLRPCServer
import xmlrpclib
import signal
import os

#import thread
import time

proc_queue = []

isFirst = True
start_time = 0
end_time = 0

########################## TIME MEASURING PROCEDURES ##########################

# check first proccess arrival time
def check_in():
	global isFirst
	global start_time
	if(isFirst):
		isFirst = False
		start_time = time.time()
	return True

# let server know process is done
def check_out():
	global end_time
	end_time = time.time()
	return True

# shows current execution time
def get_time_diff():
	global start_time
	global end_time
	return (end_time - start_time)

def reset_timer():
	global isFirst
	global start_time
	global end_time

	print(start_time)
	print(end_time)

	isFirst = True
	start_time = 0
	end_time = 0

	print("Timer has been reset")
	return True

########################## EXECUTION PROCEDURES ##########################

# puts process in waiting queue fr critical region
def acquire(pid):
	global proc_queue
	try:
		proc_queue.append(pid)
		if ((len(proc_queue)) == 1):
			print("no if")
			os.kill(pid, 30)
		return True
	except:
		return False

# releases critical region by taking process 
# away prom first position of proc_queue
def release(pid):
	global proc_queue
	try:
		if(len(proc_queue) > 0):
			if (proc_queue[0] == pid):
				proc_queue.pop(0)
				if (len(proc_queue) > 0):
					# wake up next proccess
					os.kill(proc_queue[0], 30)
		return True
	except:
		return False

# let process know if it is its turn to enter critical region
def check(pid):
	return (proc_queue[0] == pid)

# a ideia aqui era fazer uma thread para servir e outra para
# gerenciar a fila. Nao foi implementado ainda
def manage_queue():
	return False


########################## SERVER INITIALIZATION ##########################

server = SimpleXMLRPCServer(("localhost",3000))

# client processes funtions
server.register_function(acquire,"acquire")
server.register_function(release,"release")
server.register_function(check,"check")

# execution time measuring functions
server.register_function(check_in,"check_in")
server.register_function(check_out,"check_out")
server.register_function(get_time_diff,"time_diff")
server.register_function(reset_timer,"reset")

print("Ready to serve")
server.serve_forever()
#return


# try:
# 	thread.start_new_thread( serve, ())
# 	thread.start_new_thread( manage_queue, ())
# except:
# 	print("UNABLE TO START THREADS")

# while 1:
# 	pass




