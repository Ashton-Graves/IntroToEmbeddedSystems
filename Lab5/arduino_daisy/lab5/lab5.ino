#include "DaisyDuino.h"
#include <Wire.h>
#include "daisyDSP.h"
using namespace daisysp;

DaisyHardware hw;
ReverbSc verb;
byte RxByte;
Oscillator osc;
size_t num_channels;

float notes[13] = {
174.61f,
195.99f,
219.99f,
233.07f,
261.62f,
};

int note_index;

// Audio process - writes data to audio output pin on daisy seed
void MyCallback(float **in, float **out, size_t size) {
  float sine_signal;
  float wet_l, wet_r;
  for (size_t i = 0; i < size; i++) {
    sine_signal = osc.Process();
    verb.Process(sine_signal, sine_signal, &wet_l, &wet_r);
    out[0][i] = 0.7f * sine_signal + 0.3f * wet_l;
    out[1][i] = 0.7f * sine_signal + 0.3f * wet_r;
  }
}

// Initializes I2C, daisy oscillator and reverb
void setup() {
  Serial.begin(9600);
  Wire.begin(0x08); // Initialize I2C (Slave Mode: address=0x8 )
  Wire.onReceive(I2C_RxHandler);
  // Initialize seed at 48kHz
  float sample_rate;
  hw = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
  num_channels = hw.num_channels;
  sample_rate = DAISY.get_samplerate();
  osc.Init(sample_rate);

    // initialize reverb
  verb.Init(DAISY.get_samplerate());
  verb.SetFeedback(0.85f);  // Set reverb amount
  verb.SetLpFreq(8000.0f); // Reverb low-pass filter frequency

  // Set the parameters for oscillator 
  osc.SetWaveform(osc.WAVE_SAW);
  osc.SetFreq(100);
  osc.SetAmp(0.1);

  // start callback
  DAISY.begin(MyCallback);
}

void loop() {
  Serial.println(" * * * * * * * * * * * *"); // Sanity check to make sure it is on
  delay(3000);
}

// Receives and handles what to do with I2C messages.
void I2C_RxHandler(int numBytes)
{
  Serial.println("message recieved");
  while(Wire.available()) {  // Read Any Received Data
    RxByte = Wire.read();    // 
    Serial.print("RxByte: ");
    Serial.println(RxByte);
    if (RxByte == 0) { // If released, turn off sound
      osc.SetAmp(0);   //
    } else {
      osc.SetFreq(notes[RxByte-1]); // Convert I2C message to correct frequency from note array
      osc.SetAmp(0.1);
    }
  }
}
