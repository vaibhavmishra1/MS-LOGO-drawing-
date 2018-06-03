#include <Stepper.h>
#include<math.h>
#define StepsPerRevolution 200   //Change according to motor

String rc;
float angle=0pi=3.14;
float motx,moty;

motx=100*sinf(angle);
moty=100*cosf(angle);

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

void lt(floaf x){
  radtodeg();
  angle-=x;
  degtorad();
}

void fd(float x){

}

void bk(float x){
  
}



void setup() {
    Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}




char* comp(){
  char inData[20];
  char inChar=-1; // Where to store the character read
  while(Serial.available()){
    inChar = Serial.read(); 
    byte index = 0;
    inData[index] = inChar; 
    index++; 
    if(inChar=='\n') {
     break;
    }
  }
   index=0;
   return inData;
}



void loop() { 
        char ch[]=comp();
       if(strcmp(ch,"fd")==0))
       {
              
        }
         else if(comp("bk")==0)
       {
               
      }
         else if(comp("rt")==0)
       {
               
      }
        else if(comp("lt")==0)
       {
               
      }
     else if(comp("repeat")==0)
       {
               
      }
}
