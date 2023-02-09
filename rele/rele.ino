#include <SPI.h>
#include <Ethernet.h>

#define a 880
#define b 440
  
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 10, 0, 0, 109 }; // IP Fixo para o Arduino
     
EthernetServer server(80);


  
String readString;
int Pin = 7;
int spkPin = 9;
  
void setup(){
  
  pinMode(Pin, OUTPUT);
  digitalWrite(Pin, HIGH);
  Ethernet.begin(mac, ip);
  server.begin();
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
  
void loop(){
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
  
        if (readString.length() < 100) {
          readString += c;             
        }
 
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type: text/javascript");
          client.println("Access-Control-Allow-Origin: *");
          // any other header
          client.println(); //mandatory blank line
         
          // O módulo relê funciona ao contrário dos leds: LOW -> Liga, HIGH -> Desliga
          if(readString.indexOf("?ledon") > 0)
          {
           // beep(9, a, 10000);
            digitalWrite(Pin, LOW);
          }
  
          if(readString.indexOf("?ledoff") > 0)
          {
            digitalWrite(Pin, HIGH);
           // beep(9, b, 1000);
          }        
          
          client.stop();
          readString="";    
        }
      }
    }
  }
}
