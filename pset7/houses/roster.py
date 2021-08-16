# TODO
import cs50
import sys

if len(sys.argv) < 2:
    print("Nice try, do it right")
    exit()
db = cs50.SQL("sqlite:///students.db")

diction = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", sys.argv[1])

for rows in diction:
    if rows.get("middle") != None:
        print(rows.get("first") + " " + rows.get("middle") + " " + rows.get("last") + ", born " + str(rows.get("birth")) )
    else:
        print(rows.get("first") + " " + rows.get("last") + ", born " + str(rows.get("birth")) )
