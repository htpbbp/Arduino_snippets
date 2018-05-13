#include <SoftwareSerial.h>

SoftwareSerial wifiSerial(5, 6);      // RX, TX for ESP8266

bool DEBUG = true;   //show more logs
int responseTime = 10; //communication timeout

void setup()
{
  Serial.begin(115200);
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  wifiSerial.begin(115200);
  while (!wifiSerial) 
  {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  sendToWifi("Greetings from uno",responseTime,DEBUG); // configure as access point
  sendToUno("Wifi connection is running!",responseTime,DEBUG);
}


void loop()
{

  if(wifiSerial.available()>0)
  {
    String message = readWifiSerialMessage();

    Serial.println("#####");
    Serial.println(message);
    Serial.println("#####");

    if(find(message,"inline"))
    {
      String result = sendToWifi("inline received",responseTime,DEBUG);
      sendToUno("in-line-received",responseTime,DEBUG);
      sendToWifi("inline received",responseTime,DEBUG);
    }
      
    if(find(message,"outline"))
    {
      Serial.println("outline received");
       String result = sendToWifi(message.substring(8,message.length()),responseTime,DEBUG);
      if(find(result,"OK"))
      {
        sendData("\n"+result);
      }
      else
      {
        sendData("\nErrRead");     
      }          
    }
    delay(responseTime);
  }
}


void sendData(String str)
{
  String len="";
  len+=str.length();
  sendToWifi("AT+CIPSEND=0,"+len,responseTime,DEBUG);
  delay(100);
  sendToWifi(str,responseTime,DEBUG);
  delay(100);
  sendToWifi("AT+CIPCLOSE=5",responseTime,DEBUG);
}


boolean find(String string, String value)
{
  if(string.indexOf(value)>=0)
    return true;
  return false;
}


String  readSerialMessage()
{
  char value[100]; 
  int index_count =0;
  while(Serial.available()>0)
  {
    value[index_count]=Serial.read();
    index_count++;
    value[index_count] = '\0'; // Null terminate the string
  }
  String str(value);
  str.trim();
  return str;
}


String  readWifiSerialMessage()
{
  char value[100]; 
  int index_count =0;
  while(wifiSerial.available()>0)
  {
    value[index_count]=wifiSerial.read();
    index_count++;
    value[index_count] = '\0'; // Null terminate the string
  }
  String str(value);
  str.trim();
  return str;
}


String sendToWifi(String command, const int timeout, boolean debug)
{
  String response = "";
  wifiSerial.println(command); // send the read character to the esp8266
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(wifiSerial.available())
    {
    // The esp has data so display its output to the serial window 
    char c = wifiSerial.read(); // read the next character.
    response+=c;
    }  
  }
  if(debug)
  {
    Serial.println(response);
  }
  return response;
}

String sendToUno(String command, const int timeout, boolean debug)
{
  String response = "";
  Serial.println(command); // send the read character to the esp8266
  long int time = millis();
  while( (time+timeout) > millis())
  {
    while(Serial.available())
    {
      // The esp has data so display its output to the serial window 
      char c = Serial.read(); // read the next character.
      response+=c;
    }  
  }
  if(debug)
  {
    Serial.println(response);
  }
  return response;
}



