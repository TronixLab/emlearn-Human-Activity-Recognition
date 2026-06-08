>> arduino-cli board list

```bash
Port Protocol Type              Board Name          FQBN                        Core
COM3 serial   Serial Port       Unknown
COM4 serial   Serial Port       Unknown
COM6 serial   Serial Port (USB) Arduino Nano 33 BLE arduino:mbed_nano:nano33ble arduino:mbed_nano
```

>> arduino-cli upload -p COM6 --fqbn arduino:mbed_nano:nano33ble -i .\Arduino_HAR.ino.bin

```bash
no-cli upload -p COM6 --fqbn arduino:mbed_nano:nano33ble -i .\Arduino_HAR.ino.bin
Device       : nRF52840-QIAA
Version      : Arduino Bootloader (SAM-BA extended) 2.0 [Arduino:IKXYZ]
Address      : 0x0
Pages        : 256
Page Size    : 4096 bytes
Total Size   : 1024KB
Planes       : 1
Lock Regions : 0
Locked       : none
Security     : false
Erase flash

Done in 0.001 seconds
Write 129560 bytes to flash (32 pages)
[==============================] 100% (32/32 pages)
Done in 5.410 seconds
New upload port: COM6 (serial)
```