/*
 * This is my own take on finding the RPM using a Hall Effect Sensor.
 * I found other codes to be less accurate and hence used a slightly different logic.
 * Detials of interrupt pins https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 */
 /*
  * The digital pin of the Hall effect sensor is connected to digital pin 2 of the mini or mega.
  */
int iPin=0; //Set the interrupt pin(this is digital pin 2 on both the mini and mega). 
float rpm;
int flag;
volatile int t;
unsigned int lastInterrupt=0; //Stores the time of the last interrupt.
unsigned int prevInterrupt=0;
unsigned int currInterrupt=0;
unsigned int loopTime=0;  //Calculates the time between 2 interrupts. 

void setup() {
  Serial.begin(9600); //To print the RPM
  attachInterrupt(iPin,k,RISING);
  flag = 0;

}

void loop() {
  if(millis()-loopTime>1000){   //Loop runs every second.    
      detachInterrupt(iPin);    // Remove interrupt while calculating.
      float tSec=float(t)/1000; //converting to seconds.
      rpm=(1/tSec)*60;          //converting to minutes.
      if(!isfinite(rpm))
        rpm=0;
              
      loopTime=millis();        //Reset values.
      t=0;
      attachInterrupt(iPin,k,RISING);
      
      Serial.println(rpm);      //Print value.

  }
}
void k(){                     //Interrupt handler.
  if(millis() - lastInterrupt > 10 ){    
      if(flag==1){
        currInterrupt=millis();
        flag=0;
        t=currInterrupt-prevInterrupt;
      }
      else{
        prevInterrupt=millis();
        flag=1;
        t=0;
      }
    lastInterrupt = millis();
  }  
}
