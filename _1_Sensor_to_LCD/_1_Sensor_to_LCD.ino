// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"
#include <LiquidCrystal.h>

#define DHTPIN 8     // what pin we're connected to

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.print("Temp:  Humidity:");

  dht.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  lcd.setCursor(0, 1);    
  if (isnan(t) || isnan(h)) {
    lcd.print("Failed to read from DHT");
  } else {
    lcd.print(t);
    lcd.print("C");
    lcd.setCursor(7, 1);
    lcd.print(h);
    lcd.print("%");
  }
}
