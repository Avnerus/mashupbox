#define _R 9
#define _G 10
#define _B 11

#define L1 4
#define L2 2
#define L3 5
#define L4 3

struct Color {
  Color(): red(0), green(0), blue(0) {}
  Color(byte r, byte g, byte b): red(r), green(g), blue(b) {}
  byte red;
  byte green;
  byte blue;
};

const uint8_t ROWS=1;
const uint8_t COLS=4;
char keys[ROWS][COLS] = {{1, 2, 3, 4}};
byte rowPins[ROWS] = {A0};
byte colPins[COLS] = {A1, A2, A3, A4};

Color led[4];
uint8_t button_state[4] = {0,0,0,0};
uint8_t key_state[4] = {0,0,0,0};
uint8_t key_notes[4] = {72,60,72,60};

Color color_states[] = {
  Color(0  , 0  , 0  ),
  Color(255, 0  , 0  ),
  Color(0  , 255, 0  ),
  Color(0  , 0  , 255),
  Color(255, 255, 0  ),
  Color(0  , 255, 255),
  Color(0  , 255, 255),
};
uint8_t num_color_states = sizeof(color_states) / sizeof(color_states[0]);

Keypad buttons = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void buttonSetup() {
  pinMode(_R, OUTPUT);
  pinMode(_G, OUTPUT);
  pinMode(_B, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  
  buttons.addEventListener(keypadEvent);
}

void updateButtons() {
   writeLeds();
   //readButtons();
   buttons.getKey();
}

void keypadEvent(KeypadEvent key){
  switch (buttons.getState()){
    case PRESSED:
        MIDI.sendNoteOn(key_notes[key -1]   ,127,1);
        button_state[key-1] = (button_state[key-1] + 1) % num_color_states;
        led[key-1] = color_states[button_state[key-1]];
        break;     
    case RELEASED:
        MIDI.sendNoteOff(key_notes[key -1]   ,127,1);
        break;
   }
}

void readButtons() {
  char key = buttons.getKey();
  if (key && key <= 4) {
    button_state[key-1] = (button_state[key-1] + 1) % num_color_states;
    led[key-1] = color_states[button_state[key-1]];
     key_state[key-1] = 1;
     //MIDI.sendNoteOn(key_notes[key -1]   ,127,1);
     Serial.print("Key pressed: ");
     Serial.println((int)key);
     Serial.print(" : ");    
  }
}

void writeLeds() {
  digitalWrite(_R, LOW);
  digitalWrite(_G, LOW);
  digitalWrite(_B, LOW);
  analogWrite(L1, 255-led[0].red);
  analogWrite(L2, 255-led[1].red);
  analogWrite(L3, 255-led[2].red);
  analogWrite(L4, 255-led[3].red);
  digitalWrite(_R, HIGH);
  // reds are on now, wait a bit
  delayMicroseconds(300);
  digitalWrite(_R, LOW);
  analogWrite(L1, 255-led[0].green);
  analogWrite(L2, 255-led[1].green);
  analogWrite(L3, 255-led[2].green);
  analogWrite(L4, 255-led[3].green);
  digitalWrite(_G, HIGH);
  // green are on now, wait a bit
  delayMicroseconds(300);
  digitalWrite(_G, LOW);
  analogWrite(L1, 255-led[0].blue);
  analogWrite(L2, 255-led[1].blue);
  analogWrite(L3, 255-led[2].blue);
  analogWrite(L4, 255-led[3].blue);
  digitalWrite(_B, HIGH);
  // blue are on now, wait a bit
  delayMicroseconds(300);
  digitalWrite(_B, LOW);
}
