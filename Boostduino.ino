#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 4);

String psiString = "";
float maxPsi = 0;
String maxString = "";

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);


  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  Serial.println("setup complete");

  
}

// the loop routine runs over and over again forever:
void loop() {
  
  // read the input on analog pin 0 and translate to psig
  float sensorValue = (analogRead(A0)*5/1024.0+0.198)*7.25-14.7;
  
  // round to the nearest 0.2
  sensorValue = round(sensorValue * 5)/5.0;
  
  // print out the value you read:
  // Serial.println(sensorValue);
  Serial.println((analogRead(A0)*5/1024.0+0.200)*7.25-14.7);

  // if it's greater than the maxPsi, replace maxPsi
  if(maxPsi < sensorValue){
    maxPsi = sensorValue;
    maxString = "max: " + String(maxPsi, 1);
  }

  // write the psi to a string
  psiString = String(sensorValue, 1);

  // Clear display buffer
  display.clearDisplay();

  // Draw the current pressure reading
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.println(psiString);

  // Draw the maximum pressure reading
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(maxString);

  // Draw the psi unit
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(100,10);
  display.println("psig");

  // Show display buffer
  display.display();
  
  delay(250);        // delay in between reads for stability
}
