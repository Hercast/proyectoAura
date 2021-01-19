#include <Wire.h> 
#include <Thread.h>
#include <ThreadController.h>
#include <LiquidCrystal_I2C.h>
#include "Configuration.h"
#include "ButtonThread.h"
/* Declaracion de pines*/
#define EncA 2
#define EncB 3
#define EncButton 4
#define Valve 5 

int Configuration::freq, Configuration::ie, Configuration::volume; 
int aux,currentStateCLK,lastStateCLK,lastButtonPress,counter,lectura,freq,ie,value;

LiquidCrystal_I2C lcd(0x27,16,2);
ThreadController controller = ThreadController();
Thread enMarcha = Thread();
ButtonThread encoder= ButtonThread(EncButton,20000);


int dataRead(){

  encoderRead();
   
  return value;
}

void encoderRead(){

  counter = 0;
  currentStateCLK = digitalRead(EncA);
      if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

           // If the DT state is different than the CLK state then
          // the encoder is rotating CCW so decrement
        if (digitalRead(EncB) != currentStateCLK) {
          counter = counter - 20;
          if (counter < 0) {
            counter = 0;
          }
        } else {
          // Encoder is rotating CW so increment
          counter = counter + 20;
          if (counter > 100){
          counter = 100;
          }
        }

      }
  value = counter;
  lastStateCLK = currentStateCLK;
  
}

void initial_state(){
    //Clock del encoder
    lastStateCLK = digitalRead(EncA);
    aux = 0;
    //Captura de informacion

        //FRECUENCIA

    do {

      lcd.setCursor(2,1);
      lcd.print("Frecuencia:");
      freq = dataRead();
      switch (freq) {


    case '0':
      freq = 10;
      break;

    case '20':
      freq = 11;
      break;

    case '40':
      freq = 12;
      break;

    case '60':
      freq = 13;
      break;

    case '80':
      freq = 14;
      break;

    case '100':
      freq = 15;
      break;  
  }
      Configuration::freq = freq;
      lcd.setCursor(2,6);
      lcd.print(Configuration::freq);

      if (digitalRead(EncButton) == LOW){
        if (millis()- lastButtonPress > 50){
        aux = 1;
        }
        lastButtonPress = millis();
      }
    } while(aux = 0);
/*
        //RELACION IE
    do {

      lcd.setCursor(2,1);
      lcd.print("Relacion IE:");
      ie = dataRead();
      
      Configuration::freq = freq;
      lcd.setCursor(2,6);
      lcd.print(Configuration::freq);

      if (digitalRead(EncButton) == LOW){
        if (millis()- lastButtonPress > 50){
        aux = 2;
        }
        lastButtonPress = millis();
      }
    } while(aux = 1); 
    */

    



} 

void button_callback(){
};

void setup() {
  //Configuracion del LCD
  lcd.init();
  lcd.backlight();
  pinMode(EncButton,INPUT_PULLUP);
    //Mensaje inicial
  lcd.setCursor(2,1);
  lcd.print("Aura Alpha Box");
  delay(3000);
  lcd.clear();
  // Configuracion inicial
  initial_state();
  encoder.onRun(button_callback);
  encoder.setInterval(1000);
  controller.add(&encoder);
  enMarcha.onRun(Configuration::commission);
  enMarcha.setInterval(20000);
} 
void loop() {
//  controller.run();
}
