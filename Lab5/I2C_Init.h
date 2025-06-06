#ifndef I2C_INIT_H_
#define I2C_INIT_H_

// Initializes I2C communication to ARDUINO
void I2C_Init(void);


// Sends a byte of data to the Arduino
void I2C_Send(uint8_t data);

#endif // I2C_INIT_H_