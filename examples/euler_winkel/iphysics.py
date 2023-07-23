import requests
import time
import numpy as np


url = 'http://127.0.0.1:8080'
url_base = url + "/document/Vektoren/NP/ios/w/"


def put_state(state='run', info=False):
    time_start = time.time()
    if state == 'run':
        payload = {"state": 1}
    else:
        time.sleep(0.1)  # damit die letzten Operationen abgeschlossen werden können
        payload = {"state": 0}

    headers = {"Content-Type": "application/json"}
    response = requests.request("PUT", (url+'/control'), json=payload, headers=headers)
    if info:
        print(state, response)
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


def put_values(element='', position=np.array([0.0, 0.0, 0.0]), angle=np.array([0.0, 0.0, 0.0])):
    if element == 'v50':
        put_value('rest_v50_x', position[0])
        put_value('rest_v50_y', position[1])
        put_value('rest_v50_z', position[2])
        put_value('rest_v50_roll', angle[0])
        put_value('rest_v50_pitch', angle[1])
        put_value('rest_v50_yaw', angle[2])
    elif element == 'v100':
        put_value('rest_v100_x', position[0])
        put_value('rest_v100_y', position[1])
        put_value('rest_v100_z', position[2])
        put_value('rest_v100_roll', angle[0])
        put_value('rest_v100_pitch', angle[1])
        put_value('rest_v100_yaw', angle[2])
    elif element == 'v150':
        put_value('rest_v150_x', position[0])
        put_value('rest_v150_y', position[1])
        put_value('rest_v150_z', position[2])
        put_value('rest_v150_roll', angle[0])
        put_value('rest_v150_pitch', angle[1])
        put_value('rest_v150_yaw', angle[2])
    elif element == 'p1':
        put_value('rest_p1_x', position[0])
        put_value('rest_p1_y', position[1])
        put_value('rest_p1_z', position[2])
    elif element == 'p2':
        put_value('rest_p2_x', position[0])
        put_value('rest_p2_y', position[1])
        put_value('rest_p2_z', position[2])
    elif element == 'p3':
        put_value('rest_p3_x', position[0])
        put_value('rest_p3_y', position[1])
        put_value('rest_p3_z', position[2])


def rad2deg(rad):
    return rad * 180 / np.pi


def deg2rad(deg):
    return deg * np.pi / 180


if __name__ == '__main__':

    v50_position = np.array([0.0, 0.0, 0.0])
    v50_angle = np.array([deg2rad(0.0), deg2rad(20.0), deg2rad(7.0)])
    v100_position = np.array([0.0, 0.0, 0.0])
    v100_angle = np.array([deg2rad(0.0), deg2rad(-45.0), deg2rad(-45.0)])
    v150_position = np.array([0.0, 0.0, 0.0])
    v150_angle = np.array([deg2rad(0.0), deg2rad(0.0), deg2rad(20.0)])
    put_state('run')
    put_values('v50', v50_position, v50_angle)
    put_values('v100', v100_position, v100_angle)
    put_values('v150', v150_position, v150_angle)
    put_state('stop')
