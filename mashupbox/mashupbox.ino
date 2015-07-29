#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  potsSetup();
  buttonSetup();
  MIDI.begin();
  Serial.begin(115200);
}

void loop() {
  readPots();
  updateButtons();  
}


void potChange(int index, int value) {
   int midiValue = (1023-value) / 8;
   
  /* Serial.print("New Value at channel ");
   Serial.print(index);
   Serial.print(" : ");
   Serial.print(value); 
   Serial.print(". Midi Value: "); 
   Serial.println(midiValue);*/    
   // Weird bug in logic
   if (index == 7) {
     index = 27;
   }
   if (index >= 9 && index <= 11) {
     // Special 'balancing' knobs
     MIDI.sendControlChange(index, midiValue, 1);
     MIDI.sendControlChange(index + 10, 127 - midiValue, 1);     
   } else {
        MIDI.sendControlChange(index, midiValue, 1);
   } 
   
}
