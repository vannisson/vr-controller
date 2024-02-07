const byte led_red = 32;
const byte led_green = 33;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // for (int i = 0; i<256; i++){
  //   analogWrite(led_green, i);
  //   delay(50);
  // }
  digitalWrite(led_red, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(led_green, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  digitalWrite(led_red, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(led_green, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
}