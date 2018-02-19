#include"I2C.h"

void I2C_INIT()
{
    SYSCTL->RCGCI2C=0x01;                                       //Enable clock gating for I2C0
    SYSCTL->RCGCGPIO|=(1<<1);                                   //Enable clocck gating for portB (pb2->scl ,,pb3->sda)
    GPIOB->LOCK=0x4C4F434B;                                     //UNLOCK GPIOCR FOR PORTB
    GPIOB->CR=0XFF;                                              //now its permitted to write to afsel and other registers
    GPIOB->AFSEL|=(1<<2)|(1<<3);                                //ALTERNATE FUNCTION FOR PB2-PB3
    GPIOB->DEN|=(1<<2)|(1<<3);                                  //It must be enabled for Open drain
    GPIOB->ODR|=(1<<3);                                         //Enable open drain for sda
    GPIOB->PCTL|=0X00003300;                                    //Enable I2C function for pb2-pb3
    I2C0->MCR|=(1<<4);                                          //Enable master mode
    I2C0->MTPR=1;                                               //Set the clock to 400khz
}


void I2C_TRANSMIT_ADDRESS(unsigned char address)
{
    I2C0->MSA=address;                                         //Address of the slave + write  ((0xD0))
}

void I2C_START_TRANSMIT_ONCE(unsigned char data)
{
    //to transmit only one byte
    //here it will transmit the start bit then the address then the data then a stop bit
    I2C0->MDR=data;                                           //data to be transmitted
    I2C0->MCS=(1<<0)|(1<<1)|(1<<2);                             //ENABLE RUN-START-STOP
    //START condition followed by a TRANSMIT and STOP condition (master remains in Idle state)
    while((I2C0->MCS)&(1<<0));                                  //Wait signal on busy bit
}

/*void I2C_TRANSMIT_DATA(unsigned char data)
{
    //only one byte
    I2C0->MDR=data;                                           //data to be transmitted
}*/
void I2C_START_MULTIPLE_transmit(unsigned char data)
{
    //here it will send the address and the first byte only
    I2C0->MDR=data;
    I2C0->MCS=(1<<0)|(1<<1);                                    //ENABLE RUN AND START
    while((I2C0->MCS)&(1<<0));                                  //Wait signal
    if((I2C0->MCS)&(1<<1))                                       //ERROR BIT
    {
        if((I2C0->MCS)&(1<<4))                                  //CHECK ARB. LOST
        {
            //ARB. LOST
        }
        else
        {
            I2C0->MCS=(1<<2);                                   //it's just an error so send stop
        }
    }
}

void I2C_TRANSMIT_MIDDLE(unsigned char data)
{
    I2C0->MDR=data;                                            //add data
    I2C0->MCS=(1<<0);                                          //RUN
    while((I2C0->MCS)&(1<<0));                                  //Wait signal on busy bit

    if((I2C0->MCS)&(1<<1))                                       //ERROR BIT
    {
        if((I2C0->MCS)&(1<<4))                                  //CHECK ARB. LOST
        {
            //ARB. LOST
        }
        else
        {
            I2C0->MCS=(1<<2);                                   //it's just an error so send stop
        }
    }
    //add data
    //run
    //wait
}
void I2C_TRANSMIT_STOP(unsigned char data)
{
    I2C0->MDR=data;                                             //data
    I2C0->MCS=(1<<0)|(1<<2);                                    //Run and stop
    while((I2C0->MCS)&(1<<0));                                  //Wait signal on busy bit
    //add data
    //stop run
    //wait
}

unsigned char I2C_START_RECEIVE_ONCE()
{
    //to receive only one byte
    //here it will transmit the start bit then the address then receive the data then a stop bit
    I2C0->MCS=(1<<0)|(1<<1)|(1<<3)|(1<<2);                    //ENABLE RUN-START-ACK-STOP
    //START condition followed by a TRANSMIT and STOP condition (master remains in Idle state)
    while((I2C0->MCS)&(1<<0));                                  //Wait signal on busy bit
    return I2C0->MDR;
}

unsigned char I2C_START_MULTIPLE_RECEIVE()
{
    I2C0->MCS=(1<<0)|(1<<1)|(1<<3);                             //ENABLE RUN-START-ACK
    while((I2C0->MCS)&(1<<0));                                  //Wait signal on busy bit
    if((I2C0->MCS)&(1<<1))                                       //ERROR BIT
    {
        if((I2C0->MCS)&(1<<4))                                  //CHECK ARB. LOST
        {
            //ARB. LOST
        }
        else
        {
            I2C0->MCS=(1<<2);                                   //it's just an error so send stop
        }
    }
    return I2C0->MDR;
}

unsigned char I2C_RECEIVE_MIDDLE()
{
    I2C0->MCS=(1<<0)|(1<<3);                                    //RUN + ACK
    while((I2C0->MCS)&(1<<0));                                  //Wait signal on busy bit

    if((I2C0->MCS)&(1<<1))                                       //ERROR BIT
    {
        if((I2C0->MCS)&(1<<4))                                  //CHECK ARB. LOST
        {
            //ARB. LOST
        }
        else
        {
            I2C0->MCS=(1<<2);                                   //it's just an error so send stop
        }
    }
    return I2C0->MDR;
    //add data
    //run
    //wait
}
unsigned char I2C_RECEIVE_STOP()
{
    I2C0->MCS=(1<<0)|(1<<2);                                    //Run and stop with no ACK
    while((I2C0->MCS)&(1<<0));                                  //Wait signal on busy bit
    if((I2C0->MCS)&(1<<1))                                       //ERROR BIT
    {
        if((I2C0->MCS)&(1<<4))                                  //CHECK ARB. LOST
        {
            //ARB. LOST
        }
        else
        {
            I2C0->MCS=(1<<2);                                   //it's just an error so send stop
        }
    }
    return I2C0->MDR;
    //add data
    //stop run
    //wait
}


/*void I2C_STOP()
{
    I2C0->MSC=(1<<2)|(1<<0);                                           //ENABLE STOP BIT
}*/
