class Configuration {
  private:
      double periodo;
      void _setFreq(freq){
      periodo = 1/freq;
      }

      void _setIE(ie){
      }
      int getPreasure(){
      return
      }
   
  public:
    //Atributos
    int ie;
    int freq;
    int volume;
    int pin;
    Configuration(int _ie, int _freq, int _pin){
      ie=_ie;
      freq=_freq
      pin = _pin;
      pinMode(pin,OUTPUT)
      
    }
    void commission(pin,){
      }
}
    