#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
bool led = 0;
int fan_l = 25;
int fan_r = 26;
int relay_signal = 32;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(fan_l, OUTPUT);
  pinMode(fan_r, OUTPUT);
  pinMode(relay_signal, OUTPUT);
  digitalWrite(fan_l, LOW);
  digitalWrite(fan_r, HIGH);
}

void loop() {
  byte c;
  while ( !SerialBT.available() ) ;
  c = SerialBT.read();
  if (c == '1') {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(relay_signal, HIGH);
    //    delay(2000);
  }
  if (c == '0') {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(relay_signal, LOW);
    //    delay(2000);
  }

}
