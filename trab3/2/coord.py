from SimpleXMLRPCServer import SimpleXMLRPCServer
import xmlrpclib

import thread
import time

proc_queue = []

# puts process in waiting queue fr critical region
def acquire(pid):
	try:
		proc_queue.append(pid)
		print(proc_queue)
		return True
	except:
		return False

# releases critical region by taking process 
# away prom first position of proc_queue
def release(pid):
	try:
		if(len(proc_queue) > 0):
			if (proc_queue[0] == pid):
				proc_queue.pop(0)
				print(proc_queue)
		return True
	except:
		return False

# let process know if it is its turn to enter critical region
######################## ATENCAO #######################
# Essa solucao esta bem ruim. Os processos filhos      #
# precisam ficar perguntando se ja chegou              #
# a vez deles                                          #
#													   #
# Precisamos implementar um algoritmo onde os          #
# processos apenas esperam que o coordenador fale      #
# com eles, nao ficar perguntando direto			   #
#													   #
########################################################
def check(pid):
	return (proc_queue[0] == pid)

# a ideia aqui era fazer uma thread para servir e outra para
# gerenciar a fila. Nao foi implementado ainda
def manage_queue():
	return False

#def serve():
server = SimpleXMLRPCServer(("localhost",3000))

server.register_function(acquire,"acquire")
server.register_function(release,"release")
server.register_function(release,"check")

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




