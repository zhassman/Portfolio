from tqdm import tqdm
import json

markov = {}
markov['START'] = {}

with open("rockyou.txt", "r", encoding="utf8", errors="ignore") as f:
    lines = f.readlines()
    for line in tqdm(lines, desc="Iterating through Markov"):
        clean = line.strip()
        if clean == "":
            continue
        cleanLen = len(clean)
        firstChar = clean[0]
        markov['START'][firstChar] = 1 + markov['START'].get(firstChar, 0)
        for i, char in enumerate(clean):

            if not markov.get(char):
                markov[char] = {}

            if i == cleanLen - 1:
                markov[char]['END'] = 1 + markov[char].get('END', 0)
            else:
                nextChar = clean[i + 1]
                markov[char][nextChar] = 1 + markov[char].get(nextChar, 0)


for char, nextChars in markov.items():
    total = sum(nextChars.values())
    for nextChar, count in nextChars.items():
        markov[char][nextChar] = {'count': count, 'probability': count / total}

with open('markov.json', 'w', encoding='utf8') as f1:
    json.dump(markov, f1, ensure_ascii=False, indent=4)
