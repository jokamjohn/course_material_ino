#include <SoftwareSerial.h>
SoftwareSerial SIM900(6, 7); // configure software serial port

String holder = "";
int ledPin = 13;
 
void setup()
{
  pinMode(ledPin, OUTPUT);
  SIM900.begin(9600);   
  Serial.begin(9600);  
  SIM900power();  
  //delay(20000);  // give time to log on to network. 
}

void toSerial()
{
  while(SIM900.available()!=0)
  {
    Serial.write(SIM900.read());
  }
}
 
 
void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
}
 
void receiveCall()
{
  while(SIM900.available() >0)
  {
    char incoming_char=SIM900.read(); //Get the character from the cellular serial port.
    Serial.print(incoming_char); //Print the incoming character to the terminal.
    
    //holder = holder + incoming_char;
  }
  
  //holder = "";
  
}
 
void loop()
{
  if(SIM900.available() >0)
  {
    char incoming_char=SIM900.read(); //Get the character from the cellular serial port.
    Serial.print(incoming_char); //Print the incoming character to the terminal.
    
    //holder = holder + incoming_char;
  }  
  
}
