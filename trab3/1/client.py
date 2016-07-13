import xmlrpclib
import random
import threading


vecSize = 10**8

#Recebendo o numero de threads
nThreads = input("Number of Threads ")

#escolhendo a operção a ser feita
operation = input("0 - Media do vetor\n1 - Soma do vetor\n2 - Vetor ao quadrado\n")

#vetor de numeros aleatorios
numbers = [] 

#constante que determina o tamanho do array de cada thread
k = vecSize/nThreads

#Variavel que contem o retorno
response=[0 for i in range(nThreads)]


print("Populando array...")
for i in xrange(vecSize):	
	numbers.append(random.randint(1, 127));
print("Array populado.")


#Classe que implementa a thread
class RPC_thread (threading.Thread):    
    def __init__(self, threadID, name, op):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.function = op

    def run(self):
    	self.conn = xmlrpclib.ServerProxy("http://localhost:3000")
        if(self.function==0):
        	response[self.threadID] = self.conn.avg(numbers[self.threadID*k:(self.threadID+1)*k])	
        elif(self.function==1):
        	response[self.threadID] = self.conn.sum(numbers[self.threadID*k:(self.threadID+1)*k])
        elif(self.function==2):
        	response[self.threadID] = self.conn.pow(2,numbers[self.threadID*k:(self.threadID+1)*k])
        else:
        	print("Invalid function")

threads = []

print("Criando as threads")
for i in range(nThreads):
	thread =  RPC_thread(i,"Thread"+str(i),operation)
	thread.start()
	threads.append(thread)
print("Threads criadas e iniciadas.")

#aguardando as threads terminarem de executar
for t in threads:
	t.join()


conn = xmlrpclib.ServerProxy("http://localhost")
if(operation==0):
	print("Avg : ")
	print(conn.avg(response))
elif(operation==1):
	print("Sum : ")
	print(conn.sum(response))
elif(operation==2):
	print("Vector ^ 2 : ")
	print(response)

