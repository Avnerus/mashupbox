#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // put your setup code here, to run once:
  MIDI.begin();
  Serial.begin(115200);

}

void loop() {
  MIDI.sendNoteOn(42,127,1);  // Send a Note (pitch 42, velo 127 on channel 1)
  delay(1000);
  MIDI.sendNoteOff(42,0,1);  
}
