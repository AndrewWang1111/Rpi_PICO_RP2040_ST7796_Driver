#include <iostream>
#include <hardware/uart.h>
#include <hardware/gpio.h>

#define DATA_OK 0
#define DATA_ERR 1
#define PIXEL_PER_FRAME

class UartReceiver
{
public:
    UartReceiver(uart_inst *, uint tx, uint rx, uint baud);
    ~UartReceiver();
    bool BytesNeedsRead();

private:
    uart_inst_t *MyUart;
    uint PinTx;
    uint PinRx;
    uint Baud;
    uint CurrentLine;
    uint CurrentIndex;
    uint8_t TakeBuffer[24];
    bool FrameOK;
    void UartInit();
    bool CheckCrc();
    uint8_t *DataTake();
    void DataConfirm();
};