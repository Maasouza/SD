import xmlrpclib

coord = xmlrpclib.ServerProxy("http://localhost:3000")
print(coord.time_diff())
coord.reset()