#include <LiquidCrystal.h>



const int E = 12, RS = 11, D4 = 4, D5 = 5, D6 = 6, D7 = 7;
const int pwm = 9;  // PWM pin connected to the transistor controlling the fan
const int btn = 2;

int speed = 10;     // Variable to set the speed increment
int tempPin = A0;
bool btnFlag = false;
bool fanState = false;
bool manualOverride = false;

LiquidCrystal lcd(RS,E,D4,D5,D6,D7);

void setup() {
  lcd.begin(16,2);
  pinMode(pwm, OUTPUT);  // Set the PWM pin as output
  pinMode(tempPin,INPUT);
  pinMode(btn,INPUT);
  
}

void loop() {

  int temp_adc_val;
  int temp_val;
  temp_adc_val = analogRead(tempPin);
  temp_val = (temp_adc_val * 500)/1023;
  
    if (digitalRead(btn) && !btnFlag) {
    btnFlag = true;
    manualOverride = !manualOverride;  // Toggle manual override mode

 if (!fanState) {
      analogWrite(pwm, 255);  // Full speed in manual mode
      fanState = true;        // Set fanState to ON
    } else {
      analogWrite(pwm, 0);    // Turn off the fan in manual mode
      fanState = false;       // Set fanState to OFF
    }
  }

  // Reset button flag after the button is released
  if (!digitalRead(btn) && btnFlag) {
    btnFlag = false;
  }

  // Automatic temperature-based control (only if manual override is OFF)
  if (!manualOverride) {
    if (temp_val < 25) {
      analogWrite(pwm, 0);    // Fan off below 25°C
      fanState = false;
    } else if (temp_val >= 25 && temp_val < 30) {
      analogWrite(pwm, 128);  // Fan at 50% speed between 25°C and 30°C
      fanState = true;
    } else if (temp_val >= 30) {
      analogWrite(pwm, 255);  // Full speed above 30°C
      fanState = true;
    }
  }



  

  
  

  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print(temp_val);
  lcd.print((char)223);
  lcd.print("C");




  








 /* // Set fan speed to 10% (analogWrite value from 0 to 255)
  analogWrite(pwm, 25);  // 10% of 255 is roughly 25
  delay(1000);

  // Set fan speed to 50% (analogWrite value from 0 to 255)
  analogWrite(pwm, 127);  // 50% of 255 is roughly 127
  delay(1000);

  // Set fan speed to 100% (full speed)
  analogWrite(pwm, 255);  // Full speed (100%)
  delay(1000);
  */
}