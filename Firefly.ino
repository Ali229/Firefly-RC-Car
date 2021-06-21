int IN1 = 19;
int IN2 = 18;
int IN3 = 17;
int IN4 = 16;
String message = "";

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.register_callback(callback);
  SerialBT.begin("Firefly");
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void Motor1Forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void Motor1Reverse() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void Motor1Off() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void Motor2Forward() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Motor2Reverse() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void Motor2Off() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void TurnLeft() {
  Motor2Off();
  Motor1Forward();
}

void TurnRight() {
  Motor1Off();
  Motor2Forward();
}

void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_CLOSE_EVT ) {
    Motor1Off();
    Motor2Off();
  }
}

void loop() {
  if (SerialBT.available()) {
    char value = SerialBT.read();
    if (value != '\n') {
      message += String(value);
    }
    else {
      message = "";
    }
    if (message == "f") {
      Motor1Forward();
      Motor2Forward();
    }
    else if (message == "b") {
      Motor1Reverse();
      Motor2Reverse();
    }
    else if (message == "s") {
      Motor1Off();
      Motor2Off();
    }
    else if (message == "r") {
      TurnRight();
    }
    else if (message == "l") {
      TurnLeft();
    }
  }
  delay(20);
}
