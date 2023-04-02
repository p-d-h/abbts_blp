# Plantuml
# https://plantuml.com/de/state-diagram
# https://real-world-plantuml.com/
# https://dev.to/sakko/how-i-code-not-draw-my-er-diagram-4kc3
# https://nevets.github.io/2019/06/03/plantuml/
# https://plantuml.com/de-dark/ie-diagram
# https://plantuml.com/de/skinparam
# https://plantuml-documentation.readthedocs.io/en/latest/formatting/all-skin-params.html
# https://plantuml.com/es/class-diagram


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
    '-charset', 'UTF-8',
    '-png']

CREATE_NO_WINDOW = 0x08000000
process = subprocess.Popen(
    program_with_args,
    creationflags=CREATE_NO_WINDOW,
    stdout=subprocess.PIPE, stderr=subprocess.PIPE)
result = process.communicate()
print(result)