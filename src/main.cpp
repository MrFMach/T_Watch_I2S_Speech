#include <Arduino.h>
#include <WiFi.h>
#include "Audio.h"

// T-Watch config
#define LILYGO_WATCH_2020_V3
#include <LilyGoWatch.h>

TTGOClass *watch;
TFT_eSPI *tft;

//I2S T-Watch connection
#define I2S_DOUT 33
#define I2S_BCLK 26
#define I2S_LRC 25

// audio object create
Audio audio;

// Wi-Fi ssid and password
const char *ssid = "your ssid";
const char *password = "your password";

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

  // Set I2S pinout
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);

  // Set volume
  audio.setVolume(12); // 0...21

  tft->setTextFont(2);
  tft->setTextColor(0x03EF, 0x0000);
  tft->println(" conectando com Google...");
  audio.connecttospeech("parabéns. conexão okey. texto para fala okey. protocolo i2s okey", "pt");
}

void loop()
{
  audio.loop();
}
