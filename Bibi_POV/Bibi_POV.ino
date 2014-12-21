#include <SimpleTimer.h>

#define display_array_size 8
// ascii 8x8 dot font

#define data_ascii_A 0x02,0x0C,0x18,0x68,0x68,0x18,0x0C,0x02 /*"A",0*/
/** 
 **"A"
 * #define A  { //
 * {0, 0, 0, 0, 0, 0, 1, 0}, //0x02
 * {0, 0, 0, 0, 1, 1, 0, 0}, //0x0C
 * {0, 0, 0, 1, 1, 0, 0, 0}, //0x18
 * {0, 1, 1, 0, 1, 0, 0, 0}, //0x68
 * {0, 1, 1, 0, 1, 0, 0, 0}, //0x68
 * {0, 0, 0, 1, 1, 0, 0, 0}, //0x18
 * {0, 0, 0, 0, 1, 1, 0, 0}, //0x0C
 * {0, 0, 0, 0, 0, 0, 1, 0}  //0x02
 * }
 **/
#define data_ascii_B 0x00,0x7E,0x52,0x52,0x52,0x52,0x2C,0x00 /*"B",1*/
#define data_ascii_C 0x00,0x3C,0x66,0x42,0x42,0x42,0x2C,0x00 /*"C",2*/
#define data_ascii_D 0x00,0x7E,0x42,0x42,0x42,0x66,0x3C,0x00 /*"D",3*/
#define data_ascii_E 0x00,0x7E,0x52,0x52,0x52,0x52,0x52,0x42 /*"E",4*/
#define data_ascii_F 0x00,0x7E,0x50,0x50,0x50,0x50,0x50,0x40 /*"F",5*/
#define data_ascii_G 0x00,0x3C,0x66,0x42,0x42,0x52,0x16,0x1E /*"G",6*/
#define data_ascii_H 0x00,0x7E,0x10,0x10,0x10,0x10,0x7E,0x00 /*"H",7*/
#define data_ascii_I 0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00 /*"I",8*/
// display array
byte data_ascii[][display_array_size] = {
  data_ascii_A, 
  data_ascii_B,
  data_ascii_C,
  data_ascii_D,
  data_ascii_E,
  data_ascii_F,
  data_ascii_G,
  data_ascii_H,
  data_ascii_I,
};

int music_rhythm[25][2] = {
  {
    392,250  }
  ,
  {
    392,250  }
  ,
  {
    440,500  }
  ,
  {
    392,500  }
  ,
  {
    523,500  }
  ,
  {
    494,1000  }
  ,
  {
    392,250  }
  ,
  {
    392,250  }
  ,
  {
    440,500  }
  ,
  {
    392,500  }
  ,
  {
    587,500  }
  ,
  {
    523,1000  }
  ,
  {
    392,250  }
  ,
  {
    392,250  }
  ,
  {
    784,500  }
  ,
  {
    659,500  }
  ,
  {
    523,500  }
  ,
  {
    494,500  }
  ,
  {
    440,500  }
  ,
  {
    699,250  }
  ,
  {
    699,250  }
  ,
  {
    659,500  }
  ,
  {
    523,500  }
  ,
  {
    587,500  }
  ,
  {
    523,1000  }
};

//the pin to control ROW
const int row1 = 2; // the number of the row pin 24
const int row2 = 3; // the number of the row pin 23
const int row3 = 4; // the number of the row pin 22
const int row4 = 5; // the number of the row pin 21
const int row5 = 17; // the number of the row pin 4
const int row6 = 16; // the number of the row pin 3
const int row7 = 15; // the number of the row pin 2
const int row8 = 14; // the number of the row pin 1

SimpleTimer timer;

void displayNum(byte rowNum)
{
  int j;
  byte temp = rowNum;
  for(j=row1;j<=row4;j++)
  {
    digitalWrite(j, LOW);
  }
  digitalWrite(row5, LOW);
  digitalWrite(row6, LOW);
  digitalWrite(row7, LOW);
  digitalWrite(row8, LOW);
  for(j = 1 ;j < 9; j++)
  {
    temp = (0x80)&(temp) ;
    if(temp==0)
    {
      temp = rowNum<<j;
      continue;
    }
    switch(j)
    {
    case 1: 
      digitalWrite(row1, HIGH); 
      break;
    case 2: 
      digitalWrite(row2, HIGH); 
      break;
    case 3: 
      digitalWrite(row3, HIGH); 
      break;
    case 4: 
      digitalWrite(row4, HIGH); 
      break;
    case 5: 
      digitalWrite(row5, HIGH); 
      break;
    case 6: 
      digitalWrite(row6, HIGH); 
      break;
    case 7: 
      digitalWrite(row7, HIGH); 
      break;
    case 8: 
      digitalWrite(row8, HIGH); 
      break;
    default: 
      break;
    }
    temp = rowNum<<j;
  }
}

// function to be called repeatedly
void POV() {
  static unsigned counter=0;
  unsigned charCounter;
  charCounter = counter>>3;
  displayNum(data_ascii[counter>>3][counter&7]);
  if(charCounter>1)counter=0;
  // Serial.println(counter);
  counter++;
}

void Music(){
  //Serial.println("music");
  static int counter=0;
  static int rhythm=0;
  if(rhythm == 0){
    rhythm = music_rhythm[counter][1];
  }
  tone(8,music_rhythm[counter][0],280);
  rhythm -= 250;
  if(rhythm == 0){
    counter++;
  }
  if(counter>=25){
    counter=0;
  }
}


void setup() {
  //  Serial.begin(9600);
  //
  //  // welcome message
  //  Serial.println("SimpleTimer Example");

  // timed actions setup
  timer.setInterval(30, POV);
  timer.setInterval(250, Music);

  int i = 0 ;
  for(i=2;i<18;i++)
  {
    pinMode(i, OUTPUT);
  }

  for(i=2;i<18;i++) {
    digitalWrite(i, LOW);
  }
}

void loop() {
  // this is where the "polling" occurs
  timer.run();
}



