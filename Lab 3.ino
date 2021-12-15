#include <DS1307RTC.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;

int sec = 0;                 // the seconds component of the time
int num_prs = 0;             // the number of button presses
int buttonState = 0;         // 

const int btn_pin = 2;       // the buttons pin
int dir1 = 3;                // pin for the first directional output
int dir2 = 4;                // pin for the second directional output
int speedPin = 5;            // pin for the speed
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
    Serial.begin(9600);
    lcd.begin(16,2); 
    if (! rtc.begin()){
        lcd.print("Couldn't find RTC");
        while (1);
    }
    if (! rtc.isrunning()){
        lcd.print("RTC is NOT running!");
    }

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    pinMode(btn_pin, INPUT);
    pinMode(speedPin, OUTPUT);
    pinMode(dir1, OUTPUT);
    pinMode(dir2, OUTPUT);                           
}

void loop() {
    buttonState = digitalRead(btn_pin);
    lcd.setCursor(0,1);
    lcd.print("Time:  ");
    DateTime now = rtc.now();
    Serial.println(now.second());
    sec = now.second ();
    lcd.print(now.hour());
    lcd.print(':');
    lcd.print(now.minute());
    lcd.print(':');
    lcd.print(now.second());
    lcd.print("   ");
    delay(1000);
    // put your main code here, to run repeatedly
    
    if (sec > 30){
        num_prs=0;
        lcd.begin(16,2);
        lcd.setCursor(0,0);
        lcd.print("Speed: 0");
        digitalWrite(dir1, LOW);
        digitalWrite(dir2, LOW);
        analogWrite(speedPin, 0);
    }
    else{
        if (buttonState == HIGH){
            num_prs = num_prs + 1;
            delay(500);
        }
        if (num_prs == 0){
            lcd.begin(16,2);
            lcd.setCursor(0,0);
            lcd.print("Speed: 0");
            digitalWrite(dir1, LOW);
            digitalWrite(dir2, LOW);
            analogWrite(speedPin, 0);
        }
        else if (num_prs == 1){
            lcd.begin(16,2);
            lcd.setCursor(0,0);
            lcd.print("Speed: 1/2 C");
            digitalWrite(dir1, LOW);
            digitalWrite(dir2, HIGH);
            delay(100);
            analogWrite(speedPin, 128);
        }
        else if (num_prs == 2){
            lcd.begin(16,2);
            lcd.setCursor(0,0);
            lcd.print("Speed: 3/4 C");
            digitalWrite(dir1, LOW);
            digitalWrite(dir2, HIGH);
            delay(100);
            analogWrite(speedPin,191);
        }
        else if (num_prs == 3){
            lcd.begin(16,2);
            lcd.setCursor(0,0);
            lcd.print("Speed: FULL C");
            digitalWrite(dir1, LOW);
            digitalWrite(dir2, HIGH);
            delay(100);
            analogWrite(speedPin,255);
        }
        else if (num_prs == 4){
            lcd.begin(16,2);
            lcd.setCursor(0,0);
            lcd.print("Speed: 1/2 CC");
            digitalWrite(dir1, HIGH);
            digitalWrite(dir2, LOW);
            delay(100);
            analogWrite(speedPin,128);
        }
        else if (num_prs == 5){
            lcd.begin(16,2);
            lcd.setCursor(0,0);
            lcd.print("Speed: 3/4 CC");
            digitalWrite(dir1, HIGH);
            digitalWrite(dir2, LOW);
            delay(100);
            analogWrite(speedPin,191);
        }
        else if (num_prs == 6){
            lcd.begin(16,2);
            lcd.setCursor(0,0);
            lcd.print("Speed: FULL CC");
            digitalWrite(dir1, HIGH);
            digitalWrite(dir2, LOW);
            delay(100);
            analogWrite(speedPin,255);
        }
        else{
            digitalWrite(dir1, LOW);
            digitalWrite(dir2, LOW);
            delay(100);
            analogWrite(speedPin,0); 
            num_prs=0;
        }
    }
    Serial.print("num_prs = ");
    Serial.print(num_prs);
    Serial.print("\n");
}
