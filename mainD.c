#define LED_BUILTIN 2 // Define the GPIO pin for the built-in LED. May need to adjust based on your ESP32 board.

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED pin as an output
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
  delay(1000); // Wait for a second
  digitalWrite(LED_BUILTIN, LOW); // Turn the LED off
  delay(1000); // Wait for a second
}
