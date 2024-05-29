import json

# Add site sizes to map
def update(sitesToNeighbors, siteNumToAck):
    siteToSiteAndSize = {}
    for i, site in enumerate(sitesToNeighbors):
        size = siteNumToAck[str(i + 1)]
        siteToSiteAndSize[site] = [site, size]

    updated = {}
    for site in sitesToNeighbors:
        newList = []
        for neighbor in sitesToNeighbors[site]:
            newList.append(siteToSiteAndSize[neighbor])
        
        updated[site] = newList

    return updated


with open('step1-sites_to_neighbors.json') as f1:
    sitesToNeighbors = json.load(f1)

with open('siteNumToAck.json') as f2:
    siteNumToAck = json.load(f2)

updated = update(sitesToNeighbors, siteNumToAck)
print(updated)

with open('updatedSitesToNeighbors.json', 'w') as file:
    json.dump(updated, file, indent=4)
