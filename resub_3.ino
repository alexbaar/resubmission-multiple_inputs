const byte ledBtn = 12;
const byte ledMotion = 11;
const byte ledTouch = 9;
const byte interruptPinMotion = 2; 
const byte interruptPinTouch = 3;
const byte interruptPinBtn = 5;


volatile bool ledStateBtn = LOW;
volatile bool ledStateMotion = LOW;
volatile bool ledStateTouch = LOW;

void setup()
{
pinMode(ledBtn, OUTPUT);
pinMode(ledMotion, OUTPUT);
pinMode(ledTouch, OUTPUT);
pinMode(interruptPinMotion, INPUT);
pinMode(interruptPinTouch, INPUT);
pinMode(interruptPinBtn, INPUT);

// step 1 : turn interrupts on the port we use -> D
PCICR |= 0b00000100;

// step 2 : select pin D2, D3 and D5
PCMSK2 |= 0b00101100;

//Serial.begin(9600); // Starts the serial communication
}
void loop()
{

/*
Serial.print((String)"Rain: " + digitalRead(interruptPinRain));
Serial.println((String)" // Rain led: " + digitalRead(ledRain));
Serial.print((String)"Motion: " + digitalRead(interruptPinMotion));
Serial.println((String)" // Motion led: " + digitalRead(ledMotion));
delay(1000);
*/
}

ISR (PCINT2_vect)
{
// interrupt for port D
// check which port caused interruption:

// D2 ? motion Led?
if(digitalRead(interruptPinMotion) == HIGH)
{
// Pin D2 triggered the ISR when detecting rain and sending data value "1" to→ pin D2
ledStateMotion = !ledStateMotion;
// reflect that state in green led
digitalWrite(ledMotion, ledStateMotion);}


// D3 ? touch Led?
if(digitalRead(interruptPinTouch) == HIGH)
{
// Pin D3 triggered the ISR when detecting motion and sending data value "1" to→ pin D3
 ledStateTouch = !ledStateTouch;
 // reflect that state in green led
 digitalWrite(ledTouch, ledStateTouch);
}

 // D5 ? simple button Led?
if(digitalRead(interruptPinBtn) == HIGH)
{
// Pin D3 triggered the ISR when detecting motion and sending data value "1" to→ pin D3
 ledStateBtn = !ledStateBtn;
 // reflect that state in green led
 digitalWrite(ledBtn, ledStateBtn);
 }

 }
