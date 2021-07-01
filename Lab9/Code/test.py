from random import randint
n = int(input())
print(n, (n-1)*n//2) 
for i in range(1, n+1):
    for j in range(i+1, n+1):
        print(i, j, randint(1, 1000000000))
        
