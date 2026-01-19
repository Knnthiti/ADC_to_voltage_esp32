#include <driver/adc.h>
#include <esp_adc_cal.h>

// Define the ADC channel to use (ADC1_CHANNEL_6 corresponds to GPIO 34)
#define ADC_CHANNEL ADC1_CHANNEL_6 

// Structure to store ADC calibration characteristics
esp_adc_cal_characteristics_t adc1_chars;

void setup() {
  Serial.begin(115200);

  // 1. Configure ADC resolution to 12-bit (Output range: 0 - 4095)
  adc1_config_width(ADC_WIDTH_BIT_12);

  // 2. Set Attenuation to 11dB (Allows measuring input voltage up to approx. 2.6V - 3.3V)
  // Note: This hardware configuration must match the characterization parameters set below.
  adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_11);

  // 3. Characterize the ADC to correct non-linearity and reference voltage error
  // This function uses the factory Vref stored in the ESP32's eFuse for precision.
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 0, &adc1_chars);
}

void loop() {
  uint32_t raw_sum = 0;
  uint32_t raw_avg = 0;
  uint32_t voltage_mV = 0;

  // Take 100 samples to calculate the average (Signal smoothing)
  for (int i = 0; i < 100; i++) {
    raw_sum += adc1_get_raw(ADC_CHANNEL);
    delay(1); // Small delay between samples
  }

  // Calculate the average raw value
  raw_avg = raw_sum / 100;

  // Convert the raw average to voltage (mV) using the calibration data
  voltage_mV = esp_adc_cal_raw_to_voltage(raw_avg, &adc1_chars);

  // Print results to Serial Monitor
  Serial.print("Raw: ");
  Serial.print(raw_avg);
  Serial.print("\t Voltage: ");
  Serial.print(voltage_mV);
  Serial.println(" mV");
}
