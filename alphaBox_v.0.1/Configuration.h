class Configuration{
  public:
      static int ie;
      static int freq;
      static int volume;
      static int pin;
      static double periodo;
      static double porcentaje;
      static unsigned long lastTime;
      
      static void setFreq(){
      periodo = 1/freq;
      
      }

      static void setIE(){
      }
      
      static int getPreasure(){
      return;
      }
       //Atributos
      static void commission(){
        setIE();
        setFreq();
        getPreasure();
        do{
          digitalWrite(pin,HIGH);
          }while ((millis()- lastTime< (periodo * porcentaje)));
      }
};
