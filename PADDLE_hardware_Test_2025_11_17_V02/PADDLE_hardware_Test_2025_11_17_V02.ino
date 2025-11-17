// #include <HID.h>
/*
  HW_TEST_ButtonLR_PaddleLR_HID_V02

  make LED LIGHT when at ZERO

*/
//=================================================================
#include <Joystick.h>
#define JOYSTICK_COUNT 2
// Create the Joystick*
/*
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  7, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  true, true, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering
*/
Joystick_ Joystick[JOYSTICK_COUNT] = {
  Joystick_(0x03, JOYSTICK_TYPE_GAMEPAD, 7, 0, true, false, false, false, false, false, false, false, false, false, false),
  Joystick_(0x04, JOYSTICK_TYPE_JOYSTICK, 1, 0, true, false, false, false, false, false, false, false, false, false, false)
};
//=================================================================
// constants won't change. They're used here to set pin numbers:


const int LED_LEFT = 10;    // the number of the LED pin
const int LED_RIGHT = 14;    // the number of the LED pin
const int LED_MIDDLE = 16;    // the number of the LED pin

const int BUTTON_LEFT_A = 9;  // the number of the pushbutton pin
const int BUTTON_RIGHT_A = 8;  // the number of the pushbutton pin
const int BUTTON_SEL = 2; 
const int BUTTON_STA = 3; 
const int BUTTON_X = 5; 
const int BUTTON_Y = 6; 
const int BUTTON_B = 4; 

//======SOFRWARE VARIABLES ===========================================================
// variable for reading the pushbutton status
int State_Button_LEFT= 0;  
int State_Button_RIGHT = 0;

int State_Button_SEL = 0;
int State_Button_STA = 0;

int State_Button_X = 0;
int State_Button_Y = 0;
int State_Button_H = 0;
int State_Button_FLAG = 0;

//=================================================================
//=================================================================

int sensorPinR = A0;   // select the input pin for the potentiometer
long sensorValueR = 0;  // variable to store the value coming from the sensor

int sensorPinL = A1;   // select the input pin for the potentiometer
long sensorValueL = 0;  // variable to store the value coming from the sensor
long sensorMinValue= 300;

long sensorValueRMAX = 0;
long sensorValueRMIN = 1024;
long sensorValueLMAX = 0;
long sensorValueLMIN = 1024;

int sensorMode = A2;   // select the input pin for the potentiometer
long sensorModeValue = 0;  // variable to store the value coming from the sensor

int Timer_Loop = 0;

long nJoystickX = 0;
long nJoystickY = 0;

const int nJOY_Range = 127;  // the number of the pushbutton pin
//===================================================================
//=================================================================
void setup() {
  
    // Set Range Values
  Joystick[0].setXAxisRange(-nJOY_Range, nJOY_Range);
  Joystick[0].setYAxisRange(-nJOY_Range, nJOY_Range);

  Joystick[1].setXAxisRange(-nJOY_Range, nJOY_Range);
  Joystick[1].setYAxisRange(-nJOY_Range, nJOY_Range);

  pinMode(LED_LEFT, OUTPUT);// initialize the LED pin as an output:  
  pinMode(LED_RIGHT, OUTPUT);// initialize the LED pin as an output:  
  pinMode(LED_MIDDLE, OUTPUT);

 
  pinMode(BUTTON_LEFT_A, INPUT);// initialize the pushbutton pin as an input:  
  pinMode(BUTTON_RIGHT_A, INPUT);// initialize the pushbutton pin as an input:

  pinMode(BUTTON_SEL, INPUT);// initialize the pushbutton pin as an input:
  pinMode(BUTTON_STA, INPUT);// initialize the pushbutton pin as an input:
  pinMode(BUTTON_X, INPUT);// initialize the pushbutton pin as an input:
  pinMode(BUTTON_Y, INPUT);// initialize the pushbutton pin as an input:
  pinMode(BUTTON_B, INPUT);// initialize the pushbutton pin as an input:

	// Initialize Joystick Library
  Joystick[0].begin();
  Joystick[1].begin();

  //Initiate Serial communication.
  Serial.begin(9600); 
  
  }
//=================================================================


#include <TimerOne.h>

void Timer1_ISR(void) {
  Timer_Loop = Timer_Loop + 1;
  if (Timer_Loop == 10) { Timer_Loop = 0; }  // timer counts one to 10
}
//=================================================================
//=================================================================== 
	long nLoadLEFT=80;			// 0-100 %
  long nLoadRIGHT=80;			// 0-100 %
	long nPWM_period=10;  // length of on off pulses 

//===================================================================  
void sendtoserial(bool bDEBUG) 
{
  Serial.print("\n========BUTTON====================================================================================================\n");
  Serial.print("LEFT:");
  Serial.print(State_Button_LEFT);
  Serial.print("   RIGHT:");
  Serial.print(State_Button_RIGHT);

  Serial.print("   nJoystickY:");
  Serial.print(nJoystickY);
  Serial.print("   nJoystickX:");
  Serial.print(nJoystickX);

  Serial.print("   nLoadLEFT:");
  Serial.print(nLoadLEFT);
  Serial.print("   nLoadRIGHT:");
  Serial.print(nLoadRIGHT);
  

  Serial.println();
  //Serial.print("A1  A2  X  Y  H  SEL PLAY ");

  Serial.print(" A1:" + String(State_Button_LEFT) );
  Serial.print(" A2:" +  String(State_Button_RIGHT ));

  Serial.print(" SEL:" + String(State_Button_SEL ));
  Serial.print(" STA:" +  String(State_Button_STA ));

  Serial.print(" X:" +  String(State_Button_X));
  Serial.print(" Y:" + String(State_Button_Y ));
  Serial.print(" B:" + String(State_Button_H ));
  Serial.print(" MODE:" +  String(sensorModeValue));

  
 

  Serial.print("\n========PADDLE======================================================================================================\n");

  if (false)
  {

    Serial.println();
    Serial.print("10 BIT L:");
    Serial.print(sensorValueL);
    Serial.print("\t");
    Serial.print("10 BIT R:");
    Serial.print(sensorValueR);

    Serial.println();

    Serial.print("% LOAD LEFT:");
    Serial.print(nLoadLEFT);
    Serial.print("\t");
    Serial.print("% LOAD RIGHT:");
    Serial.print(nLoadRIGHT);
    Serial.print("\t");
    Serial.println();

  }
  Serial.println();
  Serial.print("% Timer_Loop:");
  Serial.print(Timer_Loop);
}
//=================================================================
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

  State_Button_LEFT= digitalRead(BUTTON_LEFT_A); 
  State_Button_RIGHT = digitalRead(BUTTON_RIGHT_A);
  State_Button_SEL = digitalRead(BUTTON_SEL);
  State_Button_STA = digitalRead(BUTTON_STA);
  State_Button_X = digitalRead(BUTTON_X);
  State_Button_Y = digitalRead(BUTTON_Y);
  State_Button_H = digitalRead(BUTTON_B);
  State_Button_LEFT= digitalRead(BUTTON_LEFT_A);



  if (State_Button_LEFT== HIGH) 
        {
          // turn LED on:
          if (bDEBUG_LED) 
          {digitalWrite(LED_LEFT, HIGH);
          digitalWrite(LED_MIDDLE, HIGH);
          Joystick[0].setButton(0, 1);
          digitalWrite(LED_RIGHT, LOW);
          }
        } 
//------------------------------------------------------------------
  State_Button_RIGHT = digitalRead(BUTTON_RIGHT_A);
  if (State_Button_RIGHT == HIGH) 
        {
          // turn LED on:
          if (bDEBUG_LED) 
          {digitalWrite(LED_RIGHT, HIGH);
          Joystick[0].setButton(1, 1);
          digitalWrite(LED_LEFT, LOW);
          digitalWrite(LED_MIDDLE, LOW);
          }
        } 
//------------------------------------------------------------------
 
//------------------------------------------------------------------   
//==================================================================
// Analog Paddle
// Long variables are extended size variables for number storage, and store 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647.
//==================================================================
 
   // read the value from the sensor:
  sensorValueR = analogRead(sensorPinR);
  sensorValueL = analogRead(sensorPinL);

  sensorModeValue = analogRead(sensorMode);

  if (sensorValueR > sensorValueRMAX) {  sensorValueRMAX=sensorValueR;}  // initial 0
  if (sensorValueR < sensorValueRMIN) {  sensorValueRMIN=sensorValueR;}   // initial 1024

  if (sensorValueL > sensorValueLMAX) {  sensorValueLMAX=sensorValueL;}
  if (sensorValueL < sensorValueLMIN) {  sensorValueLMIN=sensorValueL;}

 
 nJoystickX=(-nJOY_Range+nLoadLEFT*nJOY_Range/50);  // 50 = 100 / 2
 nJoystickY=(-nJOY_Range+nLoadRIGHT*nJOY_Range/50);

  Joystick[0].setXAxis( 1 * nJoystickX);
  Joystick[1].setYAxis(1 * nJoystickY);
  
  sensorMinValue=300;
  nLoadLEFT=((sensorValueL-sensorValueLMIN)*100/(sensorValueLMAX-sensorValueLMIN));  // 1024 * 100 = 102`400
  nLoadRIGHT=((sensorValueR-sensorValueRMIN)*100/(sensorValueRMAX-sensorValueRMIN)) ;

  int nTest=0;

  if (nLoadRIGHT > 40 && nLoadRIGHT < 60) 
  {  nTest=nTest+1;} else {nTest=nTest+0;}


  if (nLoadLEFT > 40 && nLoadLEFT <60) 
  {  nTest=nTest+1;} else {nTest=nTest+0;}

  if (nTest==2) 
  {  digitalWrite(LED_MIDDLE, HIGH);} else {digitalWrite(LED_MIDDLE, LOW);}

 if (sensorModeValue<100) 
  {  digitalWrite(LED_MIDDLE, LOW);}

if (sensorModeValue>800) 
  {  digitalWrite(LED_MIDDLE, HIGH);}
  

//============================================================================================
  //==================================================================
  // Fire Buutons READ & WRITE
  //==================================================================
  // read the state of the pushbutton value:
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  //--------FIRE----------------------------------------------------------
  State_Button_LEFT= digitalRead(BUTTON_LEFT_A); 
  State_Button_RIGHT = digitalRead(BUTTON_RIGHT_A);
  State_Button_SEL = digitalRead(BUTTON_SEL);
  State_Button_STA = digitalRead(BUTTON_STA);
  State_Button_X = digitalRead(BUTTON_X);
  State_Button_Y = digitalRead(BUTTON_Y);
  State_Button_H = digitalRead(BUTTON_B);
  
  //------------------------------------------------------------------
  //==================================================================
  
if (bDEBUG) { sendtoserial(bDEBUG); }

}
