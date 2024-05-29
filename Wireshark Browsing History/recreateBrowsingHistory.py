import json


# Find a list of all paths given some percent difference
def solveRecursively(mySites, ghostSites, currentGhostSite, position, path, maxPercent, depth):
    if position > depth:
        return [path]
    
    paths = []
    currentGhostSize = ghostSites[str(position)]
    currentNeighbors = currentNeighbors = mySites[currentGhostSite]

    for site, size in currentNeighbors:
        diff = abs(100 * (currentGhostSize - size) / currentGhostSize)
        if diff <= maxPercent:
            possiblePath = path + [site]
            paths.extend(solveRecursively(mySites, ghostSites, site, position + 1, possiblePath, maxPercent, depth))

    return paths


# Find percent accuracy for which there is only one path
def getMinPercent(mySites, ghostSites, startSite, startPos, depth, startPercent):
    minPercent = startPercent
    minPathCount = len(solveRecursively(mySites, ghostSites, startSite, startPos, [startSite], startPercent, depth))
    for i in range(startPercent - 1, 0, -1):
        currentNumPaths = len(solveRecursively(mySites, ghostSites, startSite, startPos, [startSite], i, depth))
        if ((currentNumPaths < minPathCount) and currentNumPaths != 0):
            minPercent = i
        
    return minPercent


with open("updatedSitesToNeighbors.json") as f2:
    mySites = json.load(f2)

with open("ghostSiteNumToAck.json") as f3:
    ghostSites = json.load(f3)

minP = getMinPercent(mySites, ghostSites, "http://blase.courses/5235101353139427677.html", 3, 22, 25)
start = "http://blase.courses/5235101353139427677.html"
path = solveRecursively(mySites, ghostSites, start, 3, [start], minP, 22)
for site in path[0]:
    print(site)
