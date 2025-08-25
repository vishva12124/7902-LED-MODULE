from machine import UART, Pin
import utime

test_uart = UART(0, baudrate=4800, tx=Pin(16), rx=Pin(17))
send_interrupt = machine.Pin(2, machine.Pin.OUT, value = 0)

while (True):
    i = 0
    y = 0
    userInput = str(input()).split(',')
    for x in userInput:
        print(i)
        i += 1
    newList = [0]*i
    print(userInput)
    for x in userInput:
        print(x + "aaa")
        newList[y] = int(x)
        y += 1
    print(newList)    
    byte_array = bytearray(newList)
    test_uart.write(byte_array)
    send_interrupt.value(1)
    utime.sleep_ms(1)
    send_interrupt.value(0)
    test_uart.flush()
    print("flushed")
    
