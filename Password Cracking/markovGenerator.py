import json
import random

def generate(markov):
    password = ''
    char = 'START'
    while True:
        nextOptions = markov[char]
        nextChars = list(nextOptions.keys())
        nextCharProbs = [nextOptions[char]['probability'] for char in nextChars]
        
        next = random.choices(nextChars, nextCharProbs, k=1)[0]

        if next == 'END':
            break
        else:
            password += next
            char = next

    return password

with open('markov.json', 'r', encoding='utf8', errors="ignore") as f:
    markov = json.load(f)

with open('markov-generate.txt', 'w', encoding='utf8') as f1:
    for _ in range(1000):
        password = generate(markov)
        f1.write(f'{password}\n')
