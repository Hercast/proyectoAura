#include <Wire.h>
#include <Thread.h>
#include <ThreadController.h>
#include <LiquidCrystal_I2C.h>
#include "Configuration.h"
#include "ButtonThread.h"
/* Declaracion de pines*/
#define EncA 1
#define EncB 2
#define EncButton 3
#define Valve 4 
int Configuration::freq, Configuration::ie, Configuration::volume; 

LiquidCrystal_I2C lcd(0x27,16,2);
ThreadController controller = ThreadController();
Thread enMarcha = Thread();
ButtonThread encoder= ButtonThread(EncButton,20000);
int enconderRead(){
  return;
}
void lcd_display(){
    //Display de informacion
  lcd.setCursor(2,1);
  lcd.print("Frecuencia:");
  Configuration::freq = enconderRead();
  lcd.setCursor(2,6);
  lcd.print(Configuration:: freq);
  delay(3000);
} 

void button_callback(){
};

void setup() {
  //Configuracion del LCD
  lcd.init();
  lcd.backlight();
  pinMode(EncButton,INPUT);
    //Mensaje inicial
  lcd.setCursor(2,1);
  lcd.print("Aura Alpha Box");
  delay(3000);
  lcd.clear();
  // Configuracion inicial
  lcd_display();
  encoder.onRun(button_callback);
  encoder.setInterval(1000);
  controller.add(&encoder);
  enMarcha.onRun(Configuration::commission);
  enMarcha.setInterval(20000);
} 
void loop() {
//  controller.run();
}
