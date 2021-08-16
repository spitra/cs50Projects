# TODO
import cs50
import csv 
import sys

if len(sys.argv) < 2:
    print("Nice try, do it right")
    exit()
db = cs50.SQL("sqlite:///students.db")
reader = csv.DictReader(open(sys.argv[1], newline = ""))
for rows in reader:
    name = rows.get("name")
    first = ""
    mid = ""
    last = ""
    splitname = name.split(" ")
    if len(splitname) == 3:
        first = splitname[0]
        mid = splitname[1]
        last = splitname[2]
    else:   
        first = splitname[0]
        last = splitname[1]
    if mid == "":
        mid = None
    db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)", first, mid, last, rows.get("house"), rows.get("birth"))
    