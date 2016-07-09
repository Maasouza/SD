import xmlrpclib

conn = xmlrpclib.ServerProxy("http://localhost:3000")

l=[1,2,3,4,5]
print("l = "),
print(l)

l_2 = conn.pow(2,l)
print("l^2 = "),
print(l_2)

avg = conn.avg(l)
print("avg = "),
print(avg)
