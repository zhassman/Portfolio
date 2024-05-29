# example: "comparePots.py first.potfile second.potfile"
import sys

if len(sys.argv) !=3:
    print("Incorrect number of arguemnts.")
    exit()

potfile1 = sys.argv[1]
potfile2 = sys.argv[2]

with open(potfile1) as p1:
    data1 = p1.readlines()

with open(potfile2) as p2:
    data2 = p2.readlines()

set1 = set()
set2 = set()

for line in data1:
    if ':' in line:
        set1.add(line.strip().split(':')[1])

for line in data2:
    if ':' in line:
        set2.add(line.strip().split(':')[1])

count = 0
for password in set2:
    if password not in set1:
        print(password)
        count +=1

print('\n'+str(count))
