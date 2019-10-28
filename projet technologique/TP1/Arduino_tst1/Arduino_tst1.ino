
// these constants won't change:
const int ledPin = 13;      // LED connected to digital pin 13


// these variables will change:
int sensorValue = 0;      // variable to store the value read from the analog pin
  
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:(debug tool)
  // Serial.begin(9600); ( debug tool)
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  sensorValue = analogRead(A0);
  // print out the value you read: (debug tool)
  // Serial.println(sensorValue); ( debug tool)

  if (sensorValue > 300)
  {
    digitalWrite(ledPin, HIGH);   // turn the LED on 
  }
  else 
  {
    digitalWrite(ledPin, LOW);   // turn the LED off
  }
  
  delay(1);        // delay in between reads for stability
}
