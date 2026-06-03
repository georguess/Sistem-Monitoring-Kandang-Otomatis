
#define BLYNK_TEMPLATE_ID "TMPL6BGFKJ4yJ"
#define BLYNK_TEMPLATE_NAME "UAP"
#define BLYNK_AUTH_TOKEN    "Ycg8Qal5XmEGRKflYTI4ihXRQWQitbNN"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Servo.h>

// ================= WIFI =================
char ssid[] = "andyfhome";       // ganti dengan nama WiFi kamu
char pass[] = "0606f@iz";   // ganti dengan password WiFi kamu

// ================= PIN ==================
#define DHT_PIN      D4
#define DHT_TYPE     DHT22

#define MQ135_PIN    A0          // sensor amonia (analog)

#define LED_PIN      D1          // sinyal ke relai lampu pemanas
#define SERVO_PIN    D2          // servo ventilasi

// =============== THRESHOLD ==============
#define TEMP_THRESHOLD  25.0
#define GAS_THRESHOLD   420
// =============== INTERVAL ===============
#define SEND_INTERVAL   2000     // ms

DHT dht(DHT_PIN, DHT_TYPE);
Servo ventServo;
BlynkTimer timer;

bool ledState  = false;
bool servoOpen = false;

void readAndControl()
{
  float temp  = dht.readTemperature();
  float humid = dht.readHumidity();

  if (isnan(temp) || isnan(humid))
  {
    Serial.println("[DHT] Gagal membaca sensor - cek wiring & pin D4");
    return;
  }

  int gasRaw = analogRead(MQ135_PIN);

  // ===== KONTROL LAMPU PEMANAS =====
  bool newLed = (temp < TEMP_THRESHOLD);
  if (newLed != ledState)
  {
    ledState = newLed;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    Serial.printf("[LAMPU] %s | Suhu = %.1f C\n", ledState ? "ON" : "OFF", temp);
  }

  // ===== KONTROL VENTILASI (SERVO) =====
  bool newServo = (gasRaw > GAS_THRESHOLD);
  if (newServo != servoOpen)
  {
    servoOpen = newServo;
    ventServo.write(servoOpen ? 90 : 0);
    Serial.printf("[VENTILASI] %s | Amonia = %d\n", servoOpen ? "BUKA" : "TUTUP", gasRaw);
  }

  // ===== KIRIM DATA KE BLYNK  =====
  if (Blynk.connected())
  {
    Blynk.virtualWrite(V0, temp);
    Blynk.virtualWrite(V1, humid);
    Blynk.virtualWrite(V2, gasRaw);
    Blynk.virtualWrite(V3, ledState ? 1 : 0);
    Blynk.virtualWrite(V4, servoOpen ? "BUKA" : "TUTUP");
  }

  // ===== LOG KE SERIAL MONITOR =====
  Serial.printf(
    "[DATA] Suhu=%.1f C | Kelembapan=%.1f %% | Amonia=%d | Lampu=%s | Ventilasi=%s | Blynk=%s\n",
    temp, humid, gasRaw,
    ledState ? "ON" : "OFF",
    servoOpen ? "BUKA" : "TUTUP",
    Blynk.connected() ? "OK" : "OFF"
  );
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println("==================================");
  Serial.println(" MONITORING KANDANG AYAM PINTAR ");
  Serial.println("==================================");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();

  ventServo.attach(SERVO_PIN);
  ventServo.write(0);              
  Serial.print("Menghubungkan ke WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  Blynk.config(BLYNK_AUTH_TOKEN);

  unsigned long mulai = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - mulai < 10000)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("[WiFi] Terhubung.");
    Blynk.connect(5000);   
  }
  else
  {
    Serial.println("[WiFi] Gagal konek. Sistem jalan OFFLINE (kontrol lokal tetap aktif).");
  }

  timer.setInterval(SEND_INTERVAL, readAndControl);

  Serial.println("Sistem siap...");
}

void loop()
{
  Blynk.run();    
  timer.run();
}