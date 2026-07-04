# Smart-Transformer-Protection-Monitoring-System
An ESP32-based Smart Transformer Protection and Monitoring System that continuously monitors transformer temperature and current, detects abnormal conditions, and provides real-time alerts using LEDs, buzzer, relay, and LCD display.


# Smart Transformer Protection & Monitoring System

## 📌 Project Overview
This project presents an **IoT-ready Smart Transformer Protection and Monitoring System** powered by the **ESP32** microcontroller. The system continuously tracks the transformer's temperature and load current in real time, providing automated, instantaneous protection against abnormal operating conditions.

When the temperature or load current exceeds predefined safe thresholds, the system automatically triggers a multi-tier safety protocol:
* 🚨 **Activates** the audible alarm buzzer.
* 🔴 **Turns ON** the red fault indication LED.
* ⚡ **Operates** the relay module to isolate the transformer.
* 📊 **Displays** the real-time fault status on an I2C LCD screen.

This system is designed to prevent transformer overheating, mitigate overload conditions, and significantly improve overall power system reliability.

---

## 🎯 Objectives
* **Real-Time Monitoring:** Continuously track transformer temperature and load current.
* **Threshold Detection:** Instantly identify dangerous overload and overheating conditions.
* **Automated Alerting:** Provide immediate visual (LED) and audible (Buzzer) alarms.
* **Local Display:** Present clear, live telemetry data on a 16x2 I2C LCD.
* **Active Protection:** Command a relay control module to isolate the system during critical faults.

---

## ✨ Features
* ✔ **Real-Time Telemetry:** Continuous sampling of vital parameters.
* ✔ **Over-Temperature Protection:** Automated trip when thermal limits are breached.
* ✔ **Over-Current Protection:** Automated trip when current limits are breached.
* ✔ **I2C LCD Status Display:** Reduces wiring complexity while keeping the user informed.
* ✔ **Relay-Based Isolation:** Physical circuit interruption for true hardware protection.
* ✔ **Dual LED Indicators:** Quick visual diagnostic status (Green = Safe, Red = Fault).
* ✔ **Manual Reset Button:** Allows safe system recovery after a fault has been cleared.

---

## 🛠️ Components & Hardware Requirements

| Component | Quantity | Description |
| :--- | :---: | :--- |
| **ESP32 DevKit V1** | 1 | Main microcontroller with Wi-Fi/Bluetooth capabilities |
| **LM35 Temperature Sensor** | 1 | Precision IC temperature sensor |
| **Potentiometer** | 1 | Used for load current simulation |
| **I2C LCD Display (16x2)** | 1 | Alphanumeric display for system data and state |
| **Relay Module** | 1 | Acts as the circuit breaker for isolation |
| **Green LED** | 1 | System STATUS: SAFE indicator |
| **Red LED** | 1 | System STATUS: FAULT indicator |
| **Buzzer** | 1 | Audible alarm indicator |
| **Push Button** | 1 | Manual system reset switch |
| **Resistors** | 3 | Current limiting for LEDs/Pull-ups |
| **Jumper Wires** | Several | Circuit interconnections |

---

## 📌 Pin Configuration

| Component | ESP32 Pin | Type | Description |
| :--- | :---: | :---: | :--- |
| **LM35 Output** | `GPIO34` | Analog Input | Temperature Reading |
| **Potentiometer** | `GPIO35` | Analog Input | Current Simulation |
| **Green LED** | `GPIO25` | Digital Output | Safe Indicator |
| **Red LED** | `GPIO26` | Digital Output | Fault Indicator |
| **Buzzer** | `GPIO19` | Digital Output | Audible Alarm |
| **Relay** | `GPIO18` | Digital Output | Isolation Control |
| **Push Button** | `GPIO27` | Digital Input | Manual Reset |
| **LCD SDA** | `GPIO21` | I2C Data | Display Data Line |
| **LCD SCL** | `GPIO22` | I2C Clock | Display Clock Line |

---

## ⚙️ Working Principle

The system continuously loops through data acquisition, threshold evaluation, and peripheral control state machines:

1. **Data Acquisition:** The ESP32 reads raw analog values from the **LM35** sensor and converts them to Celsius. Concurrently, it reads the **Potentiometer** value, scaling it to simulate real-time load current (Amperes).
2. **Display Update:** Live metrics are updated dynamically on the I2C LCD screen.
3. **Logic Evaluation:** The microcontroller evaluates the system state based on the following safety boundaries:

### ⚠️ Condition Thresholds
* **Temperature Limit:** 50 deg Celcius
* **Current Limit:**  5A

* +-----------------------+
              |  Read Sensors (ESP32) |
              +-----------+-----------+
                          |
          +---------------+---------------+
          |                               |
 [Temp >= 50°C OR Current >= 5A]       [Else]
          |                               |
          v                               v
+-------------------+           +-------------------+
|    FAULT MODE     |           |     SAFE MODE     |
+-------------------+           +-------------------+
| • Green LED: OFF  |           | • Green LED: ON   |
| • Red LED: ON     |           | • Red LED: OFF    |
| • Buzzer: ON      |           | • Buzzer: OFF     |
| • Relay: ON (Trip)|           | • Relay: OFF      |
| • LCD: "FAULT"    |           | • LCD: "SAFE"     |
+-------------------+           +-------------------+

  ## 💻 Software & Tools Used
* **Arduino IDE:** For writing, compiling, and flashing the C++ firmware.
* **Wokwi Simulator:** Used for rapid prototyping and virtual hardware testing.
* **GitHub:** For version control and documentation tracking.

---

## 🚀 Future Scope
* 🌐 **IoT Cloud Integration:** Connecting to platforms like Blynk, AWS IoT, or ThingsBoard for remote monitoring and telemetry dashboards.
* 📲 **GSM Alert System:** Integrating a SIM800L module to send instantaneous SMS alerts to grid operators during a trip event.
* 📊 **Edge AI & Predictive Maintenance:** Implementation of machine learning models to analyze thermal and load trends to predict transformer degradation before a failure occurs.
* 💾 **Local Data Logging:** Utilizing an SD card module or flash memory to log historic parameters for incident analysis.

---

## 👩‍💻 Author
Harika 
 B.Tech Student(23UEE137)
Department of Electrical Engineering  
National Institute of Technology Agartala

## 🚀 Live Simulation
You can run and test this project directly in your browser here: [Launch Wokwi Simulation](https://wokwi.com/projects/468509449705909249)
