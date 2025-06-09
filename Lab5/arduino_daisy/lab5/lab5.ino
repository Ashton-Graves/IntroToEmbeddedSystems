#include "DaisyDuino.h"
#include <Wire.h>
#include "daisyDSP.h"  // Add this
using namespace daisysp;

ReverbSc verb;
 
byte RxByte;

DaisyHardware hw;
static Oscillator osc;

size_t num_channels;

float notes[13] = {
174.61f,
195.99f,
219.99f,
233.07f,
261.62f,
};

int note_index;

void MyCallback(float **in, float **out, size_t size) {
  float sine_signal;
  float wet_l, wet_r;
  for (size_t i = 0; i < size; i++) {
    sine_signal = osc.Process();
    verb.Process(sine_signal, sine_signal, &wet_l, &wet_r);
    //out[0][i] = sine_signal;
    //out[1][i] = sine_signal; 
    out[0][i] = 0.7f * sine_signal + 0.3f * wet_l;
    out[1][i] = 0.7f * sine_signal + 0.3f * wet_r;
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin(0x08); // Initialize I2C (Slave Mode: address=0x55 )
  Wire.onReceive(I2C_RxHandler);
  // Initialize seed at 48kHz
  float sample_rate;
  hw = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
  num_channels = hw.num_channels;
  sample_rate = DAISY.get_samplerate();
  osc.Init(sample_rate);

    // initialize reverb
  verb.Init(DAISY.get_samplerate());
  verb.SetFeedback(0.85f);  // Range: 0 to ~0.95
  verb.SetLpFreq(8000.0f); // Low-pass filter frequency

  // Set the parameters for oscillator 
  osc.SetWaveform(osc.WAVE_SAW);
  osc.SetFreq(100);
  osc.SetAmp(0.1);

  // start callback
  DAISY.begin(MyCallback);
}

void loop() {
  Serial.println(" * * * * * * * * * * * *");
  delay(3000);
}

void I2C_RxHandler(int numBytes)
{
  Serial.println("message recieved");
  while(Wire.available()) {  // Read Any Received Data
    RxByte = Wire.read();
    Serial.print("RxByte: ");
    Serial.println(RxByte);
    if (RxByte == 0) {
      osc.SetAmp(0);
    } else {
      osc.SetFreq(notes[RxByte-1]);
      osc.SetAmp(0.1);
      Serial.println("note");

    }
  }
}

