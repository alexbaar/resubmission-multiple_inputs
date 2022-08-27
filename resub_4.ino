volatile byte m, t ,b = 0;

const int touchLed = 12;
const int buttonLed = 11;
const int motionLed = 9;

const uint16_t t1_load = 0;
const uint16_t t1_comp = 31250;




void setup() 
{
  // led
  pinMode(motionLed, OUTPUT); 
  pinMode(touchLed, OUTPUT);  
  pinMode(buttonLed, OUTPUT); 

  // step 1 : turn interrupts on the port we use -> D
  PCICR |= 0b00000111;

  // step 2 : select pin D2 (third bit from right) ; rain sensor data pin and motion are both interruptors now
  PCMSK2 |= 0b00101100; 
  
  Serial.begin(9600); // Starts the serial communication
cli();//stop interrupts

// MOTION sensor
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 71;// = (16*10^6) / (2000*64) - 1 (must be <256)       
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

// TOUCH button
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 65124;// = (16*10^6) / (1*1024) - 1 (must be <65536)  
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

// TOUCH button
  TCCR2A = 0;// set entire TCCR1A register to 0
  TCCR2B = 0;// same for TCCR1B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR2A = 254;//  (must be <255)    
  // turn on CTC mode
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);  
  // enable timer compare interrupt
  TIMSK2 |= (1 << TOIE2);

 sei();
}
void loop() 
{
  //digitalWrite(12,r); // rain
  //digitalWrite(9,t); // touch 
  digitalWrite(11,b); // button

}

ISR (PCINT2_vect)
{
  m = PIND & B00000100; // motion
  t = PIND & B00001000; // touch
  b = PIND & B00100000; // button
}

ISR(TIMER0_COMPA_vect)
{
  if (t){
    digitalWrite(touchLed,HIGH);
    t = 0;
    
  }
  else{
    digitalWrite(touchLed,LOW);
  }
}


ISR(TIMER1_COMPA_vect)
{
  if (m){
    digitalWrite(motionLed,HIGH);
    m=0;
    //digitalWrite(touchLed,LOW);
    
  }
  else{
    digitalWrite(motionLed,LOW);
}
}

ISR(TIMER2_COMPA_vect)
{
  if (t){
    digitalWrite(buttonLed,HIGH);
    b = 0;
    
  }
  else{
    digitalWrite(buttonLed,LOW);
  }
}
/*
  Serial.print((String)"Rain: " + digitalRead(2));
  Serial.print((String)"  led: " + digitalRead(motionLed));
  Serial.print((String)"// Touch: " + digitalRead(3));
  Serial.print((String)" led: " + digitalRead(touchLed));
  Serial.print((String)"// Button: " + digitalRead(5));
  Serial.println((String)" led: " + digitalRead(buttonLed));
  */
