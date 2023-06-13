# https://github.com/adafruit/Adafruit_Learning_System_Guides/blob/main/Jupyter_USB/MCP2221_Test.ipynb

# Set an Environment Variable so Adafruit Blinka knows we're using the MCP2221
import os
os.environ["BLINKA_MCP2221"] = "1"

# Attempt to import a CircuitPython Module
import board