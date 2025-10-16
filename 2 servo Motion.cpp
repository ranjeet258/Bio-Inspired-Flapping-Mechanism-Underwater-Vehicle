#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create the PWM driver instance
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);  // Default I2C address 0x40

// Servo parameters
#define SERVOMIN 125    // Minimum pulse length out of 4096
#define SERVOMAX 625    // Maximum pulse length out of 4096

// Flapping parameters
float A = 1.0;               // Amplitude coefficient
float B = 1.0;               // Frequency coefficient
float x = PI / 2;            // Base x value
float baselength = 1.0;      // Fins' base length for atan calculation
float phase = 0;             // Current phase
float PhaseShift = PI / 2;   // Phase difference between fins
int N = 2;                    // Number of oscillations
unsigned long t1, t2 = 0;
float interval = 60;         // Update interval (ms)

// Servo channel mapping
int servoChannels[2] = {0, 1}; // Example: forward fin pair

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos ~60 Hz

  // Initialize servos to 90°
  pwm.setPWM(servoChannels[0], 0, angleToPulse(90));
  pwm.setPWM(servoChannels[1], 0, angleToPulse(ro(90)));
  delay(2000);
}

void loop() {
  t1 = millis();
  
  if (t1 - t2 >= interval) {
    phase += 0.1;
    if (phase >= N * PI) phase = 0;

    // Compute and send angles to servos
    float angle0 = sineWave0(phase);
    float angle1 = ro(sineWave1(phase));
    
    pwm.setPWM(servoChannels[0], 0, angleToPulse(angle0));
    pwm.setPWM(servoChannels[1], 0, angleToPulse(angle1));

    Serial.print("Servo Angles: ");
    Serial.print(angle0);
    Serial.print("\t");
    Serial.println(angle1);

    t2 = t1;
  }
}

// Convert degrees to pulse for Adafruit PWM driver
int angleToPulse(float ang) {
  return map(ang, 0, 180, SERVOMIN, SERVOMAX);
}

// Sinusoidal motion for first servo
float sineWave0(float phase0) {
  float y = A * sin(B * x + phase0);
  float radians = atan(y / baselength);
  return 90 - (radians * 180 / PI);
}

// Sinusoidal motion for second servo (phase-shifted)
float sineWave1(float phase1) {
  float y = A * sin(B * x + phase1 - PhaseShift);
  float radians = atan(y / baselength);
  return 90 - (radians * 180 / PI);
}

// Reverse angle function
float ro(float angle) {
  return 180 - angle;
}
