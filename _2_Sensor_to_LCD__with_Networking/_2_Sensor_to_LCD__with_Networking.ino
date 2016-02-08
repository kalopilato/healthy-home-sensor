// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"
#include <LiquidCrystal.h>
#include <Ethernet.h>
#include <SPI.h>

#define DHTPIN1 8     // what pin we're connected to
#define DHTPIN2 9     // what pin we're connected to

#define DHTTYPE DHT22   // DHT 22  (AM2302)

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// assign MAC address
// TODO: generate and record a meaningful MAC address (replace hard coded)
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,178,50);

// Initialize the Ethernet server library
// (port 80 is default for HTTP):
EthernetServer server(80);

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
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
  
  // LCD Stuff
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
  
  // Ethernet Stuff
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
	  client.println("Refresh: 3");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          
          // output temp/humidity data
          client.print("<h2>Sensor 1</h2>");
          client.print("Temperature: ");
          client.print(t1);
          client.println("<br />");  
          client.print("Humidity: ");
          client.print(h1);
          client.println("<br />");  
          
          client.print("<h2>Sensor 2</h2>");
          client.print("Temperature: ");
          client.print(t2);
          client.println("<br />");  
          client.print("Humidity: ");
          client.print(h2);
          client.println("<br />");  
          
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
  
}
