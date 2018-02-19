/*
 * GPU.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: DELL
 */
#include"GPU.h"
float fax,fay,faz;
float fgx,fgy,fgz;

void GPU_INIT()
{
    I2C_TRANSMIT_ADDRESS(0xD0);
    I2C_START_MULTIPLE_transmit(0x6B);
    I2C_TRANSMIT_STOP(0x00);
    I2C_TRANSMIT_ADDRESS(0xD0);
    I2C_START_MULTIPLE_transmit(0x1B);
    I2C_TRANSMIT_STOP(0x00);
    I2C_TRANSMIT_ADDRESS(0xD0);
    I2C_START_MULTIPLE_transmit(0x1C);
    I2C_TRANSMIT_STOP(0x00);
	//TWI_start();
	//TWI_send_DeviceAddress_Write(0x68);
	//TWI_send_data(0x6B,MASTER);								//SET POWERMANAGMENT TO CLEAR SLEEP MODE AND DISABLE TEMP.SENSOR
	//TWI_send_data(0x00,MASTER);
	//TWI_stop();
	//TWI_start();
	//TWI_send_DeviceAddress_Write(0x68);
	//TWI_send_data(0x1B,MASTER);								//SET GYRO. CONFIG. TO +-250
	//TWI_send_data(0x00,MASTER);
	//TWI_stop();
	//TWI_start();
	//TWI_send_DeviceAddress_Write(0x68);
	//TWI_send_data(0x1C,MASTER);								//SET ACC. CONFIG. TO +-2g
	//TWI_send_data(0x00,MASTER);
	//TWI_stop();
}

void GPU_READ_ACC(int* ax,int* ay,int* az)
{
    I2C_TRANSMIT_ADDRESS(0xD0);
    I2C_START_TRANSMIT_ONCE(0x3B);
    I2C_TRANSMIT_ADDRESS(0xD1);
    *ax=(((int)I2C_START_MULTIPLE_RECEIVE())<<8)|((int)I2C_RECEIVE_MIDDLE());
    *ay=(((int)I2C_RECEIVE_MIDDLE())<<8)|((int)I2C_RECEIVE_MIDDLE());
    *az=(((int)I2C_RECEIVE_MIDDLE())<<8)|((int)I2C_RECEIVE_STOP());

	//TWI_start();
	//TWI_send_DeviceAddress_Write(0X68);
	//TWI_send_data(0x3B,MASTER);								//acc. output address
	//TWI_stop();
	//TWI_start();
	//TWI_send_DeviceAddress_Read(0x68);
	//*ax=(((int)TWI_recieve_data_ACK(MASTER))<<8)|((int)TWI_recieve_data_ACK(MASTER));
	//*ay=(((int)TWI_recieve_data_ACK(MASTER))<<8)|((int)TWI_recieve_data_ACK(MASTER));
	//*az=(((int)TWI_recieve_data_ACK(MASTER))<<8)|((int)TWI_recieve_data_NACK(MASTER));
	//TWI_stop();
}

void GPU_READ_GYRO(int* gx,int* gy,int* gz)
{
    I2C_TRANSMIT_ADDRESS(0xD0);
    I2C_START_TRANSMIT_ONCE(0x43);
    I2C_TRANSMIT_ADDRESS(0xD1);
    *gx=(((int)I2C_START_MULTIPLE_RECEIVE())<<8)|((int)I2C_RECEIVE_MIDDLE());
    *gy=(((int)I2C_RECEIVE_MIDDLE())<<8)|((int)I2C_RECEIVE_MIDDLE());
    *gz=(((int)I2C_RECEIVE_MIDDLE())<<8)|((int)I2C_RECEIVE_STOP());
	//TWI_start();
	//TWI_send_DeviceAddress_Write(0X68);
	//TWI_send_data(0x43,MASTER);								//acc. output address
	//TWI_stop();
	//TWI_start();
	//TWI_send_DeviceAddress_Read(0x68);
	//*gx=(((int)TWI_recieve_data_ACK(MASTER))<<8)|((int)TWI_recieve_data_ACK(MASTER));
	//*gy=(((int)TWI_recieve_data_ACK(MASTER))<<8)|((int)TWI_recieve_data_ACK(MASTER));
	//*gz=(((int)TWI_recieve_data_ACK(MASTER))<<8)|((int)TWI_recieve_data_NACK(MASTER));
	//TWI_stop();
}

void GPU_some_operations(int x,int y,int z,int mode)
{
	switch(mode)
	{
	case ACC:
		fax=x/16384.0;				//divide the acc on the sensitivity since we use +-2g
		fay=y/16384.0;
		faz=z/16384.0;
		break;
	case GYRO:
		fgx=x/131.0;				//divide the gyro on this number from the datasheet since we use +-250
		fgy=y/131.0;
		fgz=z/131.0;
		break;
	default:
		break;
	}
}

void GPU_to_uart(unsigned char mode)
{
	unsigned char arr[15],i;
	for(i=0;i<15;i++)
	{
		arr[i]=0;
	}
	int decimal,d_fraction;
	switch(mode)
	{
	case ACC:
		for(i=0;i<15;i++)
		{
			arr[i]=0;
		}
		decimal=(int)fax;
		d_fraction=(int)((fax-decimal)*10000);
		if(fax<0)
		{
			d_fraction=0-d_fraction;
		}
		sprintf((char*)arr,"%d.%d",decimal,d_fraction);
		uart_send_string((unsigned char*)" ax: ");
		uart_send_string(arr);
		uart_send_char('\n');
		for(i=0;i<15;i++)
		{
			arr[i]=0;
		}
		decimal=(int)fay;
		d_fraction=(int)((fay-decimal)*10000);
		if(fay<0)
		{
			d_fraction=0-d_fraction;
		}
		sprintf((char*)arr,"%d.%d",decimal,d_fraction);
        uart_send_string((unsigned char*)" ay: ");
        uart_send_string(arr);
        uart_send_char('\n');
		//UART_SEND_STRING((unsigned char*)" ay: ");
		//UART_SEND_STRING(arr);
		//UART_SEND_BYTE('\n');

		for(i=0;i<15;i++)
		{
			arr[i]=0;
		}
		decimal=(int)faz;
		d_fraction=(int)((faz-decimal)*10000);
		if(faz<0)
		{
			d_fraction=0-d_fraction;
		}
		sprintf((char*)arr,"%d.%d",decimal,d_fraction);
        uart_send_string((unsigned char*)" az: ");
        uart_send_string(arr);
        uart_send_char('\n');
		//UART_SEND_STRING((unsigned char*)" az: ");
		//UART_SEND_STRING(arr);
		//UART_SEND_BYTE('\n');
		break;

	case GYRO:
		for(i=0;i<15;i++)
		{
			arr[i]=0;
		}
		decimal=(int)fgx;
		d_fraction=(int)((fgx-decimal)*10000);
		if(fgx<0)
		{
			d_fraction=0-d_fraction;
		}
		sprintf((char*)arr,"%d.%d",decimal,d_fraction);
        uart_send_string((unsigned char*)" gx: ");
        uart_send_string(arr);
        uart_send_char('\n');
		//UART_SEND_STRING((unsigned char*)" gx: ");
		//UART_SEND_STRING(arr);
		//UART_SEND_BYTE('\n');

		for(i=0;i<15;i++)
		{
			arr[i]=0;
		}
		decimal=(int)fgy;
		d_fraction=(int)((fgy-decimal)*10000);
		if(fgy<0)
		{
			d_fraction=0-d_fraction;
		}
		sprintf((char*)arr,"%d.%d",decimal,d_fraction);
        uart_send_string((unsigned char*)" gy: ");
        uart_send_string(arr);
        uart_send_char('\n');
		//UART_SEND_STRING((unsigned char*)" gy: ");
		//UART_SEND_STRING(arr);
		//UART_SEND_BYTE('\n');

		for(i=0;i<15;i++)
		{
			arr[i]=0;
		}
		decimal=(int)fgz;
		d_fraction=(int)((fgz-decimal)*10000);
		if(fgz<0)
		{
			d_fraction=0-d_fraction;
		}
		sprintf((char*)arr,"%d.%d",decimal,d_fraction);
        uart_send_string((unsigned char*)" gz: ");
        uart_send_string(arr);
        uart_send_char('\n');
		//UART_SEND_STRING((unsigned char*)" gz: ");
		//UART_SEND_STRING(arr);
		//UART_SEND_STRING("\n\n");
		break;
	default:
		break;
	}
}
