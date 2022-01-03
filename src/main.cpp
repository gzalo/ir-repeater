#include <IRremote.h>

IRrecv irrecv(0);
IRsend irsend(1); // Defaults to pin 3
decode_results results;
unsigned int rawCodes[RAWBUF];

void setup(){
  irrecv.enableIRIn();
}

void loop(){
  if (irrecv.decode(&results)) {
    int codeLen = results.rawlen - 1;
    for (int i = 1; i <= codeLen; i++) {
      if (i % 2) {
        // Mark
        rawCodes[i - 1] = results.rawbuf[i]*USECPERTICK - MARK_EXCESS;
      } else {
        // Space
        rawCodes[i - 1] = results.rawbuf[i]*USECPERTICK + MARK_EXCESS;
      }
    }
    irsend.sendRaw(rawCodes, codeLen, 38);
    irrecv.enableIRIn();
    irrecv.resume(); 
  }
}
