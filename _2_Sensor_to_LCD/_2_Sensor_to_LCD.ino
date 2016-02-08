// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"
#include <LiquidCrystal.h>

#define DHTPIN1 8     // what pin we're connected to
#define DHTPIN2 9     // what pin we're connected to

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // set up DHT22 sensor;
  dht1.begin();
  dht2.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  
  lcd.clear();
  lcd.print("Temp:  Humidity:");    
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  lcd.setCursor(0, 1);    
  if (isnan(t1) || isnan(h1)) {
    lcd.print("Failed to read from DHT");
  } else {
    lcd.print(t1, 1);
    lcd.print("C");
    lcd.setCursor(7, 1);
    lcd.print(h1, 1);
    lcd.print("%");
    lcd.setCursor(14, 1);
    lcd.print("S1");
    delay(2000);
  }    
  lcd.clear();
  lcd.print("Temp:  Humidity:");    
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  lcd.setCursor(0, 1);    
  if (isnan(t2) || isnan(h2)) {
    lcd.print("Failed to read from DHT");
  } else {
    lcd.print(t2, 1);
    lcd.print("C");
    lcd.setCursor(7, 1);
    lcd.print(h2, 1);
    lcd.print("%");
    lcd.setCursor(14, 1);
    lcd.print("S2");
    delay(1100);
  }  
}
