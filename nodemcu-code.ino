#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

const char* ssid = "Home automation Device";
const char* pass = "12345678";

ESP8266WebServer server(80);

int dhtPin = 12;

DHT dht(dhtPin, DHT11);

AsyncWebServer ws(80);

String temperature() {
  float t = dht.readTemperature();

  if(isnan(t)){
    return "--";
  } else {
    return String(t);
  }
}
String humidity() {
  float t = dht.readHumidity();

  if(isnan(t)){
    return "--";
  } else {
    return String(t);
  }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Home Automation</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }

        button {
            font-size: 1.3em;
            padding: 7px 15px;
            border-radius: 10px;
            border: none;
            font-weight: 600;
            color: white;
            background-color: burlywood;
        }

        body,
        html {
            width: 100%;
            height: 100%;
        }

        h1 {
            font-size: 3.5em;
            text-align: center;
            margin-bottom: 15px;
        }

        h2 {
            text-align: center;
            font-size: 2.3em;
        }

        h3 {
            font-size: 1.4em;
        }

        .btn-cont {
            display: flex;
            justify-content: center;
            gap: 10px;
            align-items: center;
        }

        .start h1 {
            font-size: 2em;
            margin-top: 20px;
        }

        .hall,
        .bedroom,
        .kitchen {
            padding: 5px 10px;
            margin: 10px;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 20px;
            flex-direction: column;
            display: none;
        }

        .lights,
        .normalLights,
        .fan,
        .tv {
            padding: 5px 10px;
            margin: 10px;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 20px;
        }

        .on {
            background-color: rgb(30, 211, 30);
        }

        .off {
            background-color: rgb(255, 91, 91);
        }

        .btn-cont .ambience {
            background-color: rgb(248, 165, 57);
        }

        .normalLights {
            display: none;
        }

        @media (max-width: 600px) {

            .hall,
            .bedroom,
            .lights,
            .normalLights,
            .fan,
            .tv {
                display: flex;
                align-items: center;
                justify-content: center;
                flex-direction: column;
            }

            .hall,
            .bedroom,
            .kitchen {
                display: none;
            }
        }
    </style>
</head>

<body>
    <h1>Control Your Home</h1>
    <div class="temperature-humidity">
        <h2 class="temp-cont">
            <span>temperature : </span>
            <span id="temp">%TEMPERATURE%</span>
        </h2>
        <h2 class="hum-cont">
            <span>humidity : </span>
            <span id="temp">%HUMIDITY%</span>
        </h2>
    </div>
    <div class="btn-cont">
        <button class="hall-btn">Hall</button>
        <button class="bed-btn">Bedroom</button>
        <button class="kitchen-btn">Kitchen</button>
    </div>
    <div class="start">
        <h1>Choose Button for each rooms</h1>
    </div>
    <div class="hall">
        <div class="btn-cont">
            <button class="ambience">Ambience Light Mode</button>
            <button class="normal">Normal Light Mode</button>
        </div>
        <div class="lights">
            <h3>Lights</h3>
            <button class="on" onclick="hallfunon()">Fun Mode</button>
            <button class="on" onclick="hallseriouson()">Serious Mode</button>
            <button class="on" onclick="hallrelaxon()">Relaxed Mode</button>
            <button class="off" onclick="hallbulboff()">Hall Light Off</button>
        </div>
        <div class="normalLights">
            <h3>Lights</h3>
            <button class="on" onclick="hallNormalLightOn()">Hall Light On</button>
            <button class="off" onclick="hallNormalLightOff()">Hall Light Off</button>
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
    <!-- <h2>Bedroom Controls</h2> -->
    <div class="bedroom">
        <div class="btn-cont">
            <button class="ambience">Ambience Light Mode</button>
            <button class="normal">Normal Light Mode</button>
        </div>
        <div class="lights">
            <h3>Lights</h3>
            <button class="on" onclick="bedfunon()">Fun Mode</button>
            <button class="on" onclick="bedseriouson()">Serious Mode</button>
            <button class="on" onclick="bedrelaxon()">Relaxed Mode</button>
            <button class="off" onclick="bedbulboff()">Bedroom Light Off</button>
        </div>
        <div class="normalLights">
            <h3>Lights</h3>
            <button class="on" onclick="bedNormalLightOn()">Bedroom Light On</button>
            <button class="off" onclick="bedNormalLightOff()">Bedroom Light Off</button>
        </div>
        <div class="fan">
            <h3>Fan</h3>
            <button class="on" onclick="bedFanSlow()">Speed: Slow</button>
            <button class="on" onclick="bedFanMedium()">Speed: Medium</button>
            <button class="on" onclick="bedFanFast()">Speed: Fast</button>
            <button class="off" onclick="bedFanOff()">Fan OFF</button>
        </div>
    </div>
    <div class="kitchen">
        <div class="lights">
            <h3>Lights</h3>
            <button class="on" onclick="kitchenlighton()">Kitchen Light On</button>
            <button class="off" onclick="kitchenlightoff()">Kitchen Light Off</button>
        </div>
    </div>

    <script>
        let hall_btn = document.querySelector(".hall-btn")
        let bed_btn = document.querySelector(".bed-btn")
        let kitchen_btn = document.querySelector(".kitchen-btn")
        let hall = document.querySelector(".hall")
        let start = document.querySelector(".start")
        let bedroom = document.querySelector(".bedroom")
        let kitchen = document.querySelector(".kitchen")
        let hallAmbienceLight_btn = document.querySelector(".hall .btn-cont .ambience")
        let hallAmbienceLight = document.querySelector(".hall .lights")
        let hallNormalLight_btn = document.querySelector(".hall .btn-cont .normal")
        let hallNormalLight = document.querySelector(".hall .normalLights")
        let bedAmbienceLight_btn = document.querySelector(".bedroom .btn-cont .ambience")
        let bedAmbienceLight = document.querySelector(".bedroom .lights")
        let bedNormalLight_btn = document.querySelector(".bedroom .btn-cont .normal")
        let bedNormalLight = document.querySelector(".bedroom .normalLights")

        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("temp").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "/temperature", true);
            xhttp.send();
        }, 1000);
        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("hum").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "/humidity", true);
            xhttp.send();
        }, 1000);

        hall_btn.addEventListener("click", () => {
            hall_btn.style.backgroundColor = "rgb(248, 165, 57)"
            bed_btn.style.backgroundColor = "burlywood"
            kitchen_btn.style.backgroundColor = "burlywood"

            hall.style.display = "inline"
            bedroom.style.display = "none"
            kitchen.style.display = "none"
            start.style.display = "none"
        })
        bed_btn.addEventListener("click", () => {
            hall_btn.style.backgroundColor = "burlywood"
            bed_btn.style.backgroundColor = "rgb(248, 165, 57)"
            kitchen_btn.style.backgroundColor = "burlywood"

            hall.style.display = "none"
            bedroom.style.display = "inline"
            kitchen.style.display = "none"
            start.style.display = "none"
        })
        kitchen_btn.addEventListener("click", () => {
            hall_btn.style.backgroundColor = "burlywood"
            bed_btn.style.backgroundColor = "burlywood"
            kitchen_btn.style.backgroundColor = "rgb(248, 165, 57)"

            hall.style.display = "none"
            bedroom.style.display = "none"
            kitchen.style.display = "inline"
            start.style.display = "none"
        })
        hallAmbienceLight_btn.addEventListener("click", () => {
            hallAmbienceLight_btn.style.backgroundColor = "rgb(248, 165, 57)"
            hallNormalLight_btn.style.backgroundColor = "burlywood"

            hallAmbienceLight.style.display = "flex"
            hallNormalLight.style.display = "none"
        })
        hallNormalLight_btn.addEventListener("click", () => {
            hallAmbienceLight_btn.style.backgroundColor = "burlywood"
            hallNormalLight_btn.style.backgroundColor = "rgb(248, 165, 57)"

            hallAmbienceLight.style.display = "none"
            hallNormalLight.style.display = "flex"
        })
        bedAmbienceLight_btn.addEventListener("click", () => {
            bedAmbienceLight_btn.style.backgroundColor = "rgb(248, 165, 57)"
            bedNormalLight_btn.style.backgroundColor = "burlywood"

            bedAmbienceLight.style.display = "flex"
            bedNormalLight.style.display = "none"
        })
        bedNormalLight_btn.addEventListener("click", () => {
            bedAmbienceLight_btn.style.backgroundColor = "burlywood"
            bedNormalLight_btn.style.backgroundColor = "rgb(248, 165, 57)"

            bedAmbienceLight.style.display = "none"
            bedNormalLight.style.display = "flex"
        })

        // Hall 
        // Ambience Lights 
        function hallfunon() {
            fetch('/hallfunon')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function hallseriouson() {
            fetch('/hallseriouson')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function hallrelaxon() {
            fetch('/hallrelaxon')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function hallbulboff() {
            fetch('/hallbulboff')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        // Normal Lights 
        function hallnormalLightOn() {
            fetch('/hallnormalon')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function hallNormalLightOff() {
            fetch('/hallnormaloff')
                .then(response => response.text())
                .then(data => console.log(data))
        }

        // Fans 
        function hallFanSlow() {
            fetch('/hallFanSlow')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function hallFanMedium() {
            fetch('/hallFanMedium')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function hallFanFast() {
            fetch('/hallFanFast')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function hallFanOff() {
            fetch('/hallFanOff')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        // TV
        function tvOn() {
            fetch('/tvOn')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function tvOff() {
            fetch('/tvOff')
                .then(response => response.text())
                .then(data => console.log(data))
        }


        //Bedroom
        // Ambience Lights 
        function bedfunon() {
            fetch('/bedfunon')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function bedseriouson() {
            fetch('/bedseriouson')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function bedrelaxon() {
            fetch('/bedrelaxon')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function bedbulboff() {
            fetch('/bedbulboff')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        // Normal Lights 
        function bedNormalLightOn() {
            fetch('/bedlighton')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function bedNormalLightOff() {
            fetch('/bedlightoff')
                .then(response => response.text())
                .then(data => console.log(data))
        }


        // Fan
        function bedFanSlow() {
            fetch('/bedFanSlow')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function bedFanMedium() {
            fetch('/bedFanMedium')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function bedFanFast() {
            fetch('/bedFanFast')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function bedFanOff() {
            fetch('/bedFanOff')
                .then(response => response.text())
                .then(data => console.log(data))
        }

        // Kitchen 
        // Lights 
        function kitchenlighton() {
            fetch('/kitchenlighton')
                .then(response => response.text())
                .then(data => console.log(data))
        }
        function kitchenlightoff() {
            fetch('/kitchenlightoff')
                .then(response => response.text())
                .then(data => console.log(data))
        } 
    </script>
</body>

</html>
)rawliteral";

String processor(const String& var){
  if(var == "TEMPERATURE"){
    return temperature();
  } else if(var == "HUMIDITY"){
    return humidity();
  }
  return String();
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  dht.begin();

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

  ws.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", temperature().c_str());
  })
  ws.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", humidity().c_str());
  })

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
    // Normal Lights
  server.on("/hallnormalon", HTTP_GET, [](){
    Serial.println("Hall Normal Light On");
    server.send(200, "text/plain", "Hall Bulb On");
  });
  server.on("/hallnormaloff", HTTP_GET, [](){
    Serial.println("Hall Normal Light Off");
    server.send(200, "text/plain", "Hall Bulb On");
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
    // Ambience Lights
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
    // Normal Light
  server.on("/bednormalon", HTTP_GET, [](){
    Serial.println("Bedroom Normal Light On");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });
  server.on("/bednormaloff", HTTP_GET, [](){
    Serial.println("Bedroom Normal Light Off");
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

  // Kitchen
  server.on("/kitchenlighton", HTTP_GET, [](){
    Serial.println("Kitchen Light On");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });
  server.on("/kitchenlightoff", HTTP_GET, [](){
    Serial.println("Kitchen Light Off");
    server.send(200, "text/plain", "Hall Bulb OFF");
  });

  server.begin();
  ws.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

}
