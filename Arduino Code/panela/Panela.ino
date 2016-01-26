// include libraries
#include <LiquidCrystal.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>

// Constants
#define BUTTONS_PIN A0
#define DS18B20_PIN 2
#define RELAY_PIN 3
#define BUZZER_PIN 11
// Shield Buttons
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// declare variables
int  clockIconState = 0, steamIconState = 0;
double currentTemperature = 0, targetTemperature = 50, PIDOutput = 0;
long targetTime = 0, timeStarted = 0, currentWorkingTime = 0, lastTimeButtonsAreProcessed = 0, iconLastMillis = 0;
boolean machineIsWorking = false;
//PID Stuff
double kp=196, ki=33, kd=290;


// create library instances
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
OneWire ds18b20(DS18B20_PIN);
DallasTemperature temperatureSensor(&ds18b20);
PID PIDCalculation(&currentTemperature, &PIDOutput, &targetTemperature,kp,ki,kd, DIRECT);

void setup() {
  Serial.begin(9600);
  initializePins();
  initializeDisplay();
  initializePID();
}

void loop() {
  processButtons();
  readCurrentTemperature();
  processPIDCalculation();
  printLCDData();
  proccessTimers();
  checkMachineStatus();
  proccessIconAnimations();
}

void initializePID(){
 PIDCalculation.SetTunings(kp,ki,kd);
 PIDCalculation.SetMode(AUTOMATIC);
}

void processPIDCalculation(){
  
  // Limit the resistor block using PWM since the heating is precise
  if(targetTemperature - currentTemperature > 15){
   PIDCalculation.SetOutputLimits(0, 255); 
  }else if(targetTemperature - currentTemperature > 10){
       PIDCalculation.SetOutputLimits(0, 130); 
  }else if(targetTemperature - currentTemperature > 3){
       PIDCalculation.SetOutputLimits(0, 100);     
  }else if(targetTemperature - currentTemperature > 1){
       PIDCalculation.SetOutputLimits(0, 40);     
  }else if(targetTemperature - currentTemperature > 0){
       PIDCalculation.SetOutputLimits(0, 120);     
  }else if(targetTemperature - currentTemperature > -2){
       PIDCalculation.SetOutputLimits(0, 255);     
  }
  
  // Compute the PID calculation
  PIDCalculation.Compute(); 
  Serial.print(currentTemperature);
  Serial.print(" - ");
  Serial.println(PIDOutput);
}

void readCurrentTemperature(){
  temperatureSensor.requestTemperatures();
  currentTemperature = temperatureSensor.getTempCByIndex(0);
}

void checkMachineStatus(){
  if(machineIsWorking)
    analogWrite(RELAY_PIN, PIDOutput);
  else
    digitalWrite(RELAY_PIN, false);
}

void proccessTimers(){
   if(machineIsWorking && (currentTemperature >= (targetTemperature * 0.95))){
     long difference = millis() - lastTimeButtonsAreProcessed;
     if(targetTime > 0){
       // Turn off the machine when the time is over
       if((targetTime - (difference)) <= 0){
         machineIsWorking = false;
         beep(5);
       }
       targetTime -= difference;
       if(targetTime < 0)
         targetTime = 0;
     }
     currentWorkingTime += difference;
   }
   lastTimeButtonsAreProcessed = millis();
}

void initializePins(){
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void initializeDisplay(){
  lcd.begin(16, 2);
  lcd.write("T");
  lcd.setCursor(0, 1);
  lcd.write("C");
}

void processButtons(){
  int sensorValue = read_LCD_buttons();
  
  if(sensorValue == btnSELECT){
    machineIsWorking = !machineIsWorking;
    beep(1);
    if(timeStarted == 0)
      timeStarted = millis();
    delay(100);
  }else if(sensorValue == btnDOWN){
    if(targetTemperature > 50){
      targetTemperature--;
      delay(100);
    }
  }else if(sensorValue == btnUP){
    if(targetTemperature <= 100){
      targetTemperature++;
      delay(100);
    }
  }else if(sensorValue == btnLEFT){
    if(targetTime > 0){
      targetTime-=300000;
      delay(100);
    }
  }else if(sensorValue == btnRIGHT){
    if(targetTime < 43200000){
      targetTime+=300000;
      delay(100);
    }
  }

}

void printLCDData(){
  lcd.setCursor(2, 0);

  if(currentTemperature < 10)
      lcd.print("  ");
  else if(currentTemperature < 100)
      lcd.print(" ");

  lcd.print(currentTemperature);
  lcd.setCursor(7, 0);  
  lcd.print("C");
  lcd.setCursor(8, 0);  
  lcd.print("/");  
  
  if(targetTemperature < 13)
      lcd.print("  ");
  else if(targetTemperature < 100)
      lcd.print(" ");  
  
  lcd.print((int)targetTemperature);
  lcd.print("C");
  
  lcd.setCursor(2, 1);
  if(targetTime == 0)
    lcd.print("--:--");
  else
    lcd.print(convertMillisToText(targetTime));
    
  lcd.setCursor(10, 1);
  if(timeStarted == 0)
    lcd.print("00:00");
  else
    lcd.print(convertMillisToText(currentWorkingTime));
  
  
}

int read_LCD_buttons(){               // read the buttons
    int adc_key_in = analogRead(BUTTONS_PIN);       // read the value from the sensor 
 
    if (adc_key_in > 1000) return btnNONE; 
    /*
    if (adc_key_in < 50)   return btnRIGHT;  
    if (adc_key_in < 250)  return btnUP; 
    if (adc_key_in < 450)  return btnDOWN; 
    if (adc_key_in < 650)  return btnLEFT; 
    if (adc_key_in < 850)  return btnSELECT;  
 */
   // For V1.0 comment the other threshold and use the one below:
     if (adc_key_in < 50)   return btnRIGHT;  
     if (adc_key_in < 195)  return btnUP; 
     if (adc_key_in < 380)  return btnDOWN; 
     if (adc_key_in < 555)  return btnLEFT; 
     if (adc_key_in < 790)  return btnSELECT;   
   
 
    return btnNONE;                // when all others fail, return this.
}

String convertMillisToText(long time){
  long hours = (time / 3600000) % 24;
  long minutes = (time / 60000) % 60;
  String timeText = "";
  if(hours < 10)
    timeText += "0";
  timeText += String(hours);
  timeText += ":";
  if(minutes < 10)
    timeText += "0";
  timeText += String(minutes);
  return timeText;
}

void proccessIconAnimations(){
  if(millis() - iconLastMillis > 600){
    iconLastMillis = millis();
    if(machineIsWorking){
        lcd.setCursor(8, 1);
        switch(clockIconState){
          case 0:
            lcd.print("|");
            break;
          case 1:
            lcd.print("-");
            break;
          default:
            lcd.print("|");
            break;
        }  
        clockIconState = clockIconState == 1 ? 0 : clockIconState + 1; 
        lcd.setCursor(13, 0);        
        lcd.print("!!!");
    }else{
      lcd.setCursor(8, 1);
      lcd.print("+");
      lcd.setCursor(13, 0);        
      lcd.print("   ");
    }
  }
}
void beep(int b){
  int toneFrequency = 3000;
  for(int i = 0; i < b; i++){
    tone(BUZZER_PIN, toneFrequency, 600);
    if(i < 0);
      delay(1200);
  }
  //noTone(BUZZER_PIN);
}
