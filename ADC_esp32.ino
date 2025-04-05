#include <driver/adc.h>

uint32_t raw_value_1 = 0;
uint32_t raw_value_2 = 0;

float V_1 = 0;
float V_2 = 0;

void setup() {
  adc1_config_channel_atten(ADC1_CHANNEL_1, ADC_ATTEN_DB_11);
  adc1_config_width(ADC_WIDTH_BIT_12);
  
  adc1_config_channel_atten(ADC1_CHANNEL_2, ADC_ATTEN_DB_11);
  adc1_config_width(ADC_WIDTH_BIT_12);

  Serial.begin(115200);
}

void loop() {
  raw_value_1 = adc1_get_raw(ADC1_CHANNEL_1);  //analogRead(pin 1);

  // float V_1 = (float)((map(raw_value_1 ,0 ,4096 ,0 ,2800))+134)/1000.00;
  float V_1 = (float)map(raw_value_1 ,330 ,4095 ,-100 ,100);

  if((V_1 < 12) && (V_1 > -12)){
    V_1 = 0;
  }

  raw_value_2 = adc1_get_raw(ADC1_CHANNEL_2);  //analogRead(pin 1);

  // float V_2 = (float)((map(raw_value_2 ,0 ,4096 ,0 ,2800))+134)/1000.00;
  float V_2 = (float)map(raw_value_2 ,500 ,4095 ,-100 ,100);

  if((V_2 < 12) && (V_2 > -12)){
    V_2 = 0;
  }

  Serial.print(raw_value_1);
  Serial.print(" , ");
  Serial.print(V_1, 4);
  Serial.print(" % ");

  Serial.print(raw_value_2);
  Serial.print(" , ");
  Serial.print(V_2, 4);
  Serial.println(" % ");
  
  delay(1);
}