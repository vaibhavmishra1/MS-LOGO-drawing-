
String rc;



void setup() {
    Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

char* comp(){
    char inData[20];
    char inChar=-1; // Where to store the character read
 while(Serial.available())
 {
   inChar = Serial.read(); 
     byte index = 0;
 
     inData[index] = inChar; 
     index++; 
    if(inChar=='\n') 
   {
     break;
   }
    
    
 }


   
   index=0;
   return inData;
}



class fd()
{
       private:
    char *ch;
    int num; //distance motor to move forward
    public:
    fd()
    {
        
    }
};
class bk()
{
     char ch[]=comp();
      int num=ch.toInt(); //distance motor to move backward
};
class rt()
{
    char ch[]=comp();
      int num=ch.toInt(); //angle motor move to turn right
};
class lt()
{
     char ch[]=comp();
      int num=ch.toInt(); //angle motor move to turn left
};
class repeat()
{
};
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

