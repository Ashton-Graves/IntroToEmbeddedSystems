#ifndef I2C_INIT_H_
#define I2C_INIT_H_

// Initializes I2C communication to Arduino.
void I2C_Init(void);


// Sends the parameter, a single byte of data, to the Arduin via I2C.
void I2C_Send(uint8_t data);

#endif // I2C_INIT_H_