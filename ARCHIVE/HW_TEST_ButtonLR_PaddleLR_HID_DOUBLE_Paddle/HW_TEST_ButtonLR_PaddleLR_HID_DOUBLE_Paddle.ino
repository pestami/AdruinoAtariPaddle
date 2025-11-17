// #include <HID.h>
/*
  HW_TEST_ButtonLR_PaddleLR_HID_V02
//=================================================================
Functions:
  1-make LED LIGHT when at ZERO



// ------------------------------------------------------------------- 
    https://github.com/MHeironimus/ArduinoJoystickLibrary
    JOYSTICK_TYPE_JOYSTICK or 0x04 - Joystick
    JOYSTICK_TYPE_GAMEPAD or 0x05 - Gamepad
    JOYSTICK_TYPE_MULTI_AXIS or 0x08 - Multi-axis Controller
 ------------------------------------------------------------------ 
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
//====================================================================================
//=====HARDWARE MAPNG PINS============================================================
const int Button_RIGHT = 7;  // the number of the pushbutton pin
const int Button_LEFT = 6;   // the number of the pushbutton pin

const int Button_SEL = 10;  //8;
const int Button_STA = 11;  //12;

const int Button_X = 8;
const int Button_Y = 12;

const int Button_H = 9;
const int Button_FLAG = 13;

const int LED_MID = 2;  // select the pin for the LED

const int LED_RIGHT = 4;  // the number of the LED pin
const int LED_LEFT = 3;   // the number of the LED pin

//======SOFRWARE VARIABLES ===========================================================
int Button_State_LEFT = 0;  // variable for reading the pushbutton status
int Button_State_RIGHT = 0;

int State_Button_SEL = 0;
int State_Button_STA = 0;

int State_Button_X = 0;
int State_Button_Y = 0;
int State_Button_H = 0;
int State_Button_FLAG = 0;

//=================================================================
long sensorValueR = 0;  // variable to store the value coming from the sensor
long sensorValueL = 0;  // variable to store the value coming from the sensor

int sensorPinR = A1;
int sensorPinL = A0;  // select the input pin for the potentiometer

long sensorValueRMAX = 0;
long sensorValueRMIN = 1024;
long sensorValueLMAX = 0;
long sensorValueLMIN = 1024;

long nJoystickX = 0;
long nJoystickY = 0;

const int nJOY_Range = 127;  // the number of the pushbutton pin



//=================================================================
//=================================================================

long nLoadLEFT = 80;    // 0-100 %
long nLoadRIGHT = 80;   // 0-100 %
long nPWM_period = 10;  // length of on off pulses

int sensorValueR_PRE = 0;
int sensorValueL_PRE = 0;
int sensorValueR_POST = 0;
int sensorValueL_POST = 0;

int Timer_Loop = 0;

//===================================================================

void sendtoserial(bool bDEBUG) {
  Serial.print("\n========BUTTON============\n");
  Serial.print("LEFT:");
  Serial.print(Button_State_LEFT);
  Serial.print("   RIGHT:");
  Serial.print(Button_State_RIGHT);

  Serial.print("\n========PADDLE============\n");

  Serial.println();
  Serial.print("nJoystickY:");
  Serial.print(nJoystickY);
  Serial.print("   nJoystickX:");
  Serial.print(nJoystickX);

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

  Serial.print("% sensorValueR_POST:");
  Serial.print(sensorValueR_POST);
  Serial.print("\t");
  Serial.print("% sensorValueR_PRE:");
  Serial.print(sensorValueR_PRE);
  Serial.print("\t");

  Serial.println();
  Serial.print("% Timer_Loop:");
  Serial.print(Timer_Loop);
}
//=================================================================
#include <TimerOne.h>

void Timer1_ISR(void) {
  Timer_Loop = Timer_Loop + 1;
  if (Timer_Loop == 10) { Timer_Loop = 0; }  // timer counts one to 10
}
//=================================================================
void setup() {
  // Set Range Values
  Joystick[0].setXAxisRange(-nJOY_Range, nJOY_Range);
  Joystick[0].setYAxisRange(-nJOY_Range, nJOY_Range);

  Joystick[1].setXAxisRange(-nJOY_Range, nJOY_Range);
  Joystick[1].setYAxisRange(-nJOY_Range, nJOY_Range);

  pinMode(LED_LEFT, OUTPUT);   // initialize the LED pin as an output:
  pinMode(LED_RIGHT, OUTPUT);  // initialize the LED pin as an output:
  pinMode(LED_MID, OUTPUT);
  pinMode(LED_MID, OUTPUT);

  pinMode(Button_LEFT, INPUT);   // initialize the pushbutton pin as an input:
  pinMode(Button_RIGHT, INPUT);  // initialize the pushbutton pin as an input:

  pinMode(Button_SEL, INPUT);   // initialize the pushbutton pin as an input:
  pinMode(Button_STA, INPUT);   // initialize the pushbutton pin as an input:
  pinMode(Button_X, INPUT);     // initialize the pushbutton pin as an input:
  pinMode(Button_Y, INPUT);     // initialize the pushbutton pin as an input:
  pinMode(Button_H, INPUT);     // initialize the pushbutton pin as an input:
  pinMode(Button_FLAG, INPUT);  // initialize the pushbutton pin as an input:

  // Initialize Joystick Library
  Joystick[0].begin();
  Joystick[1].begin();

  //Initiate Serial communication.
  Serial.begin(9600);
  //===================================================================
}


void loop() {
  //===============================================================
  // Program SETUP

  bool bDEBUG = false;
  bool bDEBUG_LED = true;

  if (bDEBUG) { delay(100); }  // slow down the program for debuging

  //https://docs.arduino.cc/language-reference/en/functions/external-interrupts/attachInterrupt/
  Timer1.initialize(10 * 1000);  // Fire An Interrupt Every 100ms // Timer_Loop counts to 10 = 1 count per second
  Timer1.attachInterrupt(Timer1_ISR);

  //==================================================================
  // Fire Buutons READ & WRITE
  //==================================================================
  // read the state of the pushbutton value:
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  //--------FIRE----------------------------------------------------------
  Button_State_LEFT = digitalRead(Button_LEFT);
  if (Button_State_LEFT == HIGH) {
    // turn LED on:
    if (bDEBUG_LED) { digitalWrite(LED_MID, HIGH); }
    Joystick[1].setButton(0, 1);
  } else {
    // turn LED off:
    if (bDEBUG_LED) { digitalWrite(LED_MID, LOW); }
    Joystick[1].setButton(0, 0);
  }
  //-----------FIRE-------------------------------------------------------
  Button_State_RIGHT = digitalRead(Button_RIGHT);
  if (Button_State_RIGHT == HIGH) {
    // turn LED on:
    if (bDEBUG_LED) { digitalWrite(LED_RIGHT, HIGH); }
    Joystick[0].setButton(1, 1);
  } else {
    // turn LED off:
    if (bDEBUG_LED) { digitalWrite(LED_RIGHT, LOW); }
    Joystick[0].setButton(1, 0);
  }
  //-------------MENU-----------------------------------------------------
  State_Button_SEL = digitalRead(Button_SEL);
  if (State_Button_SEL == HIGH) {
    Joystick[0].setButton(5, 1);
    if (bDEBUG_LED) { digitalWrite(LED_MID, HIGH); }
  } else {
    Joystick[0].setButton(5, 0);
    if (bDEBUG_LED) { digitalWrite(LED_MID, LOW); }
  }
  //------------------------------------------------------------------
  State_Button_STA = digitalRead(Button_STA);
  if (State_Button_STA == HIGH) {
    Joystick[0].setButton(6, 1);
    if (bDEBUG_LED) { digitalWrite(LED_MID, HIGH); }
  } else {
    Joystick[0].setButton(6, 0);
    if (bDEBUG_LED) { digitalWrite(LED_MID, LOW); }
  }
  //------------------------------------------------------------------
  State_Button_X = digitalRead(Button_X);
  if (State_Button_X == HIGH) {
    Joystick[0].setButton(2, 1);
    if (bDEBUG_LED) { digitalWrite(LED_MID, HIGH); }
  } else {
    Joystick[0].setButton(2, 0);
    if (bDEBUG_LED) { digitalWrite(LED_MID, LOW); }
  }
  //------------------------------------------------------------------
  State_Button_Y = digitalRead(Button_Y);
  if (State_Button_Y == HIGH) {
    Joystick[0].setButton(3, 1);
    if (bDEBUG_LED) { digitalWrite(LED_MID, HIGH); }
  } else {
    Joystick[0].setButton(3, 0);
    if (bDEBUG_LED) { digitalWrite(LED_MID, LOW); }
  }
  //------------------------------------------------------------------
  State_Button_H = digitalRead(Button_H);
  if (State_Button_H == HIGH) {
    Joystick[0].setButton(4, 1);
    if (bDEBUG_LED) { digitalWrite(LED_MID, HIGH); }
  } else {
    Joystick[0].setButton(4, 0);
    if (bDEBUG_LED) { digitalWrite(LED_MID, LOW); }
  }
  //------------------------------------------------------------------
  //==================================================================
  // Analog Paddle
  // Long variables are extended size variables for number storage, and store 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647.
  //==================================================================

  sensorValueR = analogRead(sensorPinR);
  sensorValueL = analogRead(sensorPinL);
  //===============================================================================================
  if (1 == 2)  // enable spinner
               // read the value from the sensor:
    if (Timer_Loop == 1) {
      {
        sensorValueR_PRE = sensorValueR_POST;
        sensorValueL_PRE = sensorValueL_POST;
        //Serial.print(millis());
      }
      sensorValueR = analogRead(sensorPinR);
      sensorValueL = analogRead(sensorPinL);

      sensorValueR_POST = sensorValueR / 50;  // make less sensitive to noise also reduces range -100 to 100
      sensorValueL_POST = sensorValueL / 50;

      if (sensorValueR_PRE > sensorValueR_POST) {
        Joystick[0].setButton(1, 1);
        if (bDEBUG_LED) { digitalWrite(LED_MID, HIGH); }
      } else {
        Joystick[0].setButton(1, 0);
        if (bDEBUG_LED) { digitalWrite(LED_MID, LOW); }
      }

      if (sensorValueR_PRE < sensorValueR_POST) {
        Joystick[0].setButton(0, 1);
        if (bDEBUG_LED) { digitalWrite(LED_MID, HIGH); }
      } else {
        Joystick[0].setButton(0, 0);
        if (bDEBUG_LED) { digitalWrite(LED_MID, LOW); }
      }
    }
  //===============================================================================================
  sensorValueRMAX = 0;     // initial 0
  sensorValueRMIN = 1024;  // initial 1024

  nJoystickY = (-nJOY_Range + nLoadLEFT * nJOY_Range / 50);  // 50 = 100 / 2
  nJoystickX = (-nJOY_Range + nLoadRIGHT * nJOY_Range / 50);

  nLoadLEFT = ((sensorValueL - sensorValueLMIN) * 100 / (sensorValueLMAX - sensorValueLMIN));  // 1024 * 100 = 102`400
  nLoadRIGHT = ((sensorValueR - sensorValueRMIN) * 100 / (sensorValueRMAX - sensorValueRMIN));

  digitalWrite(LED_RIGHT, LOW);
  Joystick[0].setXAxis(1 * nJoystickX);

  //digitalWrite(LED_LEFT, LOW);Joystick.setYAxis(1 * nJoystickY);
  digitalWrite(LED_LEFT, LOW);
  Joystick[1].setXAxis(1 * nJoystickY);

  if (nLoadRIGHT > 40 && nLoadRIGHT < 60) {
    digitalWrite(LED_RIGHT, HIGH);
  } else {
    digitalWrite(LED_RIGHT, LOW);
  }
  if (nLoadLEFT > 40 && nLoadLEFT < 60) {
    digitalWrite(LED_LEFT, HIGH);
  } else {
    digitalWrite(LED_LEFT, LOW);
  }


  //============================================================================================
  if (bDEBUG) { sendtoserial(bDEBUG); }

  //============================================================================================
}
// if (nLoadRIGHT > 40 && nLoadRIGHT < 59)
// {  digitalWrite(LED_RIGHT, HIGH);Joystick.setXAxis( 0 * nJoystickX);}
// else
// {digitalWrite(LED_RIGHT, LOW);Joystick.setXAxis( 1 * nJoystickX);}

// if (nLoadLEFT > 40 && nLoadLEFT <59)
// {  digitalWrite(LED_LEFT, HIGH);Joystick.setYAxis(0 * nJoystickY);}
// else
// {digitalWrite(LED_LEFT, LOW);Joystick.setYAxis(1 * nJoystickY);}
