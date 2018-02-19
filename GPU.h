/*
 * GPU.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */
#ifndef GPU_H_
#define GPU_H_

#include"headers.h"
#include"I2C.h"
#include"uart.h"
//#include"UART.h"
#define GYRO 0
#define ACC 1


void GPU_INIT();
void GPU_READ_GYRO(int* gx,int* gy,int* gz);
void GPU_READ_ACC(int* ax,int* ay,int* az);
void GPU_some_operations(int x,int y,int z,int mode);
void GPU_to_uart(unsigned char mode);

#endif /* GPU_H_ */
