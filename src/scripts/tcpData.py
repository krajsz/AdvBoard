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

            interval = settingsJson[LDS]['interval']
            type = int(settingsJson[LDS]['type'])

            #write to file
            if type == 0:
                fileName = settingsJson[LDS]['file']

            #write to TCP socket
            elif type == 1:
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

                    connection.close()
    else:
        print('Error: Settings file not existing')

if __name__ == '__main__':
                    main()
