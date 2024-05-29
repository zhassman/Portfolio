import json

# Sum all of the bytes sent across all flows for a site
def sumAcrossFlows(packetsForSite):
    flowToAck = {}
    for pkt in packetsForSite:
        srcPrt = pkt['sourcePort']
        dstPrt = pkt['destPort']
        ack = pkt['ack']
        flow = (srcPrt, dstPrt)

        if flow in flowToAck:
            flowToAck[flow] = max(ack, flowToAck[flow])
        else:
            flowToAck[flow] = ack

    totalAck = sum(flowToAck.values())
    return totalAck

# Iterate through sites and assess their size
def iterateThroughSites(packetlist):

    siteNumToAck = {}
    hitSyn = False
    twentyPassed = False
    timeStart = packetlist[0]['time']
    startInd = None
    endInd = None
    siteCount = 1

    for i, pkt in enumerate(packetlist):

        if ((pkt['time'] - timeStart) > 20):
            twentyPassed = True

        if (pkt['tcp']):
            if (pkt['syn'] == 1):
                if (hitSyn):
                    if (not twentyPassed):
                        pass
                    else:
                        endInd = i 
                        siteNumToAck[siteCount] = sumAcrossFlows(packetlist[startInd : endInd])
                        twentyPassed = False
                        timeStart = pkt['time']
                        startInd = i
                        endInd = None
                        siteCount += 1
                else:
                    hitSyn = True
                    timeStart = pkt['time']
                    startInd = i

    if startInd < len(packetlist):
            siteNumToAck[siteCount] = sumAcrossFlows(packetlist[startInd :])

    return siteNumToAck


with open("simplifiedGhost.json") as f:
    packetlist = json.load(f)

siteNumToAck = iterateThroughSites(packetlist)

with open("ghostSiteNumToAck.json", "w") as out:
    json.dump(siteNumToAck, out, indent=4)
