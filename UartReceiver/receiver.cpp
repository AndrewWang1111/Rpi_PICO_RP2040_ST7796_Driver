#include "receiver.h"

UartReceiver::UartReceiver(uart_inst *uart, uint tx, uint rx, uint baud)
{
    MyUart = uart;
    PinRx = rx;
    PinTx = tx;
    Baud = baud;

    UartInit();
}
UartReceiver::~UartReceiver() {}

void UartReceiver::UartInit()
{
    uart_init(MyUart, Baud);
    gpio_set_function(PinRx, GPIO_FUNC_UART);
    gpio_set_function(PinTx, GPIO_FUNC_UART);
}

bool UartReceiver::CheckCrc()
{
    return false;
}

uint8_t *UartReceiver::DataTake()
{
    if (FrameOK)
        return &TakeBuffer[0];
    else
        return nullptr;
}

void UartReceiver::DataConfirm()
{
}