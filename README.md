
# Smart Listener: Ambient Sound Classifier using MQTT

## 🧠 Project Overview
The **Smart Listener** is a machine learning-based system that classifies ambient sounds in a home environment. Using the **Infineon PSoC™ 6 AI Evaluation Kit**, this system can detect different sounds like appliance beeps (microwave, fridge), emergency alarms (fire, glass break), and human speech. Once detected, it sends the classification results to a web server via MQTT for further actions or visualization.


This repository serves as the **parent project**, linking together the 3 major components of the system.

---

## ✨ Features

- Real-time sound detection and classification
- Edge ML inference using DeepCraft Studio models
- Debounced output filtering to reduce false positives
- MQTT communication to send classified events to the cloud
- Compatible with Node-RED or MQTT dashboards
- 3D-printable enclosure for deployment and testing

---

## 📋 Requirements

### 🔧 Hardware

- [PSoC™ 6 AI Kit](https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-ai/)
- USB cable (for power and programming)
- Wi-Fi access point
- Optional: 3D printer for enclosure

### 🧰 Software

- [ModusToolbox™ 3.x](https://www.infineon.com/modustoolbox)
- DeepCraft Studio (for ML model training/export)
- FreeCAD (for editing the 3D enclosure)
- MQTT broker (e.g., [HiveMQ](https://broker.hivemq.com))
- `mosquitto_sub` (for testing MQTT messages)

---

## 🧩 Project Components

### 1. 🔧 ModusToolbox Project (Firmware)
- **Location:** [`ModusToolbox_Project/`](./ModusToolbox_Project/)
- Embedded firmware that:
  - Captures microphone input via PDM
  - Performs inference using a pre-trained model
  - Debounces and publishes events via MQTT

📄 See the [ModusToolbox README](./ModusToolbox_Project/README.md) for detailed firmware instructions.

---

### 2. 🧠 DeepCraft Studio Project (ML Model)
- **Location:** [`ML_Model/`](./ML_Model/)
- Project used to create and train the sound classification model
- Exported model is integrated directly into the firmware

---

### 3. 🧱 FreeCAD Project (3D Enclosure)
- **Location:** [`Enclosure/`](./Enclosure/)
- STL and FreeCAD source files to print a custom case for the PSoC6 AI Kit
- Designed for acoustic access, USB connectivity, and wall-mounting

---

## 🛠️ Setup Instructions

### 1. Flash the Firmware
- Open `ModusToolbox_Project/` in ModusToolbox IDE
- Update Wi-Fi and MQTT settings
- Build and program the device

### 2. Train or Replace the Model *(optional)*
- Open `ML_Model/` in DeepCraft Studio
- Train and export the updated model
- Replace the generated files in the firmware

### 3. Print the Enclosure *(optional)*
- Open `Enclosure/` in FreeCAD
- Export STL and print using a 3D printer

### 4. Monitor MQTT Messages
```bash
mosquitto_sub -h broker.hivemq.com -t SmartListener -v
```

---

## 🌐 Example Output

```json
{"event": "baby_crying"}
```

---

## 📜 License

MIT License

---

## 👤 Author

- **Mohamed Bedair** – [GitHub](https://github.com/Bedair)

---

## 💡 Future Directions

- Secure MQTT with TLS and authentication
- Mobile app integration via push notifications
- Low-power optimizations

