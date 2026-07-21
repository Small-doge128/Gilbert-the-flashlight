#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Preferences.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define MAX_LUMENS 1000

const int mosfetPin = D3;
const int pwmFreq = 5000;
const int pwmResolution = 8;

const int btnUpPin = D1;
const int btnDownPin = D0;

const int BATTERY_PIN = A2;


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long lastActivityTime = 0;
bool screenOn = true;
Preferences preferences;


uint16_t calculateLumens(uint8_t pct) {
   return ((uint32_t)pct *MAX_LUMENS) / 100;
}

uint8_t getBatteryPercent() {
   int rawADC = analogRead(BATTERY_PIN);
   float voltage  = (rawADC / 4095.0) * 3.3 * 2.0;

   if (voltage >= 4.2) return 100;
   if (voltage <= 3.3) return 0;
   return (uint8_t )((voltage - 3.3) * 100.0 / (4.2 - 3.3));
}

uint8_t brightness = 0;
 uint8_t brightnessPercent(uint8_t value) {
    return (uint16_t)value *100 / 255; 
 }


 uint8_t targetBrightness = 0;
 unsigned long lastFadeTime = 0;


void setup() {


    //mosfet
    pinMode(mosfetPin, OUTPUT);
    digitalWrite(mosfetPin, LOW);
    
    //LEDs
    ledcSetup(0, pwmFreq, pwmResolution);
    ledcAttachPin(mosfetPin, 0);
    
    //display
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)){
     for(;;);     
    }
    display.clearDisplay();
    display.display();

    //buttons
    pinMode(btnUpPin, INPUT_PULLUP);
    pinMode(btnDownPin, INPUT_PULLUP);

    //display timeout
    lastActivityTime = millis();

    preferences.begin("led-app", false);
    brightness = preferences.getUChar("bright", 0);
    targetBrightness =  brightness;
    ledcWrite(0, brightness);

}

    //display
void drawBrightnessScreen() {
    
    uint8_t pct = brightnessPercent(targetBrightness); 
    uint16_t lumens = calculateLumens(pct);
    uint8_t batPct = getBatteryPercent();

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.print(lumens);
    display.print(" lm");

    display.setCursor(80, 0);
    display.print("BAT:");
    display.print(batPct);
    display.println("%");
    
    display.drawRect(0, 16, 128, 10, SSD1306_WHITE);
     int fillW = (pct *126) / 100;
     if (fillW > 0) {
        display.fillRect(1, 17, fillW, 8, SSD1306_WHITE);
     }
    
     display.display();
}


void loop() {
      bool activity = false;


   //buttons
   if(digitalRead(btnUpPin) == LOW){
     if (screenOn) {
        if (targetBrightness <= 240) targetBrightness += 15;
        else targetBrightness = 255;
        preferences.putUChar("bright", targetBrightness);
   }
    activity = true;
    delay(150);
   }

   if (digitalRead(btnDownPin) == LOW) {
    if (screenOn) {
       if (targetBrightness >= 15) targetBrightness -= 15;
       else targetBrightness = 0;
       preferences.putUChar("bright", targetBrightness);
     }
     delay(150);
     activity = true;
   }

   //display timeout

   if (activity) {
    lastActivityTime = millis();
    if (!screenOn) {
        display.ssd1306_command(SSD1306_DISPLAYON);
        screenOn = true;
    }
   }
   if (screenOn && (millis() - lastActivityTime >5000)) {
    display.ssd1306_command(SSD1306_DISPLAYOFF);
    screenOn = false;
   }
   if (screenOn) {
    drawBrightnessScreen();
   }

   if (millis() - lastFadeTime >= 5) {
      lastFadeTime = millis();
      if (brightness < targetBrightness) brightness++;
      else if (brightness > targetBrightness) brightness --;

      ledcWrite(0, brightness);
   }
}
