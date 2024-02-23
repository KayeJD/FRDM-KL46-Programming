# FRDM-KL46Z-Programming

![image](https://github.com/KayeJD/FRDM-KL46Z-Programming/assets/139111295/5be178dd-96f1-4fb9-9ebd-d2201e01a7d4)

Welcome to the repository showcasing my practices with embedded programming using MCUXpresso on the FRDM KL46 development board. This repository demonstrates my proficiency in working with various peripherals and configuring functionalities such as PWM (Pulse Width Modulation), ADC (Analog to Digital Converter), TPM (Timer/Pulse Width Modulation), and more. You can find the necessary files, configurations, and source code I used in developing these embedded systems applications in C. In each folder, you'll be able to find the **peripherals, setup, and description/overview** of each project. The Schematics and Datasheets needed are provided as files

### Skills learned so far...
- PWM Configuration: Demonstrates how to configure and utilize PWM for controlling motors, LEDs, or other devices.
- ADC Implementation: Shows the implementation of ADC for reading analog sensor data.
- TPM Setup: Illustrates how to set up and utilize TPM for various timing and pulse-width modulation tasks.
- Peripheral Integration: Examples integrating multiple peripherals to accomplish specific tasks or functionalities.

## Reference Manuals and Datasheets
1. [FRDMKL46 User's Manual](https://www.farnell.com/datasheets/1728679.pdf)
2. [FRDMKL46 Reference Manual](https://home.agh.edu.pl/~ostrowsk/teksty/manual.pdf)
3. [FRDMKL46 Schematic](https://www.openhacks.com/uploadsproductos/frdm-kl46z_sch.pdf)
4. [TB6612FNG Motor Driver](https://www.sparkfun.com/datasheets/Robotics/TB6612FNG.pdf)

## Usage
1. Clone the repository to your local machine.
2. Open the projects in MCUXpresso IDE or your preferred development environment.
3. Explore the source files in the /src directory to understand the implementation details.
4. Refer to documentation in the /docs folder for additional insights or explanations.

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
