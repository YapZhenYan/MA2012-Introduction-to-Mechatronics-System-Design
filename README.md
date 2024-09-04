# MA2012-Introduction-to-Mechatronics-System-Design
Design a control system of en electric toy car for children using Arduino UNO MCU

The schematic diagram is shown in Figures 1A and 1B.

<img width="464" alt="image" src="https://github.com/user-attachments/assets/4ee53685-e4c4-43fc-8914-0b80dd1cd74b">

<img width="464" alt="image" src="https://github.com/user-attachments/assets/b0e7917e-ddbd-46ac-be35-69266e37cfb9">

**• The operation of the electric car is as follow:**

- The electric car is turned ON when pushbutton PS1 is pressed and held for 1s.

**▪ The car can only be turned ON if the gear shift (TS3) is at NEUTRAL position.**

**▪ Upon starting, the Piezo Buzzer sounds off 1 time and LED1 is turned ON.**

- When the car is turned ON, pressing PS1 again will turn it OFF, and all operations of the car will be halted.
  
- The 3-way Toggle switch (TS3) is used as gear shift control of the car.
  
**▪ Switch to Position 1 means Forward driving mode.**

**▪ Switch to Position 2 means Reverse driving mode.**

**▪ NEUTRAL (Position N) means neutral mode.**

- The car is back wheel drive.

**▪ Turning POT1 (i.e. stepping on the accelerator) controls the rotation speed of the DC Motor. When POT1 = 0 – 5.0V, the DC Motor runs at 0 – 100% duty cycle.**(It would be fine if the DC Motor can only start rotating at some higher value of duty cycle, i.e. 30%, as long as its speed can be tuned after starting to move)

**▪ When it is at forward driving mode, the DC Motor rotates CCW (looking into the motor shaft).**

**▪ When it is at reverse driving mode, the DC Motor rotates CW and the Piezo Buzzer beeps continuously until the mode changes.**

- Opto-switch OS senses whether the safety belt is worn. When it is blocked, the safety belt is buckled; when it is unblocked, it is unbuckled.

**▪ If the safety belt is unbuckled and the speed of the car exceeds 25% duty cycle, LED 2 (Red) will blink continuously until the safety belt is buckled or the speed drops back to 25% duty cycle or lower.**

  o The car has a dashboard controlled by another Arduino Uno (Figure 1B) to display the car’s operation.
  
▪ The control unit of the toy car transmits the operation information to the dashboard via UART protocol.

**▪ The LCD (U1) displays:**

- In row 1, from column 1: “Forward”, “Reverse” or “Neutral” that corresponds to the position of the Gear Shift, i.e. TS3.
  
- In row 1, from column 10: Speed of car, i.e. percentage of duty cycle
  
**• You are to write a C++ language program to perform these tasks**

