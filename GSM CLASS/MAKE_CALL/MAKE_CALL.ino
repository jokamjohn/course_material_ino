#include <SoftwareSerial.h>
SoftwareSerial SIM900(6, 7); // configure software serial port
 
void setup()
{
  SIM900.begin(9600);   
  Serial.begin(9600);  
  SIM900power();  
  delay(20000);  // give time to log on to network. 
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
 
void callSomeone()
{
  SIM900.println("ATD + +256702143973;"); // dial US (212) 8675309
  delay(2000);
  SIM900.println();
  toSerial();
  
  delay(30000);        // wait for 30 seconds...
  
  
  SIM900.println("ATH");   // hang up
  delay(2000);
  toSerial();
  
}
 
void loop()
{
  callSomeone(); // call someone
  SIM900power();   // power off GSM shield
  do {} while (1); // do nothing
}
