import xmlrpclib
import os
import time

coord = xmlrpclib.ServerProxy("http://localhost:3000")
pid = os.getpid()

while(not coord.acquire(pid)):
	print "bug 1"
	time.sleep(1)

while (not coord.check(pid)):
	print "bug 2"
	time.sleep(1)

# abrir arquivo
# escrever
# fechar arquivo

print("crit in")

while(not coord.release(pid)):
	print "bug 3"
	time.sleep(1)

print("crit out")