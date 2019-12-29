#include <MicroArduino.h>

#define ultrasonic Serial1

#define ULTRASONIC_PIN C3
#define TRIGGER_PIN I6
#define ULTRASONIC_TIMEOUT 15

int getDistance()
{
  while (ultrasonic.available())
  {
    ultrasonic.read();
  }

  // Trigger measurement
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  delay(1);
  pinMode(TRIGGER_PIN, INPUT_PULLUP);

  long starttime = millis();    // timeout
  while (ultrasonic.available() < 3)
  {
    if (millis() - starttime > ULTRASONIC_TIMEOUT)
    {
      return -1;
    }
  }

  ultrasonic.read(); // read byte 0 (result of trigger)
  int distance = (ultrasonic.read() & B1) << 8;
  distance += ultrasonic.read();

  return distance;
}

void setup()
{
  ultrasonic.begin(115200);  // ultrasonic sensor
  Serial.begin(115200);      // serial monitor
  pinMode(ULTRASONIC_PIN, INPUT_PULLUP); // connect ultrasonic sensor to C3

  while (!Serial) {}         // wait for Serial connection
  Serial.println("Start");
}

void loop()
{
  Serial.println(getDistance());
  delay(200);
}
