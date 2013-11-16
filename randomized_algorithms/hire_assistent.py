def hire(h):
	return h+1

def hire_assistent():
	best = 0
	h = 0
	A = []	
	n = int(input())
	for i in xrange(0,n):
		A.append( int(input()))
	for i in xrange(0,n):
		result = A[i];
		if result > best:
			h = hire(h);
			best = result
	return h

print hire_assistent()