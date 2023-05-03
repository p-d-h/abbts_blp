def write_to_file(file_name = 'dummy.txt', text=''):
    with open(file_name, 'w', encoding='utf-8') as f:
        f.write(text)


def create_input(modulname='module DATA_IN_VAR_TEENSY',
                 device='TEENSY',
                 items=({'typ': '08_bit', 'n': 4},
                        {'typ': '16_bit', 'n': 22},
                        {'typ': '32_bit', 'n': 4}),
                 bit_offset=0,
                 file_name='teensy_input.txt'):

    text = ''

    # Moduldefinition
    text += 'module ' + modulname + '(\n\t//\n'
    for item in items:
        if item['n'] > 0:
            for i in range(1, item['n']+1, 1):
                if item['typ'] == '08_bit':
                    text += f'\tinput [7:0] FPGA_TO_{device.upper()}_8BIT_{i:02d},\n'
                if item['typ'] == '16_bit':
                    text += f'\tinput [15:0] FPGA_TO_{device.upper()}_16BIT_{i:02d},\n'
                if item['typ'] == '32_bit':
                    text += f'\tinput [31:0] FPGA_TO_{device.upper()}_32BIT_{i:02d},\n'
            text += '\t//\n'
    text += '\toutput [1023:0] DATA\n\t);\n\t//\n'

    # Zuweisungsaufrufe
    bit_pos = bit_offset
    for item in items:
        if item['n'] > 0:
            for i in range(1, item['n']+1, 1):
                if item['typ'] == '08_bit':
                    text += f'\t{device.upper()}_8BIT  {device.lower()}_8bit_{i:02d}(FPGA_TO_{device.upper()}_8BIT_{i:02d}[7:0],    DATA[{bit_pos+7:03d}:{bit_pos:03d}]);\n'
                    bit_pos += 8
                if item['typ'] == '16_bit':
                    text += f'\t{device.upper()}_16BIT {device.lower()}_16bit_{i:02d}(FPGA_TO_{device.upper()}_16BIT_{i:02d}[15:0], DATA[{bit_pos+15:03d}:{bit_pos:03d}]);\n'
                    bit_pos += 16
                if item['typ'] == '32_bit':
                    text += f'\t{device.upper()}_32BIT {device.lower()}_32bit_{i:02d}(FPGA_TO_{device.upper()}_32BIT_{i:02d}[31:0], DATA[{bit_pos+31:03d}:{bit_pos:03d}]);\n'
                    bit_pos += 32
            text += '\t//\n'
    text += f'\t//Prozessabbild: {bit_pos / 8:1.0f} Bytes\n'
    text += 'endmodule\n'

    # Speicherung des Textes in einer Datei
    write_to_file(file_name, text)
    return text


def create_output(modulname='module DATA_OUT_VAR_TEENSY',
                  device='TEENSY',
                  items=({'typ': '08_bit', 'n': 4},
                         {'typ': '16_bit', 'n': 22},
                         {'typ': '32_bit', 'n': 4}),
                  bit_offset=0,
                  file_name='teensy_input.txt'):
    text = ''

    # Moduldefinition
    text += 'module ' + modulname + '(\n\t//\n'
    text += '\tinput [1023:0] DATA,\n\t//\n'

    for item in items:
        if item['n'] > 0:
            for i in range(1, item['n'] + 1, 1):
                if item['typ'] == '08_bit':
                    text += f'\toutput [7:0] {device.upper()}_TO_FPGA_8BIT_{i:02d},\n'
                if item['typ'] == '16_bit':
                    text += f'\toutput [15:0] {device.upper()}_TO_FPGA_16BIT_{i:02d},\n'
                if item['typ'] == '32_bit':
                    text += f'\toutput [31:0] {device.upper()}_TO_FPGA_32BIT_{i:02d},\n'
            text += '\t//\n'
    text = text[:-6]
    text += '\n\t);\n\t//\n'


    # Zuweisungsaufrufe
    bit_pos = bit_offset
    for item in items:
        if item['n'] > 0:
            for i in range(1, item['n']+1, 1):
                if item['typ'] == '08_bit':
                    text += f'\t{device.upper()}_8BIT {device.lower()}_8bit_{i:02d}(DATA[{bit_pos+7:03d}:{bit_pos:03d}],   {device.upper()}_TO_FPGA_8BIT_{i:02d}[7:0]);\n'
                    bit_pos += 8
                if item['typ'] == '16_bit':
                    text += f'\t{device.upper()}_16BIT {device.lower()}_16bit_{i:02d}(DATA[{bit_pos+15:03d}:{bit_pos:03d}], {device.upper()}_TO_FPGA_16BIT_{i:02d}[15:0]);\n'
                    bit_pos += 16
                if item['typ'] == '32_bit':
                    text += f'\t{device.upper()}_32BIT {device.lower()}_32bit_{i:02d}(DATA[{bit_pos+31:03d}:{bit_pos:03d}], {device.upper()}_TO_FPGA_32BIT_{i:02d}[31:0]);\n'
                    bit_pos += 32
            text += '\t//\n'

    text += f'\t//Prozessabbild: {bit_pos/8:1.0f} Bytes\n'
    text += 'endmodule\n'

    # Speicherung des Textes in einer Datei
    write_to_file(file_name, text)
    return text


if __name__ == '__main__':
    # TEENSY
    text_ = create_input(modulname='DATA_IN_VAR_TEENSY',
                         device='TEENSY',
                         items=({'typ': '08_bit', 'n': 10},
                                {'typ': '16_bit', 'n': 27},
                                {'typ': '32_bit', 'n': 0}),
                         bit_offset=0,
                         file_name='teensy_input.txt')

    text_ = create_output(modulname='DATA_OUT_VAR_TEENSY',
                          device='TEENSY',
                          items=({'typ': '08_bit', 'n': 34},
                                 {'typ': '16_bit', 'n': 15},
                                 {'typ': '32_bit', 'n': 0}),
                          bit_offset=0,
                          file_name='teensy_output.txt')

    # RPI
    text_ = create_input(modulname='DATA_IN_VAR_RPI',
                         device='RPI',
                         items=({'typ': '08_bit', 'n': 9},
                                {'typ': '16_bit', 'n': 27},
                                {'typ': '32_bit', 'n': 0}),
                         bit_offset=8,
                         file_name='rpi_input.txt')

    text_ = create_output(modulname='DATA_OUT_VAR_RPI',
                          device='RPI',
                          items=({'typ': '08_bit', 'n': 33},
                                 {'typ': '16_bit', 'n': 27},
                                 {'typ': '32_bit', 'n': 0}),
                          bit_offset=8,
                          file_name='rpi_output.txt')
    # print(text_)
