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

ip = '192.168.1.20'
port = 4840
client = Client(f'opc.tcp://{ip}:{port}')
# client.set_user('Administrator')
# client.set_password('1')

try:
    client.connect()
    root = client.get_root_node()

    # Zusammenstellung des Basispfades => Ermittlung am einfachsten mithilfe des
    # UaExpert Clients
    node_root_main = ['0:Objects', '4:PLC1', '4:MAIN']

    # Verlinkung mit dem Node
    iStep_node = root.get_child(node_root_main + ['4:iStep'])

    # lese den Radius aus der Steuerung
    iStep = iStep_node.get_value()
    print(f'{iStep = }')

    # schreibe iStep die Steuerung
    iStep_node.set_value(ua.DataValue(ua.Variant((iStep + 1), ua.VariantType.Int16)))

    # lese iStep aus der Steuerung
    iStep = iStep_node.get_value()
    print(f'{iStep = }')

finally:
    client.disconnect()