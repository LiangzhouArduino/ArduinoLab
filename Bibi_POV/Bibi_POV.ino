#include <SimpleTimer.h>

#define PIN_COUNT  16

//define pin
int pinRow[PIN_COUNT] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17
};
const int pinMusic = 18;

// (\w{2})H.{1,3}(\w{2})H,?     0x\1\2,
// display array
unsigned charList[][PIN_COUNT] = {
  {0x1008,0x1FFC,0x2808,0x2FF8, 0x6888,0xA8A8,0x2BF8,0x2AA8, 0x2AA8,0x2AA8,0x2AA8,0x2AA8, 0x2AEA,0x288A,0x3086,0x2080},//pei
  {0x1008,0x1FFC,0x2808,0x2FF8, 0x6888,0xA8A8,0x2BF8,0x2AA8, 0x2AA8,0x2AA8,0x2AA8,0x2AA8, 0x2AEA,0x288A,0x3086,0x2080},
  {0x0000,0x0000,0x0000,0x0000, 0x0000,0x0000,0x0000,0x0000, 0x0000,0x0000,0x1800,0x1800, 0x1000,0x2000,0x0000,0x0000},
  {0x0100,0x1100,0x1100,0x1108, 0x3FFC,0x2100,0x4100,0x4100, 0x8110,0x3FF8,0x0100,0x0100, 0x0100,0x0104,0xFFFE,0x0000},//sheng
  {0x0010,0x1FF8,0x1010,0x1010, 0x1010,0x1010,0x1010,0x1FF0, 0x1010,0x1010,0x1010,0x1010, 0x1010,0x1FF0,0x1010,0x0000}, // ri
  {0x1080,0x1080,0x1080,0x1088, 0x5BFC,0x5488,0x5088,0x9088, 0x1088,0x1FFE,0x1080,0x1140, 0x1120,0x1210,0x140E,0x1804},//kuai
  {0x0020,0x00F0,0x1F00,0x1000, 0x1100,0x1100,0x2104,0x7FFE, 0x0100,0x0100,0x0920,0x0910, 0x1108,0x210C,0x4504,0x0200},//le
  {0x0000,0x0180,0x03C0,0x03C0, 0x03C0,0x0180,0x0180,0x0180, 0x0180,0x0180,0x0000,0x0000, 0x0180,0x0180,0x0000,0x0000}
};
int charCount=0;

int music_rhythm[][2] = {
  { 392,250  } ,
  { 392,250  } ,
  { 440,500  } ,
  { 392,500  } ,
  { 523,500  } ,
  { 494,1000  } ,
  { 392,250  } ,
  { 392,250  } ,
  { 440,500  } ,
  { 392,500  } ,
  { 587,500  } ,
  { 523,1000  } ,
  { 392,250  } ,
  { 392,250  } ,
  { 784,500  } ,
  { 659,500  } ,
  { 523,500  } ,
  { 494,500  } ,
  { 440,500  } ,
  { 699,250  } ,
  { 699,250  } ,
  { 659,500  } ,
  { 523,500  } ,
  { 587,500  } ,
  { 523,1000  }
};
int rhythmCount = 0;

SimpleTimer timer;

void displayNum(unsigned rowNum)
{
  int i;
  unsigned mask = 0x8000;
  for(i=0;i<16;i++)
  {
    if(mask & rowNum > 0){
      digitalWrite(pinRow[i], HIGH);
    }else{
      digitalWrite(pinRow[i], LOW);
    }
    mask = mask>>1;
  }
}

// function to be called repeatedly
void POV() {
  static unsigned counter;
  unsigned charCounter;
  charCounter = counter >> 4;
  displayNum(charList[charCounter][counter & 0xF]);
  counter++;
  if(charCounter >= charCount){
    counter=0;
  }
}

void Music(){
  static int counter=0;
  static int rhythm=0;
  if(rhythm == 0){
    rhythm = music_rhythm[counter][1];
    tone(pinMusic,music_rhythm[counter][0],rhythm);
  }
  rhythm -= 250;
  if(rhythm == 0){
    counter++;
  }
  if(counter >= rhythmCount){
    counter=0;
  }
  Serial.println(counter);
}


void setup() {
  Serial.begin(9600);
  //
  //  // welcome message
  // timed actions setup
  charCount = sizeof(charList) / sizeof(charList[0]);
  rhythmCount = sizeof(music_rhythm) / sizeof(music_rhythm[0]);
//  Serial.print("charCount:");
//  Serial.println(charCount);
//  Serial.print("rhythmCount:");
//  Serial.println(rhythmCount);
  
  timer.setInterval(10, POV);
  timer.setInterval(250, Music);

  int i = 0 ;
  for(i=0;i<16;i++)
  {
    pinMode(pinRow[i], OUTPUT);
    digitalWrite(pinRow[i], LOW);
  }
}

void loop() {
  // this is where the "polling" occurs
  timer.run();
}



