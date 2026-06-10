🖐️ Smart Glove: Translating Gestures into Text

A wearable assistive technology device that converts hand gestures into readable text in real time — bridging the communication gap for deaf and mute individuals.

📌 Overview
The Smart Glove is a low-cost, portable, wearable system that detects finger bending patterns using flex sensors and translates them into alphabet letters displayed on a 16×2 LCD screen. Each unique combination of bent and straight fingers forms a 5-bit binary code that maps to a specific letter (A–Z), enabling real-time gesture-to-text communication.
This project was developed as part of the Community Engagement Project (SE, 1st Semester) at Dr. D. Y. Patil Institute of Technology, Pimpri, Pune — Department of Artificial Intelligence and Data Science (2025–2026).

👥 Team
NameRoll NoIshita BhoirSAI&DA02Tanuja NaphadeSAI&DA05Vaibhavi ShindeSAI&DA15Sameer TalekarSAI&DA18
Project Guide: Mrs. Chetana Shravage
HOD AI & DS: Dr. D. R. Dhotre

🎯 Objectives

Develop a wearable glove with flex sensors to detect finger bending and hand gestures
Process analog sensor data using Arduino Uno with noise reduction via signal conditioning
Map gesture combinations to alphabet characters using a binary-coded logic system
Display detected letters on a 16×2 LCD in real time
Build an affordable, portable communication aid for deaf and mute individuals
Reduce dependency on interpreters by enabling direct gesture-based interaction


🔧 Hardware Components
ComponentSpecificationMicrocontrollerArduino Uno R3Flex Sensors5 units, 10kΩ base resistanceDisplay16×2 LCD (LiquidCrystal interface)Resistors10kΩ (voltage divider per sensor)Filtering MethodMedian + EMA filteringPower Supply5V DC via USBCommunicationSerial 9600 bps (testing)Simulation ToolTinkercadProgramming ToolArduino IDE

💻 Software & Tools

Arduino IDE — firmware development
Tinkercad — circuit simulation and validation before physical prototyping
Serial Monitor — real-time debugging of sensor values


⚙️ How It Works
1. Sensing
Five flex sensors (one per finger) detect bending. Each sensor acts as a variable resistor — resistance changes as the finger bends, producing a varying analog voltage read by the Arduino's ADC pins (A0–A4).
2. Signal Conditioning
Raw sensor data passes through three stages:

Median Filtering — takes 3 consecutive samples and selects the median to remove random spikes:

xM=M(x1,x2,x3)x_M = M(x_1, x_2, x_3)xM​=M(x1​,x2​,x3​)

Exponential Moving Average (EMA) — smooths rapid fluctuations while maintaining responsiveness (α = 0.4):

EMAnew=α×Vcurrent+(1−α)×EMApreviousEMA_{new} = \alpha \times V_{current} + (1 - \alpha) \times EMA_{previous}EMAnew​=α×Vcurrent​+(1−α)×EMAprevious​

Dynamic Self-Calibration — at startup, each sensor sets its own baseline. A dynamic threshold accounts for noise:

Margin=Fixed Margin+(Noise×K)Margin = Fixed\ Margin + (Noise \times K)Margin=Fixed Margin+(Noise×K)


3. Binary Mapping
Each finger is assigned a single bit:
FingerLabelBit PositionThumbF1LSB (bit 0)IndexF2bit 1MiddleF3bit 2RingF4bit 3PinkyF5MSB (bit 4)
A bent finger = 1, straight = 0. The 5-bit combination maps to a letter:
Binary CodeLetterBinary CodeLetter00001A10001Q00010B10010R00011C10011S00100D10100T00101E10101U00110F10110V00111G10111W01000H11000X01001I11001Y01010J11010Z01011K......01100L01101M01110N01111O10000P
4. Output

Row 1 of LCD — displays the currently detected letter
Row 2 of LCD — displays the accumulated word/sentence (up to 32 characters)


✅ Key Features

Real-time translation — gesture to letter with ~100ms refresh rate
Dynamic self-calibration — adapts to different users, finger lengths, and sensor placements at every startup
Noise-resistant — triple-stage signal conditioning (Median + EMA + Dynamic Threshold)
Word construction — letters string together to form complete words
Offline & portable — no internet, no camera, no controlled lighting required
Deterministic logic — fully debuggable, no black-box ML model
Low cost — built entirely with basic electronic components
Simulation-first — validated on Tinkercad before physical prototyping


🌍 Applications

Assistive communication for hearing and speech impaired individuals
Educational tools in special schools
Hospital and clinic interactions
Public service counters for accessibility
Future integration into IoT and smart home systems


📁 Repository Structure
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

🚀 How to Run

Clone the repository

bashgit clone https://github.com/Sameer0726152/smart-glove-gesture-to-text.git

Open the code

Open code/smart_glove.ino in Arduino IDE


Connect hardware

Wire flex sensors to analog pins A0–A4 via 10kΩ voltage dividers
Connect 16×2 LCD to digital pins 12, 11, 5, 4, 3, 2
Power via USB


Upload

Select board: Arduino Uno
Select correct COM port
Click Upload


Use

Hold the glove still for 2 seconds during calibration
Bend fingers to form gestures
Read the detected letter on the LCD




⚠️ Limitations

Only supports preprogrammed single letters (A–Z)
Calibration required for different users
Rapid gesture transitions may cause misreads
Does not support dynamic or motion-based gestures
Physical sensor contact must be secure for accurate readings


🔮 Future Scope

Full word and phrase mapping beyond single letters
Speech synthesis module for audio output
Bluetooth / Wi-Fi integration to send text to smartphone
Machine learning for adaptive thresholds and complex gestures
More ergonomic glove design with flexible PCB
IoT integration for controlling smart devices via gestures


📄 License
This project is submitted for academic purposes at Dr. D. Y. Patil Institute of Technology, Pimpri, Pune. All rights reserved by the authors.

🙏 Acknowledgements
We sincerely thank Mrs. Chetana Shravage for her expert guidance, constant support, and encouragement throughout this project. We also thank Dr. D. R. Dhotre (HOD, AI & DS) for his support.

Smart Glove — Making communication inclusive, one gesture at a time. 🤝