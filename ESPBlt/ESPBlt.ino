// Please support Youtube Channel ADSP
// https://www.youtube.com/channel/UCaFqpdENcVNK2Zn4qY-vOzQ
// VIDEO TUTOR: https://youtu.be/dzrSM-cvhgM
// GITHUB: https://github.com/adsp17/ESP32-Wifi-Bluetooth

#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
const int led1 = 2;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_LED");
  Serial.println("Bluetooth aktif. Pair dengan 'ESP32_BT_LED'");
  pinMode(led1, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    Serial.print("Diterima: ");
    Serial.println(command);

    switch (command) {
      case '1':
        digitalWrite(led1, HIGH);
        break;
      case '0':
        digitalWrite(led1, LOW);
        break;
      default:
        Serial.println("Perintah tidak dikenal");
    }
  }
}
