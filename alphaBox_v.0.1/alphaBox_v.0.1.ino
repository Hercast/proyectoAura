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
int aux,currentStateCLK,lastStateCLK,lastButtonPress,lectura,freq,ie,value;

LiquidCrystal_I2C lcd(0x27,16,2);
ThreadController controller = ThreadController();
Thread enMarcha = Thread();
ButtonThread encoder= ButtonThread(EncButton,20000);

// Update this shit, use value directly. Get rid of dataRead.


int freqRead(){
  int aux = 1;
  static int counter, counter2;

  while (aux == 1) {
    currentStateCLK = digitalRead(EncA);
        if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
        // If the DT state is different than the CLK state then
        // the encoder is rotating CCW so decrement
          if (digitalRead(EncB) != currentStateCLK) {
            counter = counter - 20;
            counter = min(max(0,counter),100);
            counter2 = map(counter,0,100,10,15);
          }  else {
            // Encoder is rotating CW so increment
            counter = counter + 20;
            counter = min(max(0,counter),100);
            counter2 = map(counter,0,100,10,15);
          }
        }
    
    lcd.setCursor(12,0);
    lcd.print(counter2);
    lastStateCLK = currentStateCLK;
    
    Serial.println(counter2);
    if (digitalRead(EncButton) == LOW){
        if (millis()- lastButtonPress > 50){
          aux = 0;
        }
      lastButtonPress = millis();
    }
  }
  return counter2;
}
int ieRead(){
  int aux = 1;
  static int counter, counter2;

  while (aux == 1) {
    currentStateCLK = digitalRead(EncA);
        if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
        // If the DT state is different than the CLK state then
        // the encoder is rotating CCW so decrement
          if (digitalRead(EncB) != currentStateCLK) {
            counter = counter - 10;
            counter = min(max(0,counter),30);
            counter2 = map(counter,0,30,1,3);
          }  else {
            // Encoder is rotating CW so increment
            counter = counter + 10;
            counter = min(max(0,counter),30);
            counter2 = map(counter,0,30,1,3);
          }
        }
    
    lcd.setCursor(15,0);
    lcd.print(counter2);
    lastStateCLK = currentStateCLK;
    
    Serial.println(counter2);
    if (digitalRead(EncButton) == LOW){
        if (millis()- lastButtonPress > 50){
          aux = 0;
        }
      lastButtonPress = millis();
    }
  }
  return counter2;


}
void initial_state(){
  
    Serial.println("entre al Initial State");
    //Captura de informacion

    //FRECUENCIA
      lcd.setCursor(0,0);
      lcd.print("Frecuencia:");
      freq = freqRead();

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
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Relacion I-E:1/");
      ie = ieRead();
      lcd.setCursor(15,0);
      lcd.print(ie);
      delay(1000);
      

      
      /*
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

} 


void button_callback(){
};

void setup() {
  Serial.begin(9600);
  //Configuracion del LCD
  Configuration configuracion;
  lcd.init();
  lcd.backlight();
  pinMode(EncButton,INPUT_PULLUP);
  pinMode(Valve,OUTPUT);
    //Mensaje inicial
  lcd.setCursor(2,1);
  lcd.print("Aura Alpha Box");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ajustar");
  lcd.setCursor(2,1);
  lcd.print("lentamente");
  lcd.clear();
  lastStateCLK = digitalRead(EncA);
  // Configuracion inicial
  initial_state();
  lcd.setCursor(2,1);
  lcd.print("Sali del initial state");
  encoder.onRun(button_callback);
  encoder.setInterval(1000);
  controller.add(&encoder);
  enMarcha.onRun(configuracion.commission);
  enMarcha.setInterval(20000);
} 
void loop() {
//  controller.run();
}
