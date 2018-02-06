import socket
import json
import sys
import os.path
import time

LDS='liveDataSettings'

def usage():
    print('python settingsFile')

def main():

    if len(sys.argv) < 2:
        print('No file set')
        usage()
        return

    file = str(sys.argv[1]);
    print (str(file))
    if os.path.isfile(file) == True:
        with open(file,'r') as settingsFile:
            #load the settings in a json documet
            settingsJson = json.load(settingsFile)

            type = int(settingsJson[LDS]['source'])
            sensors = settingsJson[LDS]['sensors']

            print (sensors)

            for sensor in sensors:
                print (sensor)
            # "sensors":[{"id": 1, "type": 1},
            #write to file
            if type == 0:
                fileName = settingsJson[LDS]['file']
                if os.path.isfile(fileName) == True:
                    interval = settingsJson[LDS]['interval']

                    #write
                    time.sleep(interval)
            #write to TCP socket
            elif type == 1:
                 #TODO some condition
                 read = True
                 #while read:
                 tcpPort = int(settingsJson[LDS]['tcp']['port'])
                 host = str(settingsJson[LDS]['tcp']['host'])
                 print (tcpPort)
                 print (host)

                 sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                 server_address = (host, tcpPort)
                 sock.bind(server_address)
                 sock.listen(1)

                 print ('Waiting for a client..')
                 #connection, client_addr = sock.accept()

                 #print ('Client connected ', client_addr)
                 #read sensors and send json data

                 sensorData = {}
                 data = [1,2,[3,4,5]]
                 sensorData['data'] = data

                 print(json.dumps(sensorData, indent=1))

                 #sock.sendall(sensorData)

                 #connection.close()
    else:
        print('Error: Settings file not existing')

if __name__ == '__main__':
                    main()
