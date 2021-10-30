#include <Arduino.h>
#include <WiFi.h>
#include "Audio.h"

// Config
#define LILYGO_WATCH_2020_V3 // To use T-Watch2020 V3, please uncomment this line
#include <LilyGoWatch.h>

TTGOClass *watch;
TFT_eSPI *tft;

// Pinos de conexão do ESP32-I2S e o módulo I2S/DAC CJMCU 1334
#define I2S_DOUT 33
#define I2S_BCLK 26
#define I2S_LRC 25

// Cria o objeto que representará o áudio
Audio audio;

// Wi-Fi ssid and password
const char *ssid = "ssid";
const char *password = "password";

void startTwatch()
{
  watch = TTGOClass::getWatch(); // Get TTGOClass instance
  watch->begin();                // Initialize the hardware
  watch->openBL();               // Turn on the backlight
  tft = watch->tft;              // Receive objects for easy writing
  tft->setTextFont(2);
}

void startWifi()
{
  tft->print("Wifi ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    tft->print(".");
    delay(1000);
  }
  tft->println(" conectado");
  tft->println("Watch IP address: ");
  tft->println(WiFi.localIP());
}

void audio_eof_speech(const char *info)
{
  tft->println("speech:");
  tft->println(info);
}

void setup()
{
  startTwatch();
  startWifi();

  // Ajusta os pinos de conexão I2S
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);

  // Ajusta o volume de saída
  audio.setVolume(21); // 0...21

  tft->setTextColor(0x03EF, 0x0000);
  tft->println(" conectando com Google...");
  audio.connecttospeech("parabéns. conexão okey. transcrição de texto okey. protocolo i2s okey", "pt");
}

void loop()
{
  audio.loop(); // Executa o loop interno da biblioteca audio
}
