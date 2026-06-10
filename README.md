# 🖐️ Smart Glove: Translating Gestures into Text

> A wearable assistive technology device that converts hand gestures into readable text in real time — bridging the communication gap for deaf and mute individuals.

![Project Banner](images/glove_prototype.png)

## 📌 Overview

The **Smart Glove** is a low-cost, portable, wearable system that detects finger bending patterns using flex sensors and translates them into alphabet letters displayed on a 16×2 LCD screen. Each unique combination of bent and straight fingers forms a 5-bit binary code that maps to a specific letter (A–Z), enabling real-time gesture-to-text communication.

This project was developed as part of the **Community Engagement Project (SE, 1st Semester)** at **Dr. D. Y. Patil Institute of Technology, Pimpri, Pune** — Department of Artificial Intelligence and Data Science (2025–2026).

---

## 👥 Team

| Name | Roll No |
|------|---------|
| Ishita Bhoir | SAI&DA02 |
| Tanuja Naphade | SAI&DA05 |
| Vaibhavi Shinde | SAI&DA15 |
| Sameer Talekar | SAI&DA18 |

**Project Guide:** Mrs. Chetana Shravage  
**HOD AI & DS:** Dr. D. R. Dhotre

---

## 🎯 Objectives

- Develop a wearable glove with flex sensors to detect finger bending and hand gestures
- Process analog sensor data using Arduino Uno with noise reduction via signal conditioning
- Map gesture combinations to alphabet characters using a binary-coded logic system
- Display detected letters on a 16×2 LCD in real time
- Build an affordable, portable communication aid for deaf and mute individuals
- Reduce dependency on interpreters by enabling direct gesture-based interaction

---

## 🔧 Hardware Components

| Component | Specification |
|-----------|--------------|
| Microcontroller | Arduino Uno R3 |
| Flex Sensors | 5 units, 10kΩ base resistance |
| Display | 16×2 LCD (LiquidCrystal interface) |
| Resistors | 10kΩ (voltage divider per sensor) |
| Filtering Method | Median + EMA filtering |
| Power Supply | 5V DC via USB |
| Communication | Serial 9600 bps (testing) |
| Simulation Tool | Tinkercad |
| Programming Tool | Arduino IDE |

---

## 💻 Software & Tools

- **Arduino IDE** — firmware development
- **Tinkercad** — circuit simulation and validation before physical prototyping
- **Serial Monitor** — real-time debugging of sensor values

---

## ⚙️ How It Works

### 1. Sensing
Five flex sensors (one per finger) detect bending. Each sensor acts as a variable resistor — resistance changes as the finger bends, producing a varying analog voltage read by the Arduino's ADC pins (A0–A4).

### 2. Signal Conditioning
Raw sensor data passes through three stages:

- **Median Filtering** — takes 3 consecutive samples and selects the median to remove random spikes:
$$x_M = M(x_1, x_2, x_3)$$

- **Exponential Moving Average (EMA)** — smooths rapid fluctuations while maintaining responsiveness (α = 0.4):
$$EMA_{new} = \alpha \times V_{current} + (1 - \alpha) \times EMA_{previous}$$

- **Dynamic Self-Calibration** — at startup, each sensor sets its own baseline. A dynamic threshold accounts for noise:
$$Margin = Fixed\ Margin + (Noise \times K)$$

### 3. Binary Mapping
Each finger is assigned a single bit:

| Finger | Label | Bit Position |
|--------|-------|-------------|
| Thumb | F1 | LSB (bit 0) |
| Index | F2 | bit 1 |
| Middle | F3 | bit 2 |
| Ring | F4 | bit 3 |
| Pinky | F5 | MSB (bit 4) |

A bent finger = `1`, straight = `0`. The 5-bit combination maps to a letter:

| Binary Code | Letter | Binary Code | Letter |
|-------------|--------|-------------|--------|
| 00001 | A | 10001 | Q |
| 00010 | B | 10010 | R |
| 00011 | C | 10011 | S |
| 00100 | D | 10100 | T |
| 00101 | E | 10101 | U |
| 00110 | F | 10110 | V |
| 00111 | G | 10111 | W |
| 01000 | H | 11000 | X |
| 01001 | I | 11001 | Y |
| 01010 | J | 11010 | Z |
| 01011 | K | ... | ... |
| 01100 | L | | |
| 01101 | M | | |
| 01110 | N | | |
| 01111 | O | | |
| 10000 | P | | |

### 4. Output
- **Row 1 of LCD** — displays the currently detected letter
- **Row 2 of LCD** — displays the accumulated word/sentence (up to 32 characters)

---

## ✅ Key Features

- **Real-time translation** — gesture to letter with ~100ms refresh rate
- **Dynamic self-calibration** — adapts to different users, finger lengths, and sensor placements at every startup
- **Noise-resistant** — triple-stage signal conditioning (Median + EMA + Dynamic Threshold)
- **Word construction** — letters string together to form complete words
- **Offline & portable** — no internet, no camera, no controlled lighting required
- **Deterministic logic** — fully debuggable, no black-box ML model
- **Low cost** — built entirely with basic electronic components
- **Simulation-first** — validated on Tinkercad before physical prototyping

---

## 🌍 Applications

- Assistive communication for hearing and speech impaired individuals
- Educational tools in special schools
- Hospital and clinic interactions
- Public service counters for accessibility
- Future integration into IoT and smart home systems

---

## 📁 Repository Structure

```
smart-glove-gesture-to-text/
│
├── code/
│   └── smart_glove.ino          # Arduino firmware
│
├── docs/
│   ├── project_report.pdf       # Full project report
│   └── ieee_paper.pdf           # IEEE conference paper
│
├── images/
│   ├── glove_prototype.jpg      # Final glove prototype
│   ├── tinkercad_circuit.png    # Circuit simulation
│   ├── block_diagram.png        # System block diagram
│   ├── lcd_yes.jpg              # LCD displaying YES
│   ├── lcd_help.jpg             # LCD displaying HELP
│   └── breadboard_testing.jpg  # Initial breadboard setup
│
└── README.md
```

---

## 🚀 How to Run

1. **Clone the repository**
```bash
git clone https://github.com/Sameer0726152/smart-glove-gesture-to-text.git
```

2. **Open the code**
   - Open `code/smart_glove.ino` in Arduino IDE

3. **Connect hardware**
   - Wire flex sensors to analog pins A0–A4 via 10kΩ voltage dividers
   - Connect 16×2 LCD to digital pins 12, 11, 5, 4, 3, 2
   - Power via USB

4. **Upload**
   - Select board: **Arduino Uno**
   - Select correct COM port
   - Click **Upload**

5. **Use**
   - Hold the glove still for 2 seconds during calibration
   - Bend fingers to form gestures
   - Read the detected letter on the LCD

---

## ⚠️ Limitations

- Only supports preprogrammed single letters (A–Z)
- Calibration required for different users
- Rapid gesture transitions may cause misreads
- Does not support dynamic or motion-based gestures
- Physical sensor contact must be secure for accurate readings

---

## 🔮 Future Scope

- Full word and phrase mapping beyond single letters	
- Speech synthesis module for audio output
- Bluetooth / Wi-Fi integration to send text to smartphone
- Machine learning for adaptive thresholds and complex gestures
- More ergonomic glove design with flexible PCB
- IoT integration for controlling smart devices via gestures

---

## 📄 License

This project is submitted for academic purposes at Dr. D. Y. Patil Institute of Technology, Pimpri, Pune. All rights reserved by the authors.

---

## 🙏 Acknowledgements

We sincerely thank **Mrs. Chetana Shravage** for her expert guidance, constant support, and encouragement throughout this project. We also thank **Dr. D. R. Dhotre** (HOD, AI & DS) for his support.

---

*Smart Glove — Making communication inclusive, one gesture at a time. 🤝*
