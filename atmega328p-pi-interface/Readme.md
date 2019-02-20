----OLD VERSION----

Use AtmegaControl instead

The atmega328p-pi-interface is code for an atmega328 based adapter board that takes in wheel movement distance values and an acceleration 
value. Those inputs from the pi are calculated into velocity values sent every 20ms to the motor controller board. I designed it like this
so you can calibrate your motor controller and then send distance values from a python or other pi program to the motors without dealing
with timing or delays.

