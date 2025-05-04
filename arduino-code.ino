#include <Adafruit_NeoPixel.h>

// OLED Code 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_I2C_ADDR 0x3C // or 0x3C
#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
#define OLED_RST_PIN -1      // Reset pin (-1 if not available)

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST_PIN);

int hallStripPin = 2;
int bedStripPin = 3;
int stripLed = 10;
int ena = 4;
int enb = 5;
int hallNormalLight = 6;
int bedNormalLight = 7;
int exhaust = 11;
int gasPin = A0;
// int in1 = 6;
// int in2 = 7;
// int in3 = 8;
// int in4 = 9;

Adafruit_NeoPixel hallStrip(stripLed, hallStripPin, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel bedroomStrip(stripLed, bedStripPin, NEO_RGB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(hallNormalLight, OUTPUT);
  pinMode(bedNormalLight, OUTPUT);
  pinMode(exhaust, OUTPUT);
  pinMode(gasPin,  INPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR);

  Serial.begin(9600);

  hallStrip.begin();
  hallStrip.show();
  bedroomStrip.begin();
  bedroomStrip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    String command = Serial.readStringUntil('\n');
    command.trim();
    Serial.println(command);
    int gasData = analogRead(gasPin);

    if(gasPin >= 600){
      normalOn(exhaust);
    } else if(gasPin < 600){
      normalOff(exhaust);
    }
    
    if(command == "Hall Fun Mode On"){
      // digitalWrite(hallBulb, HIGH);
      fun(stripLed, hallStrip);
    } else if(command == "Hall Lights OFF"){
      // digitalWrite(hallBulb, LOW);
      stripOff(stripLed, hallStrip);
    } else if(command == "Hall Relaxed Mode On"){
      relax(stripLed, hallStrip);
    } else if(command == "Hall Serious Mode On"){
      serious(stripLed, hallStrip);
    } else if(command == "Bedroom Serious Mode On"){ //Bedroom Lights
      serious(stripLed, bedroomStrip);
    } else if(command == "Bedroom Fun Mode On"){
      fun(stripLed, bedroomStrip);
    } else if(command == "Bedroom Relaxed Mode On"){
      relax(stripLed, bedroomStrip);
    } else if(command == "Bedroom Lights OFF"){
      stripOff(stripLed, bedroomStrip);
    } else if(command == "Hall Fan Slow"){  // Hall Fans
      fanSlow(ena);
    } else if(command == "Hall Fan Medium"){ 
      fanMedium(ena);
    } else if(command == "Hall Fan Fast"){ 
      fanFast(ena);
    } else if(command == "Hall Fan Off"){ 
      fanOff(ena);
    } else if(command == "Bedroom Fan Slow"){  // Bedroom Fan
      fanSlow(enb);
    } else if(command == "Bedroom Fan Medium"){ 
      fanMedium(enb);
    } else if(command == "Bedroom Fan Fast"){ 
      fanFast(enb);
    } else if(command == "Bedroom Fan Off"){ 
      fanOff(enb);
    } else if(command == "TV ON"){       // Hall TV
      tvOn();
    } else if(command == "TV OFF"){
      tvOff();
    } else if(command == "Hall Normal Light On"){   // Hall Normal Light
      normalOn(hallNormalLight);
    } else if(command == "Hall Normal Light Off"){
      normalOff(hallNormalLight);
    } else if(command == "Bedroom Normal Light On"){  //Bedroom Normal Light
      normalOn(bedNormalLight);
    } else if(command == "Bedroom Normal Light Off"){
      normalOff(bedNormalLight);
    } else if(command == "Kitchen Light On"){   // Kitchen Light
      normalOn(kitchenLight);
    } else if(command == "Kitchen Light Off"){
      normalOff(kitchenLight);
    }
  }
}

void stripOff(int led, Adafruit_NeoPixel &rgbStrip){
  for(int i = 0;i < led;i++){
    rgbStrip.setPixelColor(i, rgbStrip.Color(0, 0, 0));
  }
  rgbStrip.show();
  // delay(30);
}
void fun(int led, Adafruit_NeoPixel &rgbStrip){
  for(int j = 0;j < 255;j++){
    for(int i = 0;i < led;i++){
      int r = sinColor(i + j, 0);
      int g = sinColor(i + j, 85);
      int b = sinColor(i + j, 170);

      rgbStrip.setPixelColor(i, rgbStrip.Color(r, g, b));
    }
    rgbStrip.show();
    delay(50);
  }
}
void serious(int led, Adafruit_NeoPixel &rgbStrip){
  for(int i = 0;i < led;i++){
    rgbStrip.setPixelColor(i, rgbStrip.Color(255, 255, 255));
  }
  rgbStrip.show();
  delay(30);
}
void relax(int led, Adafruit_NeoPixel &rgbStrip){
  for(int i = 0;i < led;i++){
    rgbStrip.setPixelColor(i, rgbStrip.Color(147, 255, 41));
  }
  rgbStrip.show();
  delay(50);
}
void fanSlow(int en){
  // digitalWrite(in1, HIGH);
  // digitalWrite(in2, LOW);
  analogWrite(en, 100);
}
void fanMedium(int en){
  // digitalWrite(in1, HIGH);
  // digitalWrite(in2, LOW);
  analogWrite(en, 170);
}
void fanFast(int en){
  // digitalWrite(in1, HIGH);
  // digitalWrite(in2, LOW);
  analogWrite(en, 255);
}
void fanOff(int en){
  // digitalWrite(in1, HIGH);
  // digitalWrite(in2, LOW);
  analogWrite(en, 0);
}
int frame = 0;
void tvOn(){
  // display.clearDisplay();
  // display.drawBitmap(40, 8, frames[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
  // display.display();
  // frame = (frame + 1) % FRAME_COUNT;
  // delay(FRAME_DELAY);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Android Powered");
  display.display();
}
void tvOff(){
  display.clearDisplay();
  display.display();
}
void normalOn(int pin){
  digitalWrite(pin, HIGH);
}
void normalOff(int pin){
  digitalWrite(pin, LOW);
}

int sinColor(int x, int offset){
  return (sin((x + offset) * 3.14 / 128.0) * 127) + 128;
}
