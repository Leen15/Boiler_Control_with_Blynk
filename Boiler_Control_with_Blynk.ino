#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TimeLib.h>
int CALDAIA_STATUS = D2;
int BLOCCO_CALDAIA = D3;
OneWire oneWire(D4);
DallasTemperature sensors(&oneWire);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

BlynkTimer timer;

WidgetLED caldaia_status_led(V7);

WidgetLED blocco_caldaia_led(V8);
byte notification_sent = false;

void sendTemps()
{
  sensors.requestTemperatures(); // Polls the sensors

  float boiler = sensors.getTempCByIndex(0); // Gets first probe on wire in lieu of by address
  Serial.print(F("BOILER: "));
  Serial.print(boiler);
  float caldaia = sensors.getTempCByIndex(1); // Gets first probe on wire in lieu of by address
  Serial.print(F(" CALDAIA: "));
  Serial.print(caldaia);
  float riscaldamento = sensors.getTempCByIndex(2); // Gets first probe on wire in lieu of by address
  Serial.print(F(" RISCALD: "));
  Serial.print(riscaldamento);
  int caldaia_status = digitalRead(CALDAIA_STATUS);
  int blocco_caldaia = digitalRead(BLOCCO_CALDAIA);
  Serial.print(F(" STATUS: "));
  Serial.print(caldaia_status);
  Serial.print(F(" BLOCCO: "));
  Serial.print(blocco_caldaia);
  Serial.println("");
  
  Blynk.virtualWrite(4, boiler);
  Blynk.virtualWrite(5, caldaia);
  Blynk.virtualWrite(6, riscaldamento);

  if (caldaia_status == 0)
  {
    caldaia_status_led.on();    
  }
  else
  {
    caldaia_status_led.off();
  }
  
  if (blocco_caldaia == 0)
  {
    blocco_caldaia_led.on();
    if (!notification_sent)
    {
      Blynk.notify(F("ATTENZIONE! CALDAIA IN BLOCCO!"));  
      notification_sent = true;
    }
    
  }
  else
  {
    blocco_caldaia_led.off();
    notification_sent = false;
  }
  //Blynk.virtualWrite(7, caldaia_status);
  //Blynk.virtualWrite(8 , blocco_caldaia);
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  
  pinMode(CALDAIA_STATUS, INPUT_PULLUP); //Set the LED (D8) as an output
  pinMode(BLOCCO_CALDAIA, INPUT_PULLUP); //Set the LED (D8) as an output

  sensors.begin();

  timer.setInterval(1000L, sendTemps); // Temperature sensor polling interval (5000L = 5 seconds)
}


void loop()
{
  Blynk.run();
  timer.run();
}
