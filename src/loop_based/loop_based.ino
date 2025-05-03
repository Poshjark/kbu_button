#include "Keyboard.h"

#define BUTTON_PIN 7

void setup() 
{
  // initialize control over the keyboard:
  Keyboard.begin();
  pinMode(BUTTON_PIN, INPUT);
}

// empirically established
const uint8_t K_key = 0x52;
const uint8_t B_key = 0x3C;
const uint8_t U_key = 0x45;
const uint8_t QUEST_key = 0x26;


constexpr auto KBU_PHRASE_LEN = 4ull;
const uint8_t KBU_PHRASE[KBU_PHRASE_LEN]
{
  K_key, B_key, U_key, QUEST_key
};

void PrintKey(uint8_t key)
{
  Keyboard.press(key);
  Keyboard.release(key);
}

void PrintKBU()
{
  for(unsigned long long i = 0; i < KBU_PHRASE_LEN; ++i)
  {
      PrintKey(KBU_PHRASE[i]);
      delay(20);
  }
}

namespace Executor
{
  struct State
  {
    using Type = uint8_t;
    enum : Type
    {
      // Waiting for button press
      Idle,
      // Performing printing
      Performing,
      // Waiting for button to release not to print multiple times in one long press.
      WaitingForButtonRelease
    };
  };
}

Executor::State::Type currentState{ Executor::State::Idle };

void loop() 
{
  // read result is non-zero when key is pressed
  const bool buttonIsPressed = !digitalRead(BUTTON_PIN);

  switch(currentState)
  {
    case Executor::State::Idle:
    {
      // If button is pressed in idle state, let's switch to performing state
      // to perform print next iteration
      if(buttonIsPressed)
      {
         currentState = Executor::State::Performing;
      }
      break;
    }
    case Executor::State::Performing:
    {
      PrintKBU();
      // To avoid multiple prints in one short press
      delay(200);
      // switching to next state to wait for button to release
      currentState = Executor::State::WaitingForButtonRelease;
      break;
    }
    case Executor::State::WaitingForButtonRelease:
    {
      // In this state we are waiting for the release only
      if(!buttonIsPressed)
      {
         currentState = Executor::State::Idle;
      }
      break;
    }
  }
}
