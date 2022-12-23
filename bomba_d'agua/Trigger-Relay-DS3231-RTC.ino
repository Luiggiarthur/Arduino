#include <DS3231.h>

int Relay = 4;

DS3231  rtc(SDA, SCL);
Time t;

 int OnHour = 23; //configura hora de ligar bomba d'agua
 int OffMin = 30; // minuto
  
 int OffHour = OnHour; //configura hora de desligar bomba d'agua
 int OnMin = OffMin+5; //minuto 
 
void setup() {
  Serial.begin(115200);
  rtc.begin();
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, HIGH);
}

void loop() {
  t = rtc.getTime();


  Serial.print(t.hour);
  Serial.print(" hour(s), ");
  Serial.print(t.min);
  Serial.print(" minute(s)");       
  Serial.println(" ");


// configura a bomba d'agua para funcionar todos os dias com intervalo de 1h
if (OnHour < 24){
 while( OffHour != t.hour )
            {     
              OnHour = OnHour+1;
              OffHour = OnHour;
              }

}
              else{
                
              OnHour = 0;
              OffHour = OnHour;
              }
 
  delay (1000);

    //liga a bomba d'agua
    if(t.hour == OnHour && t.min == OnMin)
  {
     digitalWrite(Relay,HIGH);
    Serial.println("LIGHT ON");
    OnHour = OnHour+2;}
    
    // desliga a bomba d'agua
    else if(t.hour == OffHour && t.min == OffMin){
      digitalWrite(Relay,LOW);
      Serial.println("LIGHT OFF");
      
    }
 //  Serial.print(OffMin) ;
  // Serial.print(OnMin) ;
}
