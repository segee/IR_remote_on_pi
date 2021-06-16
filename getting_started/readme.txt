Pretty basic stuff...The code assumes a 3 wire IR sensor hooked up to GPIO 21 on the pi. 
It was chosen because it is on a corner pin along with ground and power.  The sensor I used
was a 5V device...probably not the best choice, but it was the cheapest digikey had. The signal is
an NPN transistor with a pull up resistor of 30K or so, so current when the output is 5V and the
pi is clipping to 3.3V is minimal.

The code assumes wiring pi is installed and that user level gpio is allowed

each of the .c files is its own thing and there is no makefile.  compiling is of the form

gcc whatever.c -lwiringPi
