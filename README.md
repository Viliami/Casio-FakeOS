# Casio-FakeOS
A simulation of the menu for the fx-9860GII and upgraded fx-9750GII graphics calculators. It is compatible with SH4A calculators.

##How To Install The Program
**What you need:**
- Casio FA-124 Program
- Casio Fx-9860GII or an upgraded Casio Fx-9750GII
- Mirco-USB to USB cable
- The FAKEOS.G1A file (download from this repo)

**Step 1.** Connecting the calculator

Connect the Calculator to the Computer using the micro-usb cable. (alternatively you could use the program-link cable).
If successful, a popup should apppear on your calculator. Click **[F1]** to put it into receive mode.

**Step 2.** Connecting calculator with FA-124

Open up FA-124 on your computer.
On the top left corner of the left window should be a "connect button". It has an icon of a calculator connected to a computer with a wire, and if you hover over the button with the mouse, text will popup saying "Connect".
Clicking on the connect Button should bring up a few loading sequences but when it is finished the calculator will finally be ready to copy the program.

**Step 3.** Copying the program

Look at the right window in the FA-124 program, instead of clicking on the button on the far left like in step 2(the "Connect" button), you are going to be clicking on the button on the far left. It is called the "Storage" button. It has a bit of green in the icon.

Next you are going to drag the "FAKEOS.G1A" file into the left window, on top of the "Default" directory on the left window.

Once it is copied it should show up on the left window. Drag the "FAKEOS.G1A" file from the left window to the right window in the "Default directory". (the right window shows the programs in your calculator)
When it is done copying click the "Disconnect" button, which is just to the right of the "Connect" button. Press exit on your calculator. Disconnect it from the calculator and the program should now appear in your menu. The icon has the words "debug".

##About The Source code

The menu pictures are stored in C 32-bit int arrays.
The pixels are first converted to a binary array, and then the binary number is converted
to a decimal array using the bin_to_dec.py Python program.
Then it is drawn by converting the decimal back to binary and bitshifting through each of the bits and then drawing it to the calculator display.

Calculator holds little memory, which is why you can't waste memory with a 2D int array.

The Syscalls in the header part is to implement some functionality to detect the keys that are currently pressed without waiting for input, which doesn't work in the SH4A calculators.

##SCREENSHOT
![alt tag](https://cloud.githubusercontent.com/assets/13442473/12046176/8911d780-af17-11e5-9c7e-a41645ceba97.png)
