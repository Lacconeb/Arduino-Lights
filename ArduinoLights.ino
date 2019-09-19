#include "FastLED.h"
#define NUM_LEDS 174 
#define AUDIO_PIN 0 
#define DATA_PIN 6


CRGB leds[NUM_LEDS]; 
int colorNum = 0;

unsigned long colorShiftTime = 0;
unsigned long colorShiftTimeInterval = 3000;

void setup() {
  Serial.begin(9600);

  pinMode(A0, INPUT);
  
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);S
  
  FastLED.show();
  
}

void loop() {

  colorShift();
  
  int input = analogRead(AUDIO_PIN)*5;
  Serial.println(input);

  //setColorBrightness() is not very effective in this current position
  //needs to be ran inside the color shift loop with input
  setColorBrightness(input);
  
  delay(1);
  
}

void colorShift(){

  int r = 0;
  int g = 0;
  int b = 0;

  unsigned long currTime = millis();

  if(currTime >= colorShiftTime + colorShiftTimeInterval)
  {
    colorNum++;
    
    if(colorNum > 6){
      colorNum = 0;
    }
    
    colorShiftTime = millis();
  }

  Serial.println("currTime / colorShiftTime = ");
  Serial.print(currTime);
  Serial.print(" / ");
  Serial.print(colorShiftTime);
  Serial.println("********************");
  
  switch(colorNum)
  {
    case 0: //red
      r = 255;
      Serial.println("Red");
      break;
    case 1: //orange
      r = 255;
      g = 127;
      Serial.println("Orange");
      break;
    case 2: //yellow
      r = 255;
      g = 255;
      Serial.println("Yellow");
      break;
    case 3: //green
      g = 255;
      Serial.println("Green");
      break;
    case 4: //blue
      b = 255;
      Serial.println("Blue");
      break;
    case 5: //indigo
      r = 75;
      b = 130;
      Serial.println("Indigo");
      break;
    case 6: //violet
      r = 148;
      b = 211;
      Serial.println("Violet");
      break;
  }

  setColor(r,g,b);
}

void setColor(int r, int g, int b)
{
  bool isFinished = false;

  int oldr = leds[0].r;
  int oldb = leds[0].b;
  int oldg = leds[0].g;
  
  while(isFinished == false)
  {
    if(oldr > r)
      oldr--;
    else if(oldr < r)
      oldr++;

    if(oldb > b)
      oldb--;
    else if(oldb < b)
      oldb++;

    if(oldg > g)
      oldg--;
    else if(oldg < g)
      oldg++;
      
    for(int i = 0; i < NUM_LEDS ; i++) {
      
      if(i>60 && i<111)
      {
        leds[i] = CHSV(25, 0, 170);
      }
      else
      {
        leds[i] = CRGB(oldr, oldg, oldb);
      }
      
    }
  
  
    //Serial.println(p);
    FastLED.show();

    if(oldr == r && oldb == b && oldg == g)
    {
       break;  
    }
    delay(10);
  }
}

void setColorBrightness(int input)
{
  if(input < 100)
  {
    FastLED.setBrightness(100);
  }
  else
  {
    FastLED.setBrightness(255);   
  }
}
