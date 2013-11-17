from math import floor

def parent(heap, i):
  '''Retrieves parent for element at index i from heap'''
  return int(floor(i/2))

def left(heap, i):
  '''Retrieves left child from heap for element at index i'''
  return 2 * i + 1

def right(heap, i):
  '''Retrieves righ child from heap for element at index i'''
  return 2 * i + 2

def max_heapify(arr, i, limit=None):
  '''Converts subtree starting at index i to heap.
  It is assumed that both left and right subtrees of i are heaps. '''
  if limit == None:
    limit = len(arr)

  l = left(arr, i)
  r = right(arr, i)
  if l < limit and arr[l] > arr[i]:
    largest = l
  else:
    largest = i
  if r < limit and arr[r] > arr[largest]:
    largest = r
  if largest != i:
    arr[i], arr[largest] = arr[largest], arr[i]
    max_heapify(arr, largest, limit)


def max_heap(arr):
  '''Converts array to max heapsort'''
  for i in reversed(xrange(len(arr)/2)):
    max_heapify(arr, i)

def heapsort(arr):
  '''HEAPSORT MAGIC!'''
  max_heap(arr)
  left = len(arr)
  for i in reversed(xrange(len(arr))):
    arr[0], arr[i] = arr[i], arr[0]
    left -= 1
    max_heapify(arr, 0, left)


  return arr
    
if __name__ == '__main__':
  print heapsort([2, 3, 4, 3, 8, 4, 2, 4, 7, -2, 6])
