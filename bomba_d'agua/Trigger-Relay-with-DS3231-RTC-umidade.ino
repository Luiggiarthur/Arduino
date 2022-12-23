#include <DS3231.h>
#define pinSensorA A0
#define pinSensorD 8

int Relay = 4;

DS3231  rtc(SDA, SCL);
Time t;

 int OnHour = 23; //liga bomba hora
 int OffMin = 30; //liga bomba minuto
  
 int OffHour = OnHour; //Desliga bomba hora 
 int OnMin = OffMin+5; //Desliga bomba minuto 
 int Offumidade = OffMin-5;
void setup() {
  Serial.begin(115200);
  rtc.begin();
  pinMode(pinSensorD, INPUT);
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

// SENSOR DE UMIDADE
if (digitalRead(pinSensorD)) {
     Serial.print("SEM UMIDADE ");
    
     digitalWrite(Relay,HIGH);
    Serial.println("LIGHT ON");
  }
  
  else if(t.hour == OffHour && t.min == Offumidade)
  {
     Serial.print("COM UMIDADE ");
     digitalWrite(Relay,LOW);
      Serial.println("LIGHT OFF");
  }

   // REAL TIME CLOCK

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

  
    if(t.hour == OnHour && t.min == OnMin)
  {
     digitalWrite(Relay,HIGH);
    Serial.println("LIGHT ON");
    OnHour = OnHour+1;}
    
    
    else if(t.hour == OffHour && t.min == OffMin){
      digitalWrite(Relay,LOW);
      Serial.println("LIGHT OFF");
      
    }
 //  Serial.print(OffMin) ;
  // Serial.print(OnMin) ;
}
