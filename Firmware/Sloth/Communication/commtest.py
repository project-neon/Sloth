import serial
import time

ser = serial.Serial('/dev/ttyACM0', 115200)
# ser.write(6)
# ser.write(0x23)
# ser.write(0x21)
# ser.write(0x00)
# ser.write(0x00)
# ser.write(0x25)
# ser.write(0x31)

# ser.write(b'5') #Prefixo b necessario se estiver utilizando Python 3.X
while True:

    # ser.write(bytes(0x06))
    # ser.write(bytes(0x23))
    # ser.write(bytes(0x21))
    # ser.write(bytes(0x00))
    # ser.write(bytes(0x00))
    # ser.write(bytes(0x25))
    # ser.write(bytes(0x31))
    ser.write(b'\x06\x23\x21\xB4\x04\x00\x00')
    print('\nSent...')
    time.sleep(1)

    if ser.in_waiting:
        time.sleep(0.5)
        data = ""
        while ser.in_waiting:
            data = data + (ser.read(1))
        print(data)

    time.sleep(5)





