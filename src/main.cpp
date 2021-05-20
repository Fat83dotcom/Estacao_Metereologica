#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <math.h>
#define pin10k 1

Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  pinMode(pin10k, OUTPUT);
  bool status = bme.begin(0x76); 
  delay(5000);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

double getTemp() {
  
  int RawADC = analogRead(pin10k);
  long Resistance;
  double Temp;
  Resistance=((10240000/RawADC) - 10000);
  Temp = log(Resistance);
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;  // Convert Kelvin to Celsius
  return Temp;  
}


void principal() {

  static unsigned long ultimaLetura = millis();
  if ((millis() - ultimaLetura) <= 1) {
    float temp     = bme.readTemperature();
    float umid     = bme.readHumidity();
    float pressao  = bme.readPressure() / 100.0F;
    float temp10k = getTemp();

    Serial.print("u ");
    Serial.println(umid);
  
    Serial.print("1 ");
    Serial.println(temp);

    Serial.print("p ");
    Serial.println(pressao);

    Serial.print("2 ");
    Serial.println(temp10k);
  }
  if ((millis() - ultimaLetura) >= 499){
    ultimaLetura = millis();
  }
}

void loop() {

  principal();
}