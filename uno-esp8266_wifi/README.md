# Arduino UNO receives messages from ESP8266 Webserver

RX/TX connect between Arduinio UNO and ESP8266

## esp8266-uno_wifi.ino
- the ESP8266 firmware
  call an URL on the ESP8266 webserver will write via TX to RX on UNO

## uno-esp8266_wifi.ino
- the UNO firmware
  will listening on RX for defined keywords (can call a function)
