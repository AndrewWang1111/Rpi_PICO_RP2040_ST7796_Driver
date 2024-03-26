#include <iostream>
#include <hardware/i2c.h>
class Touch
{
public:
    Touch(i2c_inst_t *, uint sck, uint data, uint addr);
    ~Touch();
   

private:
    i2c_inst_t *myi2c;
    uint pinSck;
    uint pinDat;
    uint touchAddr;
    void i2cInit();
};