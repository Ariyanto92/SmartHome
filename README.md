# 🌐 Smart Home ESP32 - Cloud Web App & Control Center

Sistem kontrol rumah pintar (**Smart Home IoT**) multi-platform modern berbasis mikrokontroler **ESP32** dan antarmuka web bergaya **Dark Cyber Glassmorphism**. Aplikasi ini dirancang fleksibel dengan arsitektur **Hybrid Web App**: dapat di-deploy secara global di **Netlify** dengan database realtime **Supabase (PostgreSQL)**, dihubungkan langsung ke mikrokontroler **ESP32 Fisik / Wokwi LAN**, maupun diuji secara instan melalui **Mode Simulasi Virtual (Mock Runner)** tanpa ketergantungan perangkat keras.

---

## 🚀 Fitur Utama

1. **Hybrid Tri-Mode Architecture**:
   - ⚡ **Mode Supabase Realtime Cloud (Postgres)**: Berjalan 24/7 di hosting **Netlify** terhubung ke database **Supabase**. Sinkronisasi status sakelar dua arah secara instan via WebSockets ke seluruh gawai (smartphone/tablet/PC) tanpa jeda polling, dilengkapi tabel audit log aktivitas.
   - 🔌 **Mode ESP32 Lokal / Wokwi**: Menghubungkan dashboard secara langsung ke mikrokontroler ESP32 fisik (via Wi-Fi LAN) atau simulator Wokwi (`localhost:8080`). Dilengkapi mekanisme *failover* otomatis jika ESP32 offline.
   - 🧪 **Mode Simulasi Virtual (Mock Runner)**: Menjalankan aplikasi secara instan di peramban lokal (VS Code Live Server / berkas HTML) dengan virtual GPIO state, log serial interaktif, dan audio synthesizer alarm tanpa memerlukan perangkat keras.
2. **Virtual ESP32 Hardware Inspector**:
   - Matriks visual 19 pin GPIO (Port 1–19) dengan indikator LED neon berdenyut (*pulse glow*).
   - Klik langsung pada pin virtual untuk menguji respon relay/LED secara manual.
   - **Virtual Serial Monitor (115200 baud)**: Menampilkan log aktivitas perangkat keras dan jaringan secara *real-time*.
   - Aksi simulasi cepat: *Nyalakan Semua, Matikan Semua, Tes Alarm Darurat, Reboot ESP32, Reset State, Salin Log*.
   - **Web Audio Alarm Synthesizer**: Menghasilkan suara sirene darurat digital saat alarm aktif.
3. **Pusat Kendali Ruangan Dinamis**:
   - Ruangan bawaan: Kamar Utama, Ruang Tamu, Kamar Mandi, Dapur Modern, Alarm Rumah.
   - Kemampuan menambah ruangan baru (wadah kustom) dan sub-perangkat ke **semua ruangan**.
   - Pemetaan dinamis ke 19 port GPIO yang aman pada ESP32.
4. **Fitur Geser untuk Hapus (Swipe to Delete)**:
   - Geser ke kiri menggunakan sentuhan ponsel atau klik-seret mouse untuk menghapus ruangan atau sub-perangkat kustom.
5. **Widget Cuaca & Waktu Nyata**:
   - Menampilkan tanggal & jam Indonesia secara live.
   - Deteksi cuaca dan lokasi otomatis menggunakan integrasi Open-Meteo & Nominatim.

---

## 📁 Struktur Berkas Proyek

```text
SmartHome_ESP32/
├── .github/
│   └── workflows/
│       └── deploy_netlify.yml # CI/CD GitHub Actions untuk auto-deploy ke Netlify
├── .env.example               # Template environment variables (aman di-push ke Git)
├── .env                       # File kredensial lokal (rahasia, diabaikan oleh Git)
├── build_env.py               # Generator otomatis config.js dari .env / Netlify Env Vars
├── netlify.toml               # Konfigurasi build Netlify & routing SPA
├── supabase_schema.sql        # Skema SQL PostgreSQL & Realtime untuk Supabase
├── index.html                 # Frontend Web App Utama (Supabase SDK + Simulator + UI)
├── SmartHomeApps.html         # Berkas HTML tersinkronisasi untuk firmware ESP32
├── SmartHome_ESP32.ino        # Firmware C++ ESP32 (Web Server lokal & GPIO controller)
├── generate_ino.py            # Skrip sinkronisasi Python dari HTML ke firmware C++ .ino
├── diagram.json               # Konfigurasi sirkuit simulator Wokwi
├── wokwi.toml                 # Port forwarding simulator Wokwi
├── libraries.txt              # Pustaka eksternal Arduino Wokwi
├── README.md                  # Dokumentasi panduan lengkap
└── CHANGELOG.md               # Riwayat pembaruan versi proyek
```

---

## 🔌 Detail Pemetaan Port / GPIO ESP32

| Nama Port | Nomor Pin GPIO | Fungsi Bawaan / Contoh Perangkat |
| :--- | :---: | :--- |
| **Port 1** | GPIO 2 | Red LED (Lampu Utama Ruang Tamu) |
| **Port 2** | GPIO 4 | Green LED (Lampu Utama Kamar Utama) |
| **Port 3** | GPIO 5 | Blue LED (Lampu Kamar Mandi) |
| **Port 4** | GPIO 12 | Purple LED (Lampu Tidur Kamar Utama) |
| **Port 5** | GPIO 13 | White LED (AC Kamar Utama) |
| **Port 6** | GPIO 14 | *Tersedia untuk Perangkat Kustom* |
| **Port 7** | GPIO 15 | *Tersedia untuk Perangkat Kustom* |
| **Port 8** | GPIO 16 | *Tersedia untuk Perangkat Kustom* |
| **Port 9** | GPIO 17 | *Tersedia untuk Perangkat Kustom* |
| **Port 10** | GPIO 18 | Yellow LED (Lampu Dapur Modern) |
| **Port 11** | GPIO 19 | Buzzer Relay (Sirene Utama Alarm Rumah) |
| **Port 12** | GPIO 21 | *Tersedia untuk Perangkat Kustom* |
| **Port 13** | GPIO 22 | *Tersedia untuk Perangkat Kustom* |
| **Port 14** | GPIO 23 | *Tersedia untuk Perangkat Kustom* |
| **Port 15** | GPIO 25 | *Tersedia untuk Perangkat Kustom* |
| **Port 16** | GPIO 26 | *Tersedia untuk Perangkat Kustom* |
| **Port 17** | GPIO 27 | *Tersedia untuk Perangkat Kustom* |
| **Port 18** | GPIO 32 | *Tersedia untuk Perangkat Kustom* |
| **Port 19** | GPIO 33 | *Tersedia untuk Perangkat Kustom* |

---

## ⚡ Panduan Setup Database Supabase Realtime

Smart Home Web App menggunakan database PostgreSQL di **Supabase** dengan fitur **Realtime Replication** via WebSockets:

### 1. Eksekusi Skema Database di Supabase
1. Masuk ke dashboard akun Supabase Anda: [https://supabase.com/dashboard](https://supabase.com/dashboard).
2. Buat project baru (atau gunakan project yang sudah ada).
3. Di panel menu kiri, klik menu **SQL Editor** (`>_`).
4. Klik tombol **New query**.
5. Buka berkas [supabase_schema.sql](supabase_schema.sql) di proyek ini, salin seluruh kodenya, lalu tempelkan ke SQL Editor Supabase.
6. Klik tombol **Run** (Ctrl + Enter). Skrip ini akan otomatis membuat tabel:
   - `public.rooms`: Data kamar/ruangan.
   - `public.devices`: Status port sakelar, nama perangkat, dan pin GPIO.
   - `public.activity_logs`: Riwayat audit perubahan sakelar secara berkala.
   - `public.settings`: Konfigurasi suhu AC, target IP, dan preferensi sistem.
   - Menerapkan Row Level Security (RLS) serta mengaktifkan **Realtime Replication** pada `public.devices` dan `public.activity_logs`.

### 2. Salin Kredensial API Supabase
1. Pada dashboard Supabase, buka menu **Project Settings** (ikon roda gigi di kiri bawah) > **API**.
2. Salin nilai:
   - **Project URL** (contoh: `https://xyzprojectname.supabase.co`)
   - **Project API Keys** bagian **`anon` `public`** (key JWT publik)

### 3. Masukkan Kredensial ke Aplikasi

Tersedia **2 opsi fleksibel** untuk memasukkan kredensial:

#### Opsi 1: Menggunakan Berkas `.env` (Disarankan untuk Keamanan & CI/CD)
1. Buka berkas `.env` di komputer Anda (atau salin dari `.env.example`).
2. Masukkan URL dan Anon Key Anda:
   ```env
   SUPABASE_URL=https://xxxxxxxxxxxxxxxxxxxx.supabase.co
   SUPABASE_ANON_KEY=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...
   DEFAULT_APP_MODE=supabase
   ```
3. Jalankan perintah:
   ```bash
   python build_env.py
   # atau cukup jalankan: python generate_ino.py
   ```
4. Buka aplikasi di browser. Aplikasi akan otomatis mendeteksi kredensial dan langsung terhubung (**Badge `.env` Aktif**).
5. **Saat Deploy ke Netlify**: Di dashboard Netlify (*Site configuration > Environment variables*), masukkan `SUPABASE_URL` dan `SUPABASE_ANON_KEY`. Perintah build Netlify akan otomatis membaca variabel ini saat proses rilis berlangsung!

#### Opsi 2: Menggunakan Modal Pengaturan di Web App (Input Dinamis)
1. Buka Web App Smart Home di browser Anda.
2. Klik ikon **Pengaturan (Gear)** di kanan atas.
3. Tempelkan **Supabase Project URL** dan **Supabase Anon Key** pada input yang tersedia.
4. Pilih mode: **Supabase Realtime Cloud (Postgres)**.
5. Klik **Simpan Pengaturan**. Status koneksi akan langsung berubah menjadi hijau (**Terhubung ke Supabase**) dan tersimpan di `localStorage`.

---

## 🚀 Panduan Deploy Web App ke Netlify

Aplikasi ini adalah Static Web App murni (`index.html`) yang dapat di-hosting secara gratis, cepat, dan otomatis dengan SSL di **Netlify**:

### Opsi A: Deploy Otomatis via GitHub (Disarankan)
1. Push repository proyek ini ke GitHub Anda.
2. Masuk ke dashboard [Netlify](https://app.netlify.com).
3. Klik tombol **Add new site** > **Import an existing project**.
4. Pilih provider **GitHub** dan pilih repository `SmartHome_ESP32`.
5. Pengaturan build akan otomatis terdeteksi dari [netlify.toml](netlify.toml):
   - **Publish directory**: `.` (root direktori)
6. Klik **Deploy SmartHome_ESP32**. Dalam beberapa detik situs Anda akan live dengan domain `.netlify.app`!

### Opsi B: Deploy via Netlify CLI
Jika Anda ingin men-deploy langsung dari terminal komputer:
```bash
# 1. Pasang Netlify CLI secara global (jika belum ada)
npm install -g netlify-cli

# 2. Login ke akun Netlify Anda
netlify login

# 3. Deploy langsung ke produksi
netlify deploy --prod
```

### Opsi C: Otomatisasi CI/CD via GitHub Actions
Berkas workflow [.github/workflows/deploy_netlify.yml](.github/workflows/deploy_netlify.yml) telah disiapkan. Anda cukup menambahkan dua Secret di repository GitHub (*Settings > Secrets and variables > Actions*):
- `NETLIFY_AUTH_TOKEN`: Personal Access Token dari akun Netlify Anda.
- `NETLIFY_SITE_ID`: API ID dari situs Netlify Anda (*Site configuration > General > Site details*).

---

## 🛠️ Panduan Menjalankan & Simulasi (Mode Simulasi)

Aplikasi dirancang agar dapat langsung dibuka dan diuji coba tanpa ketergantungan perangkat keras:

### Opsi A: Langsung Buka di Browser (Offline Mock)
1. Cukup klik ganda berkas `index.html` pada File Explorer, atau klik kanan lalu pilih **Open with Live Server** di VS Code.
2. Web App akan mendeteksi lingkungan offline secara otomatis dan mengaktifkan **Mode Simulasi Virtual**.
3. Klik badge status **`Simulasi Virtual`** di header atau ikon chip mikro prosesor (`microchip`) untuk membuka **Virtual ESP32 Hardware Inspector**.
4. Anda dapat melihat status pinout menyala, mencoba sakelar lampu/AC/alarm, melihat log serial simulasi, dan mendengar suara sirene virtual.

---

## ⚙️ Menjalankan Firmware ESP32 (Lokal & Wokwi)

### 1. Sinkronisasi Kode Firmware
Setiap kali Anda memodifikasi tampilan pada `index.html`, jalankan skrip generator Python agar kode HTML disuntikkan ke firmware C++ `SmartHome_ESP32.ino`:
```bash
python generate_ino.py
```

### 2. Menjalankan di Simulator Wokwi
1. Buka VS Code dengan ekstensi Wokwi terpasang.
2. Buka `diagram.json` dan mulai simulasi (F1 > *Wokwi: Start Simulator*).
3. Buka browser komputer Anda di alamat `http://localhost:8080`.

---

## 📝 Catatan Rilis & Riwayat
Detail perubahan dan evolusi sistem terdokumentasi rapi pada berkas [CHANGELOG.md](CHANGELOG.md).
