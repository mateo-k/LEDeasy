#include <LEDeasy.h>

LEDeasy led_builtin(LED_BUILTIN);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  led_builtin.off();
  led_builtin.blink_med();
}

void loop() {
  // put your main code here, to run repeatedly:
  led_builtin.update();
}
