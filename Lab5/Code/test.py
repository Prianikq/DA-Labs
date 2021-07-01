from random import randint
strLen = int(input())
word = ""
for i in range(strLen):
    symbol = chr(ord('a') + randint(0, 25))
    word = word + symbol
print(word)
for i in range(strLen):
    print(word[:(i+1)])


    
