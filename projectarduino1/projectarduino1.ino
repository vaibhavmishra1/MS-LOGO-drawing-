
String rc;
char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character
int ledPin = 13; // Set the pin to digital I/O 4

void setup() {
    Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}
int comp(char* This){
 while(Serial.available())
 {
   inChar = Serial.read(); 
 
     inData[index] = inChar; 
     index++; 
    if(inChar=='\n') 
   {
     break;
   }
    
    
 }

 if(strcmp(inData,This)  == 0){
   for(int i=0;i<19;i++){
     inData[i]=0;
   }
   index=0;
   return(0);

 }
 else{
   return(1);


 }
}
void loop() { 
  
       if(comp("fd")==0)
       {
                
                delay(1000);
        }
          else if(comp("bk")==0)
       {
            
            delay(1000);  
            
      }
   
}

