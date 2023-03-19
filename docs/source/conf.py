# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

import pathlib
import os
import sys
import abbts_blp

sys.path.insert(0, os.path.abspath('..'))
# file_path = pathlib.Path(__file__).parents[2].resolve().as_posix() + '/abbts-blp'
# print(file_path)
# sys.path.insert(0, file_path)

project = 'abbts-blp'
copyright = '2023, Pascal Helfenstein, Thomas Ruoss'
author = 'Pascal Helfenstein'
release = abbts_blp.__VERSION__

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

# extensions = [
#     'sphinx.ext.duration',
#     'sphinx_rtd_theme',
#     'sphinx.ext.doctest',
#     'sphinx.ext.autodoc',
#     'sphinx.ext.autosummary',
# ]

extensions = ['sphinx.ext.duration',
              'sphinx.ext.autodoc',
              'sphinx.ext.coverage',
              'sphinx_rtd_theme',
              'sphinx.ext.napoleon',
              'sphinx_execute_code',]

templates_path = ['_templates']
exclude_patterns = ['_build',
                    'Thumbs.db',
                    '.DS_Store']

language = 'de'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output
html_theme = 'sphinx_rtd_theme'

# https://stackoverflow.com/questions/31951553/customizing-sphinx-to-avoid-generating-search-box
templates_path = ['templates']

# https://www.sphinx-doc.org/en/master/usage/configuration.html#confval-html_show_sphinx
html_show_sphinx = False
html_show_copyright = True

html_static_path = ['_static']

