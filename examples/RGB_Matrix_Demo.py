import time
from abbts_blp.rgb import RgbFpga

red = [1, 0, 0]
green = [0, 1, 0]
blue = [0, 0, 1]
white = [1, 1, 1]
colors = [red, green, blue, white]

rgb = RgbFpga(port='COM7')
rgb.open()

for i in range(0, 4, 1):
    for row in range(0, 8, 1):
        color = colors[row % 4]
        for col in range(0, 8, 1):
            rgb.rgb_matrix[row][col] = color
    rgb.write()
    time.sleep(0.5)
    for col in range(0, 8, 1):
        color = colors[col % 4]
        for row in range(0, 8, 1):
            rgb.rgb_matrix[row][col] = color
    rgb.write()
    time.sleep(0.5)
rgb.close()
