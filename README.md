++Overview.++

This is the result of lurking on Adafruit for some time.  It's a simple microcontroller dice roller.  It replicates the roll
2 sided (or coins if you prefer), 4 sided, 6 sided, 8 sided, 10 sided, 12 sided, 20 sided, and percentile (1-100) dice rolls.

After getting everything wired up, run the AnalogTest sketch to find out the minimum values of each of the button presses.  
Once you have those numbers, substitute them (minus about 10 just to be sure) in the appropiate place in the loop function.
After that rolling should commence.

It probably wouldn't take much effort to insert custom numbers of dice sides into the program if needed.


++Supplies needed.++

5V Trinket
https://www.adafruit.com/product/1501

7 Segment LED display with i2c backpack
https://www.adafruit.com/product/878

3x Push Buttons
https://www.adafruit.com/products/367

Trinket LiIon/LiPoly backpack
https://www.adafruit.com/product/2124

3x 1k Ohm Resistors
https://www.radioshack.com/products/radioshack-1-8-watt-1k-carbon-film-resistors-5-pack?variant=5717252293

1M Ohm Resistor
https://www.radioshack.com/products/radioshack-1m-ohm-1-2w-5-carbon-film-resistor-pk-5?variant=5717284613

LED backpack library
https://github.com/adafruit/Adafruit-LED-Backpack-Library

Adafruit GFX Library (for displays)
https://github.com/adafruit/Adafruit-GFX-Library


++Wiring.++

LiPoly/LiIon backpack
BAT - BAT+
G - Gnd
5V - USB+

i2c Seven Segment Backpack
C - #2
D - #0
+ - 5V
- - Gnd

Buttons
5V from the Trinket goes to a 1k ohm resistor, then to one side of the number of dice button.
From that same side another 1k ohm resistor goes to the number of dice sides button.
The same side of the number of dice sides button goes to through another 1k ohm resistor then to the roll button.
Finally on the same side of the roll button goes a 1M ohm resistor that then goes to pin #4 on the Trinket.

The other sides of the buttons (without the resistors) all tie to pin #4 on the Trinket also.


++Links that helped.++

https://learn.adafruit.com/adafruit-led-backpack/0-dot-56-seven-segment-backpack
Adafruit's seven segment LED backpack tutorial with all the commands and how to use them.

https://learn.adafruit.com/adafruit-pro-trinket-lipoly-slash-liion-backpack/pinouts
Adafruit's charging backpack pinout.

https://learn.adafruit.com/introducing-trinket/pinouts
Adafruit's trinket pinout.

http://www.pighixxx.com/test/portfolio-items/multiple-button-using-1-analog-input/
Pighixxx's how to wire up a bunch of buttons to a single analog input.
