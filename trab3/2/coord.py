from SimpleXMLRPCServer import SimpleXMLRPCServer
import xmlrpclib
import signal
import os
import time
import threading

proc_queue = []

isFirst = True
start_time = 0
end_time = 0

class AllowNext():
	def __init__(self, start = False):
		self.lock = threading.Lock()
		self.value = start
	def set_true(self):
		self.lock.acquire()
		self.value = True
		self.lock.release()
	def set_false(self):
		self.lock.acquire()
		self.value = False
		self.lock.release()
	def get_value(self):
		self.lock.acquire()
		return_value = self.value
		self.lock.release()
		return return_value

allow_next = AllowNext()

class server_thread (threading.Thread):
    def __init__(self, threadID, threadName):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.threadName = threadName
        self.lock = threading.Lock()
    def run(self):
    	global allow_next
        global proc_queue
        if (self.threadID == 0):
			server = SimpleXMLRPCServer(("localhost",3000))

			# client processes funtions
			server.register_function(acquire,"acquire")
			server.register_function(release,"release")
			server.register_function(check,"check")

			# execution time measuring functions
			server.register_function(check_in,"check_in")
			server.register_function(check_out,"check_out")
			server.register_function(get_time_diff,"time_diff")
			server.register_function(reset,"reset")

			print("Ready to serve")
			server.serve_forever()
        elif (self.threadID == 1):
        	while 1:      		
        		if (allow_next.get_value()):
        			os.kill(proc_queue[0], 30)
        			allow_next.set_false()
        else:
            print ("Invalid thread number : "),
            print (self.threadID)

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

def reset():
	global isFirst
	global start_time
	global end_time
	global proc_queue

	isFirst = True
	start_time = 0
	end_time = 0
	proc_queue = []

	print("Timer has been reset")
	return True

########################## EXECUTION PROCEDURES ##########################

# puts process in waiting queue fr critical region
def acquire(pid):
	global proc_queue
	try:
		proc_queue.append(pid)
		if ((len(proc_queue)) == 1):
			allow_next.set_true()
		return True
	except:
		return False

# releases critical region by taking process 
# away prom first position of proc_queue
def release(pid):
	global allow_next
	global proc_queue
	try:
		if(len(proc_queue) > 0):
			if (proc_queue[0] == pid):
				proc_queue.pop(0)
				if (len(proc_queue) > 0):
					# wake up next proccess
					#os.kill(proc_queue[0], 30)
					allow_next.set_true()
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

threads = []

# create threads
thread1 = server_thread(0, "server")
thread2 = server_thread(1, "manager")

################### INICIO EXECUCAO PARALELA #######################
#start threads
thread1.start()
thread2.start()

#put threads in vector
threads.append(thread1)
threads.append(thread2)

for t in threads:
    t.join()