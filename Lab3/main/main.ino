#include <Arduino.h>
#include <stdio.h>

#define BAUD_RATE 9600
#define TEMP_SENSOR_PIN A0   // temperature sensor
#define LIGHT_SENSOR_PIN A1  // light sensor

#define TEMP_SENSOR_VALUE_BUFFER_SIZE 3
#define FILTER_SAMPLES 5

const float SystemReferenceVoltage = 5.0;  // ADC reference voltage
const float SystempResolution = 1023.0;    // ADC resolution for 10 bits

// Temperature data
const float TempVoltageOffset = 0.5;
int TempIndex = 100;

// Photoresistor data
const float LightIntensityCalibrationFactor = 100.0;  // Calibration factor to convert voltage to light intensity
const float LightIntensityOffset = 0.0;

// Salt and pepper
int TempSensorBuff[TEMP_SENSOR_VALUE_BUFFER_SIZE];
int TempSensorBuffCopy[TEMP_SENSOR_VALUE_BUFFER_SIZE];
int TempSensorPos = 0;

// Weighted average
float weights[FILTER_SAMPLES] = { 0.1, 0.2, 0.3, 0.2, 0.2 };  // sum of 1
int tempADCBuffer[FILTER_SAMPLES];
int photoADCBuffer[FILTER_SAMPLES];
int tempADCIndex = 0;
int photoADCIndex = 0;

int compareFunction(const void* a, const void* b) {
  return (*(int*)a - *(int*)b);
}

int WeightedAverageMethod(int* buffer) {
  float sum = 0.0;
  for (int i = 0; i < FILTER_SAMPLES; i++) {
    sum += buffer[i] * weights[i];
  }
  return sum;
}

FILE f_out;
// int sput(char c, __attribute__((unused)) FILE* f) {
//   return !Serial.write(c);
// }

int sput(char c, __attribute__((unused)) FILE* f) {
  if (c == '\n') {
    Serial.write('\r');
  }
  return !Serial.write(c);
}


void redirectOutput() {
  fdev_setup_stream(&f_out, sput, nullptr, _FDEV_SETUP_WRITE);  
  // https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html#gaf41f158c022cbb6203ccd87d27301226
  stdout = &f_out;
}

void setup() {
  Serial.begin(BAUD_RATE);
  redirectOutput();
}

void loop() {
  int TempSensorValue = analogRead(TEMP_SENSOR_PIN);
  int LightSensorValue = analogRead(LIGHT_SENSOR_PIN);

  // Salt and Pepper filter
  if (++TempSensorPos >= TEMP_SENSOR_VALUE_BUFFER_SIZE) {
    TempSensorPos = 0;
  }
  for (int i = 0; i <= TEMP_SENSOR_VALUE_BUFFER_SIZE; i++) {
    TempSensorBuffCopy[i] = TempSensorBuff[i];
  }
  qsort(TempSensorBuffCopy, TEMP_SENSOR_VALUE_BUFFER_SIZE, sizeof(int), compareFunction);
  int TempSensorMedian = TempSensorBuffCopy[TEMP_SENSOR_VALUE_BUFFER_SIZE / 2];
  TempSensorBuff[TempSensorPos] = TempSensorValue;

  // WeightedAverage
  for (int i = FILTER_SAMPLES - 1; i > 0; i--) {
    photoADCBuffer[i] = photoADCBuffer[i - 1];
  }
  photoADCBuffer[0] = LightSensorValue;

  int filteredPhotoADC = WeightedAverageMethod(photoADCBuffer);

  float TempVoltage = (TempSensorMedian / SystempResolution) * SystemReferenceVoltage;  // Conversion of ADC to Voltage
  float Temp = (TempVoltage - TempVoltageOffset) * TempIndex;                           // Conversion of Voltage to Physical Parameter

  float PhotoresistorVoltage = (filteredPhotoADC / SystempResolution) * SystemReferenceVoltage;
  float LightIntensity = (PhotoresistorVoltage - LightIntensityOffset) * LightIntensityCalibrationFactor;

  // printf("Temperature ADC: %.2f\n", (float)TempSensorMedian);
  // printf("Temperature Voltage: %.2f\n", (float)TempVoltage);  // %.2f pentru două zecimale
  // printf("Temperature: %.1f C\n", (float)Temp);               // %.1f pentru o zecimală

  // printf("<<====================================>>\n");

  // printf("Photoresistor ADC: %.2f\n", (float)filteredPhotoADC);
  // printf("Photoresistor Voltage: %.2f\n", (float)PhotoresistorVoltage);
  // printf("Light Intensity: %.2f\n", (float)LightIntensity);

  printf("Temperature ADC: %d\n", TempSensorMedian);
  printf("Temperature Voltage: %d\n", (int)TempVoltage);
  printf("Temperature: %d C\n", (int)Temp);

  printf("<<====================================>>\n");

  printf("Photoresistor ADC: %d\n", filteredPhotoADC);
  printf("Photoresistor Voltage: %d\n", (int)PhotoresistorVoltage);
  printf("Light Intensity: %d\n", (int)LightIntensity);

  printf("<<====================================>>\n");

  delay(1000);  // 1s delay

  // Serial.println("Temperature ADC: " + String(TempSensorMedian));
  // Serial.println("Temperature Voltage: " + String(TempVoltage));
  // Serial.println("Temperature: " + String(Temp) + " C");

  // Serial.println("Photoresistor ADC: " + String(filteredPhotoADC));
  // Serial.println("Photoresistor Voltage: " + String(PhotoresistorVoltage));
  // Serial.println("Light Intensity: " + String(LightIntensity));

}
