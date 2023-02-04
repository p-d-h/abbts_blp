# https://realpython.com/primer-on-jinja-templating/

import pathlib
from jinja2 import Environment, FileSystemLoader

var_dict = {'name': 'abcd'}

folder_path = pathlib.Path(__file__).parents[0].resolve().as_posix()
print(folder_path)
environment = Environment(loader=FileSystemLoader(f'{folder_path}/templates'))
template = environment.get_template('message.txt')

content = template.render(var_dict)

with open(f'{folder_path}/python_jinja.rst', mode="w", encoding="utf-8") as message:
    message.write(content)