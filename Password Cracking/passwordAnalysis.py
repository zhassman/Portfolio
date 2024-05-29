import random

def getLengthFrequencies(lines):
    lengths = {}
    for line in lines:
        currentLength = len(line)
        lengths[currentLength] = 1 + lengths.get(currentLength, 0)

    sortedLengths = sorted(lengths.items(), key=lambda x: x[1], reverse=True)
    return sortedLengths


def getPasswordFrequencies(lines):
    passwords = {}
    for line in lines:
        passwords[line] = 1 + passwords.get(line, 0)

    sortedPasswords = sorted(passwords.items(), key=lambda x: x[1], reverse=True)
    return sortedPasswords


def getCountAtLeastX(x, sortedLengths):
    count = 0
    for item in sortedLengths: 
        len, freq = item
        if (len >= x):
            count += freq

    return count


def getTenRandomUnique(passwordFrequencies):
    appearOnce = []
    for pair in passwordFrequencies:
        password, freq = pair
        if freq == 1:
            appearOnce.append(password)
        
    tenUnique = []
    appearOnceCt = len(appearOnce)
    while len(tenUnique) < 10:
        randomInt = random.randint(0, appearOnceCt - 1)
        password = appearOnce[randomInt]
        if password not in tenUnique:
            tenUnique.append(password)
    
    return tenUnique


#Driver code
with open("rockyou.txt", "r", encoding="utf8", errors="ignore") as f:
    lines = [line.strip() for line in f]

totalPasswordCount = len(lines)
sortedLengths  = getLengthFrequencies(lines)
passwordFrequencies = getPasswordFrequencies(lines)

# Analysis
print(sortedLengths[0])
print("")

twelvePlusCount = getCountAtLeastX(12, sortedLengths)
print(twelvePlusCount)
print(totalPasswordCount)
print((twelvePlusCount / totalPasswordCount) * 100)
print("")

sixteenPlusCount = getCountAtLeastX(16, sortedLengths)
print(sixteenPlusCount)
print(totalPasswordCount)
print((sixteenPlusCount / totalPasswordCount) * 100)
print("")

tenRandomUnique = getTenRandomUnique(passwordFrequencies)
for password in tenRandomUnique:
    print(password)
print("")

#Make top password file
with open('top.txt', 'w', encoding="utf8", errors="ignore") as f1:
    for pair in passwordFrequencies:
        password, freq = pair
        f1.write(f"{password}\n")
    
#Make top 1000 password file
with open('top1000.txt', 'w', encoding="utf8", errors="ignore") as f2:
    for i in range(1000):
        password, freq = passwordFrequencies[i]
        f2.write(f"{password}\n")
