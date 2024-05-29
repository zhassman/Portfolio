import json

# Extract only potentially useful information
def simplifyJson(packetlist):
    simplified = []
    for pkt in packetlist:
        simplifiedJson = {}
        if (pkt['_source']['layers'].get('tcp', None)):
            simplifiedJson["tcp"] = True
            simplifiedJson["sourcePort"] = pkt['_source']['layers']['tcp']['tcp.srcport']
            simplifiedJson["destPort"] =  pkt['_source']['layers']['tcp']['tcp.dstport']
            simplifiedJson["ack"] = int(pkt['_source']['layers']['tcp']['tcp.ack'])
            simplifiedJson["reset"] = int(pkt['_source']['layers']['tcp']['tcp.flags_tree']['tcp.flags.reset'])
            simplifiedJson["syn"] = int(pkt['_source']['layers']['tcp']['tcp.flags_tree']['tcp.flags.syn'])
            simplifiedJson["fin"] = int(pkt['_source']['layers']['tcp']['tcp.flags_tree']['tcp.flags.fin'])            
        else:
            simplifiedJson["tcp"] = False
            simplifiedJson["sourcePort"] = None
            simplifiedJson["destPort"] = None
            simplifiedJson["ack"] = None
            simplifiedJson["reset"] = None
            simplifiedJson["syn"] = None
            simplifiedJson["fin"] = None   

        if (pkt['_source']['layers'].get('dns', None)):
            qryName = next(iter(pkt['_source']['layers']['dns']['Queries']))
            simplifiedJson['queryName'] = qryName
        else:
            simplifiedJson['queryName'] = None
        
        simplifiedJson['time'] = float(pkt['_source']['layers']['frame']['frame.time_relative'])
        
        simplified.append(simplifiedJson)

    return simplified


with open("myCapture751.json") as f1:
    myPacketlist = json.load(f1)
mySimplified = simplifyJson(myPacketlist)
with open("simplifiedMyCapture751.json", "w") as out:
    json.dump(mySimplified, out, indent=4)


with open("ghostFull.json") as f2:
    myPacketlist = json.load(f2)
mySimplified = simplifyJson(myPacketlist)
with open("simplifiedGhost.json", "w") as out:
    json.dump(mySimplified, out, indent=4)
