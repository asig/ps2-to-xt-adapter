/*
 * Convert PS/2 keyboard to IBM PC/XT keyboard.
 * 
 * Copyright (c) 2018 Andreas Signer <asigner@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// comment out the following define if you're not running this on
// an attiny85, maybe because you need debugging output.
#define ATTINY85



#ifdef ATTINY85

// ------------------------------------------
// -- Set up for ATtiny85

// No debugging available on an attiny
#undef DEBUG

// PS/2 pins
#define P_PS2_CLK  4
#define P_PS2_DATA 3

// PC pins
#define P_PC_CLK  1
#define P_PC_DATA 2

#define LED 0

#else

// ------------------------------------------
// -- Set up for anythinbg else

#define DEBUG

// PS/2 pins
#define P_PS2_CLK  3
#define P_PS2_DATA 2

// XT pins
#define P_PC_CLK  4
#define P_PC_DATA 5

#define LED 13

#endif



// PS/2 commands
#define PS2_CMD_RESET                               0xff
#define PS2_CMD_RESEND                              0xfe
#define PS2_CMD_SET_KEY_TYPE_MAKE                   0xfd  // (Set Key Type Make) - Disable break codes and typematic repeat for specified keys.  Keyboard responds with "ack" (0xFA), then disables scanning (if enabled) and reads a list of keys from the host.  These keys are specified by their set 3 make codes.  Keyboard responds to each make code with "ack".  Host terminates this list by sending an invalid set 3 make code (eg, a valid command.)  The keyboard then re-enables scanning (if previously disabled).
#define PS2_CMD_SET_KEY_TYPE_MAKE_BREAK             0xfc  // (Set Key Type Make/Break) - Similar to previous command, except this one only disables typematic repeat.
#define PS2_CMD_SET_KEY_TYPE_TYPEMATIC              0xfb  // (Set Key Type Typematic) - Similar to previous two, except this one only disables break codes.
#define PS2_CMD_SET_ALL_KEYS_TYPEMATIC_MAKE_BREAK   0xfa  // (Set All Keys Typematic/Make/Break) - Keyboard responds with "ack" (0xFA).  Sets all keys to their normal setting (generate scan codes on make, break, and typematic repeat)
#define PS2_CMD_SET_ALL_KEYS_MAKE                   0xf9  // (Set All Keys Make) - Keyboard responds with "ack" (0xFA).  Similar to 0xFD, except applies to all keys.
#define PS2_CMD_SET_ALL_KEYS_MAKE_BREAK             0xf8  // (Set All Keys Make/Break) - Keyboard responds with "ack" (0xFA).  Similar to 0xFC, except applies to all keys.
#define PS2_CMD_SET_ALL_KEYS_TYPEMATIC              0xf7  // (Set All Keys Typematic) - Keyboard responds with "ack" (0xFA).  Similar to 0xFB, except applies to all keys.
#define PS2_CMD_SET_DEFAULTS                        0xf6  // (Set Default) - Load default typematic rate/delay (10.9cps / 500ms), key types (all keys typematic/make/break), and scan code set (2).
#define PS2_CMD_DISABLE                             0xf5  // (Disable) - Keyboard stops scanning, loads default values (see "Set Default" command), and waits further instructions.
#define PS2_CMD_ENABLE                              0xf4  // (Enable) - Re-enables keyboard after disabled using previous command.
#define PS2_CMD_SET_TYPEMATIC_RATE_DELAY            0xf3  // (Set Typematic Rate/Delay) - Host follows this command with one argument byte that defines the typematic rate and delay as follows:
#define PS2_CMD_READ_ID                             0xf2  // (Read ID) - The keyboard responds by sending a two-byte device ID of 0xAB, 0x83. (0xAB is sent first, followed by 0x83.)
#define PS2_CMD_SET_SCANCODE_SET                    0xf0  // (Set Scan Code Set) -  Keyboard responds with "ack", then reads argument byte from the host.  This argument byte may be 0x01, 0x02, or 0x03 to select scan code set 1, 2, or 3, respectively.  The keyboard responds to this argument byte with "ack".  If the argument byte is 0x00, the keyboard responds with "ack" followed by the current scan code set.
#define PS2_CMD_ECHO                                0xee  // (Echo) - The keyboard responds with "Echo" (0xEE).
#define PS2_CMD_SET_RESET_LEDS                      0xed  // (Set/Reset LEDs) - The host follows this command with one argument byte, that specifies the state of the keyboard's Num Lock, Caps Lock, and Scroll Lock LEDs.  This argument byte is defined as follows:


// PS/2 special scan codes from Set 2
#define PS2_SET2_SCAN_CODE_CAPS   0x58
#define PS2_SET2_SCAN_CODE_SCROLL 0x7e
#define PS2_SET2_SCAN_CODE_NUM    0x77

// PS/2 LEDs
#define PS2_LED_SCROLL_LOCK 0
#define PS2_LED_NUM_LOCK    1
#define PS2_LED_CAPS_LOCK   2

// PS/2 responses
#define PS2_ACK    0xfa
#define PS2_BAT_OK 0xaa

// PS/2 Data masks
#define PS2_MASK_Y_SIGN (1<<5)
#define PS2_MASK_X_SIGN (1<<4)
#define PS2_MASK_MMB (1<<2)
#define PS2_MASK_RMB (1<<1)
#define PS2_MASK_LMB (1<<0)


const uint8_t mapping[] PROGMEM = {
    0x00,0x43,0x00,0x3F,0x3D,0x3B,0x3C,0x58,0x00,0x44,0x42,0x40,0x3E,0x0F,0x29,0x00,
    0x00,0x38,0x2A,0x00,0x1D,0x10,0x02,0x00,0x00,0x00,0x2C,0x1F,0x1E,0x11,0x03,0x00,
    0x00,0x2E,0x2D,0x20,0x12,0x05,0x04,0x00,0x00,0x39,0x2F,0x21,0x14,0x13,0x06,0x00,
    0x00,0x31,0x30,0x23,0x22,0x15,0x07,0x00,0x00,0x00,0x32,0x24,0x16,0x08,0x09,0x00,
    0x00,0x33,0x25,0x17,0x18,0x0B,0x0A,0x00,0x00,0x34,0x35,0x26,0x27,0x19,0x0C,0x00,
    0x00,0x00,0x28,0x00,0x1A,0x0D,0x00,0x00,0x3A,0x36,0x1C,0x1B,0x00,0x2B,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x4F,0x00,0x4B,0x47,0x00,0x00,0x00,
    0x52,0x53,0x50,0x4C,0x4D,0x48,0x01,0x45,0x57,0x4E,0x51,0x4A,0x37,0x49,0x46,0x00
};

const uint8_t mappingE0[] PROGMEM = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x65,0x38,0x2A,0x00,0x1D,0x10,0x00,0x00,0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x5B,
    0x67,0x2E,0x00,0x20,0x00,0x00,0x00,0x5C,0x68,0x00,0x00,0x21,0x00,0x00,0x00,0x5D,
    0x69,0x00,0x30,0x00,0x22,0x00,0x00,0x5E,0x6A,0x00,0x32,0x24,0x00,0x00,0x00,0x5F,
    0x6B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6C,0x00,0x35,0x00,0x00,0x19,0x00,0x00,
    0x6D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x00,0x63,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4F,0x00,0x4B,0x47,0x00,0x00,0x00,
    0x52,0x53,0x50,0x00,0x4D,0x48,0x00,0x00,0x00,0x00,0x51,0x00,0x37,0x49,0x00,0x00
};

const byte oddParityTable[256] PROGMEM = {
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1  
};

int leds = 0;
int pressed = 0;

static inline int sgn(int val) {
  return (val < 0) ? -1 : ((val > 0) ? 1 : 0);
}

void waitPin(int pin, int val) {
  while(digitalRead(pin) != val);
}

void ps2Send(byte val) {
  #ifdef DEBUG
  Serial.print("--> PS/2: 0x");
  Serial.println(val, HEX);
  #endif

  pinMode(P_PS2_CLK, OUTPUT);  
  pinMode(P_PS2_DATA, OUTPUT);
 
  byte parityBit = pgm_read_byte(&oddParityTable[val]);
  
  // From http://www.computer-engineering.org/ps2protocol/

  // 1)   Bring the Clock line low for at least 100 microseconds. 
  digitalWrite(P_PS2_CLK, LOW);
  delayMicroseconds(110);
  
  // 2)   Bring the Data line low. 
  digitalWrite(P_PS2_DATA, LOW);

  // 3)   Release the Clock line. 
  digitalWrite(P_PS2_CLK, HIGH);
  pinMode(P_PS2_CLK, INPUT_PULLUP);  

  // 4)   Wait for the device to bring the Clock line low. 
  waitPin(P_PS2_CLK, LOW);

  for (int i = 0; i < 8; i++) {
    // 5)   Set/reset the Data line to send the first data bit 
    digitalWrite(P_PS2_DATA, val & 1);
    val = val >> 1;

    // 6)   Wait for the device to bring Clock high. 
    waitPin(P_PS2_CLK, HIGH);
    
    // 7)   Wait for the device to bring Clock low. 
    waitPin(P_PS2_CLK, LOW);

    // 8)   Repeat steps 5-7 for the other seven data bits and the parity bit     
  }
  digitalWrite(P_PS2_DATA, parityBit);
  waitPin(P_PS2_CLK, HIGH);
  waitPin(P_PS2_CLK, LOW);

  // 9)   Release the Data line. 
  digitalWrite(P_PS2_DATA, HIGH);
  pinMode(P_PS2_DATA, INPUT_PULLUP);

  // 10) Wait for the device to bring Data low. 
  waitPin(P_PS2_DATA, LOW);

  // 11) Wait for the device to bring Clock  low. 
  waitPin(P_PS2_CLK, LOW);

  // 12) Wait for the device to release Data and Clock
  waitPin(P_PS2_DATA, HIGH);
  waitPin(P_PS2_CLK, HIGH);
}

byte ps2Receive() {  
  byte val = 0;
  byte read = 0;

  waitPin(P_PS2_CLK, LOW);

  read = digitalRead(P_PS2_DATA);
  if (read != 0) {
    // Start bit not 0??? Can't happen... What should we do now?
    #ifdef DEBUG
    Serial.println("Wrong start bit!");
    #endif
  }

  val = 0;
  byte mask = 1;
  for (int i = 0; i < 8; i++) {
    waitPin(P_PS2_CLK, HIGH);
    waitPin(P_PS2_CLK, LOW);    
    read = digitalRead(P_PS2_DATA);
    val |= (read ? mask : 0);
    mask <<= 1;
  }
  waitPin(P_PS2_CLK, HIGH);
  waitPin(P_PS2_CLK, LOW);
  byte parity = digitalRead(P_PS2_DATA);

  if (parity != pgm_read_byte(&oddParityTable[val])) {
    // Parity bit wrong? WTF?
    #ifdef DEBUG
    Serial.println("Wrong parity!");
    #endif
  }

  waitPin(P_PS2_CLK, HIGH);
  waitPin(P_PS2_CLK, LOW);
  read = digitalRead(P_PS2_DATA);
  if (read != 1) {
    // Stop bit not 1??? Can't happen... What should we do now?
    #ifdef DEBUG
    Serial.println("Wrong stop bit!");
    #endif
  }

  waitPin(P_PS2_CLK, HIGH);

#ifdef DEBUG
  Serial.print("<-- PS/2: 0x");  
  Serial.println(val, HEX);
#endif

  return val;
}

void ps2SendCommand(byte cmd) {
  ps2Send(cmd);  
  byte read = ps2Receive(); 
  if (read != PS2_ACK) {
    #ifdef DEBUG
    Serial.print("Mouse didn't ack! Expected: 0x"); Serial.print(PS2_ACK, HEX);
    Serial.print(", received: 0x"); Serial.println(read, HEX);
    #endif
  }
}

void resetKbd() {
  ps2SendCommand(PS2_CMD_RESET);
  byte read = ps2Receive();
  if (read != PS2_BAT_OK) {
    #ifdef DEBUG
    Serial.print("Bad BAT result! Expected: 0x"); Serial.print(PS2_BAT_OK, HEX);
    Serial.print(", received: 0x"); Serial.println(read, HEX);
    #endif    
  }
}

void setup() {

#ifdef DEBUG
  Serial.begin(115200);
#endif  

  // Blink a little to let people know that we entered setup()
  pinMode(LED, OUTPUT);
  for (int i = 0; i < 3; i++) {
    delay(200);
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);    
  }

  pinMode(P_PC_CLK, OUTPUT);  
  pinMode(P_PC_DATA, OUTPUT);
  digitalWrite(P_PC_CLK,  1);
  digitalWrite(P_PC_DATA, 0);
  
  resetKbd();

  // Keyboard should already be using set 2, but better
  // safe than sorry.
  // Using set 2 from the PS/2 keyboard makes it easier 
  // to control translation in detail.
  ps2SendCommand(PS2_CMD_SET_SCANCODE_SET);
  ps2SendCommand(2);
}

#define SKEW 0.8
#define PC_SEND_BIT(b, nextB, dataDelay, clockLow) \
  digitalWrite(P_PC_DATA, (b)); \
  digitalWrite(P_PC_CLK,  0); \
  delayMicroseconds((dataDelay*SKEW)); \
  digitalWrite(P_PC_DATA, (nextB)); \
  delayMicroseconds(((clockLow-dataDelay)*SKEW)); \
  digitalWrite(P_PC_CLK, 1); \
  delayMicroseconds(70*SKEW);


void pcSend(uint8_t b) {

  // This tries to emulate the original IBM 5150 behavior
  // as closely as possible, including the 2 start bits.
  // The timings are taken from a 5160 keyboard, but it
  // because the other instructions also take some time,
  // PC_SEND_BIT will skew the timings a little.
  
  #ifdef DEBUG
  Serial.print("--> 5150: 0x"); Serial.println(b, HEX);
  #endif      

  uint8_t b0 = (b >> 0) & 1;
  uint8_t b1 = (b >> 1) & 1;
  uint8_t b2 = (b >> 2) & 1;
  uint8_t b3 = (b >> 3) & 1;
  uint8_t b4 = (b >> 4) & 1;
  uint8_t b5 = (b >> 5) & 1;
  uint8_t b6 = (b >> 6) & 1;
  uint8_t b7 = (b >> 7) & 1;
  
  PC_SEND_BIT(0,  1,  5, 120);
  PC_SEND_BIT(1,  b0, 25, 30);
  PC_SEND_BIT(b0, b1, 25, 30);
  PC_SEND_BIT(b1, b2, 25, 30);
  PC_SEND_BIT(b2, b3, 25, 30);
  PC_SEND_BIT(b3, b4, 25, 30);
  PC_SEND_BIT(b4, b5, 25, 30);
  PC_SEND_BIT(b5, b6, 25, 30);
  PC_SEND_BIT(b6, b7, 25, 30);
  PC_SEND_BIT(b7, 0,  25, 30);  
}

void handleLedPressed(int led) {
  int mask = 1<<led;
  if ((pressed & mask) != 0) {
    return;
  }
  int oldLeds = leds;
  pressed |= mask;

  leds ^= mask;
  if (oldLeds != leds) {
    ps2SendCommand(PS2_CMD_SET_RESET_LEDS);
    ps2SendCommand(leds);
  }  
}

void handleLedUnpressed(int led) {
  pressed &= ~(1<<led);
}

void handleBreak(byte b, const uint8_t *mapping) {
  switch(b) {
  case PS2_SET2_SCAN_CODE_CAPS:
    handleLedUnpressed(PS2_LED_CAPS_LOCK);
    break;
  case PS2_SET2_SCAN_CODE_SCROLL:
    handleLedUnpressed(PS2_LED_SCROLL_LOCK);
    break;
  case PS2_SET2_SCAN_CODE_NUM:
    handleLedUnpressed(PS2_LED_NUM_LOCK);
    break;
  }
  
  uint8_t mapped = pgm_read_byte(&mapping[b]);
  if (mapped != 0) {
    pcSend(0x80 | mapped);
  }
}

void handleMake(byte b, const uint8_t *mapping) {
  switch(b) {
  case PS2_SET2_SCAN_CODE_CAPS:
    handleLedPressed(PS2_LED_CAPS_LOCK);
    break;
  case PS2_SET2_SCAN_CODE_SCROLL:
    handleLedPressed(PS2_LED_SCROLL_LOCK);
    break;
  case PS2_SET2_SCAN_CODE_NUM:
    handleLedPressed(PS2_LED_NUM_LOCK);
    break;
  }
  uint8_t mapped = pgm_read_byte(&mapping[b]);
  if (mapped != 0) {
    pcSend(mapped);
  }
}

void handle(uint8_t b, const uint8_t *mapping) {
  if (b == 0xf0) {
    b = ps2Receive();
    handleBreak(b, mapping);
  } else {
    handleMake(b, mapping);
  }
}

void escape2Bytes() {
  for (int i = 0; i < 2; i++) {
    uint8_t b = ps2Receive();
    if (b == 0xf0) {
      ps2Receive();
    }
  }
}

void loop() { 
  byte b = ps2Receive();
  if (b == 0xe1) {
    escape2Bytes();
  } else if (b == 0xe0) {
    b = ps2Receive();
    handle(b, mappingE0);
  } else {
    handle(b, mapping);
  }
}
