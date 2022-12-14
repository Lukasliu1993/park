#!/usr/bin/env bash
echo "open_port for driver"
#echo "password" |sudo -S chmod 777 /dev/ttyUSB*
echo "open port ttyUSB0 for IMU"
sudo chmod 777 /dev/ttyUSB0
sudo chmod 777 /dev/ttyUSB1
# echo "open port ttyUSB1 for IMU"
# sudo chmod 777 /dev/ttyUSB1
# echo "open port ttyACM0 for GPS"
# sudo chmod 777 /dev/ttyACM0
echo "open port for basic_keyboard"
sudo chmod 777 /dev/input/by-path/platform-i8042-serio-0-event-kbd
echo "open port for remote_keyboard"
sudo chmod 777 /dev/input/by-path/pci-0000:00:14.0-usb-0:1:1.1-event-kbd
sudo chmod 777 /dev/input/by-path/pci-0000:00:14.0-usb-0:1.2:1.1-event-kbd
sudo chmod 777 /dev/input/by-path/pci-0000:00:14.0-usb-0:8:1.0-event-kbd
sudo chmod 777 /dev/input/by-path/pci-0000:00:14.0-usb-0:2:1.0-event-kbd
sudo chmod 777 /dev/input/by-path/pci-0000:00:14.0-usb-0:3:1.2-event-kbd
sudo chmod 777 /dev/input/by-path/pci-0000:00:14.0-usb-0:9:1.0-event-kbd
sudo chmod 777 /dev/input/by-path/pci-0000:00:14.0-usb-0:3:1.1-event-kbd
sudo chmod 777 /dev/input/by-path/pci-0000:00:14.0-usb-0:1:1.1-event-kbd
sudo chmod 777 /dev/input/by-path/pci-0000:00:14.0-usb-0:3:1.1-event-kbd
echo "open port for CAN_BUS"
for ((i=1; i<=9; i++))
do
sudo chmod 777 /dev/bus/usb/001/"00"$i
done
for ((i=10; i<=60; i++))
do
sudo chmod 777 /dev/bus/usb/001/"0"$i
done

# echo "open port USB for camera"
# sudo chmod 777 /dev/bus/usb/
