# Set an Environment Variable so Adafruit Blinka knows we're using the MCP2221
import os
os.environ["BLINKA_MCP2221"] = "1"
import time
import board
import busio
from adafruit_lsm6ds.lsm6dsox import LSM6DSOX

i2c = busio.I2C(board.SCL, board.SDA)
sox = LSM6DSOX(i2c)

for i in range(1000):
    x, y, z = sox.acceleration
    print(f"\r{i:04d} Acceleration: x={x:0.2f}, y={y:0.2f}, z={z:0.2f} m/s^2", end='', flush=True)
    # sys.stdout.write(f"\rAcceleration: x={x:0.2f}, y={y:0.2f}, z={z:0.2f} m/s^2 ")
    # sys.stdout.flush()
    time.sleep(0.01)
