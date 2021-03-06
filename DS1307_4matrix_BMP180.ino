#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
tmElements_t tm;

#include <BMP180.h>
BMP180 barometer;
#define BMPMeasurementError 14 

#include <LedControlDS.h>
LedControl lc=LedControl(11,13,10,4);
//data,clock,load

int godz1, godz2, min1, min2, dz1, dz2, mies1, mies2, rok1,rok2,rok3,rok4; 
int temp1, temp2;
int devices=4;

#include <MaxMatrix.h>
#include <avr/pgmspace.h>
PROGMEM const unsigned char CH[] = {
3, 8, B00000000, B00000000, B00000000, B00000000, B00000000, // space
1, 8, B01011111, B00000000, B00000000, B00000000, B00000000, // !
3, 8, B00000011, B00000000, B00000011, B00000000, B00000000, // "
5, 8, B00010100, B00111110, B00010100, B00111110, B00010100, // #
4, 8, B00100100, B01101010, B00101011, B00010010, B00000000, // $
5, 8, B01100011, B00010011, B00001000, B01100100, B01100011, // %
5, 8, B00110110, B01001001, B01010110, B00100000, B01010000, // &
1, 8, B00000011, B00000000, B00000000, B00000000, B00000000, // '
3, 8, B00011100, B00100010, B01000001, B00000000, B00000000, // (
3, 8, B01000001, B00100010, B00011100, B00000000, B00000000, // )
5, 8, B00101000, B00011000, B00001110, B00011000, B00101000, // *
5, 8, B00001000, B00001000, B00111110, B00001000, B00001000, // +
2, 8, B10110000, B01110000, B00000000, B00000000, B00000000, // ,
4, 8, B00001000, B00001000, B00001000, B00001000, B00000000, // -
2, 8, B01100000, B01100000, B00000000, B00000000, B00000000, // .
4, 8, B01100000, B00011000, B00000110, B00000001, B00000000, // /
4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // 0
3, 8, B01000010, B01111111, B01000000, B00000000, B00000000, // 1
4, 8, B01100010, B01010001, B01001001, B01000110, B00000000, // 2
4, 8, B00100010, B01000001, B01001001, B00110110, B00000000, // 3
4, 8, B00011000, B00010100, B00010010, B01111111, B00000000, // 4
4, 8, B00100111, B01000101, B01000101, B00111001, B00000000, // 5
4, 8, B00111110, B01001001, B01001001, B00110000, B00000000, // 6
4, 8, B01100001, B00010001, B00001001, B00000111, B00000000, // 7
4, 8, B00110110, B01001001, B01001001, B00110110, B00000000, // 8
4, 8, B00000110, B01001001, B01001001, B00111110, B00000000, // 9
2, 8, B00100100, B00000000, B00000000, B00000000, B00000000, // :
2, 8, B10000000, B01010000, B00000000, B00000000, B00000000, // ;
3, 8, B00010000, B00101000, B01000100, B00000000, B00000000, // <
3, 8, B00010100, B00010100, B00010100, B00000000, B00000000, // =
3, 8, B01000100, B00101000, B00010000, B00000000, B00000000, // >
4, 8, B00000010, B01011001, B00001001, B00000110, B00000000, // ?
5, 8, B00111110, B01001001, B01010101, B01011101, B00001110, // @
4, 8, B01111110, B00010001, B00010001, B01111110, B00000000, // A
4, 8, B01111111, B01001001, B01001001, B00110110, B00000000, // B
4, 8, B00111110, B01000001, B01000001, B00100010, B00000000, // C
4, 8, B01111111, B01000001, B01000001, B00111110, B00000000, // D
4, 8, B01111111, B01001001, B01001001, B01000001, B00000000, // E
4, 8, B01111111, B00001001, B00001001, B00000001, B00000000, // F
4, 8, B00111110, B01000001, B01001001, B01111010, B00000000, // G
4, 8, B01111111, B00001000, B00001000, B01111111, B00000000, // H
3, 8, B01000001, B01111111, B01000001, B00000000, B00000000, // I
5, 8, B00110000, B01000000, B01000001, B00111111, B00000001, // J
4, 8, B01111111, B00001000, B00010100, B01100011, B00000000, // K
4, 8, B01111111, B01000000, B01000000, B01000000, B00000000, // L
5, 8, B01111111, B00000010, B00001100, B00000010, B01111111, // M
5, 8, B01111111, B00000100, B00001000, B00010000, B01111111, // N
4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // O
4, 8, B01111111, B00001001, B00001001, B00000110, B00000000, // P
4, 8, B00111110, B01000001, B01100001, B10111110, B00000000, // Q
5, 8, B01111111, B00001001, B00011001, B00101001, B01000110, // R
4, 8, B01000110, B01001001, B01001001, B00110010, B00000000, // S
5, 8, B00000001, B00000001, B01111111, B00000001, B00000001, // T
4, 8, B00111111, B01000000, B01000000, B00111111, B00000000, // U
5, 8, B00001111, B00110000, B01000000, B00110000, B00001111, // V
5, 8, B00111111, B01000000, B00111000, B01000000, B00111111, // W
5, 8, B01100011, B00010100, B00001000, B00010100, B01100011, // X
5, 8, B00000111, B00001000, B01110000, B00001000, B00000111, // Y
4, 8, B01100001, B01010001, B01001001, B01000111, B00000000, // Z
2, 8, B01111111, B01000001, B00000000, B00000000, B00000000, // [
4, 8, B00000001, B00000110, B00011000, B01100000, B00000000, // \ backslash
2, 8, B01000001, B01111111, B00000000, B00000000, B00000000, // ]
3, 8, B00000010, B00000001, B00000010, B00000000, B00000000, // hat
4, 8, B01000000, B01000000, B01000000, B01000000, B00000000, // _
2, 8, B00000001, B00000010, B00000000, B00000000, B00000000, // `
4, 8, B00100000, B01010100, B01010100, B01111000, B00000000, // a
4, 8, B01111111, B01001000, B01001000, B00110000, B00000000, // b
4, 8, B00111000, B01000100, B01000100, B00000000, B00000000, // c
4, 8, B00110000, B01001000, B01001000, B01111111, B00000000, // d
4, 8, B00111000, B01010100, B01010100, B00011000, B00000000, // e
4, 8, B00001000, B01111110, B00001001, B00000010, B00000000, // f
4, 8, B10011000, B10100100, B10100100, B01111000, B00000000, // g
4, 8, B01111111, B00001000, B00001000, B01110000, B00000000, // h
3, 8, B01000100, B01111101, B01000000, B00000000, B00000000, // i
4, 8, B01000000, B10000000, B10000100, B01111101, B00000000, // j
4, 8, B01111111, B00010000, B00101000, B01000100, B00000000, // k
3, 8, B01000001, B01111111, B01000000, B00000000, B00000000, // l
5, 8, B01111100, B00000100, B01111100, B00000100, B01111000, // m
4, 8, B01111100, B00000100, B00000100, B01111000, B00000000, // n
4, 8, B00111000, B01000100, B01000100, B00111000, B00000000, // o
4, 8, B11111100, B00100100, B00100100, B00011000, B00000000, // p
4, 8, B00011000, B00100100, B00100100, B11111100, B00000000, // q
4, 8, B01111100, B00001000, B00000100, B00001000, B00000000, // r
4, 8, B01001000, B01010100, B01010100, B00100100, B00000000, // s
3, 8, B00000100, B00111111, B01000100, B00000000, B00000000, // t
4, 8, B00111100, B01000000, B01000000, B01111100, B00000000, // u
5, 8, B00011100, B00100000, B01000000, B00100000, B00011100, // v
5, 8, B00111100, B01000000, B00111100, B01000000, B00111100, // w
5, 8, B01000100, B00101000, B00010000, B00101000, B01000100, // x
4, 8, B10011100, B10100000, B10100000, B01111100, B00000000, // y
3, 8, B01100100, B01010100, B01001100, B00000000, B00000000, // z
3, 8, B00001000, B00110110, B01000001, B00000000, B00000000, // {
1, 8, B01111111, B00000000, B00000000, B00000000, B00000000, // |
3, 8, B01000001, B00110110, B00001000, B00000000, B00000000, // }
4, 8, B00001000, B00000100, B00001000, B00000100, B00000000, // ~
};
MaxMatrix m (11,10,13,4); // define module
byte buffer[10];
char zyczeniaKI[] = "Kasi imieniny  ";
char zyczeniaKU[] = "Kasi urodziny  ";
char zyczeniaOI[] = "Oli imieniny  ";
char zyczeniaOU[] = "Oli urodziny  ";
char zyczeniaDI[] = "Darka imieniny  ";
char zyczeniaDU[] = "Darka urodziny  ";
char temperatura[] = "Temperatura:";
char dzisiaj[] = "Data: ";
char godzina[] = "Godzina:";
char cisPa[] = "Cisnienie:";
char hPa[] = "hPa.";
char pusty[] = "         ";

void setup() {
  Serial.begin(57600);
  Wire.begin();
  
    for(int address=0;address<devices;address++) {
    lc.shutdown(address,false);
    lc.setIntensity(address,0);
    lc.clearDisplay(address);
  }
  
  m.init();
  m.setIntensity(0);


    barometer = BMP180();
    if(barometer.EnsureConnected()) {
      barometer.SoftReset();
      // Now we initialize the sensor and pull the calibration data.
      barometer.Initialize();
      }
  }
  
//=========================matrix========================  
  void printCharWithShift(char c, int shift_speed){
  if (c < 32) return;
  c -= 32;
  memcpy_P(buffer, CH + 7*c, 7);
  m.writeSprite(32, 0, buffer);
  m.setColumn(32 + buffer[0], 0);
  
  for (int i=0; i<buffer[0]+1; i++) 
  {
    delay(shift_speed);
    m.shiftLeft(false, false);
  }
}

void printStringWithShift(char* s, int shift_speed){
  while (*s != 0){
    printCharWithShift(*s, shift_speed);
    s++;
  }
}

void printString(char* s) {
  int col = 0;
  while (*s != 0) {
    if (*s < 32) continue;
    char c = *s - 32;
    memcpy_P(buffer, CH + 7*c, 7);
    m.writeSprite(col, 0, buffer);
    m.setColumn(col + buffer[0], 0);
    col += buffer[0] + 1;
    s++;
  }
}
//========================matrix===========================
  
//delay(50); // Poczekaj między aktualizacjami ekranu
//lc.clearAll();

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  //Serial.print(number);
}

void czas() {//===========================================czas================
  RTC.read(tm);
  lc.clearAll();
  godz1=tm.Hour/10; //liczba całkowita dzielenie przez 10 zwraca pierwszą cyfrę godziny.
  godz2=tm.Hour%10; //modulo dzielenie przez 10 zwraca 2 cyfre.
  min1=tm.Minute/10;
  min2=tm.Minute%10;

  lc.displayChar(3,godz1); //Godziny 1 cyfra do lewej skrajnej (#0) LED.
  lc.displayChar(2,godz2); //Godziny 2 cyfry LED do #1
  lc.displayChar(1,min1); //Min 1 cyfra # LED 3. (Przypomnijmy, że 2 jest używane do oznaczania sekundy.)
  lc.displayChar(0,min2); //Min 1 cyfra do # 4

//delay(1000);
//lc.writeString(0,"AtuVw");
//delay(1500);
  lc.setLed(2,7,4,true); //Włącz adresowane dioda na 3/4 sek
  lc.setLed(2,7,2,true);
    delay(750);
  lc.setLed(2,7,4,false);  //Wyłącz na 1/4 sek
  lc.setLed(2,7,2,false);
    delay(250);
  
  lc.setLed(2,7,4,true); //Włącz adresowane dioda na 3/4 sek
  lc.setLed(2,7,2,true);
    delay(750);
  lc.setLed(2,7,4,false);  //Wyłącz na 1/4 sek
  lc.setLed(2,7,2,false);
    delay(250);
  
  lc.setLed(2,7,4,true); //Włącz adresowane dioda na 3/4 sek
  lc.setLed(2,7,2,true);
    delay(750);
  lc.setLed(2,7,4,false);  //Wyłącz na 1/4 sek
  lc.setLed(2,7,2,false);
    delay(250);
  
  lc.setLed(2,7,4,true); //Włącz adresowane dioda na 3/4 sek
  lc.setLed(2,7,2,true);
    delay(750);
  lc.setLed(2,7,4,false);  //Wyłącz na 1/4 sek
  lc.setLed(2,7,2,false);
    delay(250);

  lc.setLed(2,7,4,true); //Włącz adresowane dioda na 3/4 sek
  lc.setLed(2,7,2,true);
  delay(750);
  lc.setLed(2,7,4,false);  //Wyłącz na 1/4 sek
  lc.setLed(2,7,2,false);
    delay(250);

  lc.setLed(2,7,4,true); //Włącz adresowane dioda na 3/4 sek
  lc.setLed(2,7,2,true);
    delay(750);
  lc.setLed(2,7,4,false);  //Wyłącz na 1/4 sek
  lc.setLed(2,7,2,false);
    delay(250);  
  lc.setLed(2,7,4,true); //Włącz adresowane dioda na 3/4 sek
  lc.setLed(2,7,2,true);
    delay(750);
  lc.setLed(2,7,4,false);  //Wyłącz na 1/4 sek
  lc.setLed(2,7,2,false);
    delay(250);  
  lc.setLed(2,7,4,true); //Włącz adresowane dioda na 3/4 sek
  lc.setLed(2,7,2,true);
    delay(750);
  lc.setLed(2,7,4,false);  //Wyłącz na 1/4 sek
  lc.setLed(2,7,2,false);
    delay(250);  
  lc.setLed(2,7,4,true); //Włącz adresowane dioda na 3/4 sek
  lc.setLed(2,7,2,true);
    delay(750);
  lc.setLed(2,7,4,false);  //Wyłącz na 1/4 sek
  lc.setLed(2,7,2,false);
    delay(250);  
  lc.setLed(2,7,4,true); //Włącz adresowane dioda na 3/4 sek
  lc.setLed(2,7,2,true);
    delay(750);
  lc.setLed(2,7,4,false);  //Wyłącz na 1/4 sek
  lc.setLed(2,7,2,false);
    delay(250);  
  lc.setLed(2,7,4,true); //Włącz adresowane dioda na 3/4 sek
  lc.setLed(2,7,2,true);
    delay(750);
  lc.setLed(2,7,4,false);  //Wyłącz na 1/4 sek
  lc.setLed(2,7,2,false);
    delay(250);      
}

void temp() {   //===================================temperatura=============
  lc.clearAll();
  double currentTemperature = barometer.GetTemperature();
  int c = (barometer.GetTemperature());
  //Serial.print (c);
  temp1=c/10;
  temp2=c%10;
  lc.setRow(1,0,B00000100); //stopien
  lc.setRow(1,1,B00001010);
  lc.setRow(1,2,B00000100);
  lc.setRow(1,4,B01111100); // Celsiusz
  lc.setRow(1,5,B10000010);
  lc.setRow(1,6,B10000010);
  lc.setRow(1,7,B10000010);
  lc.setRow(0,0,B01000100);
  
  //===================================temperatura=============
  //lc.setColumn(2,6,B00000011);
//lc.clearDisplay(3);
lc.displayChar(3,temp1);
//lc.clearDisplay(2);
lc.displayChar(2,temp2);
//lc.clearDisplay(0);
//lc.writeString(0,"C");
}

//========================================data===========
void data() {
  RTC.read(tm);
  lc.clearAll();
  int dzien = (tm.Day);
  int miesiac = (tm.Month);
  int rok = (tmYearToCalendar(tm.Year));
  
  dz1 = dzien/10;
  dz2 = dzien%10;
  mies1 = miesiac/10;
  mies2 = miesiac%10;
   
   lc.setLed(2,7,0,true);

  rok1 = (tmYearToCalendar(tm.Year))/1000;
  rok2 = ((tmYearToCalendar(tm.Year))-(rok1 * 1000))/100;
  rok3 = ((tmYearToCalendar(tm.Year))-(rok1 * 1000)-(rok2 * 100))/10;
  rok4 = (tmYearToCalendar(tm.Year))%10;
  
  lc.displayChar(3,dz1);
  lc.displayChar(2,dz2);
  
  lc.displayChar(1,mies1);
  lc.displayChar(0,mies2); 
  delay(3000);
  lc.setLed(2,7,0,false);
  lc.displayChar(3,rok1);
  lc.displayChar(2,rok2); 
  lc.displayChar(1,rok3);
  lc.displayChar(0,rok4);
  delay(3000);
}

void cisnienie() {
  lc.clearAll();
  barometer.SoftReset();
  barometer.Initialize();
  ///  if(barometer.IsConnected)  {
    //getting current preasure in hPa
    long currentPressure = barometer.GetPressure()/100;
    //getting current temp in *C
    double currentTemperature = barometer.GetTemperature();
    Serial.println("Temperatura: ");
    Serial.print(currentTemperature);
    Serial.println("Cisnienie: ");
    Serial.print(currentPressure+BMPMeasurementError);
    Serial.println(" hPa");
    //}   
  int  c1, c2, c3, c4, c5;
  float cisnienie = (currentPressure+BMPMeasurementError);
    Serial.println(cisnienie);
    
    if(cisnienie >= 1000) {
      //  przecinek = 0;
      c1 = cisnienie/1000;
      c2 = (cisnienie - (c1 * 1000))/100;
      c3 = (cisnienie - (c1 * 1000) - (c2 * 100))/10;
      c4 = (cisnienie - (c1 * 1000) - (c2 * 100) - (c3 * 10));
          
          Serial.println("------");
          Serial.println("c1:");
          Serial.println(c1);
          Serial.println("c2:");
          Serial.println(c2);
          Serial.println("c3:");
          Serial.println(c3);
          Serial.println("c4:");
          Serial.println(c4);
  
      lc.displayChar(3,c1);
      lc.displayChar(2,c2);
      lc.displayChar(1,c3);
      lc.displayChar(0,c4);
      delay(3000);     
    }
    else 
    {
      //  przecinek = 1;
      c1 = cisnienie/100;
      c2 = (cisnienie - (c1 * 100))/10;
      c3 = (cisnienie - (c1 * 100) - (c2 * 10))/1;
      c4 = (cisnienie - (c1 * 100) - (c2 * 10) - (c3 * 1));
          
          Serial.println("------");
          Serial.println("c1:");
          Serial.println(c1);
          Serial.println("c2:");
          Serial.println(c2);
          Serial.println("c3:");
          Serial.println(c3);
          Serial.println("c4:");
          Serial.println(c4);
  
      //lc.displayChar(3,c1);
      lc.displayChar(2,c1);
      lc.displayChar(1,c2);
      lc.displayChar(0,c3);
      delay(3000); 
    }
    

}

void zyczenia() {
  
  //if miesiac=9 && dzien=27
  //printStringWithShift(zyczeniaKU,100);

}
//----------------------------------------inne-----------
void single() {
  int delaytime = 30;
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      delay(delaytime);
      lc.setLed(0,row,col,true);
      //delay(delaytime);
      for(int i=0;i<col;i++) {
        lc.setLed(0,row,col,false);
        delay(delaytime);
        lc.setLed(0,row,col,true);
        delay(delaytime);
      }
    }
  }
}
void columns() {
  int delaytime = 30;
  for(int col=0;col<8;col++) {
    delay(delaytime);
    lc.setColumn(0,col,B00000000);
    delay(delaytime);
    lc.setColumn(0,col,(byte)0);
    for(int i=0;i<col;i++) {
      //delay(delaytime);
      lc.setColumn(0,col,B00000000);
      delay(delaytime);
      lc.setColumn(0,col,(byte)0);
    }
  }
}
void mazak() {
      for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      for(int address=0;address<devices;address++) {
        delay(10);
        lc.setLed(address,row,col,true);
        //delay(10);
        //lc.setLed(address,row,col,false);
      }
    }
  }
}

void loop() {
  lc.clearAll();
    printStringWithShift(cisPa, 10);
    printStringWithShift(pusty, 10);
      cisnienie();
    printStringWithShift(hPa, 10);
    printStringWithShift(pusty, 10);      
  
  lc.clearAll();
    printStringWithShift(godzina, 10);
    printStringWithShift(pusty, 10);
    czas();
    
  lc.clearAll();
    printStringWithShift(temperatura, 10);
    printStringWithShift(pusty, 10);
    temp();
      delay(3000);
  
  lc.clearAll();
    printStringWithShift(dzisiaj, 10);
    printStringWithShift(pusty, 10);
      data();
        delay(1000);
  
  lc.clearAll();
  //printCharWithShift(1,50);
  

  //printStringWithShift(zyczenia,90);

  //lc.clearAll();
//single();
//columns();
}




//-----------------------------------lewo-----------
//scrollLeft('O');

//void scrollLeft(char ch){
//  int pos =lc.getCharArrayPosition(ch);
//  for (int scroll =0; scroll<6; scroll++) {
//     for (int i=scroll; i<6;i++) {
//        lc.setRow(0,i-scroll, alphabetBitmap[pos][i]);
//    } 
//    delay(300);
//    lc.clearDisplay(0);
//  }
//}
//-----------------------------------prawo-----------
//void scrollRight(char ch){
//  int pos =lc.getCharArrayPosition(ch);
//  for (int scroll =0; scroll<8; scroll++) {
//     for (int i=0; i<6;i++) {
//        if (scroll+i<8) lc.setRow(0, scroll+i, alphabetBitmap[pos][i]);
//    } 
//    delay(300);
//    lc.clearDisplay(0);
//  }
//}

