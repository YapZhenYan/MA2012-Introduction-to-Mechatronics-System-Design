#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define RxD 11
#define TxD 9
char recvChar;                                        //variable to store character received
char info[7];
String recvStr; 
int recvInt;
int dutycycle; 
int PWM;  
int PWM1;
int PWM2;
int PWM3;
  //variable to store the series of received character
int i;
int x;
boolean blink;
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial slave(RxD,TxD);

void setup()
{
  Serial.begin(9600);
  slave.begin(9600);
  pinMode(RxD, INPUT);                               
  pinMode(TxD, OUTPUT);                          
   // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 1);      //column 0 row 1
  i=0;
}

void loop()
{
  
     if (slave.available())                            //if data is available from the master arduino
  {
    recvChar = slave.read();                        //store character received
    recvStr = String(recvStr + String(recvChar));   //concatenate the recvChar
  }

  else   
    {  
      recvStr.toCharArray(info, 7);

    PWM1 = info[2] -48 ;
    PWM2 = info[3] -48;
    PWM3 = info[4]-48;
    PWM = (PWM1*100) + (PWM2*10) + (PWM3);
 
    if (info[0]== '3' || info[5]=='0')
      {
        dutycycle=0;
      }
    else
      {
        dutycycle = map(PWM,0,255,100,0);
      }
    Serial.println(dutycycle);
    Serial.println(info);
    lcd.setCursor(10, 0);          //column 1 row 1
      recvStr =""; 
    }

    lcd.setCursor(0, 0);
    switch (info[0])
    {
      case ('1'):
      {
        lcd.print("Forward   ");
        lcd.print(dutycycle);
        lcd.println("%     ");
        if (dutycycle >25 && info[1] =='0')
        {
            lcd.setCursor(0,1);
            lcd.print("Safety Belt!");
        }
        else
        {
            lcd.setCursor(0,1);
            lcd.print("                ");
        }
        break;

      }
      case ('2'):
      {
        lcd.print("Reverse   ");
        lcd.print(dutycycle);
        lcd.println("%     ");
        if (dutycycle >25 && info[1] =='0')
        {
            lcd.setCursor(0,1);
            lcd.print("Safety Belt!");
        }
        else
        {
            lcd.setCursor(0,1);
            lcd.print("                ");
        }
        break;
      }
      case ('3'):
      {
        lcd.print("Neutral   ");
        lcd.print(dutycycle);
        lcd.println("%     ");
        if (dutycycle >25 && info[1] =='0')
        {
            lcd.setCursor(0,1);
            lcd.print("Safety Belt!");
        }
        else
        {
            lcd.setCursor(0,1);
            lcd.print("                ");
        }
        break;
      }
    }
  }
