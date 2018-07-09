#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
from time import sleep

def main():
    print ('Started')
    print (sys.argv)

    dataFile = open("data.txt", "w")
    dataFile.write('aaaaa\n')
    if len(sys.argv) > 1:
        for i in range(len(sys.argv)):
            dataFile.write(sys.argv[i])
    else:
        dataFile.write(sys.argv[0])
    ii = 0;
    while ii < 10:
        print('Data')
        sys.stdout.flush()
        ii = ii+1
        sleep(1)

if __name__ == '__main__':
                    main()

