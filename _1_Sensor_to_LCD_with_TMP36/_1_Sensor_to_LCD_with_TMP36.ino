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

//TMP36 Pin Variables
int temperaturePin = 0; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade 
                        //(500 mV offset) to make negative temperatures an option

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  dht.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  float temperature = getVoltage(temperaturePin);  //getting the voltage reading from the temperature sensor
  temperature = (temperature - .5) * 100;          //converting from 10 mv per degree wit 500 mV offset
                                                   //to degrees ((volatge - 500mV) times 100)
  lcd.clear();
  lcd.print("Temp:  Humidity:");
    
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  lcd.setCursor(0, 1);    
  if (isnan(t) || isnan(h)) {
    lcd.print("Failed to read from DHT");
  } else {
    lcd.print(t, 1);
    lcd.print("C");
    lcd.setCursor(7, 1);
    lcd.print(h, 1);
    lcd.print("%");
    delay(2000);
    lcd.clear();
    lcd.print("TMP36 Temp:");
    lcd.setCursor(0, 1);
    lcd.print(temperature, 1);
    delay(1500);
  }
}

/*
 * getVoltage() - returns the voltage on the analog input defined by
 * pin
 */
float getVoltage(int pin){
 return (analogRead(pin) * .004882814); //converting from a 0 to 1023 digital range
                                        // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}
