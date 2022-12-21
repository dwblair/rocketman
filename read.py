import serial
import datetime
import time
ser=serial.Serial('/dev/ttyACM0')
filename="data.csv"

while True:
    out=ser.readline()
    dec=out.decode("utf-8")
    decs = dec.strip().split(",")
    #time=datetime.datetime.now()
    #stamp=datetime.datetime.timestamp(time)*1000
    stamp=int(time.time())
    print(stamp,decs[0],decs[1],decs[2])
    out_str=str(stamp)+","+str(decs[0])+","+str(decs[1])+","+str(decs[2]+"\n")
    f = open(filename,"a")
    f.write(out_str)
    f.close()
