# ECE414_Final_Project
This is the final project we created in Fall 2018 ECE 414 embedded systems in Lafayette College. The goal of this project is to design and build an 8 * 8 * 16 LED cuboid. It is very suitable for people with a low budget and still contains three powerful features that
facilitate entertainment, business and education scenarios. The balance between price and performance make this product more competitive than other existed 3D display
implementations.

## Software
The entire system is composed of multiple modules. Separating these modules allows an easier debugging. Also future developers can add their new functions to it.
A Highlight of Important Software Methods and Designs

###LED driver
Write the LED on information to the cuboid array and then write this array to the hardware: generate control signals going to the control circuit. This method was improved so that instead of looping through all of the LEDs, only the LED that are known to be on will be refreshed. This way the on LEDs get more time during the scanning and will appear brighter.

###UART test methods
These methods print out current LED status to UART when the LED cuboid gets refreshed. In this way, developers do not need to build the real circuit in order to see the display effect. Besides, it also allows developers to build hardware and software at the same time.

###Letters Display
Using this module, users can display their own message on the LEDs. We have hardcoded decode function for each input letter, which will be shown in coordination with the scrollIndex variable to create the scrolling effect. Users can also specify the time period it scrolls in the header. This function is tested and demonstrated in the presentation.

###Snake game
Similar to a regular snake game, the game is the system allows users to play in a 3D way. Users can control the snake with 6 buttons in order to eat foods that are randomly generated. It is really fantastic to play the classic snake game in 3D. This function is tested and demonstrated in the presentation.

###Model display
This module allows users to see their model in the system. First, users can code their model in this module that contains multiple points. Using the buttons, users can rotate the module either clockwise or counterclockwise. This function is tested and demonstrated in the presentation.

## Hardware

### LED Circuit
There will be 10 input signals to control the on-off of the 1024 LEDs. One LED lights up at a time. The multiple on effect is achieved by scanning.
On the LED anode side, there is one high signal selected from 16. This is achieved by inverting 16 active low (one low) signal.  All decoders we use have 3 inputs and 8 outputs. We have the 3 inputs (lev_sel[3]) of 2 decoders to be the same, then used the 4th signal to go into the enable of one decoder, and the inverted 4th signal to go into the other. We can have one high output out of the 16 this way.
On the cathode side, we need to have one low signal from 64. This is achieved by 6 input signals. We first have 3 inputs (col_sel[3]) as the input of one decoder, then use the 8 outputs as enable signals for the other 8 decoders, which all have same 3 inputs (row_sel[3]).
In a word, the setting for the anode and cathode allows for one LED to have high on the anode and low on the cathode at one time to have the scanning effect.
### Buttons
We used six buttons because in the snake game we want to control it in six different directions.
### Touchscreen
The touchscreen module receives input from the user and sends the signal to the main control.
## Authors
Feng Qiu
Zhengxie Hu
