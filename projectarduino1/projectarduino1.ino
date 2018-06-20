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
    radtodeg();
    angle=angle*(pi/180);
    degtorad();
}

void rt(float x)
{
    radtodeg();
    angle+=x;
    degtorad();
   
}


void lt(float x){
    
    angle-=x;
    
   
}

void fd(int x){
    int k=abs(motx);
    int l=abs(moty);
    
    xmotor.setSpeed(k+0.0001);
    ymotor.setSpeed(l+0.0001);
    if(moty<0)
    {
        ymotor->direction=1;
    }
     if(motx<0)
    {
        xmotor->direction=1;
    }
    step2(xmotor,ymotor,x);
    xmotor.setSpeed(0.0001);
    ymotor.setSpeed(0.0001);
}

void bk(int x){
    xmotor.setSpeed(-motx-0.0001);
    ymotor.setSpeed(-moty-0.0001);
    step2(xmotor,ymotor,x);
    xmotor.setSpeed(0.0001);
    ymotor.setSpeed(0.0001);
}

string inData="";
void comp(){
    char inChar=-1; 
    string inData="";
    // Where to store the character read
 while(Serial.available())
 {
   inChar = Serial.read();  
     inData = inData + inChar;
    if(inChar=='\n') 
   {
     break;
   }    
 }
   
}


void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}
int z=0;
int flag=0;
void loop() {
    
  motx=100*sinf(angle);
  moty=100*cosf(angle);
 
  comp();
     
  if(inData=="fd"){
      if(flag==0)
      {
    comp();
      }
      else if(flag==1)
      {
          indata=str[z+1];
          z++;
      }
    int x=inData.toInt();
    fd(x);                  
  }
  if(inData=="bk"){
       if(flag==0)
      {
    comp();
      }
      else if(flag==1)
      {
          indata=str[z+1];
          z++;
      }
    int x=inData.toInt();
    bk(x);
  }
  if(inData=="rt"){
       if(flag==0)
      {
    comp();
      }
      else if(flag==1)
      {
          indata=str[z+1];
          z++;
      }
    float x=inData.toFloat();
    rt(x);         
  }
  if(inData=="lt"){
       if(flag==0)
      {
    comp();
      }
      else if(flag==1)
      {
          indata=str[z+1];
          z++;
      }
    float x=inData.toFloat();
    lt(x);         
  }
        if(inData=="repeat")
        {
            comp();
             int times=inData.toInt();
            comp();
                        if(indata=="[")
                        {

                                             String str[100];
                                                int count=0;
                                            loop();
                                            while(indata!="]")
                                            {

                                                str[count]=indata;
                                                count++;
                                                loop();

                                            }
                                            flag=1;
                                            for(int y=0;y<times;y++)
                                            {
                                                for(z=0;z<count;z++)
                                                {
                                                    indata=str[z];
                                                    loop();
                                                }
                                            }

                        }

          }
}
