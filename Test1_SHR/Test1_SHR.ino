/*
 * PIN:
 * 
 * P0: SDA
 * P1: /G
 * P2: SCL
 * P3: CLK
 * P4: SER_IN
 * 
 * 
 */

#include <Wire.h>

char g = 1, clk = 3, ser_in = 4;
char dom[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char current[3];

#define CTC 0     //No clear on OCR
#define PWMclr 0  //PWMA disabled
#define PWMset 1  //PWMA enabled
#define COMA 2    //PWM Set to Clear on OCR and set on 0 (after OCRC)
#define CS 10     //Prescaler set to CLK/512 (with OCRC=255 it means a 64 Hz PWM) (with other OCRC values it's 8kHz/(OCRC + 1)
#define CSoff 0   //Timer is off (no clock)
#define PWMB 0    //PWMB disabled
#define COMB 0    //OCRB disconnected
#define FOC 0     //Force compare disabled
#define PSR 0     //No prescaler reset
#define OCRA 51   //20% fill
#define OCRC 255  //Full time PWM

void errorSeq(int n){
  char i;
  for(i = 0; i < n; i++){
    digitalWrite(g, 1);
    delay(1000);
    digitalWrite(g, 0);
    delay(1000);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(g, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(ser_in, OUTPUT);
  DDRB |= (1 << DDB1);
  TCCR1 = (CTC << 7) | (PWMset << 6) | (COMA << 4) | CS;
  GTCCR = (PWMB << 6) | (COMB << 4) | (FOC << 2) | (PSR << 1);
  OCR1A = OCRA;
  OCR1C = OCRC;
  Wire.begin();
  Wire.requestFrom(0x68, 7);
  char i;
  for(i = 0; i < 7; i++){
    /*if(!Wire.available()){
      errorSeq(2);
      exit(0);
    }*/
    if(i > 3)
      current[i - 4] = Wire.read();
    else
      Wire.read();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  char i;
  digitalWrite(ser_in, 1);
  for(i = 0; i < 8; i++){
    digitalWrite(g, 1);
    digitalWrite(clk, 1);
    digitalWrite(clk, 0);
    digitalWrite(g, 0);
    delay(1000);  
  }
  digitalWrite(ser_in, 0);
  for(i = 0; i < 8; i++){
    digitalWrite(g, 1);
    digitalWrite(clk, 1);
    digitalWrite(clk, 0);
    digitalWrite(g, 0);
    delay(1000);  
  }  
}
