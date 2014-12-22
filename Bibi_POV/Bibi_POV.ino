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
  {0x0400,0x0800,0x3FFF,0xC002, 0x7FFC,0x5000,0x53F8,0x5200, 0x5FFF,0x5208,0x57F8,0x5200, 0xFFFC,0x4002,0x000E,0x0000},//pei
  {0x0400,0x0800,0x3FFF,0xC002, 0x7FFC,0x5000,0x53F8,0x5200, 0x5FFF,0x5208,0x57F8,0x5200, 0xFFFC,0x4002,0x000E,0x0000},//pei
  {0x0000,0x0000,0x0004,0x0038, 0x0030,0x0000,0x0000,0x0000, 0x0000,0x0000,0x0000,0x0000, 0x0000,0x0000,0x0000,0x0000},//,
  {0x0082,0x0302,0x0C42,0x7842, 0x0842,0x0842,0x0842,0xFFFE, 0x0842,0x0842,0x0842,0x08C2, 0x1842,0x0806,0x0002,0x0000},//sheng
  {0x0000,0x0000,0x0000,0x7FFE, 0x4104,0x4104,0x4104,0x4104, 0x4104,0x4104,0x4104,0xFFFE, 0x4000,0x0000,0x0000,0x0000},//ri
  {0x0100,0x0E00,0x0000,0xFFFF, 0x0841,0x0442,0x0844,0x0858, 0xFFE0,0x0850,0x0848,0x0844, 0x1FC2,0x0843,0x0042,0x0000},//kuai
  {0x0000,0x0102,0x0304,0x3D08, 0x2130,0x2102,0x2101,0x2FFE, 0x4100,0x4100,0xC120,0x4110, 0x010C,0x0306,0x0100,0x0000},//le
  {0x0000,0x0000,0x0000,0x0000, 0x0000,0x0000,0x3800,0x7FCC, 0x7FCC,0x3800,0x0000,0x0000, 0x0000,0x0000,0x0000,0x0000} //!
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
  //Serial.println(rowNum);
  for(i=0;i<16;i++)
  {
    if((mask & rowNum) != 0){
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
}

void setup() {
  //Serial.begin(9600);
  //
  //  // welcome message
  // timed actions setup
  charCount = sizeof(charList) / sizeof(charList[0]);
  rhythmCount = sizeof(music_rhythm) / sizeof(music_rhythm[0]);
  
  timer.setInterval(10, POV);
  timer.setInterval(260, Music);

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



