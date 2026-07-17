#include <LiquidCrystal_I2C.h>
#include <WebServer.h>
#include <WiFi.h>
#include <Wire.h>

const char *ssid = "No Network 5G";
const char *password = "BAYARDULUDONG";

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
  html += R"raw-html(<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smart Home App - Dashboard</title>
    <link href="https://fonts.googleapis.com/css2?family=Rajdhani:wght@500;600;700&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
    <style>
        :root {
            --bg-dark: #f8fafc;        /* slate-50 (light body background) */
            --bg-card: #ffffff;        /* card background */
            --border-color: rgba(35, 50, 252, 0.08); /* light brand border */
            --text-main: #0f172a;      /* slate-900 */
            --text-sub: #64748b;       /* slate-500 */
            
            --blue-glow: rgba(35, 50, 252, 0.15);
            --blue-solid: #2332fc;      /* primary electric blue */
            
            --red-glow: rgba(239, 68, 68, 0.15);
            --red-solid: #ef4444;
            
            --green-glow: rgba(34, 197, 94, 0.15);
            --green-solid: #22c55e;
            
            --yellow-glow: rgba(234, 179, 8, 0.15);
            --yellow-solid: #eab308;

            --orange-glow: rgba(249, 115, 22, 0.15);
            --orange-solid: #f97316;

            --blue-gradient: linear-gradient(135deg, #2332fc, #6366f1);
        }

        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
            font-family: 'Rajdhani', sans-serif;
            -webkit-tap-highlight-color: transparent;
        }

        body {
            background-color: #e2e8f0; /* Slate 200 for desktop background */
            display: flex;
            justify-content: center;
            min-height: 100vh;
            margin: 0;
            padding: 0;
        }

        /* App Container - Responsive & Mobile-First */
        .app-container {
            width: 100%;
            max-width: 480px;
            background: var(--bg-dark);
            position: relative;
            display: flex;
            flex-direction: column;
            border-left: 1px solid rgba(0, 0, 0, 0.04);
            border-right: 1px solid rgba(0, 0, 0, 0.04);
            box-shadow: 0 0 40px rgba(0, 0, 0, 0.08);
        }

        /* Main Content App */
        .app-content {
            padding: 20px 20px 120px 20px;
            flex: 1;
            overflow-y: auto;
        }

        /* App Header - Blue Background */
        .app-header {
            background: var(--blue-gradient);
            padding: 16px 24px 14px 24px;
            border-bottom-left-radius: 20px;
            border-bottom-right-radius: 20px;
            box-shadow: 0 4px 20px rgba(35, 50, 252, 0.1);
            color: #ffffff;
            z-index: 10;
        }

        .app-header h1 {
            font-size: 24px;
            color: #ffffff;
            font-weight: 700;
            letter-spacing: -0.3px;
        }

        .app-header .live-time-text {
            font-size: 14px;
            color: rgba(255, 255, 255, 0.8);
            font-weight: 600;
            margin-top: 2px;
            letter-spacing: 0.2px;
        }

        .app-header .settings-btn {
            width: 36px;
            height: 36px;
            background: rgba(255, 255, 255, 0.15);
            border-color: rgba(255, 255, 255, 0.2);
            color: #ffffff;
            box-shadow: none;
        }

        .app-header .settings-btn:hover {
            background: rgba(255, 255, 255, 0.25);
            border-color: rgba(255, 255, 255, 0.4);
            color: #ffffff;
        }

        /* Top Bar Layout */
        .top-bar {
            display: flex;
            justify-content: space-between;
            align-items: center;
        }

        .settings-btn {
            width: 40px;
            height: 40px;
            border-radius: 50%;
            background: var(--bg-card);
            border: 1px solid rgba(0, 0, 0, 0.06);
            display: flex;
            justify-content: center;
            align-items: center;
            color: var(--text-main);
            cursor: pointer;
            box-shadow: 0 4px 12px rgba(0, 0, 0, 0.03);
            transition: all 0.3s ease;
            line-height: 1;
        }
        .settings-btn:hover {
            background: #f1f5f9;
            border-color: rgba(35, 50, 252, 0.2);
            color: var(--blue-solid);
        }
        .settings-btn i {
            display: inline-flex;
            justify-content: center;
            align-items: center;
            transition: transform 0.4s ease;
        }
        .settings-btn:hover i {
            transform: rotate(45deg);
        }

        /* Weather Card */
        .weather-card {
            background: var(--blue-gradient);
            border: 1px solid rgba(35, 50, 252, 0.1);
            border-radius: 24px;
            padding: 22px;
            color: #ffffff;
            box-shadow: 0 12px 30px rgba(35, 50, 252, 0.25);
            margin-bottom: 25px;
            position: relative;
            overflow: hidden;
        }
        .weather-card::before {
            content: '';
            position: absolute;
            top: -50%;
            right: -50%;
            width: 150px;
            height: 150px;
            background: radial-gradient(circle, rgba(255, 255, 255, 0.2) 0%, transparent 70%);
            border-radius: 50%;
        }

        .weather-info h2 {
            font-size: 20px;
            font-weight: 700;
        }

        .weather-info p {
            font-size: 14px;
            color: rgba(255, 255, 255, 0.8);
            margin-top: 2px;
        }

        .weather-temp {
            position: absolute;
            right: 25px;
            top: 20px;
            font-size: 52px;
            font-weight: 700;
            color: #ffffff;
        }

        .weather-footer {
            margin-top: 20px;
            display: flex;
            justify-content: space-between;
            font-size: 14px;
            color: rgba(255, 255, 255, 0.8);
            border-top: 1px solid rgba(255, 255, 255, 0.15);
            padding-top: 12px;
        }

        /* Segmented Control Tabs */
        .tab-control {
            background: #f1f5f9;
            padding: 5px;
            border-radius: 16px;
            border: 1px solid rgba(0, 0, 0, 0.03);
            display: flex;
            margin-bottom: 25px;
        }

        .tab-btn {
            flex: 1;
            padding: 10px;
            border: none;
            background: transparent;
            font-size: 15px;
            font-weight: 700;
            color: var(--text-sub);
            cursor: pointer;
            border-radius: 12px;
            transition: all 0.3s ease;
        }

        .tab-btn.active {
            background: #ffffff;
            color: var(--blue-solid);
            box-shadow: 0 4px 12px rgba(0, 0, 0, 0.05);
        }

        /* Grid Rooms / Devices */
        .grid-container {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 16px;
        }

        .card {
            background: var(--bg-card);
            border: 1px solid var(--border-color);
            border-radius: 24px;
            padding: 18px;
            display: flex;
            flex-direction: column;
            justify-content: space-between;
            position: relative;
            height: 165px;
            box-shadow: 0 8px 20px rgba(0, 0, 0, 0.02);
            transition: all 0.4s cubic-bezier(0.175, 0.885, 0.32, 1.275);
            cursor: pointer;
        }
        .card:hover {
            transform: translateY(-2px);
            border-color: rgba(35, 50, 252, 0.2);
            box-shadow: 0 10px 25px rgba(35, 50, 252, 0.04);
        }

        .card-icon {
            width: 44px;
            height: 44px;
            border-radius: 14px;
            background: #f8fafc;
            border: 1px solid rgba(0, 0, 0, 0.04);
            display: flex;
            justify-content: center;
            align-items: center;
            color: var(--text-sub);
            font-size: 20px;
            margin-bottom: 12px;
            transition: all 0.3s ease;
        }

        .card-title {
            font-size: 18px;
            font-weight: 700;
            color: var(--text-main);
        }

        .card-subtitle {
            font-size: 13px;
            color: var(--text-sub);
            margin-top: 2px;
            margin-bottom: 10px;
        }

        /* Dynamic Active Glowing States (Light Theme) */
        .card.active-red {
            border-color: var(--red-solid);
            box-shadow: 0 10px 25px var(--red-glow);
        }
        .card.active-red .card-icon {
            color: var(--red-solid);
            background: rgba(239, 68, 68, 0.08);
            border-color: rgba(239, 68, 68, 0.15);
        }

        .card.active-green {
            border-color: var(--green-solid);
            box-shadow: 0 10px 25px var(--green-glow);
        }
        .card.active-green .card-icon {
            color: var(--green-solid);
            background: rgba(34, 197, 94, 0.08);
            border-color: rgba(34, 197, 94, 0.15);
        }

        .card.active-blue {
            border-color: var(--blue-solid);
            box-shadow: 0 10px 25px var(--blue-glow);
        }
        .card.active-blue .card-icon {
            color: var(--blue-solid);
            background: rgba(35, 50, 252, 0.08);
            border-color: rgba(35, 50, 252, 0.15);
        }

        .card.active-yellow {
            border-color: var(--yellow-solid);
            box-shadow: 0 10px 25px var(--yellow-glow);
        }
        .card.active-yellow .card-icon {
            color: var(--yellow-solid);
            background: rgba(234, 179, 8, 0.08);
            border-color: rgba(234, 179, 8, 0.15);
        }

        .card.active-orange {
            border-color: var(--orange-solid);
            box-shadow: 0 10px 25px var(--orange-glow);
        }
        .card.active-orange .card-icon {
            color: var(--orange-solid);
            background: rgba(249, 115, 22, 0.08);
            border-color: rgba(249, 115, 22, 0.15);
        }

        /* Micro-Animations for card states */
        @keyframes wiggle {
            0%, 100% { transform: rotate(0deg); }
            25% { transform: rotate(-8deg); }
            75% { transform: rotate(8deg); }
        }
        .card.active-orange.active-alarm .card-icon i {
            animation: wiggle 0.4s ease infinite;
        }

        .card.active-red, .card.active-green, .card.active-blue, .card.active-yellow, .card.active-orange {
            transform: scale(1.01);
        }

        /* Switch/Toggle button */
        .switch-container {
            display: flex;
            justify-content: space-between;
            align-items: center;
            width: 100%;
        }

        .status-text {
            font-size: 13px;
            font-weight: 700;
            color: var(--text-sub);
            letter-spacing: 0.5px;
        }

        .switch {
            position: relative;
            display: inline-block;
            width: 44px;
            height: 24px;
        }

        .switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }

        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #e2e8f0;
            border: 1px solid rgba(0, 0, 0, 0.04);
            transition: .3s;
            border-radius: 24px;
        }

        .slider:before {
            position: absolute;
            content: "";
            height: 16px;
            width: 16px;
            left: 3px;
            bottom: 3px;
            background-color: #ffffff;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.15);
            transition: .3s;
            border-radius: 50%;
        }

        input:checked+.slider:before {
            transform: translateX(20px);
        }

        /* Color toggles dynamically based on active card type */
        .card.active-red input:checked+.slider { background-color: var(--red-solid); }
        .card.active-green input:checked+.slider { background-color: var(--green-solid); }
        .card.active-blue input:checked+.slider { background-color: var(--blue-solid); }
        .card.active-yellow input:checked+.slider { background-color: var(--yellow-solid); }
        .card.active-orange input:checked+.slider { background-color: var(--orange-solid); }

        /* Bottom Tab Bar */
        .bottom-nav {
            position: fixed;
            bottom: 0;
            left: 50%;
            transform: translateX(-50%);
            width: 100%;
            max-width: 480px;
            height: 75px;
            background: #ffffff;
            border-top: 1px solid rgba(0, 0, 0, 0.05);
            border-top-left-radius: 25px;
            border-top-right-radius: 25px;
            display: flex;
            justify-content: space-around;
            align-items: center;
            padding: 0 20px;
            z-index: 1000;
            box-shadow: 0 -10px 30px rgba(0, 0, 0, 0.04);
        }

        .nav-item {
            color: var(--text-sub);
            font-size: 20px;
            cursor: pointer;
            transition: all 0.3s;
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        .nav-item.active {
            color: var(--blue-solid);
        }

        /* Central Floating Mic Button */
        .mic-container {
            position: relative;
            top: -25px;
        }

        .mic-btn {
            width: 65px;
            height: 65px;
            border-radius: 50%;
            background: #ffffff;
            border: 5px solid var(--bg-dark);
            box-shadow: 0 8px 20px rgba(0, 0, 0, 0.06);
            display: flex;
            justify-content: center;
            align-items: center;
            color: var(--blue-solid);
            font-size: 22px;
            cursor: pointer;
            transition: all 0.3s;
        }
        .mic-btn:active {
            transform: scale(0.95);
        }

        /* Settings Modal styling */
        .modal-overlay {
            position: fixed;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background: rgba(15, 23, 42, 0.3);
            backdrop-filter: blur(8px);
            display: flex;
            justify-content: center;
            align-items: center;
            z-index: 2000;
            opacity: 0;
            pointer-events: none;
            transition: opacity 0.3s ease;
        }

        .modal-overlay.active {
            opacity: 1;
            pointer-events: auto;
        }

        .modal-card {
            background: #ffffff;
            border: 1px solid rgba(0, 0, 0, 0.05);
            width: 85%;
            max-width: 400px;
            border-radius: 24px;
            padding: 25px;
            box-shadow: 0 20px 45px rgba(0, 0, 0, 0.08);
            transform: scale(0.9);
            transition: transform 0.3s ease;
        }

        .modal-overlay.active .modal-card {
            transform: scale(1);
        }

        .modal-title {
            font-size: 22px;
            font-weight: 700;
            color: var(--text-main);
            margin-bottom: 15px;
        }

        .modal-input-group {
            margin-bottom: 20px;
        }

        .modal-input-label {
            font-size: 14px;
            font-weight: 600;
            color: var(--text-sub);
            margin-bottom: 8px;
            display: block;
        }

        .modal-input {
            width: 100%;
            padding: 12px 15px;
            border: 1px solid #e2e8f0;
            outline: none;
            background: #f8fafc;
            border-radius: 12px;
            font-family: inherit;
            font-size: 16px;
            color: var(--text-main);
            font-weight: 600;
            transition: all 0.3s;
        }
        .modal-input:focus {
            border-color: var(--blue-solid);
            box-shadow: 0 0 10px rgba(35, 50, 252, 0.1);
            background: #ffffff;
        }

        .modal-help {
            font-size: 13px;
            color: var(--text-sub);
            line-height: 1.4;
            margin-top: 8px;
        }

        .modal-buttons {
            display: flex;
            gap: 12px;
            justify-content: flex-end;
        }

        .modal-btn {
            padding: 10px 20px;
            border: 1px solid #e2e8f0;
            background: #ffffff;
            border-radius: 12px;
            font-size: 15px;
            font-weight: 700;
            cursor: pointer;
            transition: all 0.2s ease;
        }

        .modal-btn.cancel-btn {
            color: var(--text-sub);
        }
        .modal-btn.cancel-btn:hover {
            background: #f1f5f9;
        }

        .modal-btn.save-btn {
            color: #ffffff;
            background: var(--blue-solid);
            border-color: var(--blue-solid);
        }
        .modal-btn.save-btn:hover {
            box-shadow: 0 0 10px rgba(35, 50, 252, 0.4);
        }
        .modal-btn:active {
            transform: scale(0.95);
        }

        /* Room Detail Expandable Modal styling */
        .room-modal-card {
            background: #ffffff;
            border: 1px solid rgba(0, 0, 0, 0.05);
            width: 85%;
            max-width: 400px;
            border-radius: 24px;
            padding: 25px;
            box-shadow: 0 20px 45px rgba(0, 0, 0, 0.08);
            transform: translateY(50px);
            transition: all 0.3s cubic-bezier(0.175, 0.885, 0.32, 1.275);
        }

        .modal-overlay.active .room-modal-card {
            transform: translateY(0);
        }

        .room-detail-list {
            margin-top: 20px;
            display: flex;
            flex-direction: column;
            gap: 16px;
        }

        .room-detail-item {
            display: flex;
            justify-content: space-between;
            align-items: center;
            background: #f8fafc;
            padding: 14px 18px;
            border-radius: 16px;
            border: 1px solid rgba(0, 0, 0, 0.02);
            transition: all 0.3s ease;
        }

        .room-detail-item:hover {
            border-color: rgba(35, 50, 252, 0.1);
        }

        .room-item-info {
            display: flex;
            align-items: center;
            gap: 12px;
        }

        .room-item-icon {
            width: 38px;
            height: 38px;
            border-radius: 12px;
            background: rgba(35, 50, 252, 0.08);
            color: var(--blue-solid);
            display: flex;
            justify-content: center;
            align-items: center;
            font-size: 16px;
        }

        .room-item-name {
            font-size: 16px;
            font-weight: 700;
            color: var(--text-main);
        }

        .room-item-desc {
            font-size: 12px;
            color: var(--text-sub);
        }

        /* AC Range Temp Slider */
        .ac-temp-control {
            margin-top: 10px;
            background: #f8fafc;
            padding: 16px;
            border-radius: 16px;
            border: 1px solid rgba(0, 0, 0, 0.02);
        }

        .ac-temp-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 12px;
        }

        .ac-temp-title {
            font-size: 15px;
            font-weight: 700;
            color: var(--text-main);
        }

        .ac-temp-value {
            font-size: 20px;
            font-weight: 700;
            color: var(--blue-solid);
        }

        .ac-range-slider {
            -webkit-appearance: none;
            width: 100%;
            height: 6px;
            border-radius: 5px;
            background: #e2e8f0;
            outline: none;
        }

        .ac-range-slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 20px;
            height: 20px;
            border-radius: 50%;
            background: var(--blue-solid);
            cursor: pointer;
            box-shadow: 0 0 10px rgba(35, 50, 252, 0.4);
            transition: transform 0.2s;
        }

        .ac-range-slider::-webkit-slider-thumb:hover {
            transform: scale(1.15);
        }

        /* Toast Notifications */
        .toast-container {
            position: fixed;
            bottom: 90px;
            left: 50%;
            transform: translateX(-50%);
            display: flex;
            flex-direction: column;
            gap: 10px;
            z-index: 3000;
            pointer-events: none;
            width: 80%;
            max-width: 320px;
        }
        .toast {
            background: #ffffff;
            border: 1px solid rgba(0, 0, 0, 0.05);
            color: var(--text-main);
            padding: 12px 20px;
            border-radius: 12px;
            font-size: 14px;
            font-weight: 700;
            text-align: center;
            box-shadow: 0 10px 25px rgba(0, 0, 0, 0.08);
            opacity: 0;
            transform: translateY(20px);
            transition: all 0.3s cubic-bezier(0.68, -0.55, 0.27, 1.55);
        }
        .toast.show {
            opacity: 1;
            transform: translateY(0);
        }
    </style>
</head>

<body>
    <div class="app-container">
        <!-- Blue Header -->
        <div class="app-header">
            <div class="top-bar">
                <div>
                    <h1>Araya Smart Home</h1>
                    <p id="liveTime" class="live-time-text">--:-- - ---</p>
                </div>
                <div class="settings-btn" onclick="configureIP()">
                    <i class="fas fa-cog"></i>
                </div>
            </div>
        </div>

        <div class="app-content">
            <div class="weather-card">
                <div class="weather-info">
                    <h2 id="locationName">My Location</h2>
                    <p id="locationCountry">Mencari lokasi...</p>
                </div>
                <div id="weatherTemp" class="weather-temp">--°</div>
                <div class="weather-footer">
                    <span id="weatherStatus"><i class="fas fa-spinner fa-spin"></i> Memuat...</span>
                    <span id="weatherLimits">H: --° L: --°</span>
                </div>
            </div>
            <div class="tab-control">
                <button class="tab-btn active" onclick="toggleTab(this)">Room</button>
                <button class="tab-btn" onclick="toggleTab(this)">Devices</button>
            </div>
            <div class="grid-container">
                <div class="card" id="card-green" onclick="openRoomDetail('kamar-utama')">
                    <div class="card-icon"><i class="fas fa-bed"></i></div>
                    <div>
                        <div class="card-title">Kamar Utama</div>
                        <div class="card-subtitle">Lampu Hijau</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch" onclick="event.stopPropagation()">
                            <input type="checkbox" )raw-html" + greenChecked + R"raw-html( onchange="toggleStatus(this)">
                            <span class="slider"></span>
                        </label>
                    </div>
                </div>
                <div class="card" id="card-red">
                    <div class="card-icon"><i class="fas fa-couch"></i></div>
                    <div>
                        <div class="card-title">Ruang Tamu</div>
                        <div class="card-subtitle">Lampu Merah</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch">
                            <input type="checkbox" )raw-html" + ledChecked + R"raw-html( onchange="toggleStatus(this)">
                            <span class="slider"></span>
                        </label>
                    </div>
                </div>
                <div class="card" id="card-yellow">
                    <div class="card-icon"><i class="fas fa-utensils"></i></div>
                    <div>
                        <div class="card-title">Dapur Modern</div>
                        <div class="card-subtitle">Lampu Kuning</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch">
                            <input type="checkbox" )raw-html" + yellowChecked + R"raw-html( onchange="toggleStatus(this)">
                            <span class="slider"></span>
                        </label>
                    </div>
                </div>
                <div class="card" id="card-blue">
                    <div class="card-icon"><i class="fas fa-tint"></i></div>
                    <div>
                        <div class="card-title">Kamar Mandi</div>
                        <div class="card-subtitle">Lampu Biru</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch">
                            <input type="checkbox" )raw-html" + blueChecked + R"raw-html( onchange="toggleStatus(this)">
                            <span class="slider"></span>
                        </label>
                    </div>
                </div>
                <div class="card" id="card-orange">
                    <div class="card-icon"><i class="fas fa-bell"></i></div>
                    <div>
                        <div class="card-title">Alarm Rumah</div>
                        <div class="card-subtitle">Buzzer Relay</div>
                    </div>
                    <div class="switch-container">
                        <span class="status-text">OFF</span>
                        <label class="switch">
                            <input type="checkbox" )raw-html" + alarmChecked + R"raw-html( onchange="toggleStatus(this)">
                            <span class="slider"></span>
                        </label>
                    </div>
                </div>
            </div>
        </div>
        <div class="bottom-nav">
            <div class="nav-item active"><i class="fas fa-home"></i></div>
            <div class="mic-container">
                <div class="mic-btn"><i class="fas fa-microphone"></i></div>
            </div>
            <div class="nav-item"><i class="fas fa-user"></i></div>
        </div>
    </div>

    <!-- Settings Modal -->
    <div id="settingsModal" class="modal-overlay">
        <div class="modal-card">
            <div class="modal-title">Setelan Koneksi</div>
            <div class="modal-input-group">
                <label class="modal-input-label" for="ipInput">Alamat IP ESP32</label>
                <input type="text" id="ipInput" class="modal-input" placeholder="e.g. 192.168.1.15 atau localhost:8080">
                <p class="modal-help">
                    Masukkan IP ESP32 (dari LCD) atau <strong>localhost:8080</strong> jika menggunakan simulator Wokwi.
                    Kosongkan jika halaman diakses langsung dari IP ESP32.
                </p>
            </div>
            <div class="modal-buttons">
                <button class="modal-btn cancel-btn" onclick="closeSettings()">Batal</button>
                <button class="modal-btn save-btn" onclick="saveSettings()">Simpan</button>
            </div>
        </div>
    </div>

    <!-- Room Detail Modal (Expandable Card Option A) -->
    <div id="roomDetailModal" class="modal-overlay" onclick="closeRoomDetail(event)">
        <div class="room-modal-card" onclick="event.stopPropagation()">
            <div class="modal-title" id="roomDetailTitle">Detail Kamar Utama</div>
            
            <div class="room-detail-list">
                <!-- Device 1: Lampu Utama -->
                <div class="room-detail-item">
                    <div class="room-item-info">
                        <div class="room-item-icon" style="background: rgba(34, 197, 94, 0.08); color: var(--green-solid);">
                            <i class="fas fa-bed"></i>
                        </div>
                        <div>
                            <div class="room-item-name">Lampu Utama</div>
                            <div class="room-item-desc">Green LED (GPIO 4)</div>
                        </div>
                    </div>
                    <label class="switch">
                        <input type="checkbox" id="modalLampuUtama" )raw-html" + greenChecked + R"raw-html( onchange="toggleModalDevice('lampu-utama', this)">
                        <span class="slider"></span>
                    </label>
                </div>

                <!-- Device 2: Lampu Tidur -->
                <div class="room-detail-item">
                    <div class="room-item-info">
                        <div class="room-item-icon" style="background: rgba(168, 85, 247, 0.08); color: #a855f7;">
                            <i class="fas fa-moon"></i>
                        </div>
                        <div>
                            <div class="room-item-name">Lampu Tidur</div>
                            <div class="room-item-desc">Purple LED (GPIO 12)</div>
                        </div>
                    </div>
                    <label class="switch">
                        <input type="checkbox" id="modalLampuTidur" )raw-html" + tidurChecked + R"raw-html( onchange="toggleModalDevice('lampu-tidur', this)">
                        <span class="slider"></span>
                    </label>
                </div>

                <!-- Device 3: AC Kamar -->
                <div class="room-detail-item">
                    <div class="room-item-info">
                        <div class="room-item-icon" style="background: rgba(35, 50, 252, 0.08); color: var(--blue-solid);">
                            <i class="fas fa-snowflake"></i>
                        </div>
                        <div>
                            <div class="room-item-name">AC Kamar</div>
                            <div class="room-item-desc">White LED (GPIO 13)</div>
                        </div>
                    </div>
                    <label class="switch">
                        <input type="checkbox" id="modalACKamar" )raw-html" + acChecked + R"raw-html( onchange="toggleModalDevice('ac-kamar', this)">
                        <span class="slider"></span>
                    </label>
                </div>

                <!-- AC Temp Control -->
                <div class="ac-temp-control" id="acTempControl" style="display: none;">
                    <div class="ac-temp-header">
                        <span class="ac-temp-title">Temperatur AC</span>
                        <span class="ac-temp-value" id="acTempVal">24°C</span>
                    </div>
                    <input type="range" class="ac-range-slider" id="acTempRange" min="16" max="28" value="24" oninput="updateACTemp(this.value)">
                </div>
            </div>

            <div class="modal-buttons" style="margin-top: 25px;">
                <button class="modal-btn cancel-btn" onclick="closeRoomDetail(null)" style="width: 100%;">Tutup</button>
            </div>
        </div>
    </div>

    <!-- Toast Notifications Container -->
    <div id="toastContainer" class="toast-container"></div>

    <script>
        const modal = document.getElementById("settingsModal");
        const ipInput = document.getElementById("ipInput");
        let esp32IP = localStorage.getItem("esp32_ip") || "";

        function configureIP() {
            ipInput.value = esp32IP;
            modal.classList.add("active");
        }

        // Close setting modal
        function closeSettings() {
            modal.classList.remove("active");
        }

        // Save IP to localStorage
        function saveSettings() {
            esp32IP = ipInput.value.trim();
            localStorage.setItem("esp32_ip", esp32IP);
            closeSettings();
            showToast("IP Address berhasil disimpan!");
        }

        // Live Clock
        function updateTime() {
            const now = new Date();

            // Format time: HH:MM:SS
            const hrs = String(now.getHours()).padStart(2, '0');
            const mins = String(now.getMinutes()).padStart(2, '0');
            const secs = String(now.getSeconds()).padStart(2, '0');
            const timeStr = `${hrs}:${mins}:${secs}`;

            // Format date: Hari, DD MMMM YYYY
            const options = { weekday: 'long', day: '2-digit', month: 'long', year: 'numeric' };
            const dateStr = now.toLocaleDateString('id-ID', options);

            document.getElementById("liveTime").innerText = `${dateStr} | ${timeStr}`;
        }
        setInterval(updateTime, 1000);
        updateTime();

        // Toast Helper
        function showToast(message, type = "success") {
            const container = document.getElementById("toastContainer");
            const toast = document.createElement("div");
            toast.className = "toast";
            if (type === "error") {
                toast.style.borderLeft = "4px solid #ef4444";
            } else {
                toast.style.borderLeft = "4px solid #2332fc";
            }
            toast.innerText = message;
            container.appendChild(toast);

            // Force reflow
            toast.offsetHeight;

            toast.classList.add("show");

            setTimeout(() => {
                toast.classList.remove("show");
                setTimeout(() => {
                    container.removeChild(toast);
                }, 300);
            }, 2500);
        }

        // Tab Filtering
        function toggleTab(button) {
            document.querySelectorAll('.tab-btn').forEach(btn => btn.classList.remove('active'));
            button.classList.add('active');

            const isRoom = button.innerText.trim() === "Room";
            document.querySelectorAll('.grid-container .card').forEach(card => {
                const title = card.querySelector('.card-title').innerText.trim();
                if (isRoom && title === "Alarm Rumah") {
                    card.style.display = "none";
                } else {
                    card.style.display = "flex";
                }
            });
            showToast(`Menampilkan kategori: ${button.innerText}`);
        }

        // Initial setup for default active/inactive visual classes
        document.querySelectorAll('.grid-container .card').forEach(card => {
            const checkbox = card.querySelector('input[type="checkbox"]');
            const cardTitle = card.querySelector('.card-title').innerText.trim();
            updateCardVisualState(card, cardTitle, checkbox.checked);
        });

        function updateCardVisualState(card, title, isActive) {
            // Remove all active state classes
            card.classList.remove('active-red', 'active-green', 'active-blue', 'active-yellow', 'active-orange', 'active-alarm');

            if (isActive) {
                if (title === "Ruang Tamu") {
                    card.classList.add('active-red');
                } else if (title === "Kamar Utama") {
                    card.classList.add('active-green');
                } else if (title === "Kamar Mandi") {
                    card.classList.add('active-blue');
                } else if (title === "Dapur Modern") {
                    card.classList.add('active-yellow');
                } else if (title === "Alarm Rumah") {
                    card.classList.add('active-orange', 'active-alarm');
                }
            }
        }

        function toggleStatus(checkbox) {
            const card = checkbox.closest('.card');
            const statusText = card.querySelector('.status-text');
            const cardTitle = card.querySelector('.card-title').innerText.trim();

            statusText.innerText = checkbox.checked ? "ON" : "OFF";
            updateCardVisualState(card, cardTitle, checkbox.checked);

            let endpoint = "";
            if (cardTitle === "Ruang Tamu") {
                endpoint = checkbox.checked ? "/led/on" : "/led/off";
            } else if (cardTitle === "Kamar Utama") {
                endpoint = checkbox.checked ? "/led_green/on" : "/led_green/off";
            } else if (cardTitle === "Kamar Mandi") {
                endpoint = checkbox.checked ? "/led_blue/on" : "/led_blue/off";
            } else if (cardTitle === "Dapur Modern") {
                endpoint = checkbox.checked ? "/led_yellow/on" : "/led_yellow/off";
            } else if (cardTitle === "Alarm Rumah") {
                endpoint = checkbox.checked ? "/alarm/on" : "/alarm/off";
            }

            if (endpoint) {
                let path = endpoint;
                if (esp32IP) {
                    path = `http://${esp32IP}${path}`;
                }

                showToast(`${cardTitle} diubah ke ${checkbox.checked ? "ON" : "OFF"}`);

                fetch(path)
                    .then(res => {
                        if (!res.ok) {
                            showToast("Gagal berkomunikasi dengan ESP32", "error");
                        }
                    })
                    .catch(err => {
                        console.error("Error:", err);
                        showToast("Error koneksi ke ESP32", "error");
                    });
            }
        }

        // Room Expandable Modal logic
        const roomModal = document.getElementById("roomDetailModal");
        const modalLampuUtama = document.getElementById("modalLampuUtama");
        const modalLampuTidur = document.getElementById("modalLampuTidur");
        const modalACKamar = document.getElementById("modalACKamar");
        const acTempControl = document.getElementById("acTempControl");
        const acTempRange = document.getElementById("acTempRange");
        const acTempVal = document.getElementById("acTempVal");

        function openRoomDetail(roomId) {
            if (roomId === 'kamar-utama') {
                const greenChecked = document.querySelector('#card-green input[type="checkbox"]').checked;
                modalLampuUtama.checked = greenChecked;
                
                modalLampuTidur.checked = localStorage.getItem("status_lampu_tidur") === "true";
                modalACKamar.checked = localStorage.getItem("status_ac_kamar") === "true";
                
                const savedTemp = localStorage.getItem("ac_temp") || "24";
                acTempRange.value = savedTemp;
                acTempVal.innerText = `${savedTemp}°C`;

                acTempControl.style.display = modalACKamar.checked ? "block" : "none";

                roomModal.classList.add("active");
            }
        }

        function closeRoomDetail(event) {
            if (!event || event.target === roomModal) {
                roomModal.classList.remove("active");
            }
        }

        function toggleModalDevice(device, checkbox) {
            let endpoint = "";
            let toastMsg = "";

            if (device === 'lampu-utama') {
                const mainCheckbox = document.querySelector('#card-green input[type="checkbox"]');
                mainCheckbox.checked = checkbox.checked;
                toggleStatus(mainCheckbox);
                return;
            } else if (device === 'lampu-tidur') {
                endpoint = checkbox.checked ? "/kamar-utama/lampu-tidur/on" : "/kamar-utama/lampu-tidur/off";
                toastMsg = `Lampu Tidur Kamar ${checkbox.checked ? "ON" : "OFF"}`;
                localStorage.setItem("status_lampu_tidur", checkbox.checked);
            } else if (device === 'ac-kamar') {
                endpoint = checkbox.checked ? "/kamar-utama/ac/on" : "/kamar-utama/ac/off";
                toastMsg = `AC Kamar ${checkbox.checked ? "ON" : "OFF"}`;
                localStorage.setItem("status_ac_kamar", checkbox.checked);
                acTempControl.style.display = checkbox.checked ? "block" : "none";
            }

            if (endpoint) {
                let path = endpoint;
                if (esp32IP) {
                    path = `http://${esp32IP}${path}`;
                }

                showToast(toastMsg);

                fetch(path)
                    .then(res => {
                        if (!res.ok) {
                            showToast("Gagal berkomunikasi dengan ESP32", "error");
                        }
                    })
                    .catch(err => {
                        console.error("Error:", err);
                        showToast("Error koneksi ke ESP32", "error");
                    });
            }
        }

        function updateACTemp(val) {
            acTempVal.innerText = `${val}°C`;
            localStorage.setItem("ac_temp", val);
            
            let path = `/kamar-utama/ac/set?temp=${val}`;
            if (esp32IP) {
                path = `http://${esp32IP}${path}`;
            }

            fetch(path)
                .catch(err => console.error("Error setting AC temp:", err));
        }

        // Real-time Geolocation and Weather (Open-Meteo & OpenStreetMap Nominatim)
        function updateWeather() {
            if (navigator.geolocation) {
                navigator.geolocation.getCurrentPosition(
                    (position) => {
                        const lat = position.coords.latitude;
                        const lon = position.coords.longitude;
                        fetchWeatherData(lat, lon);
                        fetchLocationName(lat, lon);
                    },
                    (error) => {
                        console.warn("Geolocation denied/failed, using IP location fallback:", error);
                        fetchIPLocation();
                    }
                );
            } else {
                fetchIPLocation();
            }
        }

        // IP-based Geolocation fallback
        function fetchIPLocation() {
            fetch('https://ipapi.co/json/')
                .then(res => res.json())
                .then(data => {
                    if (data && data.latitude && data.longitude) {
                        const cityName = data.city || "Jakarta";
                        const regionName = data.country_name || "Indonesia";
                        document.getElementById("locationName").innerText = cityName;
                        document.getElementById("locationCountry").innerText = regionName;
                        fetchWeatherData(data.latitude, data.longitude);
                    } else {
                        // Default fallback
                        fetchWeatherData(-6.2088, 106.8456); // Jakarta
                        document.getElementById("locationName").innerText = "Jakarta";
                        document.getElementById("locationCountry").innerText = "Indonesia";
                    }
                })
                .catch(err => {
                    console.error("IP Geolocation failed:", err);
                    fetchWeatherData(-6.2088, 106.8456); // Jakarta default
                    document.getElementById("locationName").innerText = "Jakarta";
                    document.getElementById("locationCountry").innerText = "Indonesia";
                });
        }

        // OSM Nominatim Reverse Geocoding
        function fetchLocationName(lat, lon) {
            fetch(`https://nominatim.openstreetmap.org/reverse?format=json&lat=${lat}&lon=${lon}`)
                .then(res => res.json())
                .then(data => {
                    if (data && data.address) {
                        const city = data.address.city || data.address.town || data.address.village || data.address.suburb || "Lokasi Saya";
                        const country = data.address.country || "Indonesia";
                        document.getElementById("locationName").innerText = city;
                        document.getElementById("locationCountry").innerText = country;
                    }
                })
                .catch(err => {
                    console.error("Reverse geocoding failed:", err);
                    document.getElementById("locationName").innerText = "Lokasi Saya";
                    document.getElementById("locationCountry").innerText = "Koordinat terdeteksi";
                });
        }

        // Open-Meteo Weather Fetching
        function fetchWeatherData(lat, lon) {
            const url = `https://api.open-meteo.com/v1/forecast?latitude=${lat}&longitude=${lon}&current=temperature_2m,weather_code&daily=temperature_2m_max,temperature_2m_min&timezone=auto`;

            fetch(url)
                .then(res => res.json())
                .then(data => {
                    if (data && data.current) {
                        const temp = Math.round(data.current.temperature_2m);
                        const maxTemp = Math.round(data.daily.temperature_2m_max[0]);
                        const minTemp = Math.round(data.daily.temperature_2m_min[0]);
                        const code = data.current.weather_code;

                        let weatherDesc = "Cerah";
                        let weatherIcon = "fa-sun";

                        if (code === 0) {
                            weatherDesc = "Cerah";
                            weatherIcon = "fa-sun";
                        } else if (code >= 1 && code <= 3) {
                            weatherDesc = "Berawan";
                            weatherIcon = "fa-cloud-sun";
                        } else if (code >= 45 && code <= 48) {
                            weatherDesc = "Berkabut";
                            weatherIcon = "fa-smog";
                        } else if (code >= 51 && code <= 67) {
                            weatherDesc = "Gerimis/Hujan";
                            weatherIcon = "fa-cloud-showers-heavy";
                        } else if (code >= 71 && code <= 77) {
                            weatherDesc = "Bersalju";
                            weatherIcon = "fa-snowflake";
                        } else if (code >= 80 && code <= 82) {
                            weatherDesc = "Hujan Deras";
                            weatherIcon = "fa-cloud-showers-water";
                        } else if (code >= 95 && code <= 99) {
                            weatherDesc = "Badai Petir";
                            weatherIcon = "fa-bolt-lightning";
                        }

                        document.getElementById("weatherTemp").innerText = `${temp}°`;
                        document.getElementById("weatherStatus").innerHTML = `<i class="fas ${weatherIcon}"></i> ${weatherDesc}`;
                        document.getElementById("weatherLimits").innerText = `H: ${maxTemp}° L: ${minTemp}°`;
                    }
                })
                .catch(err => {
                    console.error("Weather fetch failed:", err);
                    document.getElementById("weatherStatus").innerHTML = `<i class="fas fa-exclamation-triangle"></i> Gagal Memuat`;
                });
        }

        // Initialize Weather Geolocation Load
        updateWeather();
    </script>
</body>

</html>)raw-html";

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
