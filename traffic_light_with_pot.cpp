/************************ TrafficLights3 **********************

Purpose:
Emulates 2 sets of traffic lights at an intersection including green for go,
yellow for clear intersection and red for stop.
This is an example of a timing sequence (sequential program).

Additional information:
Utilizes the LEDs on the Mobile Modular board
Red LEDs are at the top row (if not, have the instructor switch the cap colors)
Connections:
Light       Arduino pin     Terminal Block
NSgreen      pin 2            #46
NSyellow     pin 3            #42
NSred        pin 4            #38
EWgreen      pin 5            #49
EWyellow     pin 6            #45
EWred        pin 7            #41
             Ground           Ground

Created on July 7, 2020
 By Ron Ropson
 */

const byte NSgreen = 2; // naming the pins with familiar names makes programming easier
const byte NSyellow = 3;
const byte NSred = 4;
const byte EWgreen = 5;  // we could use longer names like NorthSouthGreen55thStreet25 too!
const byte EWyellow = 6; // but it would be too much typing.
const byte EWred = 7;
const byte NSwalk = 9;
const byte EWwalk = 8;

// Input for the potentiometer
int potPin = A0;
int potValue = 0;
int potInput = 0;

void setup()
{
  for (byte a = 2; a < 10; a++) // another cool programming tool to make pins 2-7 outputs all at once
  {
    pinMode(a, OUTPUT);
  }
  // Setup initial conditions
  digitalWrite(NSgreen, LOW);   // When the lights are first on, we can't have them all lit
  digitalWrite(NSyellow, HIGH); // nor can we have them all off. we could start with red, though!
  digitalWrite(NSred, LOW);
  digitalWrite(EWgreen, LOW);
  digitalWrite(EWyellow, LOW);
  digitalWrite(EWred, HIGH);
  digitalWrite(NSwalk, LOW);
  digitalWrite(EWwalk, LOW);
  flashLights(5); // This is something new: a call to a function.
                  // the number 5 is passed onto the function so
                  // it knows how many times to blink
}

void loop()
{
  allRed();             // function call to make sure both sets are red before starting
  northSouthSequence(); // perform the NS sequence green, then yellow, then red
  allRed();
  eastWestSequence(); // perform the EW sequence green, then yellow, then red
}

/*
 * flashinglights(int)
 * This function flashes the NS yellow lights
 * and flashes the EW red lights
 */

void flashLights(int times) // this is the function flashinglights.
                            // It blinks the lights the specified number of times then returns
{
  for (int a = 0; a < times; a++)
  {
    delay(500);
    digitalWrite(NSyellow, LOW);
    digitalWrite(EWred, LOW);
    delay(500);
    digitalWrite(NSyellow, HIGH);
    digitalWrite(EWred, HIGH);
  }
}

/*
 * allRed()
 * This function turns both the NS and EW lights red
 * It also makes sure all the others are off
 * It simplifies programming sequence and is safe
 * if the program freezes
 * It us used before any green light turns on
 * so there is no confusion
 */

void allRed()
{
  digitalWrite(NSgreen, LOW);
  digitalWrite(NSyellow, LOW);
  digitalWrite(NSred, HIGH);
  digitalWrite(EWgreen, LOW);
  digitalWrite(EWyellow, LOW);
  digitalWrite(EWred, HIGH);
  delay(250); // so it's not instant from red on one street to green on the other
}

// turn the NS light from green to yellow to red
void northSouthSequence()
{
  int potValue = analogRead(potPin); // read the potentiometer
  int potTime = map(potValue, 0, 1023, 2000, 8000); // map it to a time
  digitalWrite(NSred, LOW); // turn off red first
  digitalWrite(NSgreen, HIGH);
  digitalWrite(NSwalk, HIGH);
  delay(potTime);
  digitalWrite(NSwalk, LOW);
  delay(potTime / 2);
  digitalWrite(NSgreen, LOW);   // make sure it's turned off first!
  digitalWrite(NSyellow, HIGH); // switch to yellow
  delay(2000);                  // for two seconds
  digitalWrite(NSyellow, LOW);  // important! even though it takes only a few microseconds to
  digitalWrite(NSred, HIGH);    // complete this task, the order is  vital, because if the
  // microcontroller freezes up, we don't want confusing signals,
}

// turn the EW light from green to yellow to red
void eastWestSequence()
{
  potInput = analogRead(potPin); // read the potentiometer
  potValue = map(potInput, 0, 1023, 2000, 8000); // map it to a time
  digitalWrite(EWred, LOW); // turn off red first
  digitalWrite(EWgreen, HIGH);
  digitalWrite(EWwalk, HIGH);
  delay(potValue);              // for two seconds
  digitalWrite(EWwalk, LOW);
  delay(potValue / 2);          // Wait for half the green light time
  digitalWrite(EWgreen, LOW);   // make sure it's turned off first!
  digitalWrite(EWyellow, HIGH); // switch to yellow
  delay(2000);                  // for two seconds
  digitalWrite(EWyellow, LOW);  // important! even though it takes only a few microseconds to
  digitalWrite(EWred, HIGH);    // complete this task, the order is  vital, because if the
  // microcontroller freezes up, we don't want confusing signals,
}
