#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int flexPins[5] = {A0, A1, A2, A3, A4};
float ema[5];
int base[5];
int margin[5];
const float alpha = 0.4;
const int FIXED_MARGIN = 5;
const float NOISE_K = 1.0;
char stableLetter = '-';
char prevLetter = '-';
int sameCount = 0;
const int stableLimit = 2;
String sentence = ""; // store letters
int median3(int a, int b, int c) {
  if ((a >= b && a <= c) || (a <= b && a >= c)) return a;
if ((b >= a && b <= c) || (b <= a && b >= c)) return b;
return c;
}
float getNoise(int pin) {
int samples = 20;
float sum = 0;
int vals[20];
for (int i = 0; i < samples; i++) {
vals[i] = analogRead(pin);
sum += vals[i];
delay(5);
}
float mean = sum / samples;
float sq = 0;
for (int i = 0; i < samples; i++) sq += pow(vals[i] - mean, 2);
return sqrt(sq / samples);
}
char mapToLetter(bool f1, bool f2, bool f3, bool f4, bool f5) {
if (f1 && !f2 && !f3 && !f4 && !f5) return 'A';
if (!f1 && f2 && !f3 && !f4 && !f5) return 'B';
if (f1 && f2 && !f3 && !f4 && !f5) return 'C';
if (!f1 && !f2 && f3 && !f4 && !f5) return 'D';
if (f1 && !f2 && f3 && !f4 && !f5) return 'E';
if (!f1 && f2 && f3 && !f4 && !f5) return 'F';
if (f1 && f2 && f3 && !f4 && !f5) return 'G';
if (!f1 && !f2 && !f3 && f4 && !f5) return 'H';
if (f1 && !f2 && !f3 && f4 && !f5) return 'I';
if (!f1 && f2 && !f3 && f4 && !f5) return 'J';
if (f1 && f2 && !f3 && f4 && !f5) return 'K';
if (!f1 && !f2 && f3 && f4 && !f5) return 'L';
if (f1 && !f2 && f3 && f4 && !f5) return 'M';
if (!f1 && f2 && f3 && f4 && !f5) return 'N';
if (f1 && f2 && f3 && f4 && !f5) return 'O';
if (!f1 && !f2 && !f3 && !f4 && f5) return 'P';
if (f1 && !f2 && !f3 && !f4 && f5) return 'Q';
if (!f1 && f2 && !f3 && !f4 && f5) return 'R';
if (f1 && f2 && !f3 && !f4 && f5) return 'S';
if (!f1 && !f2 && f3 && !f4 && f5) return 'T';
if (f1 && !f2 && f3 && !f4 && f5) return 'U';
if (!f1 && f2 && f3 && !f4 && f5) return 'V';
if (f1 && f2 && f3 && !f4 && f5) return 'W';
if (!f1 && !f2 && !f3 && f4 && f5) return 'X';
if (f1 && !f2 && !f3 && f4 && f5) return 'Y';
if (!f1 && f2 && !f3 && f4 && f5) return 'Z';
return '-';
}
void setup() {
Serial.begin(9600);
lcd.begin(16, 2);
lcd.print("Calibrating...");
delay(2000);
for (int i = 0; i < 5; i++) {
base[i] = analogRead(flexPins[i]);
margin[i] = FIXED_MARGIN + getNoise(flexPins[i]) * NOISE_K;
ema[i] = base[i];
}
lcd.clear();
lcd.print("Ready!");
delay(1000);
lcd.clear();
}
void loop() {
bool bent[5];
String binaryStr = "";
for (int i = 0; i < 5; i++) {
int val = median3(analogRead(flexPins[i]), analogRead(flexPins[i]), analogRead(flexPins[i]));
ema[i] = alpha * val + (1 - alpha) * ema[i];
bent[i] = abs(ema[i] - base[i]) > margin[i];

// build 0/1 string for Serial Monitor
binaryStr += bent[i] ? "1" : "0";
}
// Print raw binary states
Serial.println(binaryStr);
// Detect letter
char detectedLetter = mapToLetter(bent[0], bent[1], bent[2], bent[3], bent[4]);
// Debounce
if (detectedLetter == prevLetter) {
sameCount++;
if (sameCount >= stableLimit && detectedLetter != stableLetter && detectedLetter != '-') {
stableLetter = detectedLetter;
sentence += stableLetter;
if (sentence.length() > 32) sentence.remove(0, 1); // keep last 32 chars
}
} else {
sameCount = 1;
prevLetter = detectedLetter;
}
// Display on LCD: current letter + sentence
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Letter: ");
lcd.print(stableLetter);
lcd.setCursor(0, 1);
lcd.print(sentence);
delay(100);
}