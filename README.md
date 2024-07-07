# Custom OBD2 Prius Dashboard
This design is intended for use in the 2004 Toyota Prius. Use at your own risk, if you decide to mess around with systems connected to the CAN bus. As is, the code only reads from available data on the CAN bus and does not solicit any data from devices on the CAN bus. 
Currently, the dashboard will show:
- Gas Tank Levels
- Hybrid Battery SOC
- Drive Mode (N, D, P, R)
- Vehicle speed (MPH)
- RPM (The dash has the functionality to show rpm, but does not have the ability to solicit RPM data from the engine ECU in its current state.)
- Which doors are open (tap bottom right of screen)

## Hardware
Code is written for the atmega328p(common in arduinos) microcontroller and the MCP2515 CAN controller. The screen used is the Nextion 3.5 inch NX4832K035 display and is interfaced by the microcontroller via serial communication using UART. 
The precise physical hardware used is an arduino UNO with a Seedstudio CAN Shield. The device is connected to the car via an OBD2 to DB9 cable using the built in male DB9 connector on the CAN bus shield. 

## Software
The project code is written in C and the script for generating bit timing values for the MCP2515 was written in python. I used my own CAN bus driver to communicate with the MCP2515. You can find my driver [HERE](https://github.com/Wwaylon/MCP2515_Library)
