// #include <HID.h>

/*
  Button  
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

/*
  Analog Input

    https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInput
*/

//=================================================================
#include <Joystick.h>

// Create the Joystick
//Joystick_ Joystick;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  2, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering
//=================================================================
// Constant that maps the physical pin to the joystick button.
const int pinToButtonMap = 9;
// constants won't change. They're used here to set pin numbers:
const int Button_LEFT = 7;  // the number of the pushbutton pin
const int LED_LEFT = 5;    // the number of the LED pin

const int Button_RIGHT = 6;  // the number of the pushbutton pin
const int LED_RIGHT = 4;    // the number of the LED pin

// variables will change:
int Button_State_LEFT = 0;  // variable for reading the pushbutton status
int Button_State_RIGHT = 0;

int sensorPinR = A0;   // select the input pin for the potentiometer
int ledPinR = 2;      // select the pin for the LED
long sensorValueR = 0;  // variable to store the value coming from the sensor

int sensorPinL = A1;   // select the input pin for the potentiometer
int ledPinL = 3;      // select the pin for the LED
long sensorValueL = 0;  // variable to store the value coming from the sensor
long sensorMinValue= 300;

long sensorValueRMAX = 0;
long sensorValueRMIN = 1024;
long sensorValueLMAX = 0;
long sensorValueLMIN = 1024;

long nJoystickX = 0;
long nJoystickY = 0;

bool DEBUG=true;

const int nJOY_Range = 127;  // the number of the pushbutton pin

//=================================================================
void setup() {
  
    // Set Range Values
  Joystick.setXAxisRange(-nJOY_Range, nJOY_Range);
  Joystick.setYAxisRange(-nJOY_Range, nJOY_Range);

  pinMode(LED_LEFT, OUTPUT);// initialize the LED pin as an output:  
  pinMode(Button_LEFT, INPUT);// initialize the pushbutton pin as an input:
  pinMode(LED_RIGHT, OUTPUT);// initialize the LED pin as an output:  
  pinMode(Button_RIGHT, INPUT);// initialize the pushbutton pin as an input:
  
  // declare the ledPin as an OUTPUT:
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinL, OUTPUT);

// ATARI PUSH BUTTONS: 7 6 Left Right
  	// Initialize Button Pins
	pinMode(pinToButtonMap, INPUT_PULLUP);

	// Initialize Joystick Library
	Joystick.begin();

  //Initiate Serial communication.
  Serial.begin(9600); 
  
  }
//=================================================================
//=================================================================== 
 bool LoadCycleRIGHT( long *LoopCounter,  long LoopCounterCieling, long Load) 
 {
	 bool bONOFF=0;
	 
    if ( *LoopCounter > LoopCounterCieling) 
    {
         //if (bDEBUG) {  Serial.print("Reset Counter \n");}
        *LoopCounter=0;
    }
    
    if ( *LoopCounter > LoopCounterCieling*Load/100) 
    {
         //if (bDEBUG) {  Serial.print("000000000000000000\n");}
        bONOFF=0;
    }
    if ( *LoopCounter < LoopCounterCieling*Load/100) 
    {
        // if (bDEBUG) {  Serial.print("111111111111111111\n");}
        bONOFF=1;
    }    
   
    return bONOFF;
}
  //=================================================================== 
 bool LoadCycleLEFT( unsigned  long *LoopCounter,  long LoopCounterCieling, long Load) 
 {
	 bool bONOFF=0;
	 
    if ( *LoopCounter > LoopCounterCieling) 
    {
         //if (bDEBUG) {  Serial.print("Reset Counter \n");}
        *LoopCounter=0;
    }
    
    if ( *LoopCounter > LoopCounterCieling*Load/100) 
    {
         //if (bDEBUG) {  Serial.print("...................\n");}
        bONOFF=0;
    }
    if ( *LoopCounter < LoopCounterCieling*Load/100) 
    {
         //if (bDEBUG) {  Serial.print("--------------------\n");}
        bONOFF=1;
    }    
   
    return bONOFF;
}
//===================================================================  

  long nLoopCounter=0;	
	int iResultLEFT=0;
  int iResultRIGHT=0;
	long nLoadLEFT=80;			// 0-100 %
  long nLoadRIGHT=80;			// 0-100 %
	long nPWM_period=10;  // length of on off pulses 

void loop() 
{
  //===============================================================
  // Program SETUP
  
  //bool bDEBUG=true;
  bool bDEBUG=false;
  if (bDEBUG) {delay(100);}  // slow down the program for debuging
   //bool bDEBUG=False
   // if (bDEBUG) {        };

 //===============================================================
  nLoopCounter++;
  iResultLEFT=LoadCycleLEFT( &nLoopCounter,nPWM_period,nLoadLEFT);  
  iResultRIGHT=LoadCycleRIGHT( &nLoopCounter,nPWM_period,nLoadRIGHT);       
//==================================================================
// Fire Buutons READ & WRITE
//==================================================================
  // read the state of the pushbutton value:
  Button_State_LEFT = digitalRead(Button_LEFT);
  Button_State_RIGHT = digitalRead(Button_RIGHT);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (Button_State_LEFT == HIGH) 
        {
          // turn LED on:
          digitalWrite(LED_LEFT, HIGH);
          Joystick.setButton(0, 1);
        } else 
        {
          // turn LED off:
          digitalWrite(LED_LEFT, LOW);
          Joystick.setButton(0, 0);
        }
  if (Button_State_RIGHT == HIGH) 
        {
          // turn LED on:
          digitalWrite(LED_RIGHT, HIGH);
          Joystick.setButton(1, 1);
        } else 
        {
          // turn LED off:
          digitalWrite(LED_RIGHT, LOW);
          Joystick.setButton(1, 0);
        }

  
  if (bDEBUG) {  Serial.print("\n========BUTTON============\n"); }
 
  if (bDEBUG) {  Serial.print("LEFT:" );}
  if (bDEBUG) {  Serial.print(Button_State_LEFT);}
  if (bDEBUG) {  Serial.print("   RIGHT:" );}
  if (bDEBUG) {  Serial.print(Button_State_RIGHT);}
 
 
//==================================================================
// Analog Paddle
// Long variables are extended size variables for number storage, and store 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647.
//==================================================================
 

  if (bDEBUG) {  Serial.print("\n========PADDLE============\n");}
   // read the value from the sensor:
  sensorValueR = analogRead(sensorPinR);
  sensorValueL = analogRead(sensorPinL);


  if (sensorValueR > sensorValueRMAX) {  sensorValueRMAX=sensorValueR;}  // initial 0
  if (sensorValueR < sensorValueRMIN) {  sensorValueRMIN=sensorValueR;}   // initial 1024

  if (sensorValueL > sensorValueLMAX) {  sensorValueLMAX=sensorValueL;}
  if (sensorValueL < sensorValueLMIN) {  sensorValueLMIN=sensorValueL;}


 
 nJoystickX=(-nJOY_Range+nLoadLEFT*nJOY_Range/50);  // 50 = 100 / 2
 nJoystickY=(-nJOY_Range+nLoadRIGHT*nJOY_Range/50);

  if (bDEBUG) {  Serial.println(); }
  if (bDEBUG) {  Serial.print("nJoystickX:");}
  if (bDEBUG) {  Serial.print(nJoystickX);}
  if (bDEBUG) {  Serial.print("  nJoystickY:");}
  if (bDEBUG) {  Serial.print(nJoystickY);}

 if (bDEBUG) {  Serial.println(); }
  if (bDEBUG) {  Serial.print("sensorValueLMIN:");}
  if (bDEBUG) {  Serial.print(sensorValueLMIN);}
  if (bDEBUG) {  Serial.print("  sensorValueLMAX:");}
  if (bDEBUG) {  Serial.print(sensorValueLMAX);}

 if (bDEBUG) {  Serial.println(); }
  if (bDEBUG) {  Serial.print("sensorValueRMIN:");}
  if (bDEBUG) {  Serial.print(sensorValueRMIN);}
  if (bDEBUG) {  Serial.print("  sensorValueRMAX:");}
  if (bDEBUG) {  Serial.print(sensorValueRMAX);}




  Joystick.setXAxis( 1 * nJoystickX);
  Joystick.setYAxis(1 * nJoystickY);
 if (bDEBUG) {  Serial.println(); }
  if (bDEBUG) {  Serial.print("10 BIT L:");}
  if (bDEBUG) {  Serial.print(sensorValueL);}
  if (bDEBUG) {  Serial.print("\t"); }
  if (bDEBUG) {  Serial.print("10 BIT R:");}
  if (bDEBUG) {  Serial.print(sensorValueR);}
  
  if (bDEBUG) {  Serial.println(); }
  
  sensorMinValue=300;
  nLoadLEFT=((sensorValueL-sensorValueLMIN)*100/(sensorValueLMAX-sensorValueLMIN));  // 1024 * 100 = 102`400
  nLoadRIGHT=((sensorValueR-sensorValueRMIN)*100/(sensorValueRMAX-sensorValueRMIN)) ;

  if (bDEBUG) {  Serial.print("% PWM LEFT:" );}
  if (bDEBUG) {  Serial.print(nLoadLEFT);}
  if (bDEBUG) {  Serial.print("\t"); }
  if (bDEBUG) {  Serial.print("% PWM RIGHT:" );}
  if (bDEBUG) {  Serial.print(nLoadRIGHT);}
  if (bDEBUG) {  Serial.print("\t");}
  if (bDEBUG) {  Serial.println();   }

  if (bDEBUG) {  Serial.print("iResultLEFT:" );}
  if (bDEBUG) {  Serial.print(iResultLEFT);}
  if (bDEBUG) {  Serial.print("\t"); }

  if (bDEBUG) {  Serial.print("iResultRIGHT:" );}
  if (bDEBUG) {  Serial.print(iResultRIGHT);}
  if (bDEBUG) {  Serial.print("\t"); }

  if (iResultLEFT) 
        { 
          // turn LED on:
          digitalWrite(ledPinR, HIGH);
        } else 
        {
          // turn LED off:
          digitalWrite(ledPinR, LOW);
        }

  if (iResultRIGHT)
        {
          digitalWrite(ledPinL, HIGH);
        } else 
        {
          // turn LED off:
          digitalWrite(ledPinL, LOW);
        }

  

}
