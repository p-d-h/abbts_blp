# Plantuml
# https://plantuml.com/de/state-diagram

import os, sys
import pathlib
import subprocess


path = str(pathlib.Path.cwd())
print(path)
path_tools = str(pathlib.Path.cwd().parent.parent).replace('\\', '/') + '/tools'
print(path_tools)

program_with_args = [
    'java', '-jar',
    f'{path_tools}/plantuml-1.2023.4.jar',
    f'{path}/plantuml_demo_state_diagram.txt',
    '-png']

CREATE_NO_WINDOW = 0x08000000
process = subprocess.Popen(
    program_with_args,
    creationflags=CREATE_NO_WINDOW,
    stdout=subprocess.PIPE, stderr=subprocess.PIPE)
result = process.communicate()
print(result)