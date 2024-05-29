import requests
from lxml import html
import json


# Identify a given site's neighbors
def getNeighbors(site):
    r = requests.get(site, timeout=10)
    root = html.fromstring(r.content)
    linksToNeighbors = root.xpath('//a/@href')
    return linksToNeighbors


# A bfs to find all sites and their neighbors (22 layers deep)
def bfs(start):
    sitesToNeighbors = {}
    toVisit = []
    toVisit.append((start, 1))

    while (len(toVisit) != 0):
        
        currentSite, currentDepth = toVisit.pop(0)

        if sitesToNeighbors.get(currentSite):
            continue

        if (currentDepth > 22):
            break

        nextDepth = currentDepth + 1
        print(nextDepth)

        linksToNeighbors = getNeighbors(currentSite)
        neighborUrls = []
        for link in linksToNeighbors:
            if link.startswith('http://') or link.startswith('https://'):
                url  = link
            else:
                url = start + "/" + link
            neighborUrls.append(url)
            toVisit.append((url, nextDepth))

        sitesToNeighbors[currentSite] = neighborUrls

    return sitesToNeighbors

sitesToNeighbors = bfs("https://blase.courses")

sitesToNeighborsJson = json.dumps(sitesToNeighbors, indent=4)
with open('step1-sitesToNeighbors.json', 'w') as json_file:
    json.dump(sitesToNeighbors, json_file, indent=4)
