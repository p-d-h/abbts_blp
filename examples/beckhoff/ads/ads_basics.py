# https://pyads.readthedocs.io/en/latest/index.html
# https://github.com/stlehmann/pyads
# https://pypi.org/project/pyads/
# pip install pyads

import pyads

try:
    plc = pyads.Connection('192.168.0.33.1.1', pyads.PORT_TC3PLC1)
    plc.open()
    rRadius = plc.read_by_name('MAIN.rRadius', pyads.PLCTYPE_REAL)
    print(rRadius)
    plc.write_by_name('MAIN.rRadius', rRadius+5.0, pyads.PLCTYPE_REAL)
    print(plc.read_by_name('MAIN.rRadius', pyads.PLCTYPE_REAL))

except Exception as exc:
    print(exc)

finally:
    plc.close()
