import os
import build_env

def generate():
    # Build config.js from .env and environment variables
    try:
        build_env.build()
    except Exception as e:
        print(f"Warning: Could not build config.js: {e}")

    # Read index.html or SmartHomeApps.html
    html_path = "index.html" if os.path.exists("index.html") else "SmartHomeApps.html"
    if not os.path.exists(html_path):
        print(f"Error: {html_path} not found.")
        return

    with open(html_path, "r", encoding="utf-8") as f:
        html = f.read()

    # Extract existing WiFi credentials from SmartHome_ESP32.ino if it exists
    existing_ssid = "Wokwi-GUEST"
    existing_password = ""
    ino_path = "SmartHome_ESP32.ino"
    if os.path.exists(ino_path):
        with open(ino_path, "r", encoding="utf-8") as f:
            content = f.read()
            import re
            ssid_match = re.search(r'const\s+char\s*\*\s*ssid\s*=\s*"([^"]*)"', content)
            pass_match = re.search(r'const\s+char\s*\*\s*password\s*=\s*"([^"]*)"', content)
            if ssid_match:
                existing_ssid = ssid_match.group(1)
            if pass_match:
                existing_password = pass_match.group(1)

    # Perform C++ raw string insertions for check boxes using simple tag IDs
    html = html.replace(
        '<input type="checkbox" id="greenCheckbox" onchange="toggleStatus(this)">',
        '<input type="checkbox" id="greenCheckbox" )raw-html" + greenChecked + R"raw-html( onchange="toggleStatus(this)">'
    )
    html = html.replace(
        '<input type="checkbox" id="redCheckbox" onchange="toggleStatus(this)">',
        '<input type="checkbox" id="redCheckbox" )raw-html" + ledChecked + R"raw-html( onchange="toggleStatus(this)">'
    )
    html = html.replace(
        '<input type="checkbox" id="yellowCheckbox" onchange="toggleStatus(this)">',
        '<input type="checkbox" id="yellowCheckbox" )raw-html" + yellowChecked + R"raw-html( onchange="toggleStatus(this)">'
    )
    html = html.replace(
        '<input type="checkbox" id="blueCheckbox" onchange="toggleStatus(this)">',
        '<input type="checkbox" id="blueCheckbox" )raw-html" + blueChecked + R"raw-html( onchange="toggleStatus(this)">'
    )
    html = html.replace(
        '<input type="checkbox" id="orangeCheckbox" onchange="toggleStatus(this)">',
        '<input type="checkbox" id="orangeCheckbox" )raw-html" + alarmChecked + R"raw-html( onchange="toggleStatus(this)">'
    )

    # Modal device inputs
    html = html.replace(
        '<input type="checkbox" id="modalLampuUtama" onchange="toggleModalDevice(\'lampu-utama\', this)">',
        '<input type="checkbox" id="modalLampuUtama" )raw-html" + greenChecked + R"raw-html( onchange="toggleModalDevice(\'lampu-utama\', this)">'
    )
    html = html.replace(
        '<input type="checkbox" id="modalLampuTidur" onchange="toggleModalDevice(\'lampu-tidur\', this)">',
        '<input type="checkbox" id="modalLampuTidur" )raw-html" + tidurChecked + R"raw-html( onchange="toggleModalDevice(\'lampu-tidur\', this)">'
    )
    html = html.replace(
        '<input type="checkbox" id="modalACKamar" onchange="toggleModalDevice(\'ac-kamar\', this)">',
        '<input type="checkbox" id="modalACKamar" )raw-html" + acChecked + R"raw-html( onchange="toggleModalDevice(\'ac-kamar\', this)">'
    )

    # Generate full C++ code
    cpp_code = """#include <LiquidCrystal_I2C.h>
#include <WebServer.h>
#include <WiFi.h>
#include <Wire.h>

const char *ssid = "Wokwi-GUEST";
const char *password = "";

WebServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ledPin = 2;
const int ledGreenPin = 4;
const int ledBluePin = 5;
const int ledYellowPin = 18;
const int alarmPin = 19;

// New Bedroom Sub-devices Pins
const int ledKamarTidurPin = 12;
const int acKamarPin = 13;

const int AVAILABLE_PINS[] = {2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33};
const int NUM_PINS = sizeof(AVAILABLE_PINS) / sizeof(AVAILABLE_PINS[0]);

String getHTML() {
  bool isLedOn = (digitalRead(ledPin) == HIGH);
  String ledChecked = isLedOn ? "checked" : "";

  bool isGreenOn = (digitalRead(ledGreenPin) == HIGH);
  String greenChecked = isGreenOn ? "checked" : "";

  bool isBlueOn = (digitalRead(ledBluePin) == HIGH);
  String blueChecked = isBlueOn ? "checked" : "";

  bool isYellowOn = (digitalRead(ledYellowPin) == HIGH);
  String yellowChecked = isYellowOn ? "checked" : "";

  bool isAlarmOn = (digitalRead(alarmPin) == HIGH);
  String alarmChecked = isAlarmOn ? "checked" : "";

  bool isTidurOn = (digitalRead(ledKamarTidurPin) == HIGH);
  String tidurChecked = isTidurOn ? "checked" : "";

  bool isAcOn = (digitalRead(acKamarPin) == HIGH);
  String acChecked = isAcOn ? "checked" : "";

  String html = "";
  html += R"raw-html(""" + html + """)raw-html";

  return html;
}

void handleRoot() { server.send(200, "text/html", getHTML()); }
void handleLEDOn() {
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "ON");
}
void handleLEDOff() {
  digitalWrite(ledPin, LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OFF");
}
void handleLEDGreenOn() {
  digitalWrite(ledGreenPin, HIGH);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "ON");
}
void handleLEDGreenOff() {
  digitalWrite(ledGreenPin, LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OFF");
}
void handleLEDBlueOn() {
  digitalWrite(ledBluePin, HIGH);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "ON");
}
void handleLEDBlueOff() {
  digitalWrite(ledBluePin, LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OFF");
}
void handleLEDYellowOn() {
  digitalWrite(ledYellowPin, HIGH);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "ON");
}
void handleLEDYellowOff() {
  digitalWrite(ledYellowPin, LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OFF");
}
void handleAlarmOn() {
  digitalWrite(alarmPin, HIGH);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "ON");
}
void handleAlarmOff() {
  digitalWrite(alarmPin, LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OFF");
}

void handleLampuTidurOn() {
  digitalWrite(ledKamarTidurPin, HIGH);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "ON");
}
void handleLampuTidurOff() {
  digitalWrite(ledKamarTidurPin, LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OFF");
}
void handleACOn() {
  digitalWrite(acKamarPin, HIGH);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "ON");
}
void handleACOff() {
  digitalWrite(acKamarPin, LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OFF");
}
void handleACSet() {
  String temp = server.arg("temp");
  Serial.print("AC Kamar Utama temperature set to: ");
  Serial.print(temp);
  Serial.println(" degC");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", temp);
}

void handleApiDevice() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  if (server.hasArg("pin") && server.hasArg("state")) {
    int pinNumber = server.arg("pin").toInt();
    int pinState = server.arg("state").toInt();
    
    bool isValidPin = false;
    for (int i = 0; i < NUM_PINS; i++) {
      if (AVAILABLE_PINS[i] == pinNumber) {
        isValidPin = true;
        break;
      }
    }
    
    if (isValidPin) {
      digitalWrite(pinNumber, (pinState == 1) ? HIGH : LOW);
      String response = "Pin " + String(pinNumber) + " set to " + String(pinState);
      server.send(200, "text/plain", response);
    } else {
      server.send(400, "text/plain", "Invalid GPIO Pin");
    }
  } else {
    server.send(400, "text/plain", "Missing pin or state");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting ESP32...");

  // Inisialisasi semua pin GPIO sebagai OUTPUT
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(AVAILABLE_PINS[i], OUTPUT);
    digitalWrite(AVAILABLE_PINS[i], LOW);
  }

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting Wifi");
  Serial.println("Connecting to WiFi...");

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(ledGreenPin, OUTPUT);
  digitalWrite(ledGreenPin, LOW);
  pinMode(ledBluePin, OUTPUT);
  digitalWrite(ledBluePin, LOW);
  pinMode(ledYellowPin, OUTPUT);
  digitalWrite(ledYellowPin, LOW);
  pinMode(alarmPin, OUTPUT);
  digitalWrite(alarmPin, LOW);

  pinMode(ledKamarTidurPin, OUTPUT);
  digitalWrite(ledKamarTidurPin, LOW);
  pinMode(acKamarPin, OUTPUT);
  digitalWrite(acKamarPin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.print(".");
    Serial.print(".");
  }
  Serial.println();

  // Tampilkan IP di Layar LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wifi Connected!");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP().toString());

  Serial.print("Connected to WiFi. IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/led/on", handleLEDOn);
  server.on("/led/off", handleLEDOff);
  server.on("/led_green/on", handleLEDGreenOn);
  server.on("/led_green/off", handleLEDGreenOff);
  server.on("/led_blue/on", handleLEDBlueOn);
  server.on("/led_blue/off", handleLEDBlueOff);
  server.on("/led_yellow/on", handleLEDYellowOn);
  server.on("/led_yellow/off", handleLEDYellowOff);
  server.on("/alarm/on", handleAlarmOn);
  server.on("/alarm/off", handleAlarmOff);

  server.on("/kamar-utama/lampu-tidur/on", handleLampuTidurOn);
  server.on("/kamar-utama/lampu-tidur/off", handleLampuTidurOff);
  server.on("/kamar-utama/ac/on", handleACOn);
  server.on("/kamar-utama/ac/off", handleACOff);
  server.on("/kamar-utama/ac/set", handleACSet);

  server.on("/api/device", handleApiDevice);
  server.on("/config.js", []() {
    server.send(200, "application/javascript", "window.__ENV__ = window.__ENV__ || {};");
  });

  server.begin();
  Serial.println("Web server started.");
}

void loop() { server.handleClient(); }
"""

    cpp_code = cpp_code.replace('const char *ssid = "Wokwi-GUEST";', f'const char *ssid = "{existing_ssid}";')
    cpp_code = cpp_code.replace('const char *password = "";', f'const char *password = "{existing_password}";')

    with open("SmartHome_ESP32.ino", "w", encoding="utf-8") as f:
        f.write(cpp_code)
    print("SmartHome_ESP32.ino successfully generated and synced!")

if __name__ == "__main__":
    generate()
