import sys
import math

def fmcs(A,low,mid,high):
	left_suma = -sys.maxint
	suma = 0
	max_left = -1
	max_right = -1
	for i in reversed(xrange(low, mid + 1)):
		suma = suma + A[i]
		if suma > left_suma:
			left_suma = suma
			max_left = i
	suma = 0
	right_suma = -sys.maxint	
	for i in xrange(mid + 1, high + 1):
		suma = suma + A[i]
		if suma > right_suma:
			right_suma = suma
			max_right = i
	return [max_left, max_right, left_suma + right_suma]

def find_maximum_subarray(A,low,high):
	if high == low:
		return [low, high, A[low]]
	else:
		mid = int(math.ceil((low+high)/2))
		[left_low, left_high, left_sum] = find_maximum_subarray(A, low, mid)
		[right_low, right_high, right_sum] = find_maximum_subarray(A, mid + 1, high)
		[cross_low, cross_high, cross_sum] = fmcs(A, low, mid, high)
		if left_sum >= right_sum and left_sum >= cross_sum:
			return [left_low, left_high, left_sum]
		elif right_sum >= left_sum and right_sum >= cross_sum:
			return [right_low, right_high, right_sum]
		else:
			return [cross_low, cross_high, cross_sum]

A = [13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, -77, 20, 30, 40, -1, 1, 2, 3, -4]

print find_maximum_subarray(A, 0, len(A) - 1)
