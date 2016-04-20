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

 /*
  * PWM Setup
  * 1. Set PWM Mode ->  TCCR0A (0x2A) = 00000001
  *                 ->  TCCR0B (0x33) = 00001(???) -> 3 bit CS for resolution (80. o)
  * 2. Set Compare  ->  OCR0B  (0x28) = an 8 bit value defining the pulse width between 0 and 255
  * 3. Set PWM Compare->TCCR0A (0x2A) = 00100001
  */

int g = 1, clk = 3, ser_in = 4;

#define CTC 0     //No clear on OCR
#define PWMclr 0  //PWMA disabled
#define PWMset 1  //PWMA enabled
#define COMA 2    //PWM Set to Clear on OCR and set on 0 (after OCRC)
#define CS 11     //Prescaler set to CLK/1024 (with OCRC=255 it means a 32 Hz PWM) (with other OCRC values it's 8kHz/(OCRC + 1)
#define PWMB 0    //PWMB disabled
#define COMB 0    //OCRB disconnected
#define FOC 0     //Force compare disabled
#define PSR 0     //No prescaler reset
#define OCRA 51   //20% fill
#define OCRC 255  //Full time PWM



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
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;
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
