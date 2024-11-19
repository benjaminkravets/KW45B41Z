import serial
import multiprocessing
import time
import sys

ser = serial.Serial(port='COM4', baudrate=115200)

def htois(a):
    """
    Hex to integer string
    a - Hex string
    """
    return str(int(a,16))

def address_to_three_bytes(address):
    return [(address >> z) & 0xFF for z in [16,8,0]]

def three_bytes_as_str(bytes):
    return ' '.join(str(num) for num in bytes)

def addr_bits(a):
    return three_bytes_as_str(address_to_three_bytes(a))

class W25Q128JV:

    #16777216 bytes,
    #134217728 bits

    #65536 pages (256 bytes each) (programmable), binary address should end in 8 0s
    #4096 sectors (4KB each) (errasable), binary address should end in 12 0s
    #512 sectors (32 KB) (errasable), binary address should end in 15 0s
    

    def read_page(a, b): 
        """
        Read b bytes starting at a
        a - hex address
        b - decimal # to read
        """
        return "SR " + htois("0x3") + " " + addr_bits(a) + " " + str(b)
    
    def erase_sector(a):
        """
        Erase 4KB sector at a
        a - hex address (should end in 12 0s)
        """
        return "SR " + htois("0x20") + " " + addr_bits(a) + " 0"
    

    def program_page(a, b):
        """
        Program page at a with bytes in b
        a - hex address (should end in 8 0s)
        b - string of bytes to write
        """

        return "SR " + htois("0x02") + " " + addr_bits(a) + " " + b + " 0"


    write_enable = "SR " + htois("0x6") + " 0"
    write_disable = "SR " + htois("0x4") + " 0"
    read_unique_id = "SR " + htois("0x4b") + " 13"
    read_jedec_id = "SR " + htois("0x4b") + " 8"
    read_manufacturer_device_id = "SR " + htois("0x90") + " 20"

    pause_and_end = " P 1000 "

    read_status_register = ["SR " + htois("0x5") + " 5", "SR " + htois("0x35") + " 5", "SR " + htois("0x15") + " 5"]


    

    #CS     blue    ch 1
    #DO     green   ch 3
    #WP
    #GND    black

    #VCC    red
    #RESET
    #CLK    white   ch 5
    #DI     yellow  ch 7

def send_receive():
    command_queue_index = 0


    #write to four sequential pages, then read them, then erase the sector containing all four
    # command_queue = [W25Q128JV.write_enable, W25Q128JV.program_page(0x300000, "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255"),
    #                  W25Q128JV.write_enable, W25Q128JV.program_page(0x300100, "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255"),
    #                  W25Q128JV.write_enable, W25Q128JV.program_page(0x300200, "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255"),
    #                  W25Q128JV.write_enable, W25Q128JV.program_page(0x300300, "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255")]
    
    # command_queue = [W25Q128JV.read_page(0x300000, 255),
    #                  W25Q128JV.read_page(0x300100, 255),
    #                  W25Q128JV.read_page(0x300200, 255),
    #                  W25Q128JV.read_page(0x300300, 255),
    #                  W25Q128JV.read_page(0x300400, 255),]

    #command_queue = [W25Q128JV.write_enable, W25Q128JV.erase_sector(0x300000)]



    while (True):

        a = 1 #0 loops, 1 executes queue

        match a:

            case 0:
                command = W25Q128JV.read_page(0x300000, 255)


                print(command)
                #sys.exit()
                time.sleep(2)

            case 1:

                if command_queue_index == len(command_queue): break
                command = command_queue[command_queue_index]
                command_queue_index += 1
                
                print(command, "sent")
                time.sleep(1)
                #continue

        if 0:
            continue

        ser.write(bytearray(" " + command + " E " + "\r\n", 'ascii'))



        try:
            start = time.time()
            while (time.time() - start < .5):

                if (ser.in_waiting > 0):
                    data_str = ser.read().decode('ascii')
                    print(data_str, end='') 
        

        except:
            print("exit")



if __name__ == "__main__":
    send_receive()


