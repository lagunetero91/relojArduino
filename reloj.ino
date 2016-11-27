
#define time 0.000064
uint8_t hours=23,minutes=58,seconds=1,days=31,months=12;
uint8_t dias_mes=31;
uint16_t years = 1999;
volatile uint64_t overflows= 0;

ISR(TIMER1_OVF_vect){
  overflows++; 
}


void setup(){
 Serial.begin(9600);
  TCCR1A |= (1<<(WGM11)) | (1<<(WGM10));
  TCCR1B |= (1<<(WGM12)) | (1<<(CS10));
  TCCR1B &= ~(1<<(CS12)) & ~(1<<(WGM13)) & ~(1<<(CS11));
  TIMSK1 |= (1<<(TOIE1));
 interrupts();
}


void loop(){

  getTime();
  delay(1000);
}

void getTime(){
  TIMSK1 &= ~(1<<(TOIE1));
  uint64_t aux = overflows;
  TIMSK1 |= (1<<(TOIE1));
  seconds = (int)(aux*time)%60;
  if(seconds == 0){
    minutes++;
    if(minutes == 60){
      minutes=0;
      hours++;
      if (hours == 24){
        hours=0;
        days++;
        if(days > dias_mes){
          days=1;
          months++;
          switch(months){
             case 2:
               dias_mes=28;
               break;
              case 4:
               dias_mes=30;
               break;
             case 6:
               dias_mes=30;
               break;
             case 9:
               dias_mes=30;
               break;
             case 11:
               dias_mes=30;
               break;
             default :
               dias_mes=31;
            }
          if(months > 12){
            months=1;
            years++;
          }
        }
      }
    }
  }


  Serial.print(hours);Serial.print(":");Serial.print(minutes);Serial.print(":");Serial.println(seconds); 
  
     Serial.print(days);Serial.print("/");
      Serial.print(months);Serial.print("/");
       Serial.println(years);
}


