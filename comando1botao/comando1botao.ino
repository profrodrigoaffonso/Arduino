/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/DigitalReadSerial/
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;
int onoff = 0;
int rele = 13;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(rele, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  if(buttonState == 1 && onoff == 0){
    onoff = 1;
    Serial.println("ligado");
    delay(500);
  }
  buttonState = digitalRead(pushButton);
  if(buttonState == 1 && onoff == 1){
    onoff = 0;
    Serial.println("desligado");    
    delay(500);
  }
  Serial.println(onoff);

  if(onoff == 1){
    digitalWrite(rele, LOW);
  } else {
    digitalWrite(rele, HIGH);
  }

  delay(1);  // delay in between reads for stability
}
