#ifndef CHIP_REG_H
#define CHIP_REG_H

#include "common.h"

typedef enum _io_func
{
    IO_FUNC_GPIO0_0 = 0x0,

    IO_FUNC_I2C0_SCL = 0x100,
    IO_FUNC_I2C0_SDA,
    IO_FUNC_I2C1_SCL,
    IO_FUNC_I2C1_SDA,
    IO_FUNC_I2C2_SCL,
    IO_FUNC_I2C2_SDA,
    IO_FUNC_I2C3_SCL,
    IO_FUNC_I2C4_SDA,

    IO_FUNC_TSI0_D0,
    IO_FUNC_TSI1_D0,
    IO_FUNC_TSI2_D0,
    IO_FUNC_TSI3_D0,

    IO_FUNC_TSI0_CLK,
    IO_FUNC_TSI1_CLK,
    IO_FUNC_TSI2_CLK,
    IO_FUNC_TSI3_CLK,

    IO_FUNC_TSI0_VALID,
    IO_FUNC_TSI1_VALID,
    IO_FUNC_TSI2_VALID,
    IO_FUNC_TSI3_VALID,

    IO_FUNC_TSI0_SYNC,
    IO_FUNC_TSI1_SYNC,
    IO_FUNC_TSI2_SYNC,
    IO_FUNC_TSI3_SYNC,

    IO_FUNC_SIM0_DATA,
    IO_FUNC_SIM0_CLK,
    IO_FUNC_SIM0_DET,
    IO_FUNC_SIM0_RST,
    IO_FUNC_SIM0_PWREN,

    IO_FUNC_BUTT,


}io_func_id_e;

typedef struct _io_share
{
    char io_func_name[16];
    int reg_val;
    io_func_id_e io_func_id;

}io_share_t;

typedef struct _pinmux_reg
{
    int offset_addr;
    int reset_val;
    char reg_name[16];
    char pin_name[16];
    int io_pin_num;

    int io_share_num;
    io_share_t io_share[8];
}pinmux_reg_t;

#define PINMUX_REG_BASE   0xF8A21000

typedef enum _chip_type
{
    CHIP_HI3716CV200,
    CHIP_HI3716MV310,
    CHIP_HI3716MV330,
    CHIP_HI3796MV100,
    CHIP_HI3798MV100,
    CHIP_HI3798MV200,
    CHIP_HI3798CV200,
}CHIP_TYPE_E;

class chip_reg
{

public:
    int pinmux_reg_base;
    pinmux_reg_t *pinmux_reg;

public:
    chip_reg();
    ~chip_reg();

    pinmux_reg_t* get_pinmux_reg_by_pinname(char *pin_name);
    U32 get_regval_by_funcname(pinmux_reg_t *reg, char *func_name);
    pinmux_reg_t* get_pinmux_reg_config_by_funcname(char *func_name, U32 *reg_addr, U32 *reg_val);
    pinmux_reg_t* get_pinmux_reg_config(char *pin_name, char *func_name, U32 *reg_addr, U32 *reg_val);
};

#endif // CHIP_REG_H
