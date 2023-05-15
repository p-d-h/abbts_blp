from riden import Riden
from time import sleep

def main(port: str = 'COM3', baudrate: int = 115200, address: int= 1):
    r = Riden(port, baudrate, address)
    lines = {
        "ID      ": r.id,
        "SN      ": r.sn,
        "FW      ": r.fw,
        "TYPE    ": r.type,
        "INT_C   ": r.int_c,
        "INT_F   ": r.int_f,
        "V_SET   ": r.v_set,
        "I_SET   ": r.i_set,
        "V_OUT   ": r.v_out,
        "I_OUT   ": r.i_out,
        "P_OUT   ": r.p_out,
        "V_IN    ": r.v_in,
        "KEYPAD  ": r.keypad,
        "OVP_OCP ": r.ovp_ocp,
        "CV_CC   ": r.cv_cc,
        "OUTPUT  ": r.output,
        "PRESET  ": r.preset,
        "BAT_MODE": r.bat_mode,
        "V_BAT   ": r.v_bat,
        "EXT_C   ": r.ext_c,
        "EXT_F   ": r.ext_f,
        "AH      ": r.ah,
        "WH      ": r.wh,
        "DATETIME": r.get_date_time(),
        "TAKE_OK ": r.is_take_ok(),
        "TAKE_OUT": r.is_take_out(),
        "BOOT_POW": r.is_boot_pow(),
        "BUZZ    ": r.is_buzz(),
        "LOGO    ": r.is_logo(),
        "LANG    ": r.get_lang(),
        "LIGHT   ": r.get_light(),
    }
    for key, value in lines.items():
        print(f"{key}: {value}")


def dump_regs(port: str = 'COM3', baudrate: int = 115200, address: int = 1):
    from riden import Register

    names = {
        v: k for (k, v) in Register.__dict__.items() if not k.startswith("_")
    }
    max_length = max(len(k) for k in names.values())

    r = Riden(port, baudrate, address)

    for i in range(256):
        value = r.read(i)
        name = names.get(i, "").rjust(max_length)
        print(f"{name} {i:03d}: {value}")


def demo(port: str = 'COM3', baudrate: int = 115200, address: int= 1):
    r = Riden(port, baudrate, address)
    # r.set_light(3)
    r.set_output(False)
    r.set_v_set(12.67)
    r.set_i_set(2.0)

    r.set_output(True)
    r.update()

    sleep(2)
    r.update()
    print(f'{r.v_out=}V')
    print(f'{r.i_out=}A')
    print(f'{r.p_out=}W')
    print(f'{r.ah=}Ah')
    print(f'{r.wh=}Wh')
    print(f'{r.int_c=}°C')
    print(f'{r.v_bat=}V')
    print(f'{r.is_bat_mode()=}')




if __name__ == "__main__":
    # main()
    # dump_regs()
    demo()
