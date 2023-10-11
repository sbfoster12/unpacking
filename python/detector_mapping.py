import json

def block(detectorName, detectorNum, crateNum, amcSlotNum, channelNum):
    return {
        "detectorName": detectorName,
        "detectorNum": detectorNum,
        "crateNum": crateNum,
        "amcSlotNum": amcSlotNum,
        "channelNum": channelNum
    }


#detectors dictionary
detectors = {
     "lyso" : [
        block("lyso",0,0,0,0),
        block("lyso",1,0,0,1),
        block("lyso",2,0,0,2),
        block("lyso",3,0,0,3),
        block("lyso",4,0,0,4),
        block("lyso",5,0,1,0),
        block("lyso",6,0,1,1),
        block("lyso",7,0,1,2),
        block("lyso",8,0,1,3),
        block("lyso",9,0,1,4)
    ],
    "nai" : [
        block("nai",0,0,2,0),
        block("nai",1,0,2,1),
        block("nai",2,0,2,2),
        block("nai",3,0,2,3)
    ],
    "t0" : [
        block("t0",0,0,2,4)
    ],
    "hodo_x" : [
        block("hodo_x",0,0,3,0),
        block("hodo_x",1,0,3,1),
        block("hodo_x",2,0,3,2),
        block("hodo_x",3,0,3,3),
        block("hodo_x",4,0,3,4),
        block("hodo_x",5,0,4,0),
        block("hodo_x",6,0,4,1),
        block("hodo_x",7,0,4,2),
        block("hodo_x",8,0,4,3),
        block("hodo_x",9,0,4,4),
        block("hodo_x",10,0,5,0),
        block("hodo_x",11,0,5,1)
    ],
    "hodo_y" : [
        block("hodo_y",0,0,5,2),
        block("hodo_y",1,0,5,3),
        block("hodo_y",2,0,5,4),
        block("hodo_y",3,0,6,0),
        block("hodo_y",4,0,6,1),
        block("hodo_y",5,0,6,2),
        block("hodo_y",6,0,6,3),
        block("hodo_y",7,0,6,4),
        block("hodo_y",8,0,7,0),
        block("hodo_y",9,0,7,1),
        block("hodo_y",10,0,7,2),
        block("hodo_y",11,0,7,3)
    ]
}

# Create a dictionary to hold the list of detectors
detectors_dict = { "detectors": detectors }

# Write the data to a JSON file
with open("detector_mapping.json", "w") as json_file:
    json.dump(detectors_dict, json_file, indent=4)

print("JSON data written to output.json")