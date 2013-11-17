import math
from numpy import matrix
import numpy

A = matrix( [[1,2,3,0],[11,12,13,0],[21,22,23,0],[0,0,0,1]])
B = matrix([[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]])

#print A*B

def mm(A,B):
	n = len(A)
	#C = numpy.zeros(shape=(n,n))
	if n == 1:
		C = A*B
		#print C
		#C = numpy.zeros(shape=(n,n))
	else:
		x = int(n/2)
		A_11 = A[0:x,0:x]
		A_12 = A[0:x,x:n]
		A_21 = A[x:n,0:x]
		A_22 = A[x:n,x:n]
		B_11 = B[0:x,0:x]
		B_12 = B[0:x,n:x]
		B_21 = B[x:n,0:x]
		B_22 = B[x:n,x:n]
		C_11 = mm(A_11,B_11) + mm(A_12,B_21)
		C_12 = mm(A_11,B_12) + mm(A_11,B_22)
		C_21 = mm(A_21,B_11) + mm(A_22,B_21)
		C_22 = mm(A_21,B_12) + mm(A_22,B_22)  
		C_1 = numpy.concatenate((C_11,C_12), axis = 1)
		C_2 = numpy.concatenate((C_21,C_22), axis = 1)
		C = numpy.concatenate((C_1,C_2), axis = 0)
	return C

print mm(A,B)

