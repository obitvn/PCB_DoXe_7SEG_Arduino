
#include <TM1637Display.h>
#include <Servo.h>


#define UP     2
#define DOWN   3
#define MAX    4
#define BARRIE_IN 11
#define BARRIE_OUT 12

#define SCLK   5
//#define RCLK   6
#define DIO    6
#define MODE   A0

#define SERVO_1 9
#define SERVO_2 10

#define SENSOR_1 A5
#define SENSOR_2 A4
#define SENSOR_3 A3
#define SENSOR_4 A2

Servo myservo1; 
Servo myservo2;


TM1637Display display(SCLK, DIO);

#define  MAX_SLOT_CAR  12
int slot_car;


void ControlBarrie()
{
  if(digitalRead(SENSOR_1) == 0)
  {
    while(digitalRead(SENSOR_1) == 0)
    {
      myservo1.write(90);
    };
    slot_car--;
    if(slot_car<0) slot_car=0;
    display.showNumberDec(slot_car);
    
    
  }

  else if(digitalRead(SENSOR_3) == 0)
  {
    
    while(digitalRead(SENSOR_3) == 0)
    {
      myservo2.write(90);
    };
    slot_car++;
    if(slot_car>MAX_SLOT_CAR) slot_car = MAX_SLOT_CAR;
    display.showNumberDec(slot_car);
    
  }
 
  if((digitalRead(SENSOR_2) == 0))
  {
    while(digitalRead(SENSOR_2) == 0)
    {
    };
    myservo1.write(0);
  }
  else if(digitalRead(SENSOR_4) == 0)
  {
    while(digitalRead(SENSOR_4) == 0)
    {
    };
    myservo2.write(0);
    
  }
  
}


void ScanButton()
{
  if(digitalRead(BARRIE_IN)== 0)
  {
    while(digitalRead(BARRIE_IN)== 0)
    {
      myservo1.write(90);
    }
    myservo1.write(0);
  }
  
  else if(digitalRead(BARRIE_OUT)== 0)
  {
    while(digitalRead(BARRIE_OUT)== 0)
    {
      myservo2.write(90);
    }
    myservo2.write(0);
  }

  else if(digitalRead(UP)== 0)
  {
    while(digitalRead(UP)== 0){};
    slot_car++;
    if(slot_car>MAX_SLOT_CAR) slot_car = MAX_SLOT_CAR;
  }
  else if(digitalRead(DOWN)== 0)
  {
    while(digitalRead(DOWN)== 0){};
    slot_car--;
    if(slot_car<0) slot_car=0;
  }
  else if(digitalRead(MAX)== 0)
  {
    while(digitalRead(MAX)== 0){};
    slot_car = MAX_SLOT_CAR;
    display.clear();
    delay(200);
    display.showNumberDec(slot_car);
    delay(200);
    display.clear();
    delay(200);
    display.showNumberDec(slot_car);
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(UP,INPUT);
  pinMode(DOWN,INPUT);
  pinMode(MAX,INPUT);
  pinMode(BARRIE_IN,INPUT);
  pinMode(BARRIE_OUT,INPUT);
  pinMode(MODE,INPUT);

  pinMode(SENSOR_1,INPUT);
  pinMode(SENSOR_2,INPUT);
  pinMode(SENSOR_3,INPUT);
  pinMode(SENSOR_4,INPUT);
  //display.home();
  display.clear();
  slot_car = MAX_SLOT_CAR;
  display.setBrightness(0x0a);
  myservo1.attach(SERVO_1); 
  myservo2.attach(SERVO_2); 

  myservo1.write(90);
  myservo2.write(90);
  delay(1000);
  myservo1.write(0);
  myservo2.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(digitalRead(MODE)== 0)
  {
   ControlBarrie();
  }
  else
  {
   ScanButton();
  }
  
  
  display.showNumberDec(slot_car);
}
