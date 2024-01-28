# FRDM-KL46Z-Programming

A project folder featuring my projects involving programming a FRDM-KL46Z board using MCUXpresso. You can find the necessary files, configurations, and source code I used in developing these embedded systems applications in C. In each folder, you'll be able to find the **peripherals, setup, and description/overview** of each project.


## MCUXpresso Clock Configurations
Set the clock to these settings:
```
Frequency: 8MHz
OSC Mode: Using oscillator with external crystal (low power)
Frequency Range: Very High Frequency Range 8-32 MHz </br>
```
Next, in the clock outputs pane, click "Core Clock", and update these settings:
```
MCG Mode: PEE (PLL Engaged External)
OUTDIV1: /2
```
In the clock outputs pane, click **"OSCERCLK"**. In the Path Details pane, set
OSCERCLK Output to **Enabled.** You should see the OSCERCLK frequency change to 8 MHz.
Finally, in the clock outputs pane, click **"MCG PLL/FLL clock"**. In the Path Details pane,
change the **PLLFLLSEL** to **"MCGPLLCLK clock with fixed divide by 2"** 
