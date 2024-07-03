//arduino Frequency counter
#define PIN_READ 2  //digitalPin that the PWM is coming from

//Variables
volatile bool numReads = false; //flag to select what to read
volatile unsigned long firstMeasure = 0;  //first rising edge of PWM
volatile unsigned long secondMeasure = 0; //second rising edge of PWM
volatile float period = 1.0;
volatile float frequency = 0;
unsigned long time_now = 0; 
int updateInterval = 500;  //update frequency every 500 ms

void setup() {
  pinMode(PIN_READ, INPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(PIN_READ), readFrequency, RISING);
}

void loop() {
  if (millis() > time_now + updateInterval) {
    time_now = millis();
    updateFrequency();
    printFrequency();
  }
}

void readFrequency() {
  if (numReads) {
    firstMeasure = micros();
  } else {
    secondMeasure = micros();
    period = (float)(secondMeasure - firstMeasure) / 1000000.0; //period in seconds
  }
  numReads = !numReads;
}

void updateFrequency() {
  if (period > 0.0) {
    frequency = 1.0 / period;
  } else {
    frequency = 0.0;
  }
}

void printFrequency() {
  Serial.print("Frequency: ");
  Serial.print(frequency, 2);
  Serial.println(" Hz");
}
