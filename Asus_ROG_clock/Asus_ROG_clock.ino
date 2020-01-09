#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN A0 // DHT11PIN olarak Dijital 2"yi belirliyoruz.
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include<Wire.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
DS3231  rtc(SDA, SCL);

dht11 DHT11;

 int redPin = 11; 
 int grnPin = 10; 
 int bluPin = 9;
  
 void setup(){     
    
  Serial.begin(9600); 
  Serial.println("Temperature");
  delay(1000);   // Printing Serial Monitor header    
    
  pinMode(redPin, OUTPUT);    // Printing Serial Monitor header    
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

   
  if((DHT11.temperature < 50) && (DHT11.temperature >= 40))  
  {  
  digitalWrite(redPin, HIGH); 
  digitalWrite(bluPin, LOW);
  digitalWrite(grnPin, LOW);   
  }  

  if((DHT11.temperature < 40) && (DHT11.temperature >= 30)) 
  {
   digitalWrite(grnPin, HIGH);  
   digitalWrite(redPin, HIGH);
   digitalWrite(bluPin, LOW);  
  }
  if((DHT11.temperature < 30) && (DHT11.temperature >= 20)) 
  {  
   digitalWrite(grnPin, HIGH);
   digitalWrite(redPin, LOW); 
   digitalWrite(bluPin, LOW);     
  }
  
  if((DHT11.temperature >= 10) && (DHT11.temperature < 20))  
  {  
   digitalWrite(grnPin, HIGH); 
   digitalWrite(bluPin, HIGH); 
   digitalWrite(redPin, LOW);   
  }  
  
  if((DHT11.temperature < 10) && (DHT11.temperature >= 0))  
  {  
   digitalWrite(grnPin, HIGH);  
   digitalWrite(bluPin, HIGH);  
   digitalWrite(redPin, HIGH);    
  }  

  delay(1000);  
 }
