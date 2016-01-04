# Casio-FakeOS
A simulation of the menu for the fx-9860GII and upgraded fx-9750GII graphics calculators.

The menu pictures are stored in C 32-bit int arrays.
The pixels are first converted to a binary array, and then the binary number is converted
to a decimal array using the bin_to_dec.py Python program.
Then it is drawn by converting the decimal back to binary and bitshifting through each of the bits and then drawing it to the calculator display.

Calculator doesn't hold much memory, that is why you can't just use a 2D int array.


###SCREENSHOT
![alt tag](https://cloud.githubusercontent.com/assets/13442473/12046176/8911d780-af17-11e5-9c7e-a41645ceba97.png)
