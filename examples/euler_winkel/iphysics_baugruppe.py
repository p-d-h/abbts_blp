import requests
import time
import numpy as np


url = 'http://127.0.0.1:8080'
url_base = url + "/document/Baugruppe/REST:1/ios/w/"


def put_state(state='run', info=False):
    time_start = time.time()
    if state == 'run':
        payload = {"state": 1}
    else:
        payload = {"state": 0}

    headers = {"Content-Type": "application/json"}
    response = requests.request("PUT", (url+'/control'), json=payload, headers=headers)
    if info:
        print(state)
        print(f'time request {(time.time() - time_start):.3f}s', end='\n\n')


def put_value(variable, value, info=False):
    time_start = time.time()
    payload = {"value": value}
    headers = {"Content-Type": "application/json"}
    response = requests.request('PUT', (url_base+variable), json=payload, headers=headers)
    if info:
        print(variable, value)
        print(response)
        print(f'time request {(time.time()-time_start):.3f}s', end='\n\n')

def put_values(element='b1', position=np.array([0.0, 0.0, 0.0]), angle=np.array([0.0, 0.0, 0.0])):
    if element == 'b1':
        put_value('rest_fB1_x', position[0])
        put_value('rest_fB1_y', position[1])
        put_value('rest_fB1_z', position[2])
        put_value('rest_fB1_roll', angle[0])
        put_value('rest_fB1_pitch', angle[1])
        put_value('rest_fB1_yaw', angle[2])
    elif element == 'b2':
        put_value('rest_fB2_x', position[0])
        put_value('rest_fB2_y', position[1])
        put_value('rest_fB2_z', position[2])
        put_value('rest_fB2_roll', angle[0])
        put_value('rest_fB2_pitch', angle[1])
        put_value('rest_fB2_yaw', angle[2])


if __name__ == '__main__':
    b1_position = np.array([0.0, 0.0, 0.0])
    b1_angle = np.array([0.0, -1.0, 0.0])
    b2_position = np.array([0.0, 0.0, 0.0])
    b2_angle = np.array([0.0, 0.0, 1.0])
    put_state('run')
    put_values('b1', b1_position, b1_angle)
    put_values('b2', b2_position, b2_angle)
    # put_state('stop')
