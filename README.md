++Overview.++

This is the result of lurking on Adafruit for some time.  It's a simple microcontroller dice roller.  It replicates the roll
2 sided (or coins if you prefer), 4 sided, 6 sided, 8 sided, 10 sided, 12 sided, 20 sided, and percentile (1-100) dice rolls.

It probably wouldn't take much effort to insert custom numbers of dice sides into the program if needed.


++Supplies needed.++

3v Trinket Pro
https://www.adafruit.com/products/2010

Quad Alphanumeric Display - Pure Green 0.54" Digits w/ Backpack
https://www.adafruit.com/products/2160

3x Push Buttons
https://www.adafruit.com/products/367

Trinket LiIon/LiPoly backpack
https://www.adafruit.com/product/2124

3x 1k Ohm Resistors
https://www.radioshack.com/products/radioshack-1-8-watt-1k-carbon-film-resistors-5-pack?variant=5717252293

LED backpack library
https://github.com/adafruit/Adafruit-LED-Backpack-Library

Adafruit GFX Library (for displays)
https://github.com/adafruit/Adafruit-GFX-Library


++Wiring.++

LiPoly/LiIon backpack
Attach directly to the Trinket Pro as instructed here,
https://learn.adafruit.com/adafruit-pro-trinket-lipoly-slash-liion-backpack

Quad Alphanumeric Display - Pure Green 0.54" Digits w/ Backpack
C - A5
D - A4
+ - BAT
- - Gnd

Buttons
BAT from the Trinket Pro goes to one side of the push button.  
The opposite corner connects to the pin for the switch (3, 4, and 5 on the Trinket Pro).
The last connection is a 1k ohm resistor that goes on the other side from the switch connection next to the BAT connection.
The other side of the resistor connects to Gnd.

++Links that helped.++

https://learn.adafruit.com/adafruit-led-backpack/0-54-alphanumeric
Adafruit's alphanumeric LED backpack tutorial with all the commands and how to use them.

https://learn.adafruit.com/adafruit-pro-trinket-lipoly-slash-liion-backpack/pinouts
Adafruit's charging backpack pinout.

https://learn.adafruit.com/introducing-pro-trinket/pinouts
Adafruit's trinket pro pinout.

++To do.++

Add options option to turn on/off the options below.

Add success/failure counter (such as rolling for Vampire the Masquerade or Shadowrun).

Heads or tails (HEAD vs TAIL *should* work on the seven segment display.)

Add crit failure and success option.

Configure it to "remember" the last roll instead of reset.

Get the dice number button to work when the screen shows the roll.
