#include <SPI.h>
#include <Ethernet.h>

#include "DHT.h"
#define DHTPIN A0     // what digital pin we're connected to

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(192, 168, 100, 88);

EthernetClient client; 
//char server[] = "www.dweet.io";
IPAddress server(192, 168, 100, 3);

void setup() {

Serial.begin(9600);

delay(1000);
Ethernet.begin(mac, ip);
Serial.print("My IP address: ");
Serial.println(Ethernet.localIP());

delay(1000);
dht.begin();

}

void loop() {
  
if (client.available()) 
{
  char c = client.read();
  Serial.write(c);
}

httpRequest();
delay(5000);
 
}

void httpRequest() {

float t = dht.readTemperature();

if (client.connect(server, 8086)) {
    Serial.println("Connected successfully\n");

    // Print for debugging
    Serial.print("GET /?UIDPUCK=");
    Serial.print("1"); 
    Serial.print("&TEMP=");
    Serial.print(String(t));  
    Serial.println(" HTTP/1.1");
    Serial.print("Host: ");
    Serial.println(server);
    Serial.println("Connection: close");
    
    client.print("GET  /?UIDPUCK=");
    client.print("1"); 
    client.print("&TEMP="); 
    client.print(String(t)); 
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
    client.println();
    client.stop();
   
}
}
