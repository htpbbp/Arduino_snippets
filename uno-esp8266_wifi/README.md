# Arduino UNO receives messages from ESP8266 Webserver

RX/TX connect between Arduinio UNO and ESP8266

intention was to use it as a 2nd alarming path but buffer isn't stable enough

## esp8266-uno_wifi.ino
- the ESP8266 firmware
- ESP8266 is connected to WiFi
- call an URL on the ESP8266 webserver will write via TX to RX on UNO

## uno-esp8266_wifi.ino
- the UNO firmware
- will listening on RX for defined keywords (can call a function)
