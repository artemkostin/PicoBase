#!/usr/bin/python3
'''
    Simple script to update many Picos at time.
    It is assumed that:
    1. PICO automatically mounted to /media/${USER}/RPI-RP2
    2. It supports !info and !boot commands
'''
import fnmatch
import getpass
import os
import time
import shutil
import serial


def get_serial_devices():
    '''
        Return list of potential Pico's serial ports
    '''
    devices = []
    for i in os.listdir('/dev'):
        if fnmatch.fnmatch(i, 'ttyACM*'):
            devices.append(os.path.join('/dev', i))
    return devices

def get_smp_devices():
    '''
        Check which devices are really SMP.
    '''
    smp_devices = []
    serial_devices = get_serial_devices()
    for dev in serial_devices:
        sdev = serial.Serial(dev, baudrate=115200, timeout=1)
        to_send = '!info\r\n'.encode('utf-8')
        sdev.write(to_send)
        read_from_device = sdev.readline().decode('utf-8')
        if 'SmartGarden' in read_from_device:
            print(f'SMP device at {dev}')
            smp_devices.append(dev)
    return smp_devices

def go_to_bootloader(device):
    '''
        Reboot device to UF2 bootloader
    '''
    sdev = serial.Serial(device, baudrate=115200, timeout=1)
    to_send = '!boot\r\n'.encode('utf-8')
    sdev.write(to_send)
    print(f'{device} is rebooted to uf2 bootloader')

def wait_mounting():
    '''
        Wait for Pico mounted as mass-storage
    '''
    user = getpass.getuser()
    lookup_path = os.path.join('/media', user, 'RPI-RP2')
    print('Waiting', end='')
    while not os.path.exists(lookup_path):
        time.sleep(1)
        print('.', end='', flush=True)

    print(f'\nMounted at {lookup_path}')
    return lookup_path

def get_fw():
    '''
        Lookup project PicoBase.uf2 binary.
    '''
    for root, unused_dirs, files in os.walk('../../build/'):
        for _f in files:
            if fnmatch.fnmatch(_f, 'PicoBase.uf2'):
                print(f'Found FW at: {os.path.join(root, _f)}')
                return os.path.join(root, _f)

def copy_fw(src_f, dst_f):
    '''
        Copy FW file to device.
    '''
    _p = shutil.copyfile(src=src_f, dst=dst_f)
    print(f'Copied as {_p}')

if __name__ == '__main__':
    devices = get_smp_devices()
    for dev in devices:
        go_to_bootloader(dev)
        dst = wait_mounting()
        time.sleep(1)
        src = get_fw()
        copy_fw(src, os.path.join(dst, os.path.basename(src)))
        time.sleep(1)
        print(f'Device at {dev} updated')
    print('Done')
