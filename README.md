
# Smart Listener: Ambient Sound Classifier using MQTT

## 🧠 Project Overview
The **Smart Listener** is a machine learning-based system that classifies ambient sounds in a home environment. Using the **Infineon PSoC™ 6 AI Evaluation Kit**, this system can detect different sounds like appliance beeps (microwave, fridge), emergency alarms (fire, glass break), and human speech. Once detected, it sends the classification results to a web server via MQTT for further actions or visualization.

## 🔧 Features
- **Sound Detection**: Detects the following sound classes:
  - **Appliance Sounds**: `microwave_beep`, `fridge_door_open`
  - **Emergency Sounds**: `glass_break`, `fire_smoke_alarm`
  - **Background Sounds**: `human_speech`
- **Edge Machine Learning**: Run inference directly on the PSoC™ 6 AI Evaluation Kit using the **DEEPCRAFT Studio** tool.
- **MQTT Communication**: Publish detection results to an MQTT broker (e.g., HiveMQ, Mosquitto) for integration with web applications or IoT systems.

## 🛠️ Requirements
### Hardware
- **Infineon PSoC™ 6 AI Evaluation Kit (CY8CKIT-062S2-AI)**
- **Microphone** for sound input (connected to the PSoC)

### Software
- **ModusToolbox IDE**: For firmware development and deployment.
- **DEEPCRAFT Studio**: For designing and training ML models.
- **MQTT Broker**: You can use a public broker like **HiveMQ Cloud** or host your own with **Mosquitto**.

## 🚀 Setup Instructions

### 1. **Clone the Repository**
Start by cloning this repository:
```bash
git clone https://github.com/Bedair/smart-listener.git
cd smart-listener
```

### 2. **ModusToolbox Setup**
- Download and install **ModusToolbox IDE** if you don’t have it already: [ModusToolbox Download](https://www.infineon.com/cms/en/design-support/software/modustoolbox/).
- Open the `smart-listener` project in ModusToolbox.
- Build and deploy the project to your **PSoC™ 6 AI Evaluation Kit**.

### 3. **Setting Up MQTT**
- Choose an MQTT broker to receive the messages:
  - **Cloud Broker**: [HiveMQ Cloud](https://www.hivemq.com/mqtt-cloud-broker/) (easy setup, no installation needed).
  - **Local Broker**: Install **Mosquitto** on your local machine (Linux/macOS):
    ```bash
    sudo apt-get install mosquitto mosquitto-clients
    mosquitto
    ```
- Configure the **MQTT broker settings** in the `mqtt_config.h` file of the project:
```c
#define MQTT_BROKER "mqtt.hivemq.com"
#define MQTT_PORT 1883
#define MQTT_TOPIC "home/audio/detection"
```

### 4. **Deploy ML Model**
- Train your **ML model** using **DEEPCRAFT Studio** and export the model.
- Import the trained model into the ModusToolbox project.
- Use the model to classify incoming audio from the microphone.

### 5. **Connect to Wi-Fi**
- Edit the **Wi-Fi configuration** to connect your board to your local Wi-Fi network:
```c
#define WIFI_SSID "Your_SSID"
#define WIFI_PASSWORD "Your_Password"
```

### 6. **Build and Run**
- Build the project and load it onto your **PSoC™ 6 AI Evaluation Kit** using ModusToolbox IDE.
- Once the device is running, it will begin detecting sounds and sending MQTT messages to the specified broker.

## 📡 MQTT Output Example
Once a sound is detected (e.g., `fire_smoke_alarm`), the device will publish a message in the following format to the MQTT broker:
```json
{
  "event": "fire_smoke_alarm",
  "confidence": 0.92,
  "timestamp": "2025-04-22T14:10:05Z"
}
```

You can subscribe to the topic using any MQTT client to view the results.

### MQTT Client Example:
```bash
mosquitto_sub -h mqtt.hivemq.com -t "home/audio/detection"
```

---

## 🖥️ Frontend (Optional)
You can create a simple web dashboard to visualize the incoming MQTT messages using **Node.js**, **React**, or **Home Assistant**.

---

## 🤝 Contributing
Feel free to fork this repository, submit issues, and contribute improvements. Pull requests are welcome!

## 📄 License
This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.

---

## 🧑‍💻 Acknowledgments
- **Infineon** for the PSoC™ 6 AI Evaluation Kit.
- **ModusToolbox** for the development environment.
- **DEEPCRAFT Studio** for easy deployment of ML models to edge devices.
