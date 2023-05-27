import sys

from opcua import Client
from opcua import ua


class SubscriptionHandler(object):
    """Callbackhandler des OPC-UA Datenänderungsevents."""
    def __init__(self, callback=None):
        # Referenz auf externe callbackfunktion
        self.callback = callback

    def datachange_notification(self, node, val, data):
        if self.callback is not None:
            self.callback(node.nodeid.Identifier.split()[-1], val)
        else:
            print('change event ' + node.nodeid.Identifier.split()[-1])


class OpcUaCls:
    """Kommunikation zu einer SPS-Steuerung via OPC UA Protokoll."""

    def __init__(self, ip='127.0.0.1', port=4840, user='pi', password='pi', callback_error=None):
        self.ip = ip
        self.url = 'opc.tcp://' + self.ip + f':{port}'
        if callback_error is None:
            self.callback_error = self.callback_error_function
        else:
            self.callback_error = callback_error

        self._client = Client(self.url)
        self._client.set_user(user)
        self._client.set_password(password)
        self._subscription_handler = None
        self._handler_ext_callback = None
        self._subscription = None
        self._handles = []
        self._connected = False

        self.rRadius = 0.0
        self.rBogenmass = 0.0
        self.arDatenfeld = [0.0 for i in range(10)]

        self.rRadius_node = None
        self.rBogenmass_node = None
        self.arDatenfeld_node = None

    def connect(self, ip=None):
        """Verbindungsaufbau zur SPS."""
        try:
            if ip is not None:
                self.url = 'opc.tcp://' + self.ip + ':4840'
                self._client = Client(self.url)

            # print('connect')
            self._client.connect()
            self._connected = True
            root = self._client.get_root_node()
            plc_name = "4:CODESYS Control for Raspberry Pi SL"
            node_root_main = ['0:Objects', '2:DeviceSet', plc_name,
                              '3:Resources', '4:app', '3:Programs', '4:MAIN']
            self.rRadius_node = root.get_child(node_root_main + ['4:rRadius'])
            self.rBogenmass_node = root.get_child(node_root_main + ['4:rBogenmass'])
            self.arDatenfeld_node = root.get_child(node_root_main + ['4:arDatenfeld'])
        except Exception as e:
            self.callback_error('Error OPC UA connect:', e)

    def read(self):
        """Lese die Daten."""
        try:
            # lesen der Werte aus dem Zielsystem
            # print('read')
            self.rRadius = self.rRadius_node.get_value()
            self.rBogenmass = self.rBogenmass_node.get_value()
            self.arDatenfeld = self.arDatenfeld_node.get_value()
            print(self.arDatenfeld)
        except Exception as e:
            self.callback_error('Error OPC UA read:', e)

    def write(self, rRadius):
        """Schreibe die Daten."""
        try:
            # print('write')
            self.rRadius_node.set_value(ua.Variant(rRadius, ua.VariantType.Float))
            # self.rRadius = rRadius
        except Exception as e:
            self.callback_error('Error OPC UA write:', e)

    def write_array(self, arDatenfeld):
        """Schreibe die Daten."""
        try:
            # print('write')
            self.arDatenfeld_node.set_value(ua.Variant(arDatenfeld, ua.VariantType.Float))
            # self.arDatenfeld = arDatenfeld
        except Exception as e:
            self.callback_error('Error OPC UA write:', e)

    def disconnect(self):
        """Trennen der Verbindung."""
        try:
            # print('disconnect')
            self._client.disconnect()
            self._connected = False
        except Exception as e:
            self.callback_error('Error OPC UA disconnect:', e)

    def subscribe_datachange_event(self, callback=None, inhibit_time=500):
        """Aktivierung des OPC UA Node im Server-Eventhandler bei einer Aenderung des Datenwertes."""
        self._subscription_handler = SubscriptionHandler(self.callback_datachange)
        self._handler_ext_callback = callback
        self._subscription = self._client.create_subscription(inhibit_time, self._subscription_handler)
        self._handles.append(self._subscription.subscribe_data_change(self.rRadius_node))
        self._handles.append(self._subscription.subscribe_data_change(self.rBogenmass_node))

    def unsubscribe_datachange_event(self):
        """Löschen der Einträge im Server-Eventhandler."""
        for handle in self._handles:
            self._subscription.unsubscribe(handle)
        self._handles = []

    def callback_datachange(self, identifier, val):
        """Callbackfunktion nach einer Datenänderung."""
        if identifier.find('rRadius') >= 0:
            print('callback change event => ' + identifier + ' = {:1.1f}'.format(val))
            self.rRadius = val
        elif identifier.find('rBogenmass') >= 0:
            print('callback change event => ' + identifier + ' = {:1.3f}'.format(val))
            self.rBogenmass = val
        else:
            print('callback_datachange unbekannter Variablencallback')

        if self._handler_ext_callback is not None:
            self._handler_ext_callback(identifier, val)

    def callback_error_function(self, *args):
        """Errorhandler"""
        self._connected = False
        try:
            self._client.disconnect()
        except Exception as e:
            print('Error OPC UA')
            sys.exit()

    def is_connected(self):
        return self._connected


if __name__ == '__main__':
    import time

    opc_ua = OpcUaCls(ip='192.168.0.31', port=4840)
    opc_ua.connect()
    opc_ua.read()
    print(f'rRadius = {opc_ua.rRadius:1.01f} | rBogenmass = {opc_ua.rBogenmass:0.03f}')
    print(f'arDatenfeld = ', opc_ua.arDatenfeld)
    opc_ua.write(rRadius=99.9)
    opc_ua.write_array([i*1.0 for i in range(10)])
    opc_ua.read()
    print(f'rRadius = {opc_ua.rRadius:1.01f} | rBogenmass = {opc_ua.rBogenmass:0.03f}')
    print(f'arDatenfeld = ', opc_ua.arDatenfeld)
    opc_ua.subscribe_datachange_event()
    print('before sleep')
    time.sleep(2.25)
    opc_ua.unsubscribe_datachange_event()
    time.sleep(1.25)
    opc_ua.disconnect()
