#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------- Pin Definitions ----------
const int LM35_PIN = 34;      // LM35 OUT
const int CURRENT_PIN = 35;   // Potentiometer
const int GREEN_LED = 25;
const int RED_LED = 26;
const int BUZZER = 19;
const int RELAY = 18;
const int BUTTON = 27;

// ---------- Thresholds ----------
const float TEMP_LIMIT = 50.0;     // °C
const float CURRENT_LIMIT = 5.0;   // A

bool fault = false;

void setup() {
  Serial.begin(115200);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Transformer");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring");
  delay(2000);
  lcd.clear();
}

void loop() {

  // ---------- Read Temperature ----------
  int tempADC = analogRead(LM35_PIN);
  float voltage = (tempADC * 3.3) / 4095.0;
  float temperature = voltage * 100.0;

  // ---------- Read Current ----------
  int currentADC = analogRead(CURRENT_PIN);
  float current = (currentADC * 10.0) / 4095.0;

  // ---------- Fault Detection ----------
  if (temperature >= TEMP_LIMIT ||
      current >= CURRENT_LIMIT) {
    fault = true;
  }
  else {
    fault = false;
  }

  // ---------- Manual Reset ----------
  if (digitalRead(BUTTON) == LOW) {
    fault = false;
    delay(200);
  }

  // ---------- Outputs ----------
  digitalWrite(GREEN_LED, !fault);
  digitalWrite(RED_LED, fault);
  digitalWrite(BUZZER, fault);
  digitalWrite(RELAY, fault);

  // ---------- LCD Display ----------
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C ");

  lcd.setCursor(10, 0);
  if (fault)
    lcd.print("FAULT ");
  else
    lcd.print("SAFE  ");

  lcd.setCursor(0, 1);
  lcd.print("I:");
  lcd.print(current, 1);
  lcd.print("A     ");

  // ---------- Serial Monitor ----------
  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.print(" C");

  Serial.print("   Current: ");
  Serial.print(current, 1);
  Serial.print(" A");

  if (fault)
    Serial.println(" --> FAULT");
  else
    Serial.println(" --> SAFE");

  delay(500);
}