rmdir docs\build /S /Q

venv\Scripts\sphinx-build -b html docs/source/ docs/build/html
