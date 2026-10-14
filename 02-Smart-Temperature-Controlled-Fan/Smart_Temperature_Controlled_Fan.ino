#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define FAN_PIN 9

#define GREEN_LED 3
#define YELLOW_LED 4
#define RED_LED 5

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  dht.begin();

  pinMode(FAN_PIN, OUTPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  analogWrite(FAN_PIN, 0);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Sensor Error");

    analogWrite(FAN_PIN, 0);

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);

    delay(1000);
    return;
  }

  int fanSpeed = 0;

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  if (temp < 25) {
    fanSpeed = 0;
    digitalWrite(GREEN_LED, HIGH);
  }
  else if (temp < 30) {
    fanSpeed = 150;
    digitalWrite(YELLOW_LED, HIGH);
  }
  else {
    fanSpeed = 255;
    digitalWrite(RED_LED, HIGH);
  }

  analogWrite(FAN_PIN, fanSpeed);

  int fanPercent = map(fanSpeed, 0, 255, 0, 100);

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" C   ");

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %   ");

  Serial.print("Fan Speed: ");
  Serial.print(fanPercent);
  Serial.println(" %");

  delay(1000);
}
