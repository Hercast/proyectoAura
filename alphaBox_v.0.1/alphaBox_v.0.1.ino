
/*Proyect Aura 26-Jan-2021
Contributors:
Eliezer Maduro
Hermes Castellano

*/
#include <Wire.h> 
#include <Thread.h>
#include <ThreadController.h>
#include <LiquidCrystal_I2C.h>

/* Declaracion de pines*/ 
#define EncA 2
#define EncB 3
#define EncButton 4
#define Valve 5 

// int Configuration::freq, Configuration::ie, Configuration::volume; 
int aux,currentStateCLK,lastStateCLK,lastButtonPress,lectura,value;
unsigned long lastTime;
double periodo,freq,ie;
double expOn, expOff;
int freqFut,ieFut;

class ButtonThread: public Thread{
public:
  // Our custom thread attributes
  int pin;
  long duration;
  long _lastButtonPushed;

  ButtonThread(int _pin, long _duration): Thread(){
    // Set our attributes on construct
    pin = _pin;
    duration = _duration;
    _lastButtonPushed = 0;

    // Thread will start disabled
    enabled = false;

    // Configure the pin as INPUT and enable pull-up
    pinMode(pin, INPUT);
    digitalWrite(pin, HIGH);
  }

  bool shouldRun(unsigned long time){
    // Override enabled on thread when pin goes LOW.
    if(digitalRead(pin) == LOW){
      enabled = true;
      if (time > 0){
        _lastButtonPushed = time;
      } else{
        _lastButtonPushed = millis();
      }
    }

    // Let default method check for it.
    return Thread::shouldRun(time);
  }

  void run(){
    // Check if time elapsed since last button push
    if(millis() > _lastButtonPushed + duration){
      // It exceeded time. We should disable it.
      enabled = false;
    }
    Thread::run();
  }
}; 

LiquidCrystal_I2C lcd(0x27,16,2);
ThreadController controller = ThreadController();
Thread enMarcha = Thread();
ButtonThread encoder= ButtonThread(EncButton,10);

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
} 

void commission(){

  periodo = 60 * (1/freq);
  expOn = (periodo/(ie+1))*1000;
  expOff = (ie * (periodo/(ie+1)))*1000;
 
  lastTime = millis();
  do {
    //Serial.println("Prendi la valve");
    digitalWrite(Valve,HIGH);    
  } while(millis()- lastTime < expOn);

  lastTime = millis();
  do {
    //Serial.println("Apague la valve");
    digitalWrite(Valve,LOW);
  }while(millis()-lastTime < expOff);
  
};

void button_callback(){

  //Serial.println("Detecte al encoder");
  static unsigned long buttonLastTime;
  Serial.println("entre al Initial State");
  //Captura de informacion

  //FRECUENCIA

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Frecuencia:");
  buttonLastTime = millis();
  do{

  }while(millis() - buttonLastTime < 1000);
  
  freqFut = freqRead();

  lcd.setCursor(12,0);
  lcd.print(freqFut);
  buttonLastTime = millis();
  do{

  }while(millis() - buttonLastTime < 1000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Relacion I-E:1/");
  ieFut = ieRead();
  lcd.setCursor(15,0);
  lcd.print(ieFut);

  buttonLastTime = millis();
  do{

  }while(millis() - buttonLastTime < 1000);

  freq= freqFut;
  ie = ieFut;
  
};

void setup() {
  Serial.begin(9600);
  //Configuracion del LCD
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
  //Puesta en marcha

} 

void loop() {
  commission();
}
