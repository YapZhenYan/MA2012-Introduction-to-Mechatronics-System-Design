#include <SoftwareSerial.h>

#define RxD 9             // receiver pin for SPI
#define TxD 11            // transmitter pin for SPI
#define led1 8
#define led2 7
#define pot1 A0           // accelerator for speed control
#define pot2 A1  
#define TS2 3             
#define TS3 4             //Toggle switch for gear selection
#define pushbutton A5     // Push button ON and OFF
#define DCpin1 5
#define DCpin2 6
#define OS 10             // opto switch for seatbelt
#define buzzer 2

int TSstatus;             // Toggle switch, 1 - forward, 2 - reverse, 3 neutral
bool seatbelt;            // TRUE - seatbelt on , FALSE - seatbelt off
bool carstatus;           // TRUE - ON, FALSE - OFF
int PWM;
String sendinfo;
char sendchar[7];
int j;
int k;
int h;

SoftwareSerial master(RxD,TxD);

void setup() {
   pinMode(RxD, INPUT);
   pinMode(TxD, OUTPUT);
   Serial.begin(9600);
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
   pinMode(pot1, INPUT);
   pinMode(pot2, INPUT);
   pinMode(TS2, INPUT);
   pinMode(TS3, INPUT);
   pinMode(pushbutton, INPUT);
   pinMode(DCpin1, OUTPUT);
   pinMode(DCpin2, OUTPUT);
   pinMode(OS, INPUT);
   pinMode(buzzer, OUTPUT);
   digitalWrite(led1, HIGH);
   digitalWrite(led2, HIGH);
   master.begin(9600);
 
}

void loop() {

 
    PWM = map(analogRead(pot1),0,1023,0,255);  // checking potentiometer
    
    if(digitalRead (OS) == LOW)  // checking the seatbelt state
    {
      seatbelt = false;
    }
    else
    {
      seatbelt = true;
    }
   
    if ((digitalRead(TS2)==HIGH) && (digitalRead(TS3)==HIGH))   // Checking the state of toggle switch
    {
      TSstatus = 3;   //NEUTRAL
    }
    else if ((digitalRead(TS2)==HIGH) && (digitalRead(TS3)==LOW))
    {
      TSstatus = 1;  //POSITION 1 : Forward
    }
    else if ((digitalRead(TS2)==LOW )&& (digitalRead(TS3)==HIGH))
    {
      TSstatus = 2;  //POSITION 2: Reverse
    }

 for(int i=0; i<=5; i++)
 {
   if( i==0)
   {
    sendchar[i]= char(TSstatus);
    }
    if( i==1)
    {
      sendchar[i]= char(seatbelt);
    }
    if(i==2)
    {
      j = PWM / 100 ;
      sendchar[i] =  char( j);
    }
    if(i==3)
    {
      j = (PWM / 10) % 10 ;
      sendchar[i] = char(j);
    }
    if(i==4)
    {
       j= PWM % 10; 
       sendchar[i] = char(j);
    }
    if(i==5)
    {
       sendchar[i] = char(carstatus);
    }
     
 }

    if ((carstatus == false) && (TSstatus == 3))   // turning ON operation
    {
      int i=0;
      while (analogRead(pushbutton) ==0)
      {
        if (analogRead(pushbutton)== 0)
        {
          i++;
          delay (100);
        }
        if (i== 10)
        {
          digitalWrite(led1, LOW);   // LOW - light up
          tone(buzzer, 1000, 1000);   
          carstatus = true;
          delay (2000);
          break;
        }
      }
    }
  
    if (carstatus == true)    // turning OFF operation
    {
      if (analogRead(pushbutton) == 0)
      {
        carstatus = false;
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        direction(3, PWM);  // NEUTRAL/BRAKE
      }
    }

    if (carstatus == true)   // while the car is ON
    {
      if (TSstatus == 1)
      {
        direction(1, PWM);   // FORWARD
         if (seatbelt == false && PWM <= (255*3 /4))   
          {
           blinkWithoutDelay();
          }

      }
      else if (TSstatus == 2)
      {
        direction(2, PWM);  // REVERSE
        tone(buzzer, 500);
         if (seatbelt == false && PWM <= (255*3 /4))   
       {
          blinkWithoutDelay();
       }

      }
      else
      {
        direction(3, PWM);  // NEUTRAL/BRAKE
      }
    }
 sendinfo = String(sendchar[0]*100000+sendchar[1]*10000+sendchar[2]*1000+sendchar[3]*100+sendchar[4]*10 +sendchar[5]);
 sendinfo.toCharArray(sendchar,7);
 Serial.println(sendchar);
 if (k%10 ==0)
 {
 master.write(sendchar);
 k=1;
 }
 k++;
}

void direction (int dir, int PWM)
{
  //dir 1 = forward
  //    2 = reverse
  //    0 = stop

  switch (dir)
  {
    case (2):
    {
      analogWrite(DCpin1,255-PWM);
      digitalWrite(DCpin2,LOW);
      break;
    }
    case(1):
    {
      analogWrite(DCpin1,PWM);
      digitalWrite(DCpin2,HIGH);
      noTone(buzzer);
      
      break;
    }
    case(0):
    {
      analogWrite(DCpin1,0);
      digitalWrite(DCpin2,LOW);
      noTone(buzzer);
      break;
    }
    default: // also brake
     {
      analogWrite(DCpin1,0);
      digitalWrite(DCpin2,LOW);
      noTone(buzzer);
      break;
    }
  }
  
}

void blinkWithoutDelay()
{
  unsigned long interval = 500; //ms
  unsigned long currentMillis = millis();         //store program runtime into currentMillis
  static unsigned long prevMillis;                //static variable to store the time instance when led state is toggled. static variable will self initialize to 0
  static int count;                               //static variable to store how many times the led has blink

  static boolean ledstate = LOW;                  //initialize ledstate to LOW

  if ((currentMillis - prevMillis) > interval)    //Toggle led state if the elapsed time between the last toggle time instance and current runtime is more than interval
  {
    ledstate =! ledstate;                         //toggle led state
    digitalWrite(7 , ledstate);
    prevMillis = currentMillis;                   //update toggle time instance                                   
  }
}
