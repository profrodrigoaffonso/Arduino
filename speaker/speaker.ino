/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

#define c 2000
int valor = 0;
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(9, OUTPUT);
}

void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{ 
    //digitalWrite(ledPin, HIGH);  
    //use led to visualize the notes being played
    
    int x;   
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++)   
    {    
        digitalWrite(speakerPin,HIGH);
        delayMicroseconds(delayAmount);
        digitalWrite(speakerPin,LOW);
        delayMicroseconds(delayAmount);
    }    
    
    //digitalWrite(ledPin, LOW);
    //set led back to low
    
    delay(20);
    //a little delay to make all notes sound separate
}  

// the loop function runs over and over again forever
void loop() {
  valor = analogRead(0)*2;
  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println(valor);
  beep(9, c, 10);
  //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  //digitalWrite(9, LOW);
  delay(valor);                       // wait for a second
}
