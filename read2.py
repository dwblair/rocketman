import serial
import datetime
import time
ser=serial.Serial('/dev/ttyUSB0',115200)
filename="data.csv"

counter = 0
counter_write = 40 

writing = 0

while True:
    out=ser.readline()
    dec=out.decode("utf-8")
    decs = dec.strip().split(",")
    #print(decs)
    #time=datetime.datetime.now()
    #stamp=datetime.datetime.timestamp(time)*1000
    stamp=float(time.time())
    #print(counter, stamp,decs[0],decs[1],decs[2],decs[3])
    out_str=str(stamp)+","+str(decs[0])+","+str(decs[1])+"\n"
    f = open(filename,"a")
    f.write(out_str)
    f.close()
    counter = counter + 1
    if (counter > counter_write):
        print(writing)
        writing=writing+1
        counter = 0

