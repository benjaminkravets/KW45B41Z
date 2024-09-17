import serial
import multiprocessing
import time
import sys

ser = serial.Serial(port='COM4', baudrate=115200)

htois = lambda a : str(int(a, 16))

class W25Q128JV:
    read_status_register = ["SR " + htois("0x5") + " 64 E", "SR " + htois("0x35") + " 64 E", "SR " + htois("0x15") + " 64 E"]
    read_data = "SR " + htois("0x3") + " 20 E"
    write_enable = "SR " + htois("0x6") + " 0 E"
    read_unique_id = "SR " + htois("0x4b") + " 20 E"
    read_jedec_id = "SR " + htois("0x4b") + " 8 E"
    read_manufacturer_device_id = "SR " + htois("0x90") + " 20 E"

    write_enable_then_read_status_register = "SR " + htois("0x6") + " 0 " + read_status_register[0]
    write_disable_then_read_status_register = "SR " + htois("0x4") + " 0 " + read_status_register[0]

    

    #CS     blue    ch 1
    #DO     green   ch 3
    #WP
    #GND    black

    #VCC    red
    #RESET
    #CLK    white   ch 5
    #DI     yellow  ch 7

def send_receive():

    while (True):

        a = 1
        
        match a:
            case 0:
                command = input()
            
            case 1:
                command = "SR 1 2 3 4 5 SR 5 4 3 2 1 SR 1 1 2 3 4 5 E"
                #command = "SR " + str(int("5",16)) + " 5 E"
                #command = W25Q128JV.read_status_register[1]
                command = W25Q128JV.write_disable_then_read_status_register
                #print(command)
                #sys.exit()



                print(command)
                time.sleep(1)

        ser.write(bytearray(" " + command + " " + "\r\n", 'ascii'))

        try:
            start = time.time()
            while (time.time() - start < .5):
                #print(time.time() - start)

                if (ser.in_waiting > 0):
                    data_str = ser.read().decode('ascii')
                    print(data_str, end='') 

        except:
            print("exit")

if __name__ == "__main__":
    send_receive()


