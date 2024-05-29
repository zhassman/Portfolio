import json
import math

def calculateProbability(password, markov):
    if password == "":
        return 0
    
    logSum = 0
    passwordLen = len(password)

    firstChar = password[0]
    if not markov['START'].get(firstChar):
        return 0
    else:
        logSum += math.log(markov['START'][firstChar]['probability'])

    for i in range(1, passwordLen):
        char = password[i - 1]
        nextChar = password[i]
        if not markov[char].get(nextChar):
            return 0
        else:
            logSum += math.log(markov[char][nextChar]['probability'])

    lastChar = password[-1]
    if not markov[lastChar].get('END'):
        return 0
    else:
        logSum += math.log(markov[lastChar]['END']['probability'])

    return math.exp(logSum)


with open('markov.json', 'r', encoding='utf8', errors="ignore") as f:
    markov = json.load(f)

with open('markov-input.txt', 'r', encoding="utf8", errors="ignore") as f1:
    lines = f1.readlines()

with open('markov-output.txt', 'w', encoding='utf8') as f2:
    for line in lines:
        password = line.strip()
        probability = calculateProbability(password, markov)
        f2.write(f"{password:30}\t{probability:.30f}\n")
