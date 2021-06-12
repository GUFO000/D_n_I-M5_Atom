# D_and_I
# M5 Stack Atom Matrix Challenge
**Part II, Kitchen Timer. Group 19 (Guglielmo Fonda, Aya El Mir, Aliha Anshira, Milos Vojinović)**

This repositary contains the solution to the challenge proposed in the course from the NYU Abu Dhabi University: ENGR-UH 1021J Design & Innovation Summer 2021 by Instructor Matthew Karau.

The only library used was the M5 Atom Library and the guide for installation can be found [here] (https://docs.m5stack.com/en/arduino/arduino_development).

The solution uses the M5 Atom device to allow the user to set 2 timers and monitor their progress both in the real world and through a webpage. 

Our kitchen timer proposes the following functionalities : 

1. Setting the timers :

-If the kitchen timer's position is up and the timer is not set yet, the user is automatically prompted to select the desired length of the timer by either tilting the kitchen timer right or left : 

  *Tilting right increases the time  
  
  *Tilting left decreases the time
  
2. Activating the timers :

-When the user is satisfied with the length of the timer, click on the button to activate the timer.

3. Displaying the time left for the timers :

-If the kitchen timer is positioned up the time left for timer 1 is displayed.

-If the kitchen timer is flipped down; it displays the time left for the second timer. 

4. Timer goes off :

-When the time goes off for the timer (either 1 or 2), the screen blinks with an alternation between the last number displayed and a solid color (with all pixels on).

5. Reseting the timers :

-When one of the timers go off you can shake to select another length for that specific timer and restart it.

N.B : Switching between timer 1 and timer 2 for any of the functionalities above is always done by flipping the kitchen timer up/down.


