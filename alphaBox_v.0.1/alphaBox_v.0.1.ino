#include <Thread.h>
#include <ThreadController.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
/* Declaracion de pines*/
#define EncA 1
#define EncB 2
#define EncButton 3 
int freq, ie, volume; 

LiquidCrystal_I2C lcd(0x27,16,2);

/* Dependiendo de la cantidad de procesos se define la cantidad de tread

  1. Thread para la recoleccion de datos: En este thread de debe iniciar la comunicacion
  serial de datos con el sensor a traves del protocolo ic2, usando la libreria Wire, para ello
  se usan dos pines del arduino para enviar datos y pulso de reloj

  2. Thread para monitoreo de boton del encoder: Con este thread se va a evualar si el boton es
  precionado, luego si es precionado.

*/

ThreadController controller = ThreadController();
Thread lcdThread = Thread();

/*class ButtonThread: public Thread{
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
      _lastButtonPushed = (time ? time : millis());
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
};  */
const lcd_callback(int freq,int ie,int volume){
  
  };
  
void setup() {
  //Configuracion del LCD
  lcd.init();
  lcd.backlight();
  Wire.begin();
  
  Serial.begin(9600);
  lcdThread.onRun(lcd_callback(freq,ie,volume));
  lcdThread.setInterval(1000);
  controller.add(&lcdThread);
} 

void loop() {
  controller.run();
}
