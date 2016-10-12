//Sketch for land rover discovery 2 SLS controller. 

//ATTINY 45 1MHZ INTERNAL CLOCK
 
#define SLABS_PIN 0   //pin to connect to the SLABS ecu.
#define PIN_UP 1      //grounding this will send us up
#define PIN_DOWN 2  //grounding this will send us down
#define CYCLE_TIME 40  // ( 1 / freq) *1000   (25Hz)

int dutycycle, ontime, offtime;

void setup() {                
  pinMode(SLABS_PIN, OUTPUT); 
  pinMode(PIN_UP, INPUT);     //Both up/down pins are input pins, with internal pullups.  
  digitalWrite(PIN_UP, HIGH); //Ground them to activate up/down modes
  pinMode(PIN_DOWN, INPUT);
  digitalWrite(PIN_DOWN, HIGH); 
}

// the loop routine runs over and over again forever:
void loop() {
  //The next bit needs to be as quick as possible so as to keep the cycle timing
  //as accurate as possible.
  if (digitalRead(PIN_UP) == LOW) dutycycle = 75;
  else if (digitalRead(PIN_DOWN) == LOW) dutycycle = 25;
  else dutycycle = 50;
  
  ontime = CYCLE_TIME * (float)dutycycle/100;
  offtime = CYCLE_TIME - ontime;
  
  digitalWrite(SLABS_PIN, LOW);  //The transistor means this is inverted...  
  delay(ontime); 
  digitalWrite(SLABS_PIN, HIGH); //The transistor means this is inverted...  
  delay(offtime);             
}

