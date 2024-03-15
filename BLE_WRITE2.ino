#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
int txValue = 0;
int enable = false;

/*
UUID's For Identification and Services

  SERVICE:  fc86179e-1f30-47ce-af40-06c10b45688c

  TX:       731fdd3b-76be-4ad3-b13d-5a12f56726c2

  RX:       cd7ecb5b-4a6b-481b-8696-8011b7e1d516
*/

// Define the Service, TX ,and RX for use in program
#define SERVICE_UUID "fc86179e-1f30-47ce-af40-06c10b45688c"
#define CHARACTERISTIC_UUID_TX "731fdd3b-76be-4ad3-b13d-5a12f56726c2"
#define CHARACTERISTIC_UUID_RX "cd7ecb5b-4a6b-481b-8696-8011b7e1d516"

#define LED_BUILTIN 2
#define STARTER 4
#define ON_CNTRL 5
#define CLUTCH_CANCEL 16

// For connected or not status
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) { enable = true; }
  void onDisconnect(BLEServer *pServer) { enable = false; }
};
// For managing input or output
class MyCallbacks : public BLECharacteristicCallbacks {

  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();
    // if info is received
    if (rxValue.length() > 0) {
      // if value is 1 or 0
      if (rxValue.find("1") != -1) {
        // if is 1 light on
        digitalWrite(LED_BUILTIN, HIGH);
      } else if (rxValue.find("0") != -1) {
        // if is 0 light off
        digitalWrite(LED_BUILTIN, LOW);
      }
      if(rxValue.find("6") != -1){
        enable == true;
      }
      if(rxValue.find("4") != -1){
        enable == false;
      }
      if (rxValue.find("8") != -1 && enable == true) {
        digitalWrite(ON_CNTRL,HIGH);
        digitalWrite(CLUTCH_CANCEL, HIGH);
        delay(20);
        digitalWrite(STARTER, HIGH);
        delay(3000);
        digitalWrite(CLUTCH_CANCEL, LOW);
        digitalWrite(STARTER, LOW);
      }
    }
  }
};

void setup() {
  // provide debug info by the Serial Monitor
  Serial.begin(115200);
  // Set the pin modes to allow controls
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(STARTER, OUTPUT);
  pinMode(CLUTCH_CANCEL, OUTPUT);
  pinMode(ON_CNTRL,OUTPUT);

  // Create the BLE device
  BLEDevice::init("ENG_START"); // Bluetooth Name

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create BLE Characteristics
  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks());

  // BLE2902 used to notify
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start Advertising
  pServer->getAdvertising()->start();
}

void loop() {
  if (deviceConnected) {
    // Set value to characteristic
    pCharacteristic->setValue("01");

    // Notify the client
    pCharacteristic->notify();
    delay(1500);
  }
}