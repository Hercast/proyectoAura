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
int aux,currentStateCLK,lastStateCLK,lastButtonPress,lectura,freq,ie,value,counter;

LiquidCrystal_I2C lcd(0x27,16,2);
ThreadController controller = ThreadController();
Thread enMarcha = Thread();
ButtonThread encoder= ButtonThread(EncButton,20000);

// Update this shit, use value directly. Get rid of dataRead.


int encoderRead(){

  currentStateCLK = digitalRead(EncA);
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

      // If the DT state is different than the CLK state then
      // the encoder is rotating CCW so decrement
      if (digitalRead(EncB) != currentStateCLK) {
        counter = counter - 5;
        
        }  else {
          // Encoder is rotating CW so increment
          counter = counter + 5;
        
      }

    }
  lastStateCLK = currentStateCLK;
  return counter;
}

int initial_state(){
  
    Serial.println("entre al Initial State");
    aux = 0;
    //Captura de informacion

    //FRECUENCIA
    
    do {
      
      aux= 0;
      lcd.setCursor(0,0);
      lcd.print("Frecuencia:");
      freq = encoderRead();

      /*
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

          //Update with a default statement.  
        }*/
       
      lcd.setCursor(12,0);
      lcd.print(freq);

      
      
      if (digitalRead(EncButton) == LOW){
        if (millis()- lastButtonPress > 50){
        aux = 1;
        }
        lastButtonPress = millis();
      }
    } while(aux == 0);
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

return 0;} 


void button_callback(){
};

void setup() {
  Serial.begin(9600);
  //Configuracion del LCD
  lcd.init();
  lcd.backlight();
  pinMode(EncButton,INPUT_PULLUP);
    //Mensaje inicial
  lcd.setCursor(2,1);
  lcd.print("Aura Alpha Box");
  delay(3000);
  lcd.clear();
  lastStateCLK = digitalRead(EncA);
  // Configuracion inicial
  int prueba = initial_state();
  lcd.setCursor(2,1);
  lcd.print("Sali del initial state");
  encoder.onRun(button_callback);
  encoder.setInterval(1000);
  controller.add(&encoder);
  enMarcha.onRun(Configuration::commission);
  enMarcha.setInterval(20000);
} 
void loop() {
//  controller.run();
}
