hashes = []

with open('shadow', 'r') as f:
    for line in f:
        if 'crackme' in line:
            hashes.append(line.split(':')[1])

with open('step2.txt', 'w') as f1:
    for hash in hashes:
        f1.write((f'{hash}\n'))
