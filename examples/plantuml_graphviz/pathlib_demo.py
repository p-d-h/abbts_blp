# https://www.freecodecamp.org/news/how-to-use-pathlib-module-in-python/
# https://realpython.com/python-pathlib/

import pathlib
import os

path = pathlib.Path.cwd()

print(path)
print(path.parent)
print(path.parts)
print(str(path).replace('\\', '/'))

print(os.getcwd())
print(pathlib.Path(__file__).parent)