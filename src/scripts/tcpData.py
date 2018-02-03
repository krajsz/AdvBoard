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

            sourceType = int(settingsJson[LDS]['type'])
            interval = settingsJson[LDS]['interval']

            #file
            if sourceType == 0:
                dataFile = settingsJson[LDS]['file']
                if os.path.isfile(dataFile) == True:
                    #TODO some condition
                    while True:

                        time.sleep(interval)

                        #read sensors and send json data
            #tcp
            elif sourceType == 1:

                #TODO some condition
                while True:
                    tcpPort = int(settingsJson[LDS]['tcp']['port'])
                    host = str(settingsJson[LDS]['tcp']['host'])
                    print (tcpPort)
                    print (host)

                    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    server_address = (host, tcpPort)
                    sock.bind(server_address)
                    sock.listen(1)

                    connection, client_addr = sock.accept()

                    #read sensors and send json data



                    #sock.sendall(sensorData)

                    sock.close()
                    time.sleep(interval)
    else:
        print('Error: File not existing')

if __name__ == '__main__':
                    main()
