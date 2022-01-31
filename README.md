# MQ135 Air Quality Sensor On ESP32 With MQTT
Air Quality is deteriorating day by day and Air pollution has become a common phenomenon everywhere. Specially in the urban areas, the inevitable increase in industries and urbanization would add up to make it worse.

The MQ135 Gas sensors are used in air quality control systems and are suitable for detecting gases such as CO2,  Smoke, NH3, NOx, Alcohol, Benzene, etc.

The purpose of this tutorial is to explain how to develop a device which can monitor the pollutant parameters in Air, especially CO2 in real time using MQ135 Gas Sensor with ESP32 WiFi module .

## 1) Required Materials 

Computer running Arduino IDE software.
- ESP32 development board.
- MQ135 Gas Sensor.
- 1K Resistor.
- Jumper wires.
- USB micro cable to connect ESP32 development board to the computer.

## 2) MQ135 Features

Some of the MQ135 sensor characteristics are listed below:
- Operating Voltage is +5V.
- Output voltage: Analog 0V to 5V or Digital 5V  TTL Logic.
- Preheat duration 20 seconds.
- Fast response and High sensitivity.

We can either use the digital pin or the analog pin to get indication of the PPM (Parts-per-million) of specific gas in Air. 
The digital Output (5V  TTL Logic) gives only good or bad status by setting a threshold value using the potentiometer onboard, While the Analog output gives the raw data measurements.
In this tuto we use the analog output : The ESP32 reads the analog pin A0 (0-5V) that are directly proportional to the concentration of the CO2 gas detected by the sensor.
Here are some example of indicator levels to read the CO2 PPM values:
 - Less than 400 PPM: Normal background concentration in outdoor ambient Air.
 - From 400 to 1000 PPM: Typical in occupied indoor spaces with good air exchange.
 - More than 1000 PPM: Poor air.
## 3) Circuit schematic :
The connections are pretty simple. The picture below shows the MQ135 Gas Sensor connected to the ESP32 development board.
![esp32-Gas-2_bb](https://user-images.githubusercontent.com/89652407/151814705-68ea5f25-9e54-459e-af46-b77d4372bfa9.png)
    * The MQ135 sensor is a 4-pin module. Connect the MQ135Vcc pin to the 5V of the ESP32 board.
    * Connect the ground pin of the MQ135 to the ESP32 ground.
    * Connect the Analog pin of the MQ135 to the A0 pin of the ESP32 via a 1K resistor.
    * Last, connect your ESP32 to the computer through a USB cable. The ESP32 will be powered from the USB 5V.
