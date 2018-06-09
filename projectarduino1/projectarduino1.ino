#include <Stepper.h>
#include<math.h>
#include <USBAPI.h>
#include <String.h>

#define StepsPerRevolution 200   //Change according to motor
#define pitch 1 //Pitch of ballscrew
#define scale 1000  //scale

Stepper xmotor(100,1,2),ymotor(100,3,4);

void step2(Stepper mot1, Stepper mot2, int time) {
    if(mot2.step_delay<mot1.step_delay){
        Stepper tmp=mot1;
        mot1=mot2;
        mot2=tmp;
    }

    while(micros()<(1000000*time))
    {
        if(micros()-mot1.last_step_time>mot1.step_delay)
        {
            mot1.last_step_time=micros();
            if (mot1.direction == 1)
            {
                mot1.step_number++;
                if (mot1.step_number == mot1.number_of_steps)
                {
                    mot1.step_number = 0;
                }
            }
            else
            {
                if (mot1.step_number == 0)
                {
                    mot1.step_number = mot1.number_of_steps;
                }
                mot1.step_number--;
            }
            // decrement the steps left:
            //steps_left--;
            // step the motor to step number 0, 1, ..., {3 or 10}
            if (mot1.pin_count == 5)
                mot1.stepMotor(mot1.step_number % 10);
            else
                mot1.stepMotor(mot1.step_number % 4);

            if(micros()-mot2.last_step_time>mot2.step_delay)
            {
                mot2.last_step_time=micros();
                if (mot2.direction == 1)
                {
                    mot2.step_number++;
                    if (mot2.step_number == mot2.number_of_steps)
                    {
                        mot2.step_number = 0;
                    }
                }
                else
                {
                    if (mot2.step_number == 0)
                    {
                        mot2.step_number = mot2.number_of_steps;
                    }
                    mot2.step_number--;
                }
                // decrement the steps left:
                //steps_left--;
                // step the motor to step number 0, 1, ..., {3 or 10}
                if (mot2.pin_count == 5)
                    mot2.stepMotor(mot2.step_number % 10);
                else
                    mot2.stepMotor(mot2.step_number % 4);
            }

        }
    }
}


float angle=0,pi=3.14;
float motx,moty;
String inData;

void radtodeg(){
    angle=angle*(180/pi);
}

void degtorad(){
    angle=angle*(pi/180);
}

void rt(float x){
    radtodeg();
    angle+=x;
    degtorad();
}


void lt(float x){
    radtodeg();
    angle-=x;
    degtorad();
}

void fd(int x){
    xmotor.setSpeed(motx);
    ymotor.setSpeed(moty);
    step2(xmotor,ymotor,x);
    xmotor.setSpeed(0);
    ymotor.setSpeed(0);
}

void bk(int x){
    xmotor.setSpeed(-motx);
    ymotor.setSpeed(-moty);
    step2(xmotor,ymotor,x);
    xmotor.setSpeed(0);
    ymotor.setSpeed(0);
}


void comp(){
    char inChar=-1; // Where to store the character read
 while(Serial.available())
 {
   inChar = Serial.read();  
     inData = inData + inChar;
    if(inChar=='\n') 
   {
     break;
   }    
 }
   //return inData;
}


void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {

  motx=100*sinf(angle);
  moty=100*cosf(angle);
  
  comp();
  if(inData=="fd"){
    comp();
    int x=inData.toInt();
    fd(x);                  
  }
  if(inData=="bk"){
    comp();
    int x=inData.toInt();
    bk(x);
  }
  if(inData=="rt"){
    comp();
    float x=inData.toFloat();
    rt(x);         
  }
  if(inData=="lt"){
    comp();
    float x=inData.toFloat();
    lt(x);         
  }
}

