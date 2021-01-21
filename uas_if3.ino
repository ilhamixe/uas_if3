#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <DHT.h>

#include <BlynkSimpleEsp8266.h>
const int triggerPin = D2;
const int echo = D1;
#define DHTPIN D4          // D4 pin
#define DHTTYPE DHT22
long duration;
int distance;
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


char auth[] = "w-wjTFZ0H40IORvg-aVNicl45zpCkLnT";
char ssid[] = "kania1";
char pass[] = "kania123";
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V7, h);
  Blynk.virtualWrite(V6, t);
   Serial.println(t);
}


void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(triggerPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo, INPUT); // Sets the echoPin as an Input
dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}
void loop(){
  Blynk.run();
  timer.run();
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(100);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echo, HIGH);
  distance= duration*0.034/2;
  if (distance <= 10){
    Blynk.notify("ada orang !!!");
    Blynk.virtualWrite(V5,"1");
  }
  Serial.print("Distance: ");
  Serial.println(distance);
}
