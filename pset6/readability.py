from cs50 import get_string 
import math
import string
text = get_string("Text: ")
letters = 0
words = 1
sentences = 0
for i in text:
    if i in string.ascii_letters:
        letters += 1
    if i == " ":
        words += 1
    if i == "." or i == "?" or i == "!":
        sentences += 1


L = letters / words * 100
S = sentences / words * 100

level = round((.0588 * L) - (.296 * S) - 15.8)
if level < 1:
    print("Before Grade 1")
elif level >= 16:
    print("Grade 16+")
else:
    print("Grade " + str(level))