from cs50 import get_int

card = get_int("Number: ")

i = 1

c = card 
x = 0

while ( c > 0):
    if (i % 2 == 0):
        d = c % 10 *2
        
        if (d > 9):
            x+= (1+ (d %10))
        else:
            x+=d
    i +=1 
    c = int  (c / 10)
    
c = card
i = 0

while c > 0:
    if (i % 2 == 0):
        x += (c % 10)
    c = int ( c / 10)
    i += 1
type = int( card / 1000000000000)
if (card < 1000000000000 or card > 9999999999999999):
    print("INVALID")
elif ((x % 10) != 0):
    print("INVALID :)")
elif type == 4:
    print("VISA")
elif int(type / 1000) == 4:
    print("VISA")
elif (int(type / 100) > 50) and (int(type / 100) < 56):
    print("MASTERCARD")
elif (int (type / 10) == 34) or int(type / 10) == 37:
    print("AMEX")
else:
    print("INVALID :(")
    
    
    