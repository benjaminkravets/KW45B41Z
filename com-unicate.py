import serial
import multiprocessing
import time
import sys

ser = serial.Serial(port='COM4', baudrate=115200)

htois = lambda a : str(int(a, 16)) #hex to integer string

address_to_three_bytes = lambda address : [(address >> z) & 0xFF for z in [16,8,0]]
three_bytes_as_str = lambda bytes : ' '.join(str(num) for num in bytes)

adr_bits = lambda a : three_bytes_as_str(address_to_three_bytes(a))

class W25Q128JV:

    read_status_register = ["SR " + htois("0x5") + " 2 E", "SR " + htois("0x35") + " 2 E", "SR " + htois("0x15") + " 2 E"]

    read_data = lambda a : "SR " + htois("0x3") + " " + three_bytes_as_str(address_to_three_bytes(a)) + " 10 E"

    write_enable = "SR " + htois("0x6") + " 0 E"
    write_disable = "SR " + htois("0x4") + " 0 E"
    read_unique_id = "SR " + htois("0x4b") + " 20 E"
    read_jedec_id = "SR " + htois("0x4b") + " 8 E"
    read_manufacturer_device_id = "SR " + htois("0x90") + " 20 E"

    page_program = "SR " + htois("0x02") + " " + three_bytes_as_str(address_to_three_bytes(0xFFF)) + " " + htois("0x5555")

    

    #CS     blue    ch 1
    #DO     green   ch 3
    #WP
    #GND    black

    #VCC    red
    #RESET
    #CLK    white   ch 5
    #DI     yellow  ch 7

def send_receive():

    command_queue = [W25Q128JV.write_enable, W25Q128JV.read_status_register[0], W25Q128JV.write_disable, W25Q128JV.read_status_register[0]]; command_queue_index = 0

    while (True):

        a = 1

        
        match a:
            case 0:
                command = input()
            
            case 1:
                command = W25Q128JV.write_enable


                print(command)
                #sys.exit()
                time.sleep(1)

            case 2:

                if command_queue_index == len(command_queue): break
                command = command_queue[command_queue_index]
                command_queue_index += 1
                
                time.sleep(1)
                #continue

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


