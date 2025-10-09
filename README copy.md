# PathPal: A Human Following Robot Using Sensors

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Status](https://img.shields.io/badge/Status-Active-success?style=for-the-badge)

A safety-focused Arduino-powered robot that follows people (especially children and elderly) while detecting environmental hazards like smoke, gas, and dangerous edges.

##  Team Members

- **Bharath G** - CB.SC.U4CSE24005
- **Dhanusri AP** - CB.SC.U4CSE24011
- **Kesikasri S** - CB.SC.U4CSE24023
- **Vishal Teja** - CB.SC.U4CSE24052

##  Project Overview

PathPal is an intelligent robot designed to enhance the safety of children and elderly individuals by:
- **Following users** using ultrasonic sensors while maintaining a safe distance
- **Detecting smoke and harmful gases** (LPG, Methane) using MQ-2 sensor
- **Preventing falls** by detecting edges, stairs, and ledges with IR sensors
- **Alerting users** through buzzer and LED indicators when dangers are detected

The robot acts as a mobile guardian, providing real-time hazard detection and alerts to prevent accidents and ensure user safety.

##  Hardware Components

| Component | Description |
|-----------|-------------|
| Arduino Uno | Main microcontroller board |
| HC-SR04 Ultrasonic Sensor | Distance measurement and human following |
| IR Sensors (x2) | Direction tracking and edge detection |
| MQ-2 Smoke/Gas Sensor | Detects smoke and harmful gases |
| L298N Motor Driver (AFMotor Shield) | Controls DC motors |
| DC Motors with Wheels (x4) | Robot movement |
| Servo Motor | Sensor scanning (optional) |
| Buzzer | Audible alerts |
| Red LED | Visual warnings |
| 7.4V/12V Battery Pack | Power supply |
| Chassis | Robot body frame |
| Jumper Wires & Breadboard | Connections |

##  Software Requirements

- **Arduino IDE** - Code development and upload
- **TinkerCAD Circuits** - Circuit simulation
- **CH340/CP210x Driver** - USB-to-serial communication

### Required Arduino Libraries

```cpp
#include <NewPing.h>      // Ultrasonic sensor
#include <Servo.h>        // Servo motor control
#include <AFMotor.h>      // Motor driver shield
```

Install these libraries through Arduino IDE Library Manager.

##  Pin Configuration

### Sensors
- **Ultrasonic Sensor**
  - Trigger Pin: A1
  - Echo Pin: A0
- **IR Sensors**
  - Right IR: A3
  - Left IR: A2
- **MQ-2 Gas/Smoke Sensor**: A5
- **Buzzer**: A4
- **Servo Motor**: Pin 10

### Motors
- Motor 1 & 2: MOTOR12_1KHZ
- Motor 3 & 4: MOTOR34_1KHZ

##  Getting Started

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/pathpal-robot.git
   cd pathpal-robot
   ```

2. **Install Arduino IDE**
   - Download from [arduino.cc](https://www.arduino.cc/en/software)

3. **Install Required Libraries**
   - Open Arduino IDE
   - Go to Sketch → Include Library → Manage Libraries
   - Search and install: `NewPing`, `Servo`, `AFMotor`

4. **Connect Arduino Uno**
   - Connect via USB cable
   - Select correct board: Tools → Board → Arduino Uno
   - Select correct port: Tools → Port → (your Arduino port)

5. **Upload Code**
   - Open `human_following_robot.ino`
   - Click Upload button (→)

### Initial Setup

1. **MQ-2 Sensor Warmup**
   - The sensor requires 20 seconds to warm up for accurate readings
   - The robot will automatically count down during startup
   - Wait for "✅ MQ-2 Ready! Robot Active" message

2. **Calibration**
   - Adjust motor speeds in code if needed (default: 130-150)
   - Test IR sensor sensitivity for edge detection
   - Verify ultrasonic sensor range (1-15 cm following distance)

##  How It Works

### Human Following Mode
- **Distance < 15 cm**: Robot moves forward to follow
- **Right IR triggered**: Robot turns right
- **Left IR triggered**: Robot turns left
- **Distance > 15 cm**: Robot stops (target lost)

### Safety Features

#### Gas/Smoke Detection
- **MQ-2 Value ≥ 100**: 🚨 Smoke detected → Stop & Alert
- **MQ-2 Value ≥ 70**: ⚠️ Gas detected → Stop & Alert
- **MQ-2 Value < 70**: ✅ Normal operation

#### Edge Detection
- IR sensors detect absence of surface
- Robot stops immediately
- Prevents falls from stairs, ledges, table edges

#### Alert System
- **Buzzer**: Audible warning
- **LED**: Visual indicator
- **Serial Monitor**: Real-time sensor data

##  Sensor Readings

Open Serial Monitor (9600 baud) to view real-time data:
```
Distance: 12 cm | RIGHT: 0 | LEFT: 1 | MQ2: 45 (Normal)
🚗 Following target
```

##  Applications

1. **Elderly Care**: Assists seniors by detecting gas leaks and fall hazards
2. **Child Safety**: Monitors children and identifies smoke/dangerous areas
3. **Home Automation**: Mobile safety patrol for smart homes
4. **Disaster Response**: Can be extended for search and rescue operations

##  Expected Outcomes

- ✔️ Successful human following with maintained safe distance
- ✔️ Accurate edge detection preventing falls
- ✔️ Reliable smoke/gas detection with immediate alerts
- ✔️ Synchronized buzzer and LED warnings
- ✔️ Stable operation as an intelligent safety assistant

##  Future Enhancements

- [ ] Add Bluetooth/WiFi control for remote monitoring
- [ ] Implement voice alerts
- [ ] Add camera for visual monitoring
- [ ] Integrate GPS for outdoor navigation
- [ ] Machine learning for improved obstacle avoidance
- [ ] Battery level monitoring and auto-recharge
- [ ] Mobile app integration

##  Troubleshooting

| Issue | Solution |
|-------|----------|
| Robot not moving | Check motor connections and battery voltage |
| Ultrasonic sensor not reading | Verify trigger/echo pin connections |
| MQ-2 false alarms | Allow proper warmup time (20 seconds) |
| IR sensors not working | Check sensor orientation and wiring |
| Upload errors | Install CH340 driver, check board selection |

##  Project Structure

```
pathpal-robot/
├── human_following_robot.ino    # Main Arduino code
├── README.md                     # Project documentation
├── docs/
│   └── C Project[1].pdf         # Detailed project report
└── LICENSE                       # Project license
```

##  License

This project is licensed under the MIT License - see the LICENSE file for details.

##  Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the project
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

##  Contact

For questions or feedback, please reach out to the team members listed above.

##  Acknowledgments

- Arduino Community for libraries and support
- Our institution for providing resources
- All contributors and testers

---

**⭐ If you find this project useful, please consider giving it a star!**
