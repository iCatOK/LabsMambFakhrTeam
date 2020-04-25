import random
import time

minrun = 32


def ins_sort(array, start, end):
    for i in range(start + 1, end + 1):
        elem = array[i]
        j = i - 1
        while j >= start and elem < array[j]:
            array[j + 1] = array[j]
            j -= 1
        array[j + 1] = elem
    return array


def merge(array, start, mid, end):
    if mid == end:
        return array
    first = array[start:mid + 1]
    last = array[mid + 1:end + 1]
    len1 = mid - start + 1
    len2 = end - mid
    ind1 = 0
    ind2 = 0
    ind = start

    while ind1 < len1 and ind2 < len2:
        if first[ind1] < last[ind2]:
            array[ind] = first[ind1]
            ind1 += 1
        else:
            array[ind] = last[ind2]
            ind2 += 1
        ind += 1

    while ind1 < len1:
        array[ind] = first[ind1]
        ind1 += 1
        ind += 1

    while ind2 < len2:
        array[ind] = last[ind2]
        ind2 += 1
        ind += 1

    return array


def tim_sort(array):
    n = len(array)

    for start in range(0, n, minrun):
        end = min(start + minrun - 1, n - 1)
        array = ins_sort(array, start, end)

    curr_size = minrun
    while curr_size < n:
        for start in range(0, n, curr_size * 2):
            mid = min(n - 1, start + curr_size - 1)
            end = min(n - 1, mid + curr_size)
            array = merge(array, start, mid, end)
        curr_size *= 2
    return array


def printArray(arr, n):
    print("First %d elements" % n)
    for i in range(0, n):
        print(arr[i], end=" ")
    print("\nLast %d elements" % n)
    for i in range(len(arr)-n, len(arr)):
        print(arr[i], end=" ")

if __name__ == "__main__":
    arr = [random.randint(1, 10) for i in range(1, 100000)]
    printArray(arr,10)

    start = time.time()
    n = len(arr)
    sortedArr = tim_sort(arr)
    print("\n\nTime: %s. After sorting: \n" % (time.time() - start))

    printArray(sortedArr, 10)
