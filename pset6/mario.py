from cs50 import get_int
n = 0
while(n <= 0 or n > 8):
    n = get_int("Height: ")
    
    
for i in range(n):
    print(" " * (n - (i +1)), end = "")
    print("#" * (i+1), end ="")
    print("  ", end = "")
    print("#" * (i+1))
        
#    print("#", end="")
#print("")
