import serial
import multiprocessing
import time

ser = serial.Serial(port='COM4', baudrate=115200)
ser.write(b'hi there \r\n \n')

def send_receive():

    while (True):

        command = input()

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


