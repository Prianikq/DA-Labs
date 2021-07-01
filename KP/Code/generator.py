from random import randint
fileName = input("Input name of test file: ")
rangeVal = int(input("Input the maximum value of coordinates modulo: "))
structDems = int(input("Input demensions of struct points: "))
countStruct = int(input("Input count struct points: "))
searchDems = int(input("Input demensions of search points: "))
countSearch = int(input("Input count search points: "))
f = open(fileName, 'w')
print(structDems, countStruct, file = f)
for i in range(countStruct):
    for j in range(structDems):
        print(randint(1, rangeVal), end = ' ', file = f)
    print('', file = f)
print(searchDems, countSearch, file = f)
for i in range(countSearch):
    for j in range(searchDems):
        print(randint(1, rangeVal), end = ' ', file = f)
    print('', file = f)

