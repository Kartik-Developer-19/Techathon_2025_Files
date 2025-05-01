#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

const char* ssid = "Home automation Device";
const char* pass = "12345678";

ESP8266WebServer server(80);

// Define the touch sensor pin
const int touchSensorPin = D1; // Change D1 to the appropriate pin number for your setup

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Home Automation</title>
    <style>
        *{
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }
        button{
            font-size: 1.3em;
            padding: 7px 15px;
            border-radius: 10px;
            border: none;
            font-weight: 600;
            color: white;
        }
        body, html{
            width: 100%;
            height: 100%;
        }
        h1{
            font-size: 3.5em;
            text-align: center;
            margin-bottom: 15px;
        }
        h2{
            text-align: center;
            font-size: 2.3em;
        }
        h3{
            font-size: 1.4em;
        }
        .hall, .bedroom{
            padding: 5px 10px;
            margin: 10px;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 20px;
            flex-direction: column;
        }
        .lights, .fan, .tv{
            padding: 5px 10px;
            margin: 10px;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 20px;
        }
        .on{
            background-color: rgb(30, 211, 30);
        }
        .off{
            background-color: rgb(255, 91, 91);
        }

        @media (max-width: 600px) {
            .hall, .bedroom, .lights, .fan, .tv{
                display: flex;
                align-items: center;
                justify-content: center;
                flex-direction: column;
            }
        }
        
    </style>
</head>
<body>
    <h1>Control Your Home</h1>

    <h2>Hall Controls</h2>
    <div class="hall">
        <div class="lights">
            <h3>Lights</h3>
            <button class="on" onclick="hallfunon()">Fun Mode</button>
            <button class="on" onclick="hallseriouson()">Serious Mode</button>
            <button class="on" onclick="hallrelaxon()">Relaxed Mode</button>
            <button class="off" onclick="hallbulboff()">Hall Light Off</button>
        </div>
        <div class="fan">
            <h3>Fan</h3>
            <button class="on" onclick="hallFanSlow()">Speed: Slow</button>
            <button class="on" onclick="hallFanMedium()">Speed: Medium</button>
            <button class="on" onclick="hallFanFast()">Speed: Fast</button>
            <button class="off" onclick="hallFanOff()">Fan OFF</button>
        </div>
        <div class="tv">
            <h3>TV</h3>
            <button class="on" onclick="tvOn()">TV ON</button>
            <button class="off" onclick="tvOff()">TV OFF</button>
        </div>
        
    </div>
    <h2>Bedroom Controls</h2>
    <div class="bedroom">
        <div class="lights">
            <h3>Lights</h3>
            <button class="on" onclick="bedfunon()">Fun Mode</button>
            <button class="on" onclick="bedseriouson()">Serious Mode</button>
            <button class="on" onclick="bedrelaxon()">Relaxed Mode</button>
            <button class="off" onclick="bedbulboff()">Bedroom Light Off</button>
        </div>
        <div class="fan">
            <h3>Fan</h3>
            <button class="on" onclick="bedFanSlow()">Speed: Slow</button>
            <button class="on" onclick="bedFanMedium()">Speed: Medium</button>
            <button class="on" onclick="bedFanFast()">Speed: Fast</button>
            <button class="off" onclick="bedFanOff()">Fan OFF</button>
        </div>
    </div>
    
    <script>
        // Hall 
            // Lights 
        function hallfunon(){
            fetch('/hallfunon')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function hallseriouson(){
            fetch('/hallseriouson')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function hallrelaxon(){
            fetch('/hallrelaxon')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function hallbulboff(){
            fetch('/hallbulboff')
                .then(response => response.text())
                .then(data => console.log(data))
        }
            // Fans 
        function hallFanSlow(){
            fetch('/hallFanSlow')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function hallFanMedium(){
            fetch('/hallFanMedium')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function hallFanFast(){
            fetch('/hallFanFast')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function hallFanOff(){
            fetch('/hallFanOff')
                .then(response => response.text())
                .then(data => console.log(data))
        }
            // TV
        function tvOn(){
            fetch('/tvOn')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function tvOff(){
            fetch('/tvOff')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        

        //Bedroom
            // Lights 
        function bedfunon(){
            fetch('/bedfunon')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function bedseriouson(){
            fetch('/bedseriouson')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function bedrelaxon(){
            fetch('/bedrelaxon')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function bedbulboff(){
            fetch('/bedbulboff')
                .then(response => response.text())
                .then(data => console.log(data))
        }
            // Fan
        function bedFanSlow(){
            fetch('/bedFanSlow')
                .then(response => response.text())
                .then(data => console.log(data))
        } 
        function bedFanMedium(){
            fetch('/bedFanMedium')
                .then(response => response.text())
                .then(data => console.log(data))
        } 
        function bedFanFast(){
            fetch('/bedFanFast')
                .then(response => response.text())
                .then(data => console.log(data))
        } 
        function bedFanOff(){
            fetch('/bedFanOff')
                .then(response => response.text())
                .then(data => console.log(data))
        } 
    </script>
</body>
</html>
)rawliteral";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(touchSensorPin, INPUT); // Set touch sensor pin as input

  // Set up NodeMCU as Access Point
  WiFi.softAP(ssid, pass);

  Serial.println("Waiting for a device to connect");
  while (WiFi.softAPgetStationNum() == 0) {
    Serial.print("...");
    delay(1000);
  }
  Serial.println("Device connected");
  Serial.println("\nAccess Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Server Code
  server.on("/", HTTP_GET, [](){
    server.send_P(200, "text/html", index_html);
  });

  // Hall Server Code
    // Lights
  server.on("/hallfunon", HTTP_GET, [](){
    Serial.println("Hall Fun Mode On");
    server.send(200, "text/plain", "Hall Bulb ON");
  });
  server.on("/hallseriouson", HTTP_GET, [](){
    Serial.println("Hall Serious Mode On");
    server.send(200, "text/plain", "Hall Bulb ON");
  });
  server.on("/hallrelaxon", HTTP_GET, [](){
    Serial.println("Hall Relaxed Mode On");
    server.send(200, "text/plain", "Hall Bulb ON");
  });
  server.on("/hallbulboff", HTTP_GET, [](){
    Serial.println("Hall Lights OFF");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });
    // Fan
  server.on("/hallFanSlow", HTTP_GET, [](){
    Serial.println("Hall Fan Slow");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });
  server.on("/hallFanMedium", HTTP_GET, [](){
    Serial.println("Hall Fan Medium");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });
  server.on("/hallFanFast", HTTP_GET, [](){
    Serial.println("Hall Fan Fast");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });
  server.on("/hallFanOff", HTTP_GET, [](){
    Serial.println("Hall Fan Off");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });
    // TV
  server.on("/tvOn", HTTP_GET, [](){
    Serial.println("TV ON");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });
  server.on("/tvOff", HTTP_GET, [](){
    Serial.println("TV OFF");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });
  

  // Bedroom Server Code
    // Lights
  server.on("/bedfunon", HTTP_GET, [](){
    Serial.println("Bedroom Fun Mode On");
    server.send(200, "text/plain", "Hall Bulb ON");
  });
  server.on("/bedseriouson", HTTP_GET, [](){
    Serial.println("Bedroom Serious Mode On");
    server.send(200, "text/plain", "Hall Bulb ON");
  });
  server.on("/bedrelaxon", HTTP_GET, [](){
    Serial.println("Bedroom Relaxed Mode On");
    server.send(200, "text/plain", "Hall Bulb ON");
  });
  server.on("/bedbulboff", HTTP_GET, [](){
    Serial.println("Bedroom Lights OFF");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });
    // Fan
  server.on("/bedFanSlow", HTTP_GET, [](){
    Serial.println("Bedroom Fan Slow");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });
  server.on("/bedFanMedium", HTTP_GET, [](){
    Serial.println("Bedroom Fan Medium");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });
  server.on("/bedFanFast", HTTP_GET, [](){
    Serial.println("Bedroom Fan Fast");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });
  server.on("/bedFanOff", HTTP_GET, [](){
    Serial.println("Bedroom Fan Off");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

  // Check for touch sensor input
  if (digitalRead(touchSensorPin) == HIGH) {
    Serial.println("Touch detected! Sending notification...");
    
    // Send notification to a connected device
    WiFiClient client;
    const char* notificationServer = "192.168.4.1"; // Replace with your notification server URL
    if (client.connect(notificationServer, 80)) {
      client.print(String("GET /notify?message=Touch%20detected HTTP/1.1\r\n") +
                   "Host: " + notificationServer + "\r\n" +
                   "Connection: close\r\n\r\n");
      Serial.println("Notification sent!");
    } else {
      Serial.println("Failed to connect to notification server.");
    }
    
    delay(1000); // Debounce delay
  }
}