import processing.serial.*;
Serial myPort;  // Create object from Serial class

void setup() 
{
  
  myPort = new Serial(this,"COM6", 9600);
  String[] steps =loadStrings("logofile.LGO");
  for(int i=0;i<steps.length;i++)
    {
            String[] list=split(steps[i],' ');
            for(int j=0;j<list.length;j++)
            {
              print(list[j]);
              print("\n");
              myPort.write(list[j]);
              
            }
           
           
            delay(100);
    }
    
  
}


void draw() {
  
 
}
