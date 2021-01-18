class Configuration {
  public:
    //Atributos
    int ie;
    int freq;
    int volume;
    double periodo;
    int pin;
    Configuration(int _ie, int _freq, int _pin){
      ie=_ie;
      freq=_freq
      pin = _pin;
      pinMode(pin,OUTPUT)
      
    }
    void start(){
      }
    void setFreq(freq){
      periodo = 1/freq;
      }

    void setIE(ie){
      }
    int getPreasure(){
      return
      }
    void commission(){
      }
}
    
