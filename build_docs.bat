REM HTML Renderer
REM githack.com
REM https://raw.githubusercontent.com/p-d-h/abbts_blp/main/docs/build/html/index.html
REM DEV https://raw.githack.com/p-d-h/abbts_blp/main/docs/build/html/index.html

REM rmdir docs\build /S /Q

venv\Scripts\python.exe docs\source\demo\python_jinja.py

venv\Scripts\sphinx-build -b html docs/source/ docs/build/html
