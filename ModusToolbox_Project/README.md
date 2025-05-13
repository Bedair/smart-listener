
# SmartListener – Sound Classification with PSoC6 AI Kit

**SmartListener** is a FreeRTOS-based application for the PSoC6 AI Kit that captures audio input using the onboard microphone, runs inference using an Edge ML model, and publishes classified sound events over MQTT with debouncing logic.

---

## 📦 Features

- 🎤 Real-time sound sampling via PDM microphone
- 🧠 Edge ML inference (e.g., baby crying, dog barking)
- ✅ Debounced classification output
- 📡 MQTT publishing of confirmed sound events
- 🔁 FreeRTOS-based architecture

---

## 🚀 Hardware Requirements

- [PSoC™ 6 AI Kit](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-ai/)
- USB cable for programming and power
- Wi-Fi access point with Internet connectivity

---

## 🧰 Software Requirements

- [ModusToolbox™](https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software-environment/) 3.x
- Git (for cloning)
- MQTT broker (e.g., [HiveMQ](https://broker.hivemq.com))

---

## 🔧 Setup Instructions

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/SmartListener_ModusToolbox.git
   cd SmartListener_ModusToolbox
   ```

2. **Open in ModusToolbox:**

   - Launch ModusToolbox IDE
   - Choose "Open Application" and select the cloned folder

3. **Set Wi-Fi Credentials:**

   Edit `wifi_config.h`:
   ```c
   #define WIFI_SSID     "YourSSID"
   #define WIFI_PASSWORD "YourPassword"
   ```

4. **Set MQTT Broker Info:**

   Edit `mqtt_config.h` or relevant header:
   ```c
   #define MQTT_BROKER_ADDRESS "broker.hivemq.com"
   #define MQTT_PORT           1883
   #define MQTT_TOPIC          "SmartListener"
   ```

5. **Build and Program:**

   - Click **"Build"** then **"Program"** in ModusToolbox

6. **Monitor Output:**

   - Use the integrated serial terminal or `mosquitto_sub`:
     ```bash
     mosquitto_sub -h broker.hivemq.com -t SmartListener -v
     ```

---

## 📊 Output Format

Published MQTT messages (JSON format):
```json
{"event": "baby_crying"}
```

---

## 🔁 Debouncing Logic

To avoid false positives:
- Labels like `"baby_crying"` are only confirmed after **3 consecutive detections**
- `"unlabeled"` and `"unknown"` labels are **ignored** for MQTT publishing

---

## 📡 MQTT Compatibility

Tested with:

- `broker.hivemq.com` (no TLS)
- `test.mosquitto.org`
- Local Mosquitto broker
- Node-RED & Home Assistant (via MQTT integration)

---


## 🧠 Future Enhancements

- Add TLS support for secure MQTT
- Push notifications via Telegram or email
- Node-RED dashboard for real-time visualization

---

## 📜 License

MIT License

---

## 👤 Author

- **Mohamed Bedair** – [GitHub](https://github.com/Bedair)
