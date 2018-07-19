#include <Stepper.h>
#include<math.h>
#include <USBAPI.h>
#include <String.h>

#define StepsPerRevolution 200   //Change according to motor
#define pitch 1 //Pitch of ballscrew
#define scale 1000  //scale

float angle=0,pi=3.14;

Stepper xmotor(100,9,10),ymotor(100,11,12);

void step2(Stepper mot1, Stepper mot2, long long duration) {  //duration is in microseconds
    long long start = micros();
    if(mot2.step_delay<mot1.step_delay){
        Stepper tmp=mot1;
        mot1=mot2;
        mot2=tmp;
    }

    mot1.last_step_time=micros();
    mot2.last_step_time=micros();

    long long currtime = 0;
    while(currtime < (duration))
    {
        if(micros()-mot1.last_step_time>mot1.step_delay)
        { 
          if(micros()-mot2.last_step_time>mot2.step_delay)
            {
              //move motor2
              //Serial.println("2");
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

                
            //move motor1
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
            }

            else{

              //move motor1

            if (mot1.pin_count == 5)
                mot1.stepMotor(mot1.step_number % 10);
            else
                mot1.stepMotor(mot1.step_number % 4);
                
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
             
            }            
        }
        currtime = micros() - start;
    }
}


void parabola(float a, float tim){
  double call_time=micros(),t=0,tp=50*t/a;
  while(t<tim*1000000){
    if(tp>1){//slope less than 1
      xmotor.setSpeed(100);
      ymotor.setSpeed(10*sqrt(a/t));
      step2(xmotor,ymotor,500000);
    }
    else{//slope greater than 1
      ymotor.setSpeed(100);
      xmotor.setSpeed(5000*t/a);
      step2(xmotor.ymotor,500000);
    }
    t=micros()-call_time;
  }
}



void circle(double radius){
  double call_time=micros(),t=0,omega=100/radius;
  while(t<((2*3.14/omega)*10000000))
  {
    //Serial.print(radius*omega*cosf(omega*t/10000000));
    //Serial.print("\t");
    //Serial.println(radius*omega*sinf(omega*t/10000000));
    xmotor.setSpeed(radius*omega*cosf(omega*t/10000000));
    ymotor.setSpeed(radius*omega*sinf(omega*t/10000000));
    step2(xmotor,ymotor,500000);
    t=micros()-call_time;    
  }
}

void line(double m, double len){
  if(m>1){
    ymotor.setSpeed(100);
    xmotor.setSpeed(100/m);
    step2(xmotor,ymotor,len*1000000);    
  }
  else{
    ymotor.setSpeed(100*m);
    xmotor.setSpeed(100);
    step2(xmotor,ymotor,len*1000000);       
  }
}


float motx,moty;
String inData;
int t = 1;


void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
}


void loop() {
   
  //Serial.print(motx);
  //Serial.print("\t");
  //Serial.print(moty);
  //motx = angle;
  //moty = angle;
  //Serial.println("Yo");
  circle(50);
  delay(10000);
  line(55,10);
}


