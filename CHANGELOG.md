# Catatan Perubahan (Changelog)

Semua perubahan penting pada proyek **Smart Home ESP32 Control Center** akan dicatat dalam berkas ini.

Format dokumen ini didasarkan pada [Keep a Changelog](https://keepachangelog.com/id/1.0.0/),
dan proyek ini mematuhi [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [Unreleased]

---

## [2.1.0] - 2026-10-21

### 🚀 Ditambahkan (Added)
- **Migrasi Cloud Platform ke Netlify**:
  - Berkas konfigurasi [netlify.toml](netlify.toml) dengan aturan *rewrite* Single Page Application (`/* -> /index.html 200`) dan header keamanan CORS.
  - Pipeline CI/CD otomatis via GitHub Actions pada [.github/workflows/deploy_netlify.yml](.github/workflows/deploy_netlify.yml) untuk otomatisasi build dan deploy saat push ke branch `main`.
- **Integrasi Database Cloud Supabase (PostgreSQL & Realtime)**:
  - Berkas [supabase_schema.sql](supabase_schema.sql) siap pakai untuk SQL Editor Supabase mencakup tabel `rooms`, `devices`, `activity_logs`, dan `settings`, lengkap dengan data awal (*starter seed data*) dan kebijakan Row Level Security (RLS).
  - Pustaka resmi `@supabase/supabase-js@2` disematkan via CDN di [index.html](index.html).
  - Sinkronisasi dua arah instan via WebSockets: langganan realtime (`postgres_changes`) pada tabel `devices` dan `activity_logs` sehingga perubahan status sakelar di satu perangkat langsung terpantul ke seluruh perangkat lain tanpa *refresh*.
- **Konfigurasi Kredensial Fleksibel (.env & UI Settings)**:
  - Berkas template [.env.example](.env.example) dan berkas konfigurasi lokal `.env` (diabaikan oleh git) untuk menyimpan URL Supabase, Anon Key, dan IP ESP32 secara terpisah dan aman.
  - Skrip [build_env.py](build_env.py) yang secara otomatis membuat `config.js` (`window.__ENV__`) dari `.env` lokal maupun dari Environment Variables Netlify / GitHub Actions.
  - Sinkronisasi otomatis terintegrasi pada [generate_ino.py](generate_ino.py) dan penanganan rute virtual `/config.js` di firmware ESP32.
  - Input interaktif untuk *Supabase Project URL* dan *Supabase Anon Key* di modal Pengaturan Sistem tetap dipertahankan dengan indikator visual *badge* `.env` aktif.

### 🔄 Diubah (Changed)
- **Pembaruan Tri-Mode Operational Selector**:
  - Menggantikan mode *Google Apps Script Cloud* menjadi **Supabase Realtime Cloud (Postgres)** dengan ikon dan notifikasi visual yang disesuaikan.
  - Dokumentasi panduan lengkap pada [README.md](README.md) diperbarui mencakup alur setup Supabase SQL Editor dan opsi deploy ke Netlify.

### 🗑️ Dihapus (Removed)
- **Eliminasi Berkas Legacy Google Apps Script**:
  - Dihapus berkas backend cloud lama: `Code.js`, `appsscript.json`, dan `.clasp.json`.
  - Dihapus ketergantungan terhadap Google Clasp CLI dan pemanggilan RPC `window.google.script.run`.

---

## [2.0.0] - 2026-10-20

### 🚀 Ditambahkan (Added)
- **Transformasi Menjadi Multi-Platform Web App**:
  - Mengadaptasi arsitektur Web App dari referensi *Personal Budgeting App* menggunakan runtime **Google Apps Script (GAS)** dan **Google Sheets** sebagai database cloud persisten.
  - Berkas konfigurasi Clasp CLI (`.clasp.json`) dan manifest GAS (`appsscript.json`) untuk kemudahan deploy via `clasp push` dan `clasp deploy`.
  - Backend controller `Code.js` lengkap dengan router `doGet(e)` dan `doPost(e)`, REST API untuk IoT sync, dan fungsi RPC `google.script.run`.
  - Otomatisasi inisialisasi lembar kerja Google Sheets (`setupDatabase()`): `Devices`, `Rooms`, `ActivityLogs`, dan `Settings`.
- **Mode Simulasi Virtual & Mock Runner (`window.google.script.run`)**:
  - Mock runner otomatis aktif saat dibuka secara lokal di VS Code Live Server / peramban offline di mana runtime GAS tidak tersedia.
  - Mensimulasikan operasi database, pembacaan riwayat aktivitas, dan pembaruan sakelar dengan latensi responsif menggunakan `localStorage`.
- **Virtual ESP32 Hardware Inspector & Simulator Console (`#virtualHardwareModal`)**:
  - Matriks visual 19 pin GPIO ESP32 (Port 1–19) dengan lampu LED neon dinamis (*Red, Green, Blue, Purple, Yellow, Orange, White*).
  - Indikator status pin real-time (`HIGH` berdenyut terang vs `LOW` redup) dengan interaksi klik langsung untuk uji manual.
  - **Virtual Serial Monitor (115200 baud)**: Terminal teks monospaced real-time yang mencatat setiap event perangkat keras dan HTTP request.
  - **Web Audio Alarm Synthesizer**: Menghasilkan bunyi sirene darurat digital melalui Web Audio API saat alarm (GPIO 19) diaktifkan.
  - Tombol aksi simulasi cepat: *Nyalakan Semua Port, Matikan Semua, Tes Sirene Alarm, Reboot ESP32, Reset Data Virtual, dan Salin Log Serial*.
- **Tri-Mode Operational Selector & Mode Badge**:
  - Indikator status mode operasi visual di header aplikasi (*Simulasi Virtual*, *ESP32 Lokal / Wokwi*, dan *Google Apps Script Cloud*).
  - Pilihan mode operasi di menu Pengaturan Sistem dengan konfigurasi Alamat IP Lokal dan URL Cloud Web App.
  - Fitur *graceful fallback*: pengalihan otomatis ke simulator virtual jika koneksi ke ESP32 fisik mengalami kendala atau *timeout*.
- **Pembaruan Generator Firmware (`generate_ino.py`)**:
  - Dukungan resolusi berkas `index.html` dan sinkronisasi instan ke `SmartHome_ESP32.ino`.

---

## [1.1.0] - 2026-07-23

### Ditambahkan (Added)
- **Menu Bar Navigasi Bawah Interaktif (Bottom Navigation Bar)**:
  - **Tombol Home (`fa-home`)**: Berfungsi untuk kembali ke tampilan beranda utama, menutup seluruh modal yang terbuka, dan menggulir (*scroll*) otomatis ke atas halaman.
  - **Tombol Profile (`fa-user`)**: Membuka modal *User Profile* bergaya *Glassmorphism Bottom Sheet* berisi info Admin Smart Home, status sistem real-time (Online/Offline), alamat IP ESP32, serta pintasan cepat (*Setelan IP*, *Tambah Ruangan*, dan *Pulihkan Ruangan Bawaan*).
  - **Tombol Mic (`fa-microphone`)**: Pemicu interaktif Asisten Suara (*Voice Assistant*).

---

## [1.0.0] - 2026-07-23

### Ditambahkan (Added)
- **Antarmuka Web Modern (UI Glassmorphism)**:
  - Tema *Dark Cyber Glassmorphism* dengan efek kilau neon dinamis sesuai status perangkat.
  - Tampilan daftar minimalis (*Minimalist List View*) dengan ikon jumbo 40px dan garis pembatas vertikal presisi.
- **Sistem Pengontrolan Perangkat Dinamis**:
  - Dukungan untuk menambah ruangan kustom secara dinamis dari antarmuka web.
  - Fitur penambahan sub-perangkat kustom (*custom device*) pada semua ruangan (bawaan & kustom) dengan menentukan Nama, Ikon Visual, dan Nomor Port (GPIO).
  - Sakelar utama (*Master Switch*) per ruangan untuk mengontrol seluruh sub-perangkat secara bersamaan.
- **Interaksi Geser (Swipe to Delete)**:
  - Fitur geser ke kiri (*swipe left*) pada kartu ruangan kustom di menu utama untuk menghapus ruangan.
  - Fitur geser ke kiri pada baris perangkat kustom di modal detail untuk menghapus sub-perangkat.
- **Indikator Visual Dinamis**:
  - Indikator LED bulat *glassmorphic* pada kartu utama yang menyala/berdenyut jika ada perangkat aktif di dalam ruangan.
  - Baris sub-ikon kecil perangkat yang otomatis menyala **Hijau Neon** secara independen saat perangkat bersangkutan aktif.
- **Dynamic GPIO Mapping API**:
  - Pemetaan 19 Port Hardware ESP32 ke pin GPIO (GPIO 2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33).
- **Backend Firmware ESP32 C++ (`SmartHome_ESP32.ino`)**:
  - Layanan Web Server HTTP mandiri di ESP32.
  - Pengontrolan status GPIO secara fisik berdasarkan request REST API (`/toggle`, `/status`, dll).
  - Tampilan informasi koneksi dan status pada Layar LCD I2C.
- **Alat Bantu Sinkronisasi (`generate_ino.py`)**:
  - Skrip Python otomatis untuk menyuntikkan kode HTML/CSS/JS dari `SmartHomeApps.html` ke berkas firmware `SmartHome_ESP32.ino`.
- **Penyimpanan Lokal & Migrasi Data**:
  - Penyimpanan konfigurasi ruangan, perangkat, dan IP ESP32 di `LocalStorage` peramban.
  - Deteksi dan migrasi otomatis untuk format data skema lama ke format relasional datar.
- **Simulasi Wokwi**:
  - Konfigurasi sirkuit virtual ESP32 di `diagram.json` dan `wokwi.toml`.

---

## Panduan Format Catatan Perubahan

Untuk pencatatan perubahan rilis mendatang, gunakan kategori standar berikut:
- **`Ditambahkan` (`Added`)**: Untuk fitur-fitur baru yang ditambahkan.
- **`Diubah` (`Changed`)**: Untuk perubahan fungsi pada fitur yang sudah ada.
- **`Depresiasi` (`Deprecated`)**: Untuk fitur yang akan dihapus di rilis berikutnya.
- **`Dihapus` (`Removed`)**: Untuk fitur yang telah dihapus dari proyek.
- **`Diperbaiki` (`Fixed`)**: Untuk perbaikan bug atau kesalahan program.
- **`Keamanan` (`Security`)**: Untuk perbaikan atau peningkatan keamanan.
