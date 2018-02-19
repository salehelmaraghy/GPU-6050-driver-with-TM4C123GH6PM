#ifndef I2C_H_
#define I2C_H_

#include"headers.h"

#define write 0
#define read 1

void I2C_INIT();
void I2C_TRANSMIT_ADDRESS(unsigned char address);
void I2C_START_TRANSMIT_ONCE(unsigned char data);
void I2C_START_MULTIPLE_transmit(unsigned char data);
void I2C_TRANSMIT_MIDDLE(unsigned char data);
void I2C_TRANSMIT_STOP(unsigned char data);
unsigned char I2C_START_RECEIVE_ONCE();
unsigned char I2C_START_MULTIPLE_RECEIVE();
unsigned char I2C_RECEIVE_MIDDLE();
unsigned char I2C_RECEIVE_STOP();
//void I2C_TRANSMIT_ADDRESS_READ();
//unsigned char I2C_READ_DATA_ACK(void);
//unsigned char I2C_READ_DATA_NACK(void);

//void I2C_STOP();



#endif /* I2C_H_ */
