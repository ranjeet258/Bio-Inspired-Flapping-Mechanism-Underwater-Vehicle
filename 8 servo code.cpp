#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <math.h>

// Create PWM driver instance (16-channel)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// Servo PWM limits
#define SERVOMIN 125    // Minimum pulse
#define SERVOMAX 625    // Maximum pulse

// Flapping parameters
float amplitude = 25.0;       // Flapping amplitude (degrees)
float frequency = 1.0;        // Flapping frequency (Hz)
float baselength = 1.0;       // Base length for atan calculation
float interval = 20;           // Loop interval in ms (~50Hz update)
unsigned long lastUpdate = 0;

// Phase offsets for each fin (radians)
float phaseOffset[4] = {0, PI/2, PI, 3*PI/2};

// Servo channel mapping (2 servos per fin)
int servoChannels[4][2] = {
  {0, 1}, // Forward fin 1
  {2, 3}, // Forward fin 2
  {4, 5}, // Backward fin 1
  {6, 7}  // Backward fin 2
};

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos ~60Hz

  // Initialize all servos to 90°
  for (int fin = 0; fin < 4; fin++) {
    for (int s = 0; s < 2; s++) {
      pwm.setPWM(servoChannels[fin][s], 0, angleToPulse(90));
    }
  }
  delay(2000);
}

void loop() {
  unsigned long now = millis();
  if (now - lastUpdate >= interval) {
    float t = now / 1000.0;  // Current time in seconds

    for (int fin = 0; fin < 4; fin++) {
      float phase = 2 * PI * frequency * t + phaseOffset[fin];

      // Compute angles for both servos in the fin
      float angle = finSineWave(phase);
      float angleMirror = 180 - angle; // Mirror for second servo

      pwm.setPWM(servoChannels[fin][0], 0, angleToPulse(angle));
      pwm.setPWM(servoChannels[fin][1], 0, angleToPulse(angleMirror));

      // Optional: Serial output for debugging
      Serial.print("Fin ");
      Serial.print(fin + 1);
      Serial.print(": ");
      Serial.print(angle);
      Serial.print("\t");
      Serial.println(angleMirror);
    }
    lastUpdate = now;
  }
}

// Convert degrees to PWM pulse
int angleToPulse(float angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

// Sinusoidal motion function for fin
float finSineWave(float phase) {
  float y = amplitude * sin(phase);
  float radians = atan(y / baselength);
  return 90 - (radians * 180 / PI); // Center around 90°
}
