import xmlrpclib

conn = xmlrpclib.ServerProxy("http://localhost:3000")

l=[1,2,3,4,5]
word = conn.pow(2,l)

print(word)