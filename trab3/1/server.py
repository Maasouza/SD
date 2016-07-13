
import xmlrpclib
import SocketServer
from SimpleXMLRPCServer import SimpleXMLRPCServer,SimpleXMLRPCRequestHandler
 
#ThreadingMixIn - permite que um endereço permita mais de uma conexão.
#Ele alterar o handler do objeto passado como parametro junto dele.
class MultiXMLRPCServer(SocketServer.ThreadingMixIn,SimpleXMLRPCServer):
	pass

def vec_avg(l):
	return sum(l)/len(l)

def vec_pow(a,l):
	return [pow(x,a) for x in l]

def vec_sum(l):
	return sum(l)

#Como queremos que ele forneça um servidor RPC multi-acessado passamos como parametro o handler do RPC
server =  MultiXMLRPCServer(('localhost', 3000), SimpleXMLRPCRequestHandler)

#registrando as funções no servidor
server.register_function(vec_avg,"avg")
server.register_function(vec_pow,"pow")
server.register_function(vec_sum,"sum")

print("Ready to serve")
#iniciando o servidor RPC
server.serve_forever()
