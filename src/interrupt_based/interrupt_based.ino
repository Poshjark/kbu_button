#include "Keyboard.h"

#define KEY_PIN 7

volatile unsigned long LastPrint{0};

const uint8_t K_key = 82;
const uint8_t B_key = 60;
const uint8_t U_key = 69;
const uint8_t QUEST_key = 38;


constexpr auto KBU_PHRASE_LEN = 4ull;
const uint8_t KBU_PHRASE[KBU_PHRASE_LEN]
{
  K_key, B_key, U_key, QUEST_key
};

void PrintKBU()
{
  const auto now = millis();
  if((now - LastPrint) < 100)
  {
    return;
  }
  for(unsigned long long i = 0; i < KBU_PHRASE_LEN; ++i)
  {
      Keyboard.press(KBU_PHRASE[i]);
      Keyboard.release(KBU_PHRASE[i]);

      // Optional sleep. It's highly recommended not to "sleep" in interruptions
      // but some usb drivers may skip some signals
      //delay(5);
  }

  LastPrint = now;
}
void setup() 
{
  // initialize control over the keyboard:
  Keyboard.begin();

  // Initialize key pin mode
  pinMode(KEY_PIN, INPUT);

  // Initializing last print timestamp for using in soft switch bounce fix
  // There will be hard fix but we are paranoids...
  LastPrint = 0;

  // Attaching function to hardware interruption
  // on LOW because:
  // * When key is not pressed current flows to KEY_PIN and voltage there is HIGH(non-zero)
  // * When key IS pressed current flows to the ground and voltage on KEY_PIN is LOW

  attachInterrupt(0, PrintKBU, LOW);

}

void loop() 
{
  // It would be great to turn device into deep sleep here
  // but there is no reason to do it because device will always be powered from the PC
}
