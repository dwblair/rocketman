import serial
import datetime
import time
import requests

ser=serial.Serial('/dev/ttyACM0')
filename="data.csv"


# credentials for belfast.pvos.org (for this particular sensor feed)
#public_key = "i9p7tgvmbxhg"
#private_key = "69cqt4v4hq99"

keys = [["qeaj3bt3a584","whec2jv525jv"],["834ksnvaq3hn","uas94apvata5"]]
#private_key = "iyxuuqac8gj3"

# these will stay fixed:
base_url = "http://bayou.pvos.org/data/"
#full_url = base_url+public_key

 
while True:
    
    out=ser.readline()
    dec=out.decode("utf-8")
    decs = dec.strip().split(",")
    print(decs)
    #time=datetime.datetime.now()
    #stamp=datetime.datetime.timestamp(time)*1000
    stamp=int(time.time())

    remoteID=int(decs[0])
    temp_0=decs[1]
    temp_1=decs[2]
    batt = decs[3]
    rssi = decs[4]

    out_str=str(stamp)+","+str(decs[0])+","+str(decs[1])+","+str(decs[2]+","+str(decs[3])+","+str(decs[4])+"\n")
    f = open(filename,"a")
    f.write(out_str)
    f.close()

    #print(counter, stamp,decs[0],decs[1],decs[2],decs[3])
   
    try:
        #post to bayou

        public_key = keys[remoteID][0]
        private_key = keys[remoteID][1]

        full_url = base_url+public_key

        print(public_key,private_key,full_url)

        myobj = {"private_key":private_key, "node_id":0,"temperature_c":temp_0,"battery_volts":batt,"rssi":rssi}

        x = requests.post(full_url, data = myobj)
        print(myobj) 
        print(x.text)

        time.sleep(1)

        #post node_1
        myobj = {"private_key":private_key, "node_id":1,"temperature_c":temp_1,"battery_volts":batt,"rssi":rssi}

        x = requests.post(full_url, data = myobj)
        print(myobj)
        print(x.text)

    except:
        print("an exception occurred when posting")

        