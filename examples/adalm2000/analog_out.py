# https://github.com/analogdevicesinc/libm2k/blob/master/bindings/python/examples/analog.py

import libm2k
import time
import numpy as np

ctx = libm2k.m2kOpen()
if ctx is None:
	print("Connection Error: No ADALM2000 device available/connected to your PC.")
	exit(1)


aout = ctx.getAnalogOut()
aout.reset()
ctx.calibrateDAC()

aout.setSampleRate(0, 10000*1024)
aout.setSampleRate(1, 10000*1024)
aout.enableChannel(0, True)
aout.enableChannel(1, True)
x=np.linspace(-np.pi,np.pi,1024)
buffer1 = np.linspace(-2.0,2.00,1024)
buffer2 = np.sin(x)
buffer = [buffer1, buffer2]
aout.setCyclic(True)
aout.push(buffer)

time.sleep(1.0)
libm2k.contextClose(ctx)
