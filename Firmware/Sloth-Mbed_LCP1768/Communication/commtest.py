import serial
import time

ser = serial.Serial('/dev/ttyACM0', 115200)

data = [
    # b'\x06\x23\x21\xB7\x04\x00\x00', # set kp 0.1204
    # b'\x06\x23\x22\xB5\x04\x00\x00', # set ki 0.1205
    # b'\x06\x23\x23\xB6\x04\x00\x00', # set kd 0.1206
    # b'\x02\x21\x21', #inc kp
    # b'\x02\x21\x22', #inc ki
    # b'\x02\x21\x23', #inc kd
    # b'\x02\x22\x21',  # dec kp
    # b'\x02\x22\x22',  # dec ki
    # b'\x02\x22\x23',  # dec kd
    b'\x01\x25', # start
    # b'\x01\x26', # stop
    b'\x01\x27', # save
]

for cmd in data:
    ser.write(cmd)
    print('Sending cmd: ' + cmd)
    time.sleep(2)
    rsp = ""
    while ser.in_waiting:
        rsp = rsp + (ser.read(1))
    print(rsp)



while True:

    # ser.write(b'\x06\x23\x21\xB4\x04\x00\x00') # set kp 0.1204
    time.sleep(1)

    if ser.in_waiting:
        time.sleep(0.5)
        data = ""
        while ser.in_waiting:
            data = data + (ser.read(1))
        print(data)

    # time.sleep(5)





