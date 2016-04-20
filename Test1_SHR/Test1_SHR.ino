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

 #define COM0A 0  //NORMAL OC0A Port operation
 #define COM0B 2  //Clear OC0B on up Match, Set OC0B on down Match
 #define WGM 5    //PWM Phase Correct with OCRA as TOP
 #define FOC 0    //No Forced OCR
 #define CS 5     //8MHz/1024 Prescale
 #define OCRA 51  //20% fill
 #define OCRB 51  //20% fill

void setup() {
  // put your setup code here, to run once:
  pinMode(g, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(ser_in, OUTPUT);
  DDRB |= (1 << DDB1);
  TCCR0A = WGM & 3;
  TCCR0B = ((WGM >> 2) << 3) | CS | (FOC << 6);
  OCR0A = OCRA;
  OCR0B = OCRB;
  TCCR0A = (WGM & 3) | (COM0A << 6) | (COM0B << 4);
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
