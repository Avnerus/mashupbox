#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  potsSetup();
  MIDI.begin();
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  readPots();
}


void potChange(int index, int value) {
   int midiValue = (1023-value) / 8;
   
  /* Serial.print("New Value at channel ");
   Serial.print(index);
   Serial.print(" : ");
   Serial.print(value); 
   Serial.print(". Midi Value: "); 
   Serial.println(midiValue);*/    
   
   MIDI.sendControlChange(index, midiValue, 1);
}
