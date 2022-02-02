
#define RX_PIN 8
#define LED_PIN 2
unsigned long pulses = 0;


void setup() {
  
  pinMode(RX_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  pulses = pulseIn(RX_PIN, HIGH);

  Serial.println(pulses);

  if(pulses < 1300)       //Bottom Position
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else if (pulses > 1700) // Top Position
  {
    digitalWrite(LED_PIN, LOW);
  }
  else                   //Middle Position
  {
    
  }
  
}
