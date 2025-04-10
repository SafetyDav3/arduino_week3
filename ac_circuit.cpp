/* ********************** HeaterCircuit **********************
Purpose: 
Emulates a thermostat using the 10K ohm variable resistor as a thermostat 
and an LED light as the furnace. When the pot voltage reads 2.5V or below,
the LED will turn on. When it reaches above 2.5V, the LED will turn off.

Additional information: 
Utilizes if..then.. else statement and comparison operators.
Utilizes the serial monitor.
Utilizes the Micros Mobile Modular board
LED (L0, Terminal block #38) connected to digital pin3
Pot 1 (Terminal block # 63) and VoltMeter (Terminal block #59)connected to Analog pin 0
Use the breadboard to connect them together
Arduino ground connected to Mobile Modular ground (Choose any grounded terminal block)
 
Created on June 14, 2011, Ron Ropson
Revised May 30, 2013 to include the Mobile Modular board, Ron Ropson
Revised July 7, 2020 to include terminal block numbers, voltmeter, and ground, Ron Ropson
*/ 

// Global variables
int potValue; // Note, we do not have to place a value in the variable
float potVoltage; // this needs to be a floating point value for decimal point
const byte acOutputPin=3; // a constant, because it won't be changed (must have a value)
const byte potInputPin=0;// could also be A0 - means the same thing to analogRead()

void setup() 
{
 Serial.begin(9600); // open the serial port for monitoring
 pinMode(acOutputPin,OUTPUT); //note we can use "heateroutput" that way, we can change 
                               // pin assignments in our initial statements and not worry about
                               // making a lot of changes throughout a longer program
 digitalWrite(acOutputPin,LOW); // HIGH=ON, LOW=OFF
} 

void loop()
{  
 delay (250);   // This is so that it prints to the serial monitor 4 times/second      
 potValue=analogRead(potInputPin);
 potVoltage=5.0*potValue/1023.0; // This is our scaled voltage. You may have to adjust it!
 Serial.print("Thermostat voltage = ");   // print this quote, then...
 Serial.println(potVoltage);  // print this value and do a line feed
 if(potVoltage>3.2)
 {
   digitalWrite(acOutputPin,HIGH); //if the voltage<3.2 do this operation
   Serial.print("AC is ON - ");
   // add more lines of code between the curly brackets
 }
   if(potVoltage<3.0)
 {
   digitalWrite(acOutputPin,LOW); //if the voltage<3.0 do this operation
   Serial.print("AC is OFF - ");

   // add more lines of code between the curly brackets
 }
   
}   
