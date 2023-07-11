REM lösche alle cache-Dateien
venv\Scripts\pyclean.exe -v abbts_blp

REM erstelle die whl-Datei
venv\Scripts\python.exe setup.py sdist bdist_wheel

REM installation des Paketes im Entwicklermodus
venv\Scripts\python.exe setup.py develop