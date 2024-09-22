# https://github.com/adafruit/Adafruit_Learning_System_Guides/blob/main/Jupyter_USB/MCP2221_Test.ipynb
# python -m pip install adafruit-blinka adafruit-circuitpython-msa301 hidapi
# Set an Environment Variable so Adafruit Blinka knows we're using the MCP2221
import os
os.environ["BLINKA_MCP2221"] = "1"

# Attempt to import a CircuitPython Module
import board


from adafruit_lsm6ds.lsm6dsox import LSM6DSOX