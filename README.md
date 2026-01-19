# ESP32 ADC Direct Register Access

-data sheet esp32 : https://docs.espressif.com/projects/esp-idf/en/v4.4.3/esp32/api-reference/peripherals/adc.html

-data sheet esp32s3 : https://docs.espressif.com/projects/esp-idf/en/v4.4.3/esp32s3/api-reference/peripherals/adc.html

-example : https://www.embeddedexplorer.com/esp32-adc-esp-idf-tutorial/

This project demonstrates how to read Analog signals on the ESP32 using the **ESP-IDF Low-Level Driver** (`driver/adc.h`) within the Arduino environment.

By using `<driver/adc.h>`, we bypass the standard Arduino `analogRead()` abstraction. This method offers faster execution, explicit control over attenuation (voltage range), and precise bit-width configuration.

##  Features

- **Direct Driver Access:** Uses ESP32's native `adc1_get_raw()` for high-performance reading.
- **12-Bit Resolution:** Configured for 0-4095 raw values.
- **11dB Attenuation:** Configured to measure voltages up to ~2.6V - 3.3V (depending on calibration).
- **Custom Calibration:** Includes a linear mapping formula to convert raw bits to actual voltage.
