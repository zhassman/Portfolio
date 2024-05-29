from tqdm import tqdm

def makeMask(password):
    mask = ''
    for char in password:
        if char.isdigit():
            mask += '?d'
        elif char.islower():
            mask += '?l'
        elif char.isupper():
            mask += '?u'
        elif char in " !\"#$%&'()*+,-./:;<=>?@[\]^_`{|}~":
            mask += '?s'
        else:
            mask += "?a"
    return mask

masksToCounts = {}

with open("rockyou.txt", "r", encoding="utf8", errors="ignore") as f:
    lines = f.readlines()
    for line in tqdm(lines, desc="Making masks..."):
        password = line.strip()
        mask = makeMask(password)
        masksToCounts[mask] = 1+ masksToCounts.get(mask, 0)
    print("")

sortedMasks = sorted(masksToCounts.items(), key=lambda x: x[1], reverse=True)
top10  = sortedMasks[:10]
for item in top10:
    mask, count = item
    print(f"Mask: {mask} ; Count: {count}")

with open("top10Masks.txt", "w", encoding="utf8") as f:
    for mask, count in top10:
        f.write(f"Mask: {mask} ; Count: {count}\n")
