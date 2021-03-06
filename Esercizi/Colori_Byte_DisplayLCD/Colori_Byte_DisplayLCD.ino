#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

const long int info = 190568851; // 190568851 = 001 011 010 110 111 101 100 110 010 011
String    nome[] = {"R: ", "G: ", "B: "};
String    nom[]  = {"R"  , "G"  , "B"  };
const int Pin [] = { 3   ,  6   ,  5   };
const int Pos [] = { 2   ,  8   ,  14  };
boolean   val [] = {true , false, false};
boolean valBar;
long int c;

int temp = 1, v = 1;

byte p1[8] = {B10000, B10000, B10000, B10000, B10000, B10000, B10000, B10000};
byte p2[8] = {B11000, B11000, B11000, B11000, B11000, B11000, B11000, B11000};
byte p3[8] = {B11100, B11100, B11100, B11100, B11100, B11100, B11100, B11100};
byte p4[8] = {B11110, B11110, B11110, B11110, B11110, B11110, B11110, B11110};
byte p5[8] = {B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111};
byte p6[8] = {B00000, B00100, B01010, B10001, B11111, B00000, B00000, B00000};
byte p7[8] = {B00000, B00000, B00000, B11111, B10001, B01010, B00100, B00000};



void setup() {
  lcd.init();
  lcd.backlight();
  
  lcd.createChar(1, p1);
  lcd.createChar(2, p2);
  lcd.createChar(3, p3);
  lcd.createChar(4, p4);
  lcd.createChar(5, p5);
  lcd.createChar(6, p6);
  lcd.createChar(7, p7);
  
  lcd.home();
  lcd.print("-----LED  RGB-----");
  
  pinMode(4, OUTPUT);
  for (int i = 0; i<3; i++){ pinMode(Pin[i], OUTPUT); }   
  c = info;
  //aumenta(Pin[0],0);    //001
}

void loop() {
  for (int i = 0; i<3; i++){
    if      ((c&1) == true  && val[i] == false) { aumenta   (Pin[i],i); val[i] = true ; }
    else if ((c&1) == false && val[i] == true ) { diminuisci(Pin[i],i); val[i] = false; }
      lcd.setCursor(Pos[i], 1); lcd.print (nome[i]); lcd.print(c&1);
    c = c >> 1;
  }
  lcd.setCursor(0,1);  
  if (c == 0){c = info;}
}

void aumenta(int pin, int n) {
  lcd.setCursor(9,2); lcd.print(nom[n]); lcd.write(6); 
  if (valBar == true) { delBar();}
  for (int i = 0; i <=255; i+=v){
    bar(i);
    analogWrite(pin,i);
    delay(temp);
 }
 valBar = true;
}

void diminuisci(int pin, int n) {
  lcd.setCursor(9,2); lcd.print(nom[n]); lcd.write(7); 
  for (int i = 255; i >= 0; i-=v){
    bar(i);
    analogWrite(pin,i);
    delay(temp);
  }
  valBar = false;
}

void bar(int val) {
 lcd.setCursor(0,3);
 val = map (val,0,255,0,100);
 for(int i = 0; i<val/5 ;i++) { lcd.write(5);}
 if ( val%5 != 0) {lcd.write(val%5);} else if (val != 100) {lcd.print(" ");}
}

void delBar() {
  lcd.setCursor(0,3);
  lcd.print("                    ");
}






