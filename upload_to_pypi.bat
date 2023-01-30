rmdir build /S /Q
rmdir dist /S /Q
venv\Scripts\python.exe setup.py sdist bdist_wheel
venv\Scripts\python.exe -m twine upload dist/*
