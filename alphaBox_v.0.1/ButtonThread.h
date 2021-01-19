#include <Thread.h>
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
}; 
