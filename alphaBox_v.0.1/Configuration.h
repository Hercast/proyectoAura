class Configuration{
  public:
      static int ie;
      static int freq;
      static int volume;
      static int pin;
      static double periodo;
      static void setFreq(int freq){
      periodo = 1/freq;
      }

      static void setIE(int ie){
      }
      static int getPreasure(){
      return;
      }
       //Atributos
      static void commission(){
      }
};
