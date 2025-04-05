#include <driver/adc.h>
#include <esp_adc_cal.h>

uint32_t raw_value = 0;
uint32_t raw_value_avg = 0;

// float V_offset = 0;
// uint16_t mV = 0;

uint16_t V = 0;
uint16_t V_avg = 0;

//https://docs.espressif.com/projects/esp-idf/en/v4.4.3/esp32/api-reference/peripherals/adc.html#adc-channels     //datasheet esp32
//https://embeddedexplorer.com/esp32-adc-esp-idf-tutorial/                                                        //tutorial use adc esp32 library

esp_adc_cal_characteristics_t adc1_chars;

void setup() {
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 0, &adc1_chars);

  Serial.begin(115200);
}

void loop() {
  raw_value_avg = 0;

  for (uint8_t i = 0 ; i < 100; i++) {
    raw_value = adc1_get_raw(ADC1_CHANNEL_6);  //analogRead(pin 34);

    raw_value = map(raw_value, 4095, 0, 0, 4095);

    raw_value_avg += raw_value;

    delay(1);
  }
  // mV = map(raw_value ,142 ,3145 ,0 ,24000);
  // V_offset = map(mV ,24000 ,0 ,-1000 ,1000);

  // V = (mV+V_offset)/1000.0;
  
  raw_value_avg = raw_value_avg/100;
  V = esp_adc_cal_raw_to_voltage(raw_value_avg, &adc1_chars);

  Serial.print(raw_value_avg);
  Serial.print(" , ");
  Serial.print(V);
  Serial.println(" mV");
}
