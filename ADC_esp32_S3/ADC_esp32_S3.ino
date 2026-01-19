#include <driver/adc.h>

// Global variables to store raw ADC values and calculated voltages
uint32_t raw_value_1 = 0;
uint32_t raw_value_2 = 0;

float V_1 = 0;
float V_2 = 0;

void setup() {
  // --- Configure ADC Parameters ---
  
  // Configure ADC1 Channel 1 (Typically GPIO 37)
  // ADC_ATTEN_DB_11: Sets input attenuation to 11dB (Range approx. 0 - 2.6V / 3.3V)
  adc1_config_channel_atten(ADC1_CHANNEL_1, ADC_ATTEN_DB_11);
  // ADC_WIDTH_BIT_12: Sets resolution to 12-bit (Values 0 - 4095)
  adc1_config_width(ADC_WIDTH_BIT_12);
   
  // Configure ADC1 Channel 2 (Typically GPIO 38)
  adc1_config_channel_atten(ADC1_CHANNEL_2, ADC_ATTEN_DB_11);
  adc1_config_width(ADC_WIDTH_BIT_12); // Note: Config width applies to the whole ADC unit

  Serial.begin(115200);
}

void loop() {
  // --- Channel 1 Processing ---
  // Read raw 12-bit value from Channel 1
  raw_value_1 = adc1_get_raw(ADC1_CHANNEL_1);

  // Convert raw bits to Voltage using custom linear mapping
  // Maps 0-4096 to 0-2800mV, adds an offset of 134mV, then converts to Volts.
  float V_1 = (float)((map(raw_value_1, 0, 4096, 0, 2800)) + 134) / 1000.00;

  // --- Channel 2 Processing ---
  // Read raw 12-bit value from Channel 2
  raw_value_2 = adc1_get_raw(ADC1_CHANNEL_2);

  // Convert raw bits to Voltage (Same formula as Channel 1)
  float V_2 = (float)((map(raw_value_2, 0, 4096, 0, 2800)) + 134) / 1000.00;

  // --- Display Results ---
  Serial.print(raw_value_1);
  Serial.print(" , ");
  Serial.print(V_1, 4);  // Print voltage with 4 decimal places
  Serial.print(" V | ");

  Serial.print(raw_value_2);
  Serial.print(" , ");
  Serial.print(V_2, 4);
  Serial.println(" V ");
   
  delay(10);
}
