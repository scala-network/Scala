import requests
import math
import json
import os
import ipfsApi

ipfs_api = ipfsApi.Client("https://ipfs.infura.io", 5001)
checkpoints_filename = "checkpoints.json"
scala_node = "http://remote.four.scalaproject.io:11812/json_rpc"

headers = {
    'Content-Type': 'application/json',
}

def getInfo():
    data = {"jsonrpc":"2.0","id":"0","method":"get_info"}
    data = json.dumps(data)
    response = requests.post(scala_node, headers=headers, data=data)
    return (response.json())

def getBlocksByRange(start,end):
    data = {"jsonrpc":"2.0","id":"0","method":"get_block_headers_range","params":{"start_height":start,"end_height":end}}
    data = json.dumps(data)
    response = requests.post(scala_node, headers=headers, data=data)
    return (response.json())

def getBlock(height):
    data = {"jsonrpc":"2.0","id":"0","method":"get_block","params":{"height":height}}
    data = json.dumps(data)
    response = requests.post(scala_node, headers=headers, data=data)
    return (response.json())

splitBy = 50000
currentHeight = (getInfo()["result"]["height"])
currentPrime = currentHeight - 200
counter = 0
counterEnd = math.floor(currentPrime / splitBy) + 1;
i = 0
finJson = []

blockHeaders200 = getBlocksByRange(0, 200)["result"]["headers"]
for block in blockHeaders200:
    print(block["hash"], block["height"], block["wide_cumulative_difficulty"])
    oneJson = {"height": block["height"], "hash": block["hash"], "c_difficulty":block["wide_cumulative_difficulty"]}
    finJson.append(oneJson)

while i < counterEnd:
    start = i * splitBy;
    end = (((i + 1) * splitBy) if (i < (counterEnd - 1)) else (currentPrime - 1))
    blockHeaders = getBlocksByRange(start, end)["result"]["headers"]
    for block in blockHeaders:
        if ((block["height"] != end) and (block["height"] != 0) and (block["height"] % 1000 == 0)):
            print(block["hash"], block["height"], block["wide_cumulative_difficulty"])
            oneJson = {"height": block["height"], "hash": block["hash"], "c_difficulty":block["wide_cumulative_difficulty"]}
            finJson.append(oneJson)
    i += 1

try:
    os.remove(checkpoints_filename)
except OSError:
    pass


with open(checkpoints_filename, 'w') as outfile:
    json.dump(finJson, outfile)

print("========================================================")

resIpfs = ipfs_api.add(checkpoints_filename)
print("Checkpoints uploaded to IPFS, hash is = ", resIpfs['Hash'])