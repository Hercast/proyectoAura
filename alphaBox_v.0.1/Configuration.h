class Configuration{
  private:
      int ie;
      int freq;
      int volume;
      int pin;
      double periodo;
      Configuration(int _ie, int _freq, int _pin){
        ie=_ie;
        freq=_freq;
        pin = _pin;
        pinMode(pin,OUTPUT);
      }
      void _setFreq(int freq){
      periodo = 1/freq;
      }

      void _setIE(int ie){
      }
      int getPreasure(){
      return;
      }
   
  public:
    //Atributos
    void commission(int pin){
      }
};
    
