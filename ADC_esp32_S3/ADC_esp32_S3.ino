#include <driver/adc.h>

uint32_t raw_value_1 = 0;
uint32_t raw_value_2 = 0;

float V_1 = 0;
float V_2 = 0;

void setup() {
  //setup_ADC
  adc1_config_channel_atten(ADC1_CHANNEL_1, ADC_ATTEN_DB_11);
  adc1_config_width(ADC_WIDTH_BIT_12);
  
  adc1_config_channel_atten(ADC1_CHANNEL_2, ADC_ATTEN_DB_11);
  adc1_config_width(ADC_WIDTH_BIT_12);

  Serial.begin(115200);
}

void loop() {
  //Read_ADC pin 1
  raw_value_1 = adc1_get_raw(ADC1_CHANNEL_1);

  //bit_to_V
  float V_1 = (float)((map(raw_value_1 ,0 ,4096 ,0 ,2800))+134)/1000.00;

  //Read_ADC pin 2
  raw_value_2 = adc1_get_raw(ADC1_CHANNEL_2);

  //bit_to_V
  float V_2 = (float)((map(raw_value_2 ,0 ,4096 ,0 ,2800))+134)/1000.00;

  //print value
  Serial.print(raw_value_1);
  Serial.print(" , ");
  Serial.print(V_1, 4);
  Serial.print(" V | ");

  Serial.print(raw_value_2);
  Serial.print(" , ");
  Serial.print(V_2, 4);
  Serial.println(" V ");
  
  delay(10);
}
