//V1
#define AUDPIN 21      // Digital pin connected to the Audio sensor
#define LEDPIN 11
#define BUZZERPIN 12

// Teensy 5V <--> HC-05 Vcc
// Teensy Ground <--> HC-05 GND
#define rxPin 7 // Teensy pin 7 <--> HC-05 Tx
#define txPin 8 // Teensy pin 8 <--> HC-05 Rx
//SoftwareSerial BTSerial =  SoftwareSerial(rxPin, txPin);

int val = 0;  // variable to store the value read
unsigned int audSignal=0;
unsigned int audThres=41
;
bool audAttempt=0;
bool audDetected=0;
bool audDetectedPrev =0;
unsigned long tCurrent = 0;
unsigned long tAudAttempt = 0;
unsigned int k;
int batchAverage=0;
bool mutex=1;

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 3000;  //the value is a number of milliseconds

void audDetect();

void setup() 
{
  Serial.begin(9600);   // Setup serial for monitor
  Serial.println("");
  Serial.println("Advanced activity Monitoring System");
  // Setup Serial1 for BlueTooth
  Serial1.begin(9600); // Default communication rate of the Bluetooth module
  
  startMillis = millis();  //initial start time
  
  pinMode(LEDPIN, OUTPUT);  // Setup Buildin LED
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(AUDPIN, INPUT);   // Setup Audio Sensor
  
  pinMode(LEDPIN, OUTPUT);  // Setup Buildin LED
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(AUDPIN, INPUT);   // Setup Audio Sensor
   // Setup Serial1 for BlueTooth
  Serial1.begin(9600); // Default communication rate of the Bluetooth module

  digitalWrite(BUZZERPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(BUZZERPIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second  
  digitalWrite(BUZZERPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(BUZZERPIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second  
  digitalWrite(LEDPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(300);                       // wait for a second
  digitalWrite(LEDPIN, LOW);    // turn the LED off by making the voltage LOW
  delay(300);                       // wait for a second
  
}

void loop() 
{
  currentMillis = millis();  //get the current time
  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
        //Serial1.print(F("AudioDetected="));
        Serial1.print(audDetected);
        Serial1.println();
    startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  }
  audDetect();
  if ( Serial1.available() > 0 ) 
  {
    int count = Serial.parseInt();   // print out the received number
    if (count > 0) 
    {
        Serial.print("IP:");
        Serial.println(String(count));
    }
  }
  if (audDetected)
  {
    digitalWrite(BUZZERPIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(10);                       // wait for a second
    digitalWrite(BUZZERPIN, LOW);    // turn the LED off by making the voltage LOW
    //delay(50);                       // wait for a second  
  }
  //delay(10);

}

void audDetect() 
{

  audSignal = analogRead(AUDPIN);
  Serial.print(audSignal);
  Serial.print("  ");
  if(audSignal >= audThres) //100 make it as variable //batchAverage >= cryThres
  {
    audAttempt = 1;
  } 
  else
  {
   audAttempt = 0; 
   Serial.print("aud"+ (String)k);
  }
if(audAttempt)
    {
      tAudAttempt = millis(); ////////////////////////////////////////////////////////////
      k=k+1;
      Serial.print("aud"+ (String)k);
      if(k==5)
      {
           k=0;
           audDetected = 1;
            //if (audDetected && mutex)           
            //{
              //Serial.print(F("AudioDetected: "));
              //Serial.print(audDetected);
              //Serial.println();
              //mutex=0;
            //}
      }                 
    }

  tCurrent = millis();
  
  if(   (tCurrent - tAudAttempt) > 8000) //t_old//t_new
  {
       k=0;
       audDetected = 0;
       //if (!(audDetected && mutex))
       //{
        //Serial.print(F("AudioDetected: "));
        //Serial.print(audDetected);
        //Serial.println();
        //mutex=1; 
       //}
       
  }
  
  //audDetectedPrev= audDetected;
  
  Serial.print(" det ");
  Serial.print(audDetected);
  Serial.println("");
}
