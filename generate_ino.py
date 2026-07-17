import os

def generate():
    # Read SmartHomeApps.html
    html_path = "SmartHomeApps.html"
    if not os.path.exists(html_path):
        print(f"Error: {html_path} not found.")
        return

    with open(html_path, "r", encoding="utf-8") as f:
        html = f.read()

    # Perform C++ raw string insertions for check boxes
    # Card Green (Kamar Utama)
    card_green_old = """                <div class="card" id="card-green" onclick="openRoomDetail('kamar-utama')">
                    <div class="card-icon"><i class="fas fa-bed"></i></div>
                    <div>
                        <div class="card-title">Kamar Utama</div>
                        <div class="card-subtitle">Lampu Hijau</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch" onclick="event.stopPropagation()">
                            <input type="checkbox" onchange="toggleStatus(this)">"""
    
    card_green_new = """                <div class="card" id="card-green" onclick="openRoomDetail('kamar-utama')">
                    <div class="card-icon"><i class="fas fa-bed"></i></div>
                    <div>
                        <div class="card-title">Kamar Utama</div>
                        <div class="card-subtitle">Lampu Hijau</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch" onclick="event.stopPropagation()">
                            <input type="checkbox" )raw-html" + greenChecked + R"raw-html( onchange="toggleStatus(this)">"""

    # Card Red (Ruang Tamu)
    card_red_old = """                <div class="card" id="card-red">
                    <div class="card-icon"><i class="fas fa-couch"></i></div>
                    <div>
                        <div class="card-title">Ruang Tamu</div>
                        <div class="card-subtitle">Lampu Merah</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch">
                            <input type="checkbox" onchange="toggleStatus(this)">"""
    
    card_red_new = """                <div class="card" id="card-red">
                    <div class="card-icon"><i class="fas fa-couch"></i></div>
                    <div>
                        <div class="card-title">Ruang Tamu</div>
                        <div class="card-subtitle">Lampu Merah</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch">
                            <input type="checkbox" )raw-html" + ledChecked + R"raw-html( onchange="toggleStatus(this)">"""

    # Card Yellow (Dapur Modern)
    card_yellow_old = """                <div class="card" id="card-yellow">
                    <div class="card-icon"><i class="fas fa-utensils"></i></div>
                    <div>
                        <div class="card-title">Dapur Modern</div>
                        <div class="card-subtitle">Lampu Kuning</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch">
                            <input type="checkbox" onchange="toggleStatus(this)">"""
    
    card_yellow_new = """                <div class="card" id="card-yellow">
                    <div class="card-icon"><i class="fas fa-utensils"></i></div>
                    <div>
                        <div class="card-title">Dapur Modern</div>
                        <div class="card-subtitle">Lampu Kuning</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch">
                            <input type="checkbox" )raw-html" + yellowChecked + R"raw-html( onchange="toggleStatus(this)">"""

    # Card Blue (Kamar Mandi)
    card_blue_old = """                <div class="card" id="card-blue">
                    <div class="card-icon"><i class="fas fa-tint"></i></div>
                    <div>
                        <div class="card-title">Kamar Mandi</div>
                        <div class="card-subtitle">Lampu Biru</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch">
                            <input type="checkbox" onchange="toggleStatus(this)">"""
    
    card_blue_new = """                <div class="card" id="card-blue">
                    <div class="card-icon"><i class="fas fa-tint"></i></div>
                    <div>
                        <div class="card-title">Kamar Mandi</div>
                        <div class="card-subtitle">Lampu Biru</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch">
                            <input type="checkbox" )raw-html" + blueChecked + R"raw-html( onchange="toggleStatus(this)">"""

    # Card Orange (Alarm Rumah)
    card_orange_old = """                <div class="card" id="card-orange">
                    <div class="card-icon"><i class="fas fa-bell"></i></div>
                    <div>
                        <div class="card-title">Alarm Rumah</div>
                        <div class="card-subtitle">Buzzer Relay</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch">
                            <input type="checkbox" onchange="toggleStatus(this)">"""
    
    card_orange_new = """                <div class="card" id="card-orange">
                    <div class="card-icon"><i class="fas fa-bell"></i></div>
                    <div>
                        <div class="card-title">Alarm Rumah</div>
                        <div class="card-subtitle">Buzzer Relay</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch">
                            <input type="checkbox" )raw-html" + alarmChecked + R"raw-html( onchange="toggleStatus(this)">"""

    # Apply card replacements
    html = html.replace(card_green_old, card_green_new)
    html = html.replace(card_red_old, card_red_new)
    html = html.replace(card_yellow_old, card_yellow_new)
    html = html.replace(card_blue_old, card_blue_new)
    html = html.replace(card_orange_old, card_orange_new)

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

void setup() {
  Serial.begin(115200);
  Serial.println("Starting ESP32...");

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

  server.begin();
  Serial.println("Web server started.");
}

void loop() { server.handleClient(); }
"""

    with open("SmartHome_ESP32.ino", "w", encoding="utf-8") as f:
        f.write(cpp_code)
    print("SmartHome_ESP32.ino successfully generated and synced!")

if __name__ == "__main__":
    generate()
