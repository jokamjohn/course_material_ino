#include <SoftwareSerial.h>;

SoftwareSerial mySerial(7, 8);

String a = "1";
String b = "0";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  mySerial.begin(9600);

}

void ShowSerialData(){
 while(mySerial.available()!=0)
   Serial.write(mySerial.read());
}

void sendTolightStatus(String a, String b){
  
  mySerial.println("AT+CGATT?");   //Attach or Detach from GPRS Service (Result  1 = Attach , 2 = Detached )
  delay(500); 
  ShowSerialData();
 
  //mySerial.println("AT+CIPMODE=0");
  //delay(300); 
  //ShowSerialData();
  
  mySerial.println("AT+CIPSHUT");  //Close TCP Connection
  delay(1000); 
  ShowSerialData();
  
  mySerial.println("AT+CIPSTATUS");  //Close TCP Connection
  delay(1000); 
  ShowSerialData();
 
  mySerial.println("AT+CIPMUX=0");
  delay(1000); 
  ShowSerialData();
  
//  mySerial.println("AT+CSTT=\"internet\",\"\",\"\"");//start task and setting the APN,
//  delay(2000); 
//  ShowSerialData();
 
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"internet\"");//setting the APN, the second need you fill in your local apn server
  delay(1000); 
  ShowSerialData();
  
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(5000); 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000); 
  ShowSerialData();
 
//  mySerial.println("AT+CIPSPRT=0");
//  delay(3000); 
//  ShowSerialData();
 
  mySerial.println("AT+CIPSTART=\"TCP\",\"www.powerlog.elfbay.com\",\"80\"");//start up the connection
  delay(5000); 
  ShowSerialData();
    delay(5000);
     ShowSerialData();
     
  Serial.println();
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(5000);
  ShowSerialData();
  


  mySerial.print("PUT /index.php/update_light?");//here is the feed you apply from pachube
  delay(1000);
  ShowSerialData();
  
  mySerial.print("light_id=");   //DATA feed name
  mySerial.print(a);   //DATA to send
  delay(50);
  ShowSerialData();
  
  mySerial.print("&status=");   //DATA feed name
  mySerial.print(b);   //DATA to send
  delay(50);
  ShowSerialData();
  
  mySerial.print(" HTTP/1.1\r\n");
  delay(1000);
  ShowSerialData();
  
  mySerial.print("Host: www.powerlog.elfbay.com\r\n");
  delay(1000);
  ShowSerialData();
  delay(2000);
    ShowSerialData();
    
  //mySerial.print("Connection: keep-alive");  //working
  mySerial.print("Connection: close");         //working as well
  mySerial.print("\r\n");
  mySerial.print("\r\n");
  //mySerial.println();
  delay(1000);
  ShowSerialData();


  //mySerial.println((char)26);//sending
  mySerial.write(0x1A);
  delay(1000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println(); 
  ShowSerialData();
 
  mySerial.println("AT+CIPCLOSE");//close the connection
  delay(100);
  ShowSerialData();
  
  mySerial.println("AT+CIPSHUT=0");
  delay(100); 
  ShowSerialData();

}

  

void loop() {
  // put your main code here, to run repeatedly:
    
    sendTolightStatus(a, b);
    
  
}
