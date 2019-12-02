

#include <ESP8266WiFi.h>



int sensPin= 0;
const char* ssid     = "AndroidAP516E";                 // SSID of local network
const char* password = "gjmu0001";                    // Password on network
String APIKEY = "12eecf0262f095b02b9d693ff64c7140";                                 
String CityID = "Raghogarh,in";                                 //Your City ID


WiFiClient client;
char servername[]="api.openweathermap.org";              // remote server we will connect to
String result;

int  counter = 60;                                      

String weatherDescription ="";
String weatherLocation = "";
String Country;
float Temperature;
float Humidity;
float Pressure;

void getWeatherData()                                //client function to send/receive GET request data.
{
  if (client.connect(servername, 80))   
          {                                         //starts client connection, checks for connection
          client.println("GET /data/2.5/weather?q="+CityID+"&units=metric&appid="+APIKEY);
          client.println("Host: api.openweathermap.org");
          client.println("User-Agent: ArduinoWiFi/1.1");
          client.println("Connection: close");
          client.println();
          } 
  else {
         Serial.println("connection failed");        //error message if no client connect
          Serial.println();
       }

  while(client.connected() && !client.available()) 
  delay(1);                                          //waits for data
  while (client.connected() || client.available())    
       {                                             //connected or data available
         char c = client.read();                     //gets byte from ethernet buffer
         result = result+c;
       }
//Serial.print(result);
client.stop();                                      //stop client
//result.replace('[', ' ');
//result.replace(']', ' ');
//Serial.println(result);
//char jsonArray [result.length()+1];
//result.toCharArray(jsonArray,sizeof(jsonArray));
//jsonArray[result.length() + 1] = '\0';
//StaticJsonBuffer<1024> json_buf;
//JsonObject &root = json_buf.parseObject(jsonArray);
//
//if (!root.success())
//  {
//    Serial.println("parseObject() failed");
//  }
//
//String location = root["name"];
//String country = root["sys"]["country"];
//float temperature = root["main"]["temp"];
//float humidity = root["main"]["humidity"];
//String weather = root["weather"]["main"];
//String description = root["weather"]["description"];
//float pressure = root["main"]["pressure"];
//weatherDescription = description;
//weatherLocation = location;
//Country = country;
//Temperature = temperature;
//Humidity = humidity;
//Pressure = pressure;

}




void setup() {
  // put your setup code here, to run once:
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  
             while (WiFi.status() != WL_CONNECTED) 
            {
            delay(500);
                Serial.println("Connecting to network...");
            }
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  while(WiFi.status() == WL_CONNECTED){

    Serial.println("\n\n");
    int sensorVal= analogRead(sensPin);
  double percentage = 100.00 - ((sensorVal-550) / (double)(1024-550)*100.00);
  Serial.println("Moisture of the soil is:");
  Serial.print(percentage);
  Serial.println("%");
  Serial.println("Analog reading is is:");
  Serial.print(sensorVal);
  Serial.println("%");

  if(counter == 60)                                 //Get new data every 10 minutes
    {
      counter = 0;
      Serial.println(result);
      delay(1000);
      getWeatherData();
      
      
    }else
    {
      String s="yes", t="yes";
      counter++;
      if(s==t){
        Serial.println("Works");
      }
      else{
        Serial.println("Does not Work");
      }
      Serial.println(result);
      delay(5000);
    }
  delay(1000);
  }
}
