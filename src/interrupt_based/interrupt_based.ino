/*
*     VERY IMPORTANT:
*     COMPILE AND DEPLOY PROJECT WITH "Arduino Micro" BOARD CHOSEN
*     OTHERWISE YOUR BOARD HID-FUNCTIONALITY CAN BE TURNED OFF BECAUSE OF USING
*     HID-RESERVED PINS.
*     Or just use right pin:)
*
*/

#include "Keyboard.h"

#define BUTTON_PIN 7

constexpr unsigned long long debounceDelay = 100ul;

volatile unsigned long long lastInterrupt{0};
volatile bool buttonPressed {false};
volatile uint8_t currentTypeStep{0};

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


void InterruptHandler()
{
  // just software debounce
  const auto now = millis();
  if((now - lastInterrupt) < debounceDelay)
  {
    return;
  }

  lastInterrupt = now;
  buttonPressed = true;
}

void setup() 
{
  // initialize control over the keyboard:
  Keyboard.begin();

  // Initialize key pin mode
  pinMode(BUTTON_PIN, INPUT);

  // Initializing last print timestamp for using in software debounce
  // The hardware debounce is implemented by external pullup resistor but we are paranoids...
  lastInterrupt = 0;

  // IMPORTANT(again): CHOOSE RIGHT BOARD 
  // Attaching function to hardware interruption
  // on LOW because:
  // * When key is not pressed current flows to BUTTON_PIN and voltage there is HIGH(non-zero)
  // * When key IS pressed current flows to the ground and voltage on BUTTON_PIN is LOW
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), InterruptHandler, LOW);
}

void PrintKey(uint8_t key)
{
  Keyboard.press(key);
  Keyboard.release(key);
}

void TryPerformKBUprintStep()
{
  if(buttonPressed)
  {
    PrintKey(KBU_PHRASE[currentTypeStep]);

    if(++currentTypeStep >= KBU_PHRASE_LEN)
    {
      currentTypeStep = 0;
      buttonPressed = false;
    }
  }
}

void loop() 
{
  TryPerformKBUprintStep();
  delay(20);
}
