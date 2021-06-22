//Declerations
int R1 = 19;
int R2 = 18;
int enR = 26;
int L1 = 17;
int L2 = 16;
int enL = 27;
String message = "";

//Setting PWM properties
const int freq = 30000;
const int leftChannel = 0;
const int rightChannel = 1;
const int resolution = 8;
int dutyCycle = 210;

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enRbled! Please run `make menuconfig` to and enRble it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.register_callback(callback);
  SerialBT.begin("Firefly");
  //Right setup
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(enR, OUTPUT);
  //Left setup
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(enL, OUTPUT);
  //Set channels
  ledcSetup(leftChannel, freq, resolution);
  ledcSetup(rightChannel, freq, resolution);
  //Attach pins
  ledcAttachPin(enR, rightChannel);
  ledcAttachPin(enL, leftChannel);
}

void MotorRForward() {
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  ledcWrite(rightChannel, dutyCycle);
}

void MotorRReverse() {
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  ledcWrite(rightChannel, dutyCycle);
}

void MotorROff() {
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
}

void MotorLForward() {
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  ledcWrite(leftChannel, dutyCycle);
}

void MotorLReverse() {
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  ledcWrite(leftChannel, dutyCycle);
}

void MotorLOff() {
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
}

void TurnLeft() {
  MotorLOff();
  MotorRForward();
}

void TurnRight() {
  MotorROff();
  MotorLForward();
}

void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_CLOSE_EVT ) {
    MotorROff();
    MotorLOff();
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
      MotorRForward();
      MotorLForward();
    }
    else if (message == "b") {
      MotorRReverse();
      MotorLReverse();
    }
    else if (message == "s") {
      MotorROff();
      MotorLOff();
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
