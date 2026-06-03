# 🐔 Smart Chicken Coop Monitoring System

Sistem Monitoring dan Otomatisasi Kandang Ayam Pintar menggunakan **ESP8266**, **DHT22**, **MQ-135**, **Servo Motor**, dan **Blynk IoT Platform**.

## 📌 Deskripsi Proyek

Proyek ini dirancang untuk memonitor kondisi lingkungan kandang ayam secara real-time dan melakukan pengendalian otomatis terhadap sistem pemanas serta ventilasi berdasarkan data sensor.

Parameter yang dipantau:

* Suhu udara (°C)
* Kelembapan udara (%)
* Kadar gas amonia (indikasi kualitas udara)

Data sensor dikirim ke aplikasi **Blynk** sehingga pengguna dapat memantau kondisi kandang dari smartphone secara online.

---

## 🎯 Fitur Utama

### 🌡 Monitoring Suhu dan Kelembapan

Menggunakan sensor DHT22 untuk membaca:

* Suhu kandang
* Kelembapan kandang

Data ditampilkan pada aplikasi Blynk secara real-time.

### 💡 Kontrol Otomatis Lampu Pemanas

Sistem akan menyalakan lampu pemanas apabila:

Suhu < 25°C

dan akan mematikannya secara otomatis apabila suhu telah mencapai batas yang ditentukan.

### 🌬 Ventilasi Otomatis

Menggunakan sensor MQ-135 untuk mendeteksi kualitas udara.

Ventilasi akan terbuka apabila:

Nilai MQ-135 > 420

Servo akan bergerak ke posisi 90° untuk membuka ventilasi dan kembali ke 0° saat kondisi udara normal.

### 📱 Monitoring Jarak Jauh

Semua data dapat dipantau melalui aplikasi Blynk:

* Suhu
* Kelembapan
* Kadar gas
* Status lampu
* Status ventilasi

### 🔄 Mode Offline

Apabila koneksi internet terputus:

* Sistem kontrol lokal tetap berjalan.
* Lampu dan ventilasi tetap bekerja berdasarkan sensor.
* Data tidak dikirim ke Blynk sampai koneksi kembali tersedia.

---

## 🛠 Hardware yang Digunakan

| Komponen                | Jumlah |
| ----------------------- | ------ |
| ESP8266 NodeMCU         | 1      |
| Sensor DHT22            | 1      |
| Sensor MQ-135           | 1      |
| Servo SG90              | 1      |
| Relay Module            | 1      |
| Lampu Pemanas           | 1      |
| Smartphone dengan Blynk | 1      |

---

## 🔌 Konfigurasi Pin

| Komponen        | Pin ESP8266 |
| --------------- | ----------- |
| DHT22           | D4          |
| MQ-135          | A0          |
| Relay Lampu     | D1          |
| Servo Ventilasi | D2          |

---

## ⚙️ Logika Sistem

### Lampu Pemanas

```text
IF Suhu < 25°C
    Lampu ON
ELSE
    Lampu OFF
```

### Ventilasi

```text
IF MQ135 > 420
    Ventilasi BUKA
ELSE
    Ventilasi TUTUP
```

---

## 📲 Konfigurasi Blynk

### Virtual Pin

| Virtual Pin | Fungsi           |
| ----------- | ---------------- |
| V0          | Suhu             |
| V1          | Kelembapan       |
| V2          | Kadar Gas        |
| V3          | Status Lampu     |
| V4          | Status Ventilasi |

---

## 🚀 Cara Menjalankan

### 1. Install Library Arduino

Pastikan library berikut telah terpasang:

* ESP8266WiFi
* Blynk
* DHT Sensor Library
* Servo

### 2. Konfigurasi WiFi

Ubah bagian berikut sesuai jaringan WiFi yang digunakan:

```cpp
char ssid[] = "Nama_WiFi";
char pass[] = "Password_WiFi";
```

### 3. Konfigurasi Blynk

Masukkan Template ID dan Auth Token dari dashboard Blynk:

```cpp
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
```

### 4. Upload Program

* Pilih Board ESP8266 NodeMCU
* Hubungkan perangkat ke komputer
* Upload sketch menggunakan Arduino IDE

### 5. Monitoring

Buka aplikasi Blynk dan pantau data secara real-time.

---

## 📊 Output Serial Monitor

Contoh output:

```text
[DATA] Suhu=27.5 C | Kelembapan=71.2 % | Amonia=385 | Lampu=OFF | Ventilasi=TUTUP | Blynk=OK

[LAMPU] ON | Suhu = 23.8 C

[VENTILASI] BUKA | Amonia = 460
```

---

## 🏗 Arsitektur Sistem

```text
DHT22 ----------\
                 \
                  --> ESP8266 --> Blynk Cloud --> Smartphone
                 /
MQ135 ----------/

ESP8266 --> Relay --> Lampu Pemanas

ESP8266 --> Servo --> Ventilasi
```

---

## 📈 Pengembangan Selanjutnya

Beberapa fitur yang dapat ditambahkan:

* Notifikasi Telegram
* Notifikasi WhatsApp
* Monitoring konsumsi daya listrik
* Penyimpanan data ke database
* Dashboard Web Monitoring
* Kontrol manual lampu dan ventilasi melalui aplikasi

---

## 👨‍💻 Author

**Muhammad Fadhel Saputra**

Program Studi Teknik Informatika

Universitas Lampung

2026
