# Boiler Control with Blynk and DS18B20
This sketch allows to control boiler with 3 DS18B20 sensors and 2 status LEDs.
This sketch works with a Wemos D1 Mini.
   

# Configuration

In the first part of the sketch you can find the configuration:
```
CALDAIA_STATUS= D2; -> Boiler status (ON/OFF)
BLOCCO_CALDAIA = D3; -> Boiler Blocked (ON/OFF) 
oneWire = D4; -> BUS for DS18B20
auth = ""; BLYNK Auth token 
ssid = ""; WIFI ssid
pass = ""; WIFI password
```
Keep in mind that on the DS18B20 bus you have to put a 4K7 resistor between signal wire and 3v3 (DO NOT CONNECT TO 5V).