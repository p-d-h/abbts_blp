Demo
====

Codeausführung
--------------
https://github.com/jpsenior/sphinx-execute-code

.. execute_code::
    :hide_headers:

    import numpy as np
    print (f'pi = {np.pi:04f}')


Section
-------

Subsection
~~~~~~~~~~

You can use ``backticks`` for showing ``highlighted`` code.

`A cool website`_

A cool bit of code::

   Some cool Code
   dsf
   sdf

sdfs
sdfsdf

.. code-block:: rst

   A bit of **rst** which should be *highlighted* properly.


.. code-block::
   :caption: main.py

   if __name__ == "__main__":
    print('Hello World')

.. image:: img/affe.webp
	:scale: 50 %




..
  https://www.sphinx-doc.org/en/master/usage/restructuredtext/directives.html
  https://www.sphinx-doc.org/en/master/tutorial/automatic-doc-generation.html#
  https://www.sphinx-doc.org/en/master/usage/extensions/autosummary.html#directive-autosummary
  https://sphinx-tutorial.readthedocs.io/step-2/
  https://sphinx-tutorial.readthedocs.io/crawler/docs/step2/api/

.. _A cool website: http://sphinx-doc.org