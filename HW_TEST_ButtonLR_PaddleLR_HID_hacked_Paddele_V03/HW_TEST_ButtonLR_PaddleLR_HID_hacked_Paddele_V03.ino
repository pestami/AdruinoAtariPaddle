// #include <HID.h>


/*
  HW_TEST_ButtonLR_PaddleLR_HID_V02

  make LED LIGHT when at ZERO





*/

//=================================================================
#include <Joystick.h>

// Create the Joystick
//Joystick_ Joystick;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  7, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering
//====================================================================================
//=====HARDWARE MAPNG PINS============================================================
const int Button_RIGHT = 7;  // the number of the pushbutton pin
const int Button_LEFT = 6;  // the number of the pushbutton pin

const int Button_SEL = 8; 
const int Button_STA = 9; 

const int Button_A = 10; 
const int Button_B = 11; 

const int Button_H = 12; 

int LED_RIGHT_PW = 2;      // select the pin for the LED
int LED_LEFT_PW = 3;      // select the pin for the LED
const int LED_RIGHT = 4;    // the number of the LED pin
const int LED_LEFT = 5;    // the number of the LED pin

//======SOFRWARE VARIABLES ===========================================================
int Button_State_LEFT = 0;  // variable for reading the pushbutton status
int Button_State_RIGHT = 0;

 int State_Button_SEL = 0; 
 int State_Button_STA = 0; 

 int State_Button_A = 0; 
 int State_Button_B = 0; 
 int State_Button_H= 0; 

//=================================================================
long sensorValueR = 0;  // variable to store the value coming from the sensor
long sensorValueL = 0;  // variable to store the value coming from the sensor

int sensorPinR = A1;  
int sensorPinL = A0;   // select the input pin for the potentiometer

long sensorValueRMAX = 0;
long sensorValueRMIN = 1024;
long sensorValueLMAX = 0;
long sensorValueLMIN = 1024;

long nJoystickX = 0;
long nJoystickY = 0;

const int nJOY_Range = 127;  // the number of the pushbutton pin

//=================================================================
void setup() {
  
    // Set Range Values
  Joystick.setXAxisRange(-nJOY_Range, nJOY_Range);
  Joystick.setYAxisRange(-nJOY_Range, nJOY_Range);

  pinMode(LED_LEFT, OUTPUT);// initialize the LED pin as an output:  
  pinMode(LED_RIGHT, OUTPUT);// initialize the LED pin as an output:  
  pinMode(LED_RIGHT_PW, OUTPUT);
  pinMode(LED_LEFT_PW, OUTPUT);
 
  pinMode(Button_LEFT, INPUT);// initialize the pushbutton pin as an input:  
  pinMode(Button_RIGHT, INPUT);// initialize the pushbutton pin as an input:

  pinMode(Button_SEL, INPUT);// initialize the pushbutton pin as an input:
  pinMode(Button_STA, INPUT);// initialize the pushbutton pin as an input:
  pinMode(Button_A, INPUT);// initialize the pushbutton pin as an input:
  pinMode(Button_B, INPUT);// initialize the pushbutton pin as an input:
   pinMode(Button_H, INPUT);// initialize the pushbutton pin as an input:

	// Initialize Joystick Library
	Joystick.begin();

  //Initiate Serial communication.
  Serial.begin(9600); 
  
  }
//=================================================================
//=================================================================== 


	long nLoadLEFT=80;			// 0-100 %
  long nLoadRIGHT=80;			// 0-100 %
	long nPWM_period=10;  // length of on off pulses 

//===================================================================  
void loop() 
{
  //===============================================================
  // Program SETUP  

  bool bDEBUG=true;
  bool bDEBUG_LED=true;

  if (bDEBUG) {delay(100);}  // slow down the program for debuging 
   
//==================================================================
// Fire Buutons READ & WRITE
//==================================================================
  // read the state of the pushbutton value:
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  //--------FIRE----------------------------------------------------------
  Button_State_LEFT = digitalRead(Button_LEFT);
  if (Button_State_LEFT == HIGH) 
        {
          // turn LED on:
          if (bDEBUG_LED) {digitalWrite(LED_LEFT, HIGH);}
          Joystick.setButton(1, 1);
        } else 
        {
          // turn LED off:
         if (bDEBUG_LED) {digitalWrite(LED_LEFT, LOW);}
          Joystick.setButton(1, 0);
        }
//-----------FIRE-------------------------------------------------------
  Button_State_RIGHT = digitalRead(Button_RIGHT);
  if (Button_State_RIGHT == HIGH) 
        {
          // turn LED on:
          if (bDEBUG_LED) {digitalWrite(LED_RIGHT, HIGH);}
          Joystick.setButton(0, 1);
        } else 
        {
          // turn LED off:
          if (bDEBUG_LED) {digitalWrite(LED_RIGHT, LOW);}
          Joystick.setButton(0, 0);
        }
//-------------MENU-----------------------------------------------------
  State_Button_SEL = digitalRead(Button_SEL);
  if (State_Button_SEL == HIGH) 
        {
          Joystick.setButton(2, 1);
          if (bDEBUG_LED) {digitalWrite(LED_LEFT_PW, HIGH);}
        } else 
        {
          Joystick.setButton(2, 0);
          if (bDEBUG_LED) {digitalWrite(LED_RIGHT_PW, LOW);}
        }
 //------------------------------------------------------------------
  State_Button_STA = digitalRead(Button_STA);
  if (State_Button_STA == HIGH) 
        {
          Joystick.setButton(3, 1);
          if (bDEBUG_LED) {digitalWrite(LED_RIGHT_PW, HIGH);}
        } else 
        {
          Joystick.setButton(3, 0);
          if (bDEBUG_LED) {digitalWrite(LED_RIGHT_PW, LOW);}
        }
  //------------------------------------------------------------------
  State_Button_A = digitalRead(Button_A);
  if (State_Button_A == HIGH) 
        {
          Joystick.setButton(4, 1);
          if (bDEBUG_LED) {digitalWrite(LED_LEFT_PW, HIGH);}
        } else 
        {
          Joystick.setButton(4, 0);
          if (bDEBUG_LED) {digitalWrite(LED_LEFT_PW, LOW);}
        }
        //------------------------------------------------------------------
  State_Button_B = digitalRead(Button_B);
  if (State_Button_B == HIGH) 
        {
          Joystick.setButton(5, 1);
          if (bDEBUG_LED) {digitalWrite(LED_RIGHT_PW, HIGH);}
        } else 
        {
          Joystick.setButton(5, 0);
          if (bDEBUG_LED) {digitalWrite(LED_RIGHT_PW, LOW);}
        }
        //------------------------------------------------------------------
  State_Button_H = digitalRead(Button_H);
  if (State_Button_H == HIGH) 
        {
          Joystick.setButton(6, 1);
          if (bDEBUG_LED) {digitalWrite(LED_RIGHT_PW, HIGH);}
        } else 
        {
          Joystick.setButton(6, 0);
          if (bDEBUG_LED) {digitalWrite(LED_RIGHT_PW, LOW);}
        }
//------------------------------------------------------------------   

//==================================================================
// Analog Paddle
// Long variables are extended size variables for number storage, and store 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647.
//==================================================================
 
   // read the value from the sensor:
  sensorValueR = analogRead(sensorPinR);
  sensorValueL = analogRead(sensorPinL);
  
  sensorValueRMAX=0; // initial 0
  sensorValueRMIN=1024;   // initial 1024
 
 nJoystickY=(-nJOY_Range+nLoadLEFT*nJOY_Range/50);  // 50 = 100 / 2
 nJoystickX=(-nJOY_Range+nLoadRIGHT*nJOY_Range/50);
 
  nLoadLEFT=((sensorValueL-sensorValueLMIN)*100/(sensorValueLMAX-sensorValueLMIN));  // 1024 * 100 = 102`400
  nLoadRIGHT=((sensorValueR-sensorValueRMIN)*100/(sensorValueRMAX-sensorValueRMIN)) ;

 

  if (nLoadRIGHT > 40 && nLoadRIGHT < 59) 
  {  digitalWrite(LED_RIGHT, HIGH);Joystick.setXAxis( 0 * nJoystickX);} 
  else
  {digitalWrite(LED_RIGHT, LOW);Joystick.setXAxis( 1 * nJoystickX);}

  if (nLoadLEFT > 40 && nLoadLEFT <59) 
  {  digitalWrite(LED_LEFT, HIGH);Joystick.setYAxis(0 * nJoystickY);} 
  else
  {digitalWrite(LED_LEFT, LOW);Joystick.setYAxis(1 * nJoystickY);}

  


//============================================================================================
  if (bDEBUG) {  Serial.print("\n========BUTTON============\n"); }
 
  if (bDEBUG) {  Serial.print("LEFT:" );}
  if (bDEBUG) {  Serial.print(Button_State_LEFT);}
  if (bDEBUG) {  Serial.print("   RIGHT:" );}
  if (bDEBUG) {  Serial.print(Button_State_RIGHT);}
 
  if (bDEBUG) {  Serial.print("\n========PADDLE============\n");}

 if (bDEBUG) {  Serial.println(); }
  if (bDEBUG) {  Serial.print("nJoystickY:");}
  if (bDEBUG) {  Serial.print(nJoystickY);}
  if (bDEBUG) {  Serial.print("   nJoystickX:");}
  if (bDEBUG) {  Serial.print(nJoystickX);}

 if (bDEBUG) {  Serial.println(); }
  if (bDEBUG) {  Serial.print("10 BIT L:");}
  if (bDEBUG) {  Serial.print(sensorValueL);}
  if (bDEBUG) {  Serial.print("\t"); }
  if (bDEBUG) {  Serial.print("10 BIT R:");}
  if (bDEBUG) {  Serial.print(sensorValueR);}
  
  if (bDEBUG) {  Serial.println(); }

 if (bDEBUG) {  Serial.print("% LOAD LEFT:" );}
  if (bDEBUG) {  Serial.print(nLoadLEFT);}
  if (bDEBUG) {  Serial.print("\t"); }
  if (bDEBUG) {  Serial.print("% LOAD RIGHT:" );}
  if (bDEBUG) {  Serial.print(nLoadRIGHT);}
  if (bDEBUG) {  Serial.print("\t");}
  if (bDEBUG) {  Serial.println();   }



  
//============================================================================================
}
