#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

// Pin #2 is IN from sensor (GREEN wire)
// Pin #3 is OUT from Arduino (WHITE wire)
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  Serial.begin(9600);
  Serial.println("fingertest");
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // Set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Waiting for valid finger...");
}

void loop() {
  getFingerprintIDez();
  delay(50); // Don't need to run this at full speed
}

void getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) {
    Serial.println("No finger detected");
    return;
  }

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) {
    Serial.println("Error converting image");
    return;
  }

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) {
    Serial.println("Finger not found");
    return;
  }

  // Finger found!
  Serial.print("Found ID #");
  Serial.print(finger.fingerID);
  Serial.print(" with confidence of ");
  Serial.println(finger.confidence);

  digitalWrite(13, HIGH);
  delay(3000);
  digitalWrite(13, LOW);
}