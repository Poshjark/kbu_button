#include "Keyboard.h"

#define KEY_PIN 7

void setup() 
{
  // initialize control over the keyboard:
  //Keyboard.begin();
  pinMode(KEY_PIN, INPUT);
}

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
  for(unsigned long long i = 0; i < KBU_PHRASE_LEN; ++i)
  {
      Keyboard.press(KBU_PHRASE[i]);
      Keyboard.release(KBU_PHRASE[i]);
  }
}

bool keyUp{false};

void loop() 
{
  // read result is non-zero when key is pressed
  if(!digitalRead(KEY_PIN))
  {
    PrintKBU();

    // To avoid multiple prints in one short press
    delay(200);
  }

  delay(20);
}
