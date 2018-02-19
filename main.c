#include"headers.h"
#include"I2C.h"
#include"UART.h"
#include"GPU.h"
#include"driverlib/fpu.h"
int main(void)
{
    FPUEnable();
    FPULazyStackingEnable();
    int ax,ay,az;
    int gx,gy,gz;
    uart_init();
    I2C_INIT();
    GPU_INIT();
    uart_send_string("saleeeh");

    while(1)
    {
        GPU_READ_ACC(&ax,&ay,&az);
        GPU_READ_GYRO(&gx,&gy,&gz);
        GPU_some_operations(ax,ay,az,ACC);
        GPU_some_operations(gx,gy,gz,GYRO);
        GPU_to_uart(ACC);
        GPU_to_uart(GYRO);
        delay(16000000);
    }
	return 0;

}
