from SimpleXMLRPCServer import SimpleXMLRPCServer
import xmlrpclib

def vec_avg(l):
	return sum(l)/len(l)

def vec_pow(a,l):
	return [pow(x,a) for x in l]


server = SimpleXMLRPCServer(("localhost",3000))

server.register_function(vec_avg,"avg")
server.register_function(vec_pow,"pow")

print("Ready to serve")
server.serve_forever()
