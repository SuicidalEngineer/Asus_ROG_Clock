#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN A0 // DHT11PIN olarak Dijital 2"yi belirliyoruz.
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include<Wire.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
DS3231  rtc(SDA, SCL);

dht11 DHT11;

 int redPin = 11;   // Red LED,  connected to digital pin 11  
 int grnPin = 10;  // Green LED, connected to digital pin 10  
 int bluPin = 9;  // Blue LED, connected to digital pin 9  
  
 void setup(){     
    
  Serial.begin(9600);   // Opening serial connection at 9600bps   
  Serial.println("Humidity and temperature");   // Printing Serial Monitor header  
  delay(1000);   // Wait 1 second before printing data to Serial Monitor  
    
  pinMode(redPin, OUTPUT);   // Sets the pins as output for RGB LED  
  pinMode(grnPin, OUTPUT);  
  pinMode(bluPin, OUTPUT);  
  rtc.begin();
  lcd.begin(16,2);
    
  }  
    
 void loop(){     

   lcd.setCursor(2,0);
   lcd.print(rtc.getTimeStr());
   lcd.print(" ");
   lcd.print(DHT11.temperature);
   lcd.print((char)223);
   lcd.print("C");
   lcd.setCursor(1,1);
   lcd.print(rtc.getDateStr());
   lcd.print(" ");
   lcd.print(rtc.getDOWStr(FORMAT_SHORT));

   Serial.println();
   int chk = DHT11.read(DHT11PIN);
        
   Serial.print("Sicaklik (Celcius): ");
   Serial.println((float)DHT11.temperature);
 
    
  // Setting the colours of the RGB LED based on temperature,  
 // Colour is shown for 0.1s before checking temperature again.    
   
  if((DHT11.temperature < 50) && (DHT11.temperature >= 40))  
  {  
  digitalWrite(redPin, HIGH); 
  digitalWrite(bluPin, LOW);
  digitalWrite(grnPin, LOW);   
  }  

  if((DHT11.temperature < 40) && (DHT11.temperature >= 30)) 
  {
   digitalWrite(grnPin, HIGH);  // YELLOW  
   digitalWrite(redPin, HIGH);
   digitalWrite(bluPin, LOW);  
  }
  if((DHT11.temperature < 30) && (DHT11.temperature >= 20)) 
  {  
   digitalWrite(grnPin, HIGH);  // GREEN
   digitalWrite(redPin, LOW); 
   digitalWrite(bluPin, LOW);     
  }
  
  if((DHT11.temperature >= 10) && (DHT11.temperature < 20))  
  {  
   digitalWrite(grnPin, HIGH);  // aqua  
   digitalWrite(bluPin, HIGH); 
   digitalWrite(redPin, LOW);   
  }  
  
  if((DHT11.temperature < 10) && (DHT11.temperature >= 0))  
  {  
   digitalWrite(grnPin, HIGH);  // WHITE  
   digitalWrite(bluPin, HIGH);  
   digitalWrite(redPin, HIGH);    
  }  

  delay(1000);   // Sensor shouldn't be read too frequently so delay of 1s  
 }
