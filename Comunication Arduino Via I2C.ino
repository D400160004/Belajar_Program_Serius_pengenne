/*
pin
Master || Slave
A4    =>  A4
A5    =>  A5
GND    =>  GND
5V/3,3V JANGAN PERNAH DIKONEKKAN /DISAMBUNG !!!!!!!!!!!!!!
*/
--------------------------------------------------------------------
--------------------------MASTER -----------------------------------
====================================================================
#include <Wire.h>
int x = 0; 
void setup() { 
// Start the I2C Bus as Master 
Wire.begin(); 
} 
void loop() { 
Wire.beginTransmission(9); // transmit to device #9 
Wire.write(x); // sends x 
Wire.endTransmission(); // stop transmitting 
x++; // Increment x 
if (x > 5) x = 0; // reset x once it gets 6 
delay(500); 
}
--------------------------------------------------------------------
-------------------------- SLAVE -----------------------------------
====================================================================
#include <Wire.h>
int x = 0; 
void setup() { 
pinMode (LED_BUILTIN, OUTPUT); 
// Start the I2C Bus as Slave on address 9 
Wire.begin(9); 
// Attach a function to trigger when something is received.
Wire.onReceive(receiveEvent); 
} 
void receiveEvent(int bytes) { 
x = Wire.read(); // read one character from the I2C 
} 
void loop() { 
//If value received is 0 blink LED for 200 ms 
if (x == '0') { 
digitalWrite(LED_BUILTIN, HIGH); 
delay(200); 
digitalWrite(LED_BUILTIN, LOW); 
delay(200); 
} 
//If value received is 3 blink LED for 400 ms 
if (x == '3') { 
digitalWrite(LED_BUILTIN, HIGH); 
delay(400); 
digitalWrite(LED_BUILTIN, LOW); 
delay(400); 
} 
}
