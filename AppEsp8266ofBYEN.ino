 
#include <ESP8266WiFi.h>

#include <Wire.h> 

#include <LiquidCrystal_I2C.h>



 

LiquidCrystal_I2C lcd(0x3f, 16, 02);

 

const char* ssid = "vivo eat";       // ชื่อ SSID Wifi

const char* password = "adaradar1";         // รหัส Password Wifi

 

WiFiServer server(80);

 

  int val1 = 0;

  int val2 = 0;

  int val3 = 0;

  int val4 = 0;

 

void setup() {

  Serial.begin(9600);

  delay(10);

 

  lcd.begin();

  lcd.backlight();

 

  lcd.print("Server Off..");

  lcd.setCursor(0, 1);

  


  pinMode(D5, OUTPUT);

  pinMode(D6, OUTPUT);

  pinMode(D7, OUTPUT);

  pinMode(D9, OUTPUT);
  
  digitalWrite(D5, 0);

  digitalWrite(D6, 0);

  digitalWrite(D7, 0);
  
  digitalWrite(D9, 0);
  

  // Connect to WiFi network

  Serial.println();

  Serial.println();

  Serial.print("Connecting to ");

  Serial.println(ssid);

  

  WiFi.begin(ssid, password);

  

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.println("WiFi connected");

  

  // Start the server

  server.begin();

  Serial.println("Server started");

  lcd.clear();

  lcd.print("Server On IP :");

  lcd.setCursor(0, 1);

 

  // Print the IP address

  Serial.println(WiFi.localIP());

  lcd.print(WiFi.localIP());      // แสดง IP ผ่านจอ

  lcd.setCursor(0, 2);

}

 

void loop() {

  // Check if a client has connected

  WiFiClient client = server.available();

  if (!client) {

    return;

  }

  

  // Wait until the client sends some data

  Serial.println("new client");

  while(!client.available()){

    delay(1);

  }

  

  // Read the first line of the request

  String req = client.readStringUntil('\r');

  Serial.println(req);

  client.flush();

  

  // Match the request

  // ch1

  if (req.indexOf("/?ch1=0") != -1)

    val1 = 0;

  else if (req.indexOf("/?ch1=1") != -1)

    val1 = 1;

  // ch2

  else if (req.indexOf("/?ch2=0") != -1)

    val2 = 0;

  else if (req.indexOf("/?ch2=1") != -1)

    val2 = 1;

  // ch3

  else if (req.indexOf("/?ch3=0") != -1)

    val3 = 0;

  else if (req.indexOf("/?ch3=1") != -1)

    val3 = 1;

  // ch4

  else if (req.indexOf("/?ch4=0") != -1)

    val4 = 0;

  else if (req.indexOf("/?ch4=1") != -1)

    val4 = 1;

  else {

    Serial.println("invalid request");

    client.stop();

    return;

  }

 

  // Set GPIO2 according to the request

   digitalWrite(D5, val1);

  digitalWrite(D6, val2);

  digitalWrite(D7, val3);

  digitalWrite(D9, val4);
  

  client.flush();

 

  // Prepare the response

  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n\r\n\r\nGPIO is now ";

  s += "\n";

 

  client.print(s);

  delay(1);

  Serial.println("Client disonnected");

}
