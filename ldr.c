#include <AntaresESP8266HTTP.h>
#include "MUX74HC4067.h"
#define ACCESSKEY "4398d61fc70bddcf:deccd923f2241613"
#define WIFISSID "SSID"
#define PASSWORD "coba123aja"

#define projectName "percobaan2"
#define deviceName "cobaaja"
//Antares
MUX74HC4067 mux(16, 5, 4, 0, 2);//GPIO di NodeMCU D0-5 menggunakan pin digital
unsigned int a, b, c, d, e, f, g, h, j, k, l, m, n, o, p, q, x;

byte prevState = 0;
int interval = 10000;
AntaresESP8266HTTP antares(ACCESSKEY);
void setup() {
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  //Debuging Antares
  Serial.begin(115200);
  while ( !Serial ) ;
  mux.signalPin(A0, INPUT, ANALOG);// z input analog di A0
  //Baudrate
}

void scanning()
{
  int data;
  for (byte i = 0; i < 16; ++i)//membaca dari chalnel 1 =0 sampai 15
  {
    data = mux.read(i);
    if ( i == 15 & data <= 200) {
      a = 0;
      Serial.println("Chanel 15 ON");
    }
    if ( i == 15 & data > 200)
    {
      a = 1;
      Serial.println("Chanel 15 OFF");
    }
    if ( i == 14 & data <= 200)
    {
      Serial.println("Chanel 14 ON");
      b = 0;
    }
    if ( i == 14 & data > 200)
    {
      b = 2;
      Serial.println("Chanel 14 OFF");
    }
    if ( i == 13 & data <= 200)
    {
      c = 0;
      Serial.println("Chanel 13 ON");
    }
    if ( i == 13 & data > 200)
    {
      c = 4;
      Serial.println("Chanel 13 OFF");
    }
    if ( i == 12 & data <= 200)
    {
      d = 0;
      Serial.println("Chanel 12 ON");
    }
    if ( i == 12 & data > 200)
    {
      d = 8;
      Serial.println("Chanel 12 OFF");
    }
    if ( i == 11 & data <= 200)
    {
      e = 0;
      Serial.println("Chanel 11 ON");
    }
    if ( i == 11 & data > 200)
    {
      e = 16;
      Serial.println("Chanel 11 OFF");
    }
    if ( i == 10 & data <= 200)
    {
      f = 0;
      Serial.println("Chanel 10 ON");
    }
    if ( i == 10 & data > 200)
    {
      f = 32;
      Serial.println("Chanel 10 OFF");
    }
    if ( i == 9 & data <= 200)
    {
      g = 0;
      Serial.println("Chanel 9 ON");
    }
    if ( i == 9 & data > 200)
    {
      g = 64;
      Serial.println("Chanel 9 OFF");
    }
    if ( i == 8 & data <= 200)
    {
      h = 0;
      Serial.println("Chanel 8 ON");
    }
    if ( i == 8 & data > 200)
    {
      h = 128;
      Serial.println("Chanel 8 OFF");
    }
    if ( i == 7 & data <= 200)
    {
      j = 0;
      Serial.println("Chanel 7 ON");
    }
    if ( i == 7 & data > 200)
    {
      j = 256;
      Serial.println("Chanel 7 OFF");
    }
    if ( i == 6 & data <= 200)
    {
      k = 0;
      Serial.println("Chanel 6 ON");
    }
    if ( i == 6 & data > 200)
    {
      k = 512;
      Serial.println("Chanel 6 OFF");
    }
    if ( i == 5 & data <= 200)
    {
      l = 0;
      Serial.println("Chanel 5 ON");
    }
    if ( i == 5 & data > 200)
    {
      l = 1024;
      Serial.println("Chanel 5 OFF");
    }
    if ( i == 4 & data <= 200)
    {
      m = 0;
      Serial.println("Chanel 4 ON");
    }
    if ( i == 4 & data > 200)
    {
      m = 2048;
      Serial.println("Chanel 4 OFF");
    }
    if ( i == 3 & data <= 200)
    {
      n = 0;
      Serial.println("Chanel 3 ON");
    }
    if ( i == 3 & data > 200)
    {
      n = 4096;
      Serial.println("Chanel 3 OFF");
    }
    if ( i == 2 & data <= 200)
    {
      o = 0 ;
      Serial.println("Chanel 2 ON");
    }

    if ( i == 2 & data > 200)
    {
      o = 8192;
      Serial.println("Chanel 2 OFF");
    }
    if ( i == 1 & data <= 200)
    {
      p = 0 ;
      Serial.println("Chanel 1 ON");
    }
    if ( i == 1 & data > 200)
    {
      p = 16384;
      Serial.println("Chanel 1 OFF");
    }
    if ( i == 0 & data <= 200)
    {
      q = 0 ;
      Serial.println("Chanel 0 ON");
    }
    if ( i == 0 & data > 200)
    {
      q = 32768;
      Serial.println("Chanel 1 OFF");
    }
  }
  x = a + b + c + d + e + f + g + h + j + k + l + m + n + o + p + q;
  Serial.println("Nilai X adalah :" + String(x));
  Serial.println();
}
void loop()
{
  scanning();
  Serial.println("Lagi Nyecan");
  Serial.println("Data Send");
  Serial.println("X Value:" + String(x));
  int sizeData = 1;
  String dataName[sizeData], dataValue[sizeData];
  dataName[0] = "nilai x";
  dataValue[0] = (unsigned int)x;
  Serial.println(antares.storeData(projectName, deviceName, dataName, dataValue, sizeData));
  Serial.println("\n looping 3 milidetik untuk mengcompare datat\n\n");
  delay(3000);
}
