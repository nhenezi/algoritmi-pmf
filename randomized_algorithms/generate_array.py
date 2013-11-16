import random

def generator(n):
	f = open('podaci1.txt','w');
	f.write(str(n)+"\n")
	for i in xrange(0,n):
		f.write(str(random.randint(1,pow(n,3)))+"\n")

generator(100000)
	