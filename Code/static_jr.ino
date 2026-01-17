/*
 * PROJECT: Static JR.
 * HARDWARE: ESP32-C3 SuperMini | RDA5807M | SSD1306 | Standard RGB LED
 * PINS: LED (4,5,6), Pots (1,2), Sleep (7), Pomodoro (3)
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <radio.h>
#include <RDA5807M.h>

// I2C signals
#define I2C_SDA 9
#define I2C_SCL 8

// Potentiometer control
#define POT_VOL  1
#define POT_TUNE 2

// Function buttons
#define BTN_SLEEP 7
#define BTN_POMO  3

// RGB LED
#define PIN_RED   6
#define PIN_GREEN 5
#define PIN_BLUE  4

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
RDA5807M radio;

int currentFreq = 0;
int currentVol  = 0;

// Pomodoro variables
bool pomoActive = false;
unsigned long pomoEndTime = 0;

// Sleep variables
bool sleepActive = false;
unsigned long sleepShutoffTime = 0;

void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);

  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  pinMode(BTN_POMO, INPUT_PULLUP);
  pinMode(BTN_SLEEP, INPUT_PULLUP);

  if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(25, 25);
    display.println("Static Jr. READY");
    display.display();
  }

  // Sets initia settings
  radio.init();
  radio.setBandFrequency(RADIO_BAND_FM, 10330);
  radio.setVolume(5);

  currentFreq = 10330;
  currentVol  = 5;

  // Allows the sleep timer button to wake the device from deep sleep
  esp_deep_sleep_enable_gpio_wakeup(1ULL << BTN_SLEEP, ESP_GPIO_WAKEUP_GPIO_LOW);
}

void loop() {

  // Reading and Changing volume
  int rawVol = analogRead(POT_VOL);
  int mappedVol = map(rawVol, 0, 4095, 0, 15);

  if (mappedVol != currentVol) {
    currentVol = mappedVol;
    if (!pomoActive) {
      radio.setVolume(currentVol);
    }
    visualClick(); // LED feedback
  }

  // Reading and Changing Frequency
  int rawTune = analogRead(POT_TUNE);
  int mappedFreq = map(rawTune, 0, 4095, 8700, 10800);

  if (abs(mappedFreq - currentFreq) > 10) {
    currentFreq = mappedFreq;
    radio.setFrequency(currentFreq);
    visualClick(); // LED feedback
  }

  // Podomoro
  if (digitalRead(BTN_POMO) == LOW) {
    delay(200);

    pomoActive = !pomoActive;
    if (pomoActive) {
      pomoEndTime = millis() + (25UL * 60000UL); // Set 25 min timer
      radio.setMute(true); // mutes radio
    } else {
      radio.setMute(false);
      radio.setVolume(currentVol);
    }
  }

  // sleeep mode
  if (digitalRead(BTN_SLEEP) == LOW) {
    delay(200); // Debounce

    if (!sleepActive) {
      sleepActive = true;
      sleepShutoffTime = millis() + (30UL * 60000UL); // Set 30 min timer
    } else {
      sleepActive = false;
    }
  }

  // Automation-
  if (pomoActive && millis() > pomoEndTime) {
    pomoActive = false;
    radio.setMute(false);
    radio.setVolume(currentVol);
    alarmEffect(); // Flash Green when focus time is over
  }

  if (sleepActive && millis() > sleepShutoffTime) {
    radio.term();
    display.clearDisplay();
    display.display();
    esp_deep_sleep_start(); // Hibernate
  }

  updateUI();
  delay(50);
}

// Visual "Click" for tactile feel
void visualClick() {
  setColor(255, 255, 255); // Flash White
  delay(10);
  setColor(0, 0, 0);
}

// Alarm for the end of a Pomodoro session
void alarmEffect() {
  for (int i = 0; i < 3; i++) {
    setColor(0, 255, 0); delay(200);
    setColor(0, 0, 0);   delay(200);
  }
}

void setColor(int r, int g, int b) {
  analogWrite(PIN_RED, r);
  analogWrite(PIN_GREEN, g);
  analogWrite(PIN_BLUE, b);
}

void updateUI() {

  // LED Status Indicator
  if (pomoActive) {
    int pulse = (millis() / 20) % 255;
    int glow = (pulse > 127 ? 255 - pulse : pulse) * 2;
    setColor(glow, 0, 0); // Glowing Red
  }
  else if (sleepActive) {
    setColor(20, 0, 40); // Dim Purple
  }
  else {
    setColor(0, 40, 40); // Cyan Radio Mode
  }

  display.clearDisplay();

  //System Stats
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("RSSI: ");
  display.print(radio.getRssi());

  if (sleepActive) {
    long minsLeft = (sleepShutoffTime - millis()) / 60000;
    display.setCursor(80, 0);
    display.print("Zz ");
    display.print(minsLeft);
    display.print("m");
  }

  // Basic settings
  if (pomoActive) {
    display.setCursor(20, 30);
    display.setTextSize(3);

    long remaining = (pomoEndTime - millis()) / 1000;
    display.print(remaining / 60);
    display.print(":");
    if ((remaining % 60) < 10) display.print("0");
    display.print(remaining % 60);
  }
  else {
    display.setTextSize(3);
    display.setCursor(10, 25);

    display.print(currentFreq / 100);
    display.print(".");
    display.print((currentFreq % 100) / 10);

    display.setTextSize(1);
    display.print(" MHz");

    // Volume Bar
    display.drawRect(0, 58, 128, 6, WHITE);
    int barWidth = map(currentVol, 0, 15, 0, 124);
    display.fillRect(2, 60, barWidth, 2, WHITE);
  }

  display.display();
}
