import serial
import multiprocessing
import time

ser = serial.Serial(port='COM4', baudrate=115200)
ser.write(b'hi there \r\n \n')

# SR 1 2 3 P 100 SR 1 2 245 6 P 1000 SR 1 2 23 4 E

def send_receive():

    while (True):

        a = 1
        
        match a:
            case 0:
                command = input()
            
            case 1:
                command = "SR 1 2 3 10 SR 3 2 1 20 SR 1 2 3 10 E"
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


