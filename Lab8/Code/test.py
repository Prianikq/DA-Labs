from random import randint
m = int(input())
n = int(input())
print(m, n)
for i in range(m):
    for j in range(n):
        print(randint(0, 50), end = ' ')
    print(randint(0, 50))
