/*
Program converts binary to decimal
*/

binary_array = list()
decimal_array = list()
N = int(input("Enter the amount of binary numbers:"))
for i in range(N):
    num = input()
    num = num.replace(',','')
    binary_array.append(num)
print("--==INTEGER ARRAY==---")
j = 0
for number in binary_array:
    j+=1
    if(j != N):
        print(str(int(number,2))+',')
    else:
        print(str(int(number,2)))
input("Press enter to exit...")
