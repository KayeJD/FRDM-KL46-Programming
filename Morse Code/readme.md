## Description
This project involves setting up the two onboard LED lights and flashing the LEDs in alternation
(red-green-red) depending on whether the word n a given string has the index 0, 2, 4, etc
(red) and 1, 3, 5, 7 (green). The LEDs are to flash the morse code for the given string and
the alternating LED light are to indicate when there is a new word. When the string i
finished being iterated though, it simply flashes the message again. </br>

Here is a [video](https://drive.google.com/file/d/1HgUsOvIcG5j8Gz1B7lVSTDrPluqY591O/view?usp=sharing) of the behavior

## Implementation
This code begins with setting up all of the ports and configuring them to start on OFF. We
enable the ports (E and D), clear the mux, and initialize the LEDs as outputs and the switch as
input. Then, we needed to enable a TPM to use a timer for the delays in lashing or holding the
lights on. We choose to use TPM0 in this project and configure it in the delay function. The logic
for this project were to create a delay function that takes in the number of ms the delay is
supposed to run for, a dash() and dot() function that take in bool parameters to determine which
light to flash, and a main displayMorse() function that keeps track of when there is a new word
and the corresponding morse code to flash with each char in the string. We use a for loop that
exits once ‘\0’ is detected at the end of the char string. The system is easily configurable, the user would be able to change the message in the main() function to whatever they’d like the FRDM board to say, and the use can also change how long the lights are to stay on for given the delay() inputs. Here is the following sudo code:
```
delay(int ms){waits however long ms is passed through}
dash(bool word){
if (word = odd) {flash red for 500ms}
else {flash green for 500ms}
delay(250)
}
dot (bool word){
if (word = odd) {flash red for 200ms}
else {flash green for 200ms}
delay(250)
}
period(){
if (word = odd) {flash red for 600ms}
else {flash green for 600ms}
}
displayMorse(message, length){
bool evenWord = false; //start with red
3
for (i = 0; message[i] != ‘\0’; i++){
c = message[i]
switch (c){
//Display necessary morse code by calling dash(evenWord), dot(), etc
}
}
}
```
