chclass Configuration{
  public:
    static int ie;
    static int freq;
    static int volume;
    static int pin;
    static double periodo;
    static double porcentaje;
    static unsigned long lastTime;

    Configuration();

    
           
    static void commission(){
      periodo = 1/freq;
      lastTime= millis();

      do{
        digitalWrite(pin,HIGH);    
      }while ((millis()- lastTime < (periodo/(1+ie))));

      lastTime = millis();

      do {
        digitalWrite(pin,LOW);
        }while((millis()-lastTime) < (ie*(periodo/(1+ie))));
    }
};