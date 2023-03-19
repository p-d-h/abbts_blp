# Graphviz
# - https://graphviz.org/
#     - https://graphviz.org/gallery/
# - https://github.com/pydot/pydot
#     - https://pypi.org/project/pydot/
# - https://github.com/tschoonj/GTK-for-Windows-Runtime-Environment-Installer/releases
# - https://gitlab.com/graphviz/graphviz/-/releases

import os, sys
import pathlib

path = str(pathlib.Path.cwd()).replace('\\', '/')
print(path)
path_tools = str(pathlib.Path.cwd().parent.parent).replace('\\', '/') + '/tools'
print(path_tools)
# Erweiterung der Pfadvariablen für die Einbindung von graphviz und gtk3
os.environ["PATH"] += os.pathsep + f'{path_tools}/graphviz_7_1_0'
os.environ["PATH"] += os.pathsep + f'{path_tools}/gtk3_runtime_32431'

import pydot
import cairosvg
# from abbts_blp.toolbox.win_dot_parser import pydot_win

# https://graphviz.org/doc/info/shapes.html
with open(f'{path}/graphviz_demo.txt') as f:
    dot_string = f.read()
graphs = pydot.graph_from_dot_data(dot_string)
graph = graphs[0]
graph.write_svg('graphviz_demo.svg')
cairosvg.svg2png(url='graphviz_demo.svg', write_to='graphviz_demo.png', dpi=300)