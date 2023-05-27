from opcua import Client
from opcua import ua

# Dokumentation
# http://freeopcua.github.io/
# https://github.com/FreeOpcUa/python-opcua

# Minimalbeispiel abgeleitet von
# https://github.com/FreeOpcUa/python-opcua/blob/master/examples/client-minimal.py

# Benutzerverwaltung
# https://stackoverflow.com/questions/75056713/connect-to-opcua-server-with-username-and-password

# Codesys Zertifikat
# https://content.helpme-codesys.com/en/CODESYS%20Communication/_cds_runtime_opc_ua_server.html
# Installation CODESYS Security Agent via CODESYS Installer

ip = '192.168.0.31'  # oder 192.168.16.87 <= BLP Dozent
port = 4840
client = Client(f'opc.tcp://{ip}:{port}')
client.set_user('pi')
client.set_password('pi')

try:
    client.connect()
    root = client.get_root_node()

    # Zusammenstellung des Basispfades => Ermittlung am einfachsten mithilfe des
    # UaExpert Clients
    plc_name = "4:CODESYS Control for Raspberry Pi SL"
    node_root_main = ['0:Objects', '2:DeviceSet', plc_name,
                      '3:Resources', '4:app', '3:Programs', '4:MAIN']

    # Verlinkung mit dem Node
    rRadius_node = root.get_child(node_root_main + ['4:rRadius'])

    # lese den Radius aus der Steuerung
    rRadius = rRadius_node.get_value()
    print(f'{rRadius = }')

    # schreibe den Radius in die Steuerung
    rRadius_node.set_value(ua.Variant((rRadius+5.0), ua.VariantType.Float))

    # lese den Radius aus der Steuerung
    rRadius = rRadius_node.get_value()
    print(f'{rRadius = }')

finally:
    client.disconnect()