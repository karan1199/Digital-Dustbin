  /* ultrasonic -> smartphone BT(send 1 to on barcode,ultrasonic 0)
 *  barcode send 1 -> servo on
 *  servo off-> send 1
 *  loop again
 *  
 */
 #include <Wire.h>
#include <LiquidCrystal.h>
#include<Servo.h>
#include <SoftwareSerial.h>

// defining for lcd

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define pins for ultrasonic and ledpin
int const trigPin = 13;
int const echoPin = 5;
int const ledpin = 2;
//servo pin is 9
Servo servo_test;        //initialize a servo object for the connected servo  
int angle = 0;    
char data;            //Variable for storing received data
SoftwareSerial BTserial(0,1); // RX | TX

void bluetoothrecieve();
void ultrasonic();
void servo();
void bluetoothrecieve();




void setup()
{Serial.begin(9600);
pinMode(trigPin, OUTPUT); // trig pin will have pulses output
pinMode(echoPin, INPUT); // echo pin should be input to get pulse width
pinMode(ledpin, OUTPUT); // led pin is output to control buzzering
servo_test.attach(9); 
BTserial.begin(9600);
 lcd.begin(16, 2);
  
  lcd.print("WELCOME");
}



void loop()
{ 
  // *****************************************************************ultrasonic******************************************************************************
  ultrasonic(); 
//*****************************************************************welcome******************************************************************************

 
  lcd.setCursor(0, 1);
  
  lcd.print(millis()/1000);      
  
  //*****************************************************************barcodedone******************************************************************************
  bluetoothrecieve();
  while(Serial.available())
  {data=Serial.read();
  }
    
  //*****************************************************************servo******************************************************************************  
  
                        // TO READ BARCODE 
   while(data)
    {
      servo();
      break;
    }

 // ****************************************************************sending (servo off)*********************************************************************    
 Serial.println('1');

BTserial.write('1') ;
        
 //****************************************************************thank  you send**************************************************************************     
           
}



void ultrasonic()
{
      int duration, distance;  // Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters
    
          digitalWrite(trigPin, HIGH); // Output pulse with 1ms width on trigPin

              delay(1);
                  
                   digitalWrite(trigPin, LOW);

// Measure the pulse input in echo pin
    
                   duration = pulseIn(echoPin, HIGH);

// Distance is half the duration divided by 29.1 (from datasheet)
                        
                        distance = (duration/2) / 29.1;
                   
                           
                            if (distance <= 100 && distance >= 0) 
                               {     BTserial.write('Y') ; // object detected
                                      Serial.println('Y');
                                      

                         
                               }
                                                           
                            digitalWrite(trigPin, LOW); // off ultrasonic
                            delay(500);   // Waiting 60 ms 
                            
}
void servo()
{ // put your main code here, to run repeatedly:
   
        {  for(angle = 0; angle <= 180; angle += 1)   // command to move from 0 degrees to 180 degrees 
          {                                  
            servo_test.write(angle);                 //command to rotate the servo to the specified angle
                 delay(15);                       
          } 
         
                  delay(40000);
  
                        for(angle = 180; angle>=1; angle-=5)     // command to move from 180 degrees to 0 degrees 
                        {                                
                             servo_test.write(angle);              //command to rotate the servo to the specified angle
                                  delay(10);                       
                        } 
          


        }

}

void bluetoothrecieve()
{
  while(Serial.available())
  {data=Serial.read();
  }
  Serial.println(data); 
}

