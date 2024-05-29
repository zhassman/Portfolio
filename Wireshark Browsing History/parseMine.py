import json


# Isolate the packets for a specific site
def getPacketsForSpecificSite(siteNumber, packetlist):

    start = None
    stop = None

    for i, pkt in enumerate(packetlist):
        if (not pkt['tcp']):
            currentNum = int(pkt['queryName'].split("_____id_")[1].split("____")[0])
            if currentNum == siteNumber:
                start = i + 1
            elif currentNum == siteNumber + 1:
                stop = i
                break

    return packetlist[start : stop]
    

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
    for i in range(1, 752):
        packetsForSite = getPacketsForSpecificSite(i, packetlist)
        totalAck = sumAcrossFlows(packetsForSite)
        siteNumToAck[i] = totalAck

    return siteNumToAck

with open("simplifiedMyCapture751.json") as f:
    packetlist = json.load(f)

siteNumToAck = iterateThroughSites(packetlist)

with open("siteNumToAck.json", "w") as out:
    json.dump(siteNumToAck, out, indent=4)
