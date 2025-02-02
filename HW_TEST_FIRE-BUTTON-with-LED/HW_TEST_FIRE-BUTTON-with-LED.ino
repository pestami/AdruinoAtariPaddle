#include <HID.h>

/*
  Button  
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

// constants won't change. They're used here to set pin numbers:
const int Button_Left = 6;  // the number of the pushbutton pin
const int LED_LEFT = 4;    // the number of the LED pin

const int Button_Right = 7;  // the number of the pushbutton pin
const int LED_RIGHT = 5;    // the number of the LED pin

// variables will change:
int Button_State_Left = 0;  // variable for reading the pushbutton status
int Button_State_RIGHT = 0;

const int LED_PWM1 = 3;    // the number of the LED pin
const int LED_PWM2 = 2;    // the number of the LED pin

const int Button_8 = 8; 
const int Button_9 = 9; 
const int Button_10 = 10; 
const int Button_11 = 11; 

int Button_State_11 = 0;
int Button_State_10 = 0;
int Button_State_9 = 0;
int Button_State_8 = 0;

void setup() {
  
  pinMode(LED_LEFT, OUTPUT);// initialize the LED pin as an output:  
  pinMode(Button_Left, INPUT);// initialize the pushbutton pin as an input:
  pinMode(LED_RIGHT, OUTPUT);// initialize the LED pin as an output:  
  pinMode(Button_Right, INPUT);// initialize the pushbutton pin as an input:

  pinMode(Button_8, INPUT);// initialize the pushbutton pin as an input:
  pinMode(Button_9, INPUT);// initialize the pushbutton pin as an input:
  pinMode(Button_10, INPUT);// initialize the pushbutton pin as an input:
  pinMode(Button_11, INPUT);// initialize the pushbutton pin as an input:

  }

void loop() 
{
  // read the state of the pushbutton value:
  Button_State_Left = digitalRead(Button_Left);
  Button_State_RIGHT = digitalRead(Button_Right);

  Button_State_11 = digitalRead(Button_11); 
  Button_State_10 = digitalRead(Button_10); 
   Button_State_9 = digitalRead(Button_9); 
    Button_State_8 = digitalRead(Button_8); 

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (Button_State_Left == HIGH) 
        {
          // turn LED on:
          digitalWrite(LED_LEFT, HIGH);
        } else 
        {
          // turn LED off:
          digitalWrite(LED_LEFT, LOW);
        }
  if (Button_State_RIGHT == HIGH) 
        {
          // turn LED on:
          digitalWrite(LED_RIGHT, HIGH);
        } else 
        {
          // turn LED off:
          digitalWrite(LED_RIGHT, LOW);
        }

  if (Button_State_11 == HIGH) 
        {
          // turn LED on:
          digitalWrite(LED_RIGHT, HIGH);
          digitalWrite(LED_PWM1, HIGH);
        } else 
        {
          // turn LED off:
          digitalWrite(LED_RIGHT, LOW);
          digitalWrite(LED_PWM1, LOW);
        }
  if (Button_State_10 == HIGH) 
        {
          // turn LED on:
          digitalWrite(LED_LEFT, HIGH);
          digitalWrite(LED_PWM1, HIGH);
        } else 
        {
          // turn LED off:
          digitalWrite(LED_LEFT, LOW);
          digitalWrite(LED_PWM1, LOW);
        }

  if (Button_State_9 == HIGH) 
        {
          // turn LED on:
          digitalWrite(LED_RIGHT, HIGH);
          digitalWrite(LED_PWM2, HIGH);
        } else 
        {
          // turn LED off:
          digitalWrite(LED_RIGHT, LOW);
          digitalWrite(LED_PWM2, LOW);
        }
  if (Button_State_8 == HIGH) 
        {
          // turn LED on:
          digitalWrite(LED_LEFT, HIGH);
          digitalWrite(LED_PWM2, HIGH);
        } else 
        {
          // turn LED off:
          digitalWrite(LED_LEFT, LOW);
          digitalWrite(LED_PWM2, LOW);
        }


}
