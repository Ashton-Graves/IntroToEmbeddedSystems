#include "DaisyDuino.h"
#include <Wire.h>
 
byte RxByte;

DaisyHardware hw;
static Oscillator osc;
float pitch_knob;

size_t num_channels;

float notes[12] = {
  32.70375f,
  //34.6475f,
  36.7075f,
  38.89125f,
  //41.20375f,
  43.65375f,
  //46.24875f,
  49.0f,
  51.9125f,
  //55.0f,
  58.27f,
  //61.735f,
  65.4075f
};

int note_index;

void MyCallback(float **in, float **out, size_t size) {
  float sine_signal;
  osc.SetFreq(notes[note_index] * pow(2.0, 5.0/12.0));
  for (size_t i = 0; i < size; i++) {
    sine_signal = osc.Process();
    out[0][i] = sine_signal;
    out[1][i] = sine_signal; 
  }
}

void setup() {
  // Initialize seed at 48kHz
  Wire.begin(0x55); // Initialize I2C (Slave Mode: address=0x55 )
  Wire.onReceive(I2C_RxHandler);
  float sample_rate;
  hw = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
  num_channels = hw.num_channels;
  sample_rate = DAISY.get_samplerate();
  osc.Init(sample_rate);

  // Set the parameters for oscillator 
  osc.SetWaveform(osc.WAVE_SAW);
  osc.SetFreq(100);
  osc.SetAmp(0.1);

  // start callback
  DAISY.begin(MyCallback);
}

void loop() {
  analogReadResolution(16);
  int raw = analogRead(A0);             // 0–4095
  note_index = raw / (pow(2.0, 16) / 8);       // Quantize to 0–11
  note_index = constrain(note_index, 0, 7); // Just in case

}

void I2C_RxHandler(int numBytes)
{
  while(Wire.available()) {  // Read Any Received Data
    RxByte = Wire.read();

  }
}
