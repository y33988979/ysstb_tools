#include "chip_reg.h"

static pinmux_reg_t g_pinmux_reg[80] =
{
    /* offset_addr, reg_name, pin_name, reset_val, io_share_num, io_pin_num, */
    {0x00, 0x130, "io_share_0", "NF_RDY", 0, 2,
        {
            {"GPIO0_0", 0x0, IO_FUNC_BUTT},
            {"NF_RDY", 0x1, IO_FUNC_BUTT},
        }
    },
    {0x04, 0x130, "io_share_1", "NF_CSN", 0, 2,
        {
            {"GPIO0_1", 0x0, IO_FUNC_BUTT},
            {"NF_CSN", 0x1, IO_FUNC_BUTT},
        }
    },
    {0x08, 0x1F0, "io_share_2", "NF_DQSN", 0, 3,
        {
            {"GPIO0_2", 0x0, IO_FUNC_BUTT},
            {"NF_DQSN", 0x1, IO_FUNC_BUTT},
            {"BOOT_SEL2", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x0C, 0x1F0, "io_share_3", "NF_DQS", 0, 2,
        {
            {"GPIO0_3", 0x0, IO_FUNC_BUTT},
            {"NF_DQS", 0x1, IO_FUNC_BUTT},
        }
    },
    {0x10, 0x11F0, "io_share_4", "NF_DQ7", 0, 3,
        {
            {"GPIO0_4", 0x0, IO_FUNC_BUTT},
            {"NF_DQ7", 0x1, IO_FUNC_BUTT},
            {"EMMC_CDATA3", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x14, 0x11F0, "io_share_5", "NF_DQ6", 0, 3,
        {
            {"GPIO0_5", 0x0, IO_FUNC_BUTT},
            {"NF_DQ6", 0x1, IO_FUNC_BUTT},
            {"EMMC_CDATA4", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x18, 0x11F0, "io_share_6", "NF_DQ5", 0, 3,
        {
            {"GPIO0_6", 0x0, IO_FUNC_BUTT},
            {"NF_DQ5", 0x1, IO_FUNC_BUTT},
            {"EMMC_CDATA0", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x1C, 0x11F0, "io_share_7", "NF_DQ4", 0, 3,
        {
            {"GPIO0_7", 0x0, IO_FUNC_BUTT},
            {"NF_DQ4", 0x1, IO_FUNC_BUTT},
            {"EMMC_CDATA5", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x20, 0x11F0, "io_share_8", "NF_DQ3", 0, 3,
        {
            {"GPIO1_0", 0x0, IO_FUNC_BUTT},
            {"NF_DQ3", 0x1, IO_FUNC_BUTT},
            {"EMMC_CDATA1", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x24, 0x11F0, "io_share_9", "NF_DQ2", 0, 3,
        {
            {"GPIO1_1", 0x0, IO_FUNC_BUTT},
            {"NF_DQ2", 0x1, IO_FUNC_BUTT},
            {"EMMC_CDATA6", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x28, 0x11F0, "io_share_10", "NF_DQ1", 0, 3,
        {
            {"GPIO1_2", 0x0, IO_FUNC_BUTT},
            {"NF_DQ1", 0x1, IO_FUNC_BUTT},
            {"EMMC_CDATA2", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x2C, 0x11F0, "io_share_11", "NF_DQ0", 0, 3,
        {
            {"GPIO1_3", 0x0, IO_FUNC_BUTT},
            {"NF_DQ0", 0x1, IO_FUNC_BUTT},
            {"EMMC_CDATA7", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x30, 0x1F0, "io_share_12", "NF_WEN", 0, 3,
        {
            {"GPIO1_4", 0x0, IO_FUNC_BUTT},
            {"NF_WEN", 0x1, IO_FUNC_BUTT},
            {"EMMC_CCLK_OUT", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x34, 0x130, "io_share_13", "NF_ALE", 0, 2,
        {
            {"GPIO1_5", 0x0, IO_FUNC_BUTT},
            {"NF_ALE", 0x1, IO_FUNC_BUTT},
        }
    },
    {0x38, 0x11F0, "io_share_14", "NF_CLE", 0, 3,
        {
            {"GPIO1_6", 0x0, IO_FUNC_BUTT},
            {"NF_CLE", 0x1, IO_FUNC_BUTT},
            {"EMMC_CCMD", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x3C, 0x1F0, "io_share_15", "NF_REC", 0, 3,
        {
            {"GPIO1_7", 0x0, IO_FUNC_BUTT},
            {"NF_REC", 0x1, IO_FUNC_BUTT},
            {"EMMC_RST", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x40, 0x1F0, "io_share_16", "NF_REC", 0, 3,
        {
            {"GPIO2_0", 0x0, IO_FUNC_BUTT},
            {"NF_REC", 0x1, IO_FUNC_BUTT},
            {"EMMC_DATA_STR", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x44, 0x130, "io_share_17", "PMC_CORE0", 0, 3,
        {
            {"PMC_CORE0", 0x0, IO_FUNC_BUTT},
            {"I2C0_SDA", 0x1, IO_FUNC_BUTT},
            {"GPIO2_1", 0x2, IO_FUNC_BUTT},
        }
    },
    {0x48, 0x130, "io_share_18", "PMC_GPU0", 0, 3,
        {
            {"PMC_GPU0", 0x0, IO_FUNC_BUTT},
            {"I2C0_SCL", 0x1, IO_FUNC_BUTT},
            {"GPIO2_2", 0x2, IO_FUNC_BUTT},
        }
    },

    {0x4C, 0x130, "io_share_19", "SATA0_PWREN", 0, 6,
        {
            {"GPIO2_3", 0x0, IO_FUNC_BUTT},
            {"SATA0_PWREN", 0x1, IO_FUNC_BUTT},
            {"UART3_CTSN", 0x2, IO_FUNC_BUTT},
            {"TSI0_D7", 0x5, IO_FUNC_BUTT},
            {"TSI3_CLK", 0x6, IO_FUNC_TSI3_CLK},
            {"SIM1_DATA", 0x7, IO_FUNC_BUTT},
        }
    },
    {0x50, 0x130, "io_share_20", "SATA0_LED_N", 0, 7,
        {
            {"GPIO2_4", 0x0, IO_FUNC_BUTT},
            {"SATA0_LED_N", 0x1, IO_FUNC_BUTT},
            {"UART3_RTSN", 0x2, IO_FUNC_BUTT},
            {"TSI1_SYNC", 0x3, IO_FUNC_TSI1_SYNC},
            {"TSI1_D1", 0x4, IO_FUNC_TSI1_D0},
            {"TSI0_D6", 0x5, IO_FUNC_BUTT},
            {"TSI3_VALID", 0x6, IO_FUNC_TSI3_VALID},
            {"SIM1_DET", 0x7, IO_FUNC_BUTT},
        }
    },
    {0x54, 0x130, "io_share_21", "GPIO2_5", 0, 6,
        {
            {"GPIO2_5", 0x0, IO_FUNC_BUTT},
            {"UART3_RXD", 0x2, IO_FUNC_BUTT},
            {"TSI1_D0", 0x3, IO_FUNC_TSI1_D0},
            {"TSI0_D5", 0x5, IO_FUNC_BUTT},
            {"TSI3_D0", 0x6, IO_FUNC_TSI3_D0},
            {"SIM1_RST", 0x7, IO_FUNC_BUTT},
        }
    },
    {0x58, 0x130, "io_share_22", "GPIO2_6", 0, 6,
        {
            {"GPIO2_6", 0x0, IO_FUNC_BUTT},
            {"UART3_TXD", 0x2, IO_FUNC_BUTT},
            {"TSI1_CLK", 0x3, IO_FUNC_TSI1_CLK},
            {"TSI0_D4", 0x5, IO_FUNC_BUTT},
            {"TSI2_VALID", 0x6, IO_FUNC_TSI2_VALID},
            {"SIM1_CLK", 0x7, IO_FUNC_BUTT},
        }
    },
    {0x5C, 0x130, "io_share_23", "GPIO2_7", 0, 6,
        {
            {"GPIO2_7", 0x0, IO_FUNC_BUTT},
            {"I2C2_SDA", 0x1, IO_FUNC_I2C2_SDA},
            {"TSI1_VALID", 0x3, IO_FUNC_TSI1_VALID},
            {"TSI0_D3", 0x5, IO_FUNC_BUTT},
            {"TSI2_D0", 0x6, IO_FUNC_TSI0_D0},
            {"SIM1_PWREN", 0x7, IO_FUNC_BUTT},
        }
    },
    {0x60, 0x2130, "io_share_24", "JTAG_TRSTN", 0, 5,
        {
            {"JTAG_TRSTN", 0x0, IO_FUNC_BUTT},
            {"I2C2_SCL", 0x1, IO_FUNC_I2C2_SCL},
            {"SPI0_SDO", 0x2, IO_FUNC_BUTT},
            {"SIM0_DATA", 0x3, IO_FUNC_SIM0_DATA},
            {"GPIO3_0", 0x4, IO_FUNC_BUTT},
        }
    },
    {0x64, 0x130, "io_share_25", "JTAG_TDI", 0, 5,
        {
            {"JTAG_TDI", 0x0, IO_FUNC_BUTT},
            {"SPI0_CSN", 0x2, IO_FUNC_BUTT},
            {"SIM0_DET", 0x3, IO_FUNC_SIM0_DET},
            {"GPIO3_1", 0x4, IO_FUNC_BUTT},
            {"UART2_CTSN", 0x5, IO_FUNC_BUTT},
        }
    },
    {0x68, 0x130, "io_share_26", "JTAG_TMS", 0, 6,
        {
            {"JTAG_TMS", 0x0, IO_FUNC_BUTT},
            {"I2S_RX_BCLK", 0x1, IO_FUNC_BUTT},
            {"SPI0_SCLK", 0x2, IO_FUNC_BUTT},
            {"SIM0_RST", 0x3, IO_FUNC_SIM0_RST},
            {"GPIO3_2", 0x4, IO_FUNC_BUTT},
            {"UART2_TXD", 0x5, IO_FUNC_BUTT},
        }
    },
    {0x6C, 0x130, "io_share_27", "JTAG_TCK", 0, 6,
        {
            {"JTAG_TCK", 0x0, IO_FUNC_BUTT},
            {"I2S_RX_WS", 0x1, IO_FUNC_BUTT},
            {"SPI0_SDI", 0x2, IO_FUNC_BUTT},
            {"SIM0_CLK", 0x3, IO_FUNC_SIM0_CLK},
            {"GPIO3_3", 0x4, IO_FUNC_BUTT},
            {"UART2_RXD", 0x5, IO_FUNC_BUTT},
        }
    },
    {0x70, 0x130, "io_share_28", "JTAG_TDO", 0, 6,
        {
            {"JTAG_TDO", 0x0, IO_FUNC_BUTT},
            {"I2S_RX_MCLK", 0x1, IO_FUNC_BUTT},
            {"I2S_DOUT3", 0x2, IO_FUNC_BUTT},
            {"SIM0_PWREN", 0x3, IO_FUNC_SIM0_PWREN},
            {"GPIO3_4", 0x4, IO_FUNC_BUTT},
            {"UART2_RTSN", 0x5, IO_FUNC_BUTT},
        }
    },
    {0x74, 0x130, "io_share_29", "GPIO3_5", 0, 5,
        {
            {"GPIO3_5", 0x0, IO_FUNC_BUTT},
            {"I2S_MCLK", 0x1, IO_FUNC_BUTT},
            {"I2S_DOUT2", 0x2, IO_FUNC_BUTT},
            {"SF_WPN_IO2", 0x5, IO_FUNC_BUTT},
            {"TSO0_SYNC", 0x6, IO_FUNC_BUTT},
        }
    },
    {0x78, 0x130, "io_share_30", "GPIO3_6", 0, 7,
        {
            {"GPIO3_6", 0x0, IO_FUNC_BUTT},
            {"I2S_WS", 0x1, IO_FUNC_BUTT},
            {"I2S_DOUT1", 0x2, IO_FUNC_BUTT},
            {"TSI1_SYNC；", 0x3, IO_FUNC_TSI1_SYNC},
            {"TSI1_D1", 0x4, IO_FUNC_BUTT},
            {"SF_SDI_IO1", 0x5, IO_FUNC_BUTT},
            {"TSO0_VALID", 0x6, IO_FUNC_BUTT},
        }
    },
    {0x7C, 0x130, "io_share_31", "GPIO3_7", 0, 5,
        {
            {"GPIO3_7", 0x0, IO_FUNC_BUTT},
            {"I2S_DOUT0", 0x1, IO_FUNC_BUTT},
            {"TSI1_D0；", 0x3, IO_FUNC_TSI1_D0},
            {"SF_CSN", 0x5, IO_FUNC_BUTT},
            {"TSO0_CLK", 0x6, IO_FUNC_BUTT},
        }
    },
    {0x80, 0x130, "io_share_32", "GPIO4_0", 0, 6,
        {
            {"GPIO4_0", 0x0, IO_FUNC_BUTT},
            {"I2S_BCLK", 0x1, IO_FUNC_BUTT},
            {"I2S_WS", 0x2, IO_FUNC_BUTT},
            {"TSI1_CLK", 0x3, IO_FUNC_TSI1_CLK},
            {"SF_HOLDN_IO3", 0x5, IO_FUNC_BUTT},
            {"TSO0_D0", 0x6, IO_FUNC_BUTT},
        }
    },
    {0x84, 0x130, "io_share_33", "GPIO4_1", 0, 5,
        {
            {"GPIO4_1", 0x0, IO_FUNC_BUTT},
            {"I2S_DIN", 0x1, IO_FUNC_BUTT},
            {"I2S_BCLK", 0x2, IO_FUNC_BUTT},
            {"TSI1_VALID", 0x3, IO_FUNC_TSI1_VALID},
            {"SF_CLK", 0x5, IO_FUNC_BUTT},
        }
    },
    {0x88, 0x130, "io_share_34", "GPIO4_2", 0, 4,
        {
            {"GPIO4_2", 0x0, IO_FUNC_BUTT},
            {"SDIO1_CWPR", 0x1, IO_FUNC_BUTT},
            {"I2S_MCLK", 0x2, IO_FUNC_BUTT},
            {"SF_SDO_IO0", 0x5, IO_FUNC_BUTT},
        }
    },
    {0x8C, 0x130, "io_share_35", "GPIO4_3", 0, 6,
        {
            {"GPIO4_3", 0x0, IO_FUNC_BUTT},
            {"SDIO1_CARD_PWR", 0x1, IO_FUNC_BUTT},
            {"I2C1_SCL", 0x3, IO_FUNC_I2C1_SCL},
            {"I2S_RX_BCLK", 0x4, IO_FUNC_BUTT},
            {"TSI0_D2", 0x5, IO_FUNC_BUTT},
            {"TSI2_CLK", 0x6, IO_FUNC_TSI2_CLK},
        }
    },
    {0x90, 0x170, "io_share_36", "GPIO4_4", 0, 5,
        {
            {"GPIO4_4", 0x0, IO_FUNC_BUTT},
            {"SDIO1_CDATA1", 0x1, IO_FUNC_BUTT},
            {"I2S_RX_WS", 0x4, IO_FUNC_BUTT},
            {"TSI0_D1", 0x5, IO_FUNC_BUTT},
            {"I2C1_SDA", 0x6, IO_FUNC_I2C1_SDA},
        }
    },
    {0x94, 0x170, "io_share_37", "GPIO4_5", 0, 7,
        {
            {"GPIO4_5", 0x0, IO_FUNC_BUTT},
            {"SDIO1_CDATA0", 0x1, IO_FUNC_BUTT},
            {"TSI0_D1", 0x2, IO_FUNC_BUTT},
            {"TSI0_SYNC", 0x3, IO_FUNC_TSI0_SYNC},
            {"I2S_RX_MCLK", 0x4, IO_FUNC_BUTT},
            {"TSI0_D0", 0x5, IO_FUNC_TSI0_D0},
            {"I2C1_SCL", 0x6, IO_FUNC_I2C1_SCL},
        }
    },
    {0x98, 0x1F0, "io_share_38", "GPIO4_6", 0, 6,
        {
            {"GPIO4_6", 0x0, IO_FUNC_BUTT},
            {"SDIO1_CCLK_OUT", 0x1, IO_FUNC_BUTT},
            {"TSI0_D0", 0x3, IO_FUNC_TSI0_D0},
            {"I2S_MCLK", 0x4, IO_FUNC_BUTT},
            {"TSI0_CLK", 0x5, IO_FUNC_TSI0_CLK},
            {"TSI1_VALID", 0x6, IO_FUNC_TSI1_VALID},
        }
    },
    {0x9C, 0x170, "io_share_39", "GPIO4_7", 0, 6,
        {
            {"GPIO4_7", 0x0, IO_FUNC_BUTT},
            {"SDIO1_CCMD", 0x1, IO_FUNC_BUTT},
            {"TSI0_CLK", 0x3, IO_FUNC_TSI0_CLK},
            {"I2S_WS", 0x4, IO_FUNC_BUTT},
            {"TSI0_VALID", 0x5, IO_FUNC_TSI0_VALID},
            {"TSI1_D0", 0x6, IO_FUNC_TSI1_D0},
        }
    },
    {0xA0, 0x170, "io_share_40", "GPIO6_0", 0, 7,
        {
            {"GPIO6_0", 0x0, IO_FUNC_BUTT},
            {"SDIO1_CDATA3", 0x1, IO_FUNC_BUTT},
            {"TSI1_CLK", 0x2, IO_FUNC_TSI1_CLK},
            {"TSI0_VALID", 0x3, IO_FUNC_TSI0_VALID},
            {"I2S_DOUT0", 0x4, IO_FUNC_BUTT},
            {"I2C2_SCL", 0x5, IO_FUNC_I2C2_SCL},
            {"TSI0_VALID", 0x6, IO_FUNC_TSI0_VALID},
        }
    },
    {0xA4, 0x170, "io_share_41", "GPIO6_1", 0, 6,
        {
            {"GPIO6_1", 0x0, IO_FUNC_BUTT},
            {"SDIO1_CDATA2", 0x1, IO_FUNC_BUTT},
            {"I2C2_SCL", 0x3, IO_FUNC_I2C2_SCL},
            {"I2S_BCLK", 0x4, IO_FUNC_BUTT},
            {"I2C2_SDA", 0x5, IO_FUNC_I2C2_SDA},
            {"TSI0_D0", 0x6, IO_FUNC_TSI0_D0},
        }
    },
    {0xA8, 0x130, "io_share_42", "GPIO6_2", 0, 5,
        {
            {"GPIO6_2", 0x0, IO_FUNC_BUTT},
            {"SDIO1_CARD_DET", 0x1, IO_FUNC_BUTT},
            {"I2C2_SDA", 0x3, IO_FUNC_I2C2_SDA},
            {"I2S_DIN", 0x4, IO_FUNC_BUTT},
            {"TSI0_CLK", 0x6, IO_FUNC_TSI0_CLK},
        }
    },
    {0xAC, 0x2130, "io_share_43", "GPIO6_3", 0, 2,
        {
            {"JTAG_SEL", 0x0, IO_FUNC_BUTT},
            {"GPIO6_3", 0x1, IO_FUNC_BUTT},
        }
    },
    {0xB0, 0x130, "io_share_44", "SPDIF_OUT", 0, 2,
        {
            {"GPIO6_4", 0x0, IO_FUNC_BUTT},
            {"SPDIF_OUT", 0x1, IO_FUNC_BUTT},
        }
    },
    {0xB4, 0x130, "io_share_45", "HDMITX_HOTPLUG", 0, 2,
        {
            {"HDMITX_HOTPLUG", 0x1, IO_FUNC_BUTT},
            {"GPIO6_5", 0x2, IO_FUNC_BUTT},
        }
    },
    {0xB8, 0x130, "io_share_46", "HDMITX_SDA", 0, 2,
        {
            {"HDMITX_SDA", 0x1, IO_FUNC_BUTT},
            {"GPIO6_6", 0x2, IO_FUNC_BUTT},
        }
    },
    {0xBC, 0x130, "io_share_47", "HDMITX_SCL", 0, 2,
        {
            {"HDMITX_SCL", 0x1, IO_FUNC_BUTT},
            {"GPIO6_7", 0x2, IO_FUNC_BUTT},
        }
    },
    {0xC0, 0xF30, "io_share_48", "HDMITX_CEC", 0, 2,
        {
            {"HDMITX_CEC", 0x1, IO_FUNC_BUTT},
            {"GPIO7_0", 0x2, IO_FUNC_BUTT},
        }
    },
    {0xC4, 0x170, "io_share_49", "RGMII_RXCK", 0, 4,
        {
            {"GPIO7_4", 0x0, IO_FUNC_BUTT},
            {"RGMII_RXCK", 0x1, IO_FUNC_BUTT},
            {"RMII_TXD1", 0x2, IO_FUNC_BUTT},
            {"SDIO0_CDATA1", 0x3, IO_FUNC_BUTT},
        }
    },
    {0xC8, 0x170, "io_share_50", "RGMII_RXDV", 0, 4,
        {
            {"GPIO7_5", 0x0, IO_FUNC_BUTT},
            {"RGMII_RXDV", 0x1, IO_FUNC_BUTT},
            {"RMII_TXD0", 0x2, IO_FUNC_BUTT},
            {"SDIO0_CDATA0", 0x3, IO_FUNC_BUTT},
        }
    },
    {0xCC, 0x1F0, "io_share_51", "RGMII_RXD0", 0, 4,
        {
            {"GPIO7_6", 0x0, IO_FUNC_BUTT},
            {"RGMII_RXD0", 0x1, IO_FUNC_BUTT},
            {"RMII_TXEN", 0x2, IO_FUNC_BUTT},
            {"SDIO0_CCLK_OUT", 0x3, IO_FUNC_BUTT},
        }
    },
    {0xD0, 0x170, "io_share_52", "RGMII_RXD1", 0, 4,
        {
            {"GPIO7_7", 0x0, IO_FUNC_BUTT},
            {"RGMII_RXD1", 0x1, IO_FUNC_BUTT},
            {"RMII_RXDV", 0x2, IO_FUNC_BUTT},
            {"SDIO0_CCMD", 0x3, IO_FUNC_BUTT},
        }
    },
    {0xD4, 0x170, "io_share_53", "RGMII_RXD2", 0, 4,
        {
            {"GPIO8_0", 0x0, IO_FUNC_BUTT},
            {"RGMII_RXD2", 0x1, IO_FUNC_BUTT},
            {"RMII_RXD0", 0x2, IO_FUNC_BUTT},
            {"SDIO0_CDATA3", 0x3, IO_FUNC_BUTT},
        }
    },
    {0xD8, 0x170, "io_share_54", "RGMII_RXD3", 0, 4,
        {
            {"GPIO8_1", 0x0, IO_FUNC_BUTT},
            {"RGMII_RXD3", 0x1, IO_FUNC_BUTT},
            {"RMII_RXD1", 0x2, IO_FUNC_BUTT},
            {"SDIO0_CDATA2", 0x3, IO_FUNC_BUTT},
        }
    },
    {0xDC, 0x130, "io_share_55", "RGMII_RST", 0, 4,
        {
            {"GPIO7_1", 0x0, IO_FUNC_BUTT},
            {"RGMII_RST", 0x1, IO_FUNC_BUTT},
            {"UART3_TXD", 0x2, IO_FUNC_BUTT},
            {"FE_LED_ACT", 0x3, IO_FUNC_BUTT},
        }
    },
    {0xE0, 0x130, "io_share_56", "RGMII_MDIO", 0, 4,
        {
            {"GPIO7_2", 0x0, IO_FUNC_BUTT},
            {"RGMII_MDIO", 0x1, IO_FUNC_BUTT},
            {"UART3_RXD", 0x2, IO_FUNC_BUTT},
            {"FE_LED_BASE", 0x3, IO_FUNC_BUTT},
        }
    },
    {0xE4, 0x130, "io_share_57", "RGMII_MDCK", 0, 4,
        {
            {"GPIO7_3", 0x0, IO_FUNC_BUTT},
            {"RGMII_MDCK", 0x1, IO_FUNC_BUTT},
            {"RMII_RST", 0x2, IO_FUNC_BUTT},
            {"SDIO0_CARD_DET", 0x3, IO_FUNC_BUTT},
        }
    },
    {0xE8, 0x170, "io_share_58", "RGMII_TXEN", 0, 3,
        {
            {"GPIO8_2", 0x0, IO_FUNC_BUTT},
            {"RGMII_TXEN", 0x1, IO_FUNC_BUTT},
            {"BOOT_SEL0", 0x2, IO_FUNC_BUTT},
        }
    },
    {0xEC, 0x170, "io_share_59", "RGMII_TXCK", 0, 3,
        {
            {"GPIO8_3", 0x0, IO_FUNC_BUTT},
            {"RGMII_TXCK", 0x1, IO_FUNC_BUTT},
            {"UART3_CTSN", 0x2, IO_FUNC_BUTT},
        }
    },
    {0xF0, 0x170, "io_share_60", "RGMII_TXD3", 0, 3,
        {
            {"GPIO8_4", 0x0, IO_FUNC_BUTT},
            {"RGMII_TXD3", 0x1, IO_FUNC_BUTT},
            {"UART3_RTSN", 0x2, IO_FUNC_BUTT},
        }
    },
    {0xF4, 0x170, "io_share_61", "RGMII_TXD2", 0, 4,
        {
            {"GPIO8_5", 0x0, IO_FUNC_BUTT},
            {"RGMII_TXD2", 0x1, IO_FUNC_BUTT},
            {"RMII_MDCK", 0x2, IO_FUNC_BUTT},
            {"BOOT_SEL1", 0x3, IO_FUNC_BUTT},
        }
    },
    {0xF8, 0x170, "io_share_62", "RGMII_TXD1", 0, 4,
        {
            {"RGMII_TXD1", 0x1, IO_FUNC_BUTT},
            {"RMII_MDIO", 0x2, IO_FUNC_BUTT},
            {"SDIO0_CWPR", 0x3, IO_FUNC_BUTT},
            {"GPIO8_6", 0x4, IO_FUNC_BUTT},
        }
    },
    {0xFC, 0x170, "io_share_63", "RGMII_TXD0", 0, 4,
        {
            {"RGMII_TXD0", 0x1, IO_FUNC_BUTT},
            {"RMII_REFCLK", 0x2, IO_FUNC_BUTT},
            {"SDIO0_CARD_PWR", 0x3, IO_FUNC_BUTT},
            {"GPIO8_7", 0x4, IO_FUNC_BUTT},
        }
    },
    {0x100, 0x130, "io_share_64", "CLKOUT_25M", 0, 2,
        {
            {"GPIO9_0", 0x0, IO_FUNC_BUTT},
            {"CLKOUT_25M", 0x1, IO_FUNC_BUTT},
        }
    },
    {0x104, 0x0, "io_share_65", "PMC_CPU0", 0, 2,
        {
            {"PMC_CPU0", 0x0, IO_FUNC_BUTT},
            {"GPIO9_1", 0x1, IO_FUNC_BUTT},
        }
    },

};

chip_reg::chip_reg()
{
    pinmux_reg = g_pinmux_reg;
    pinmux_reg_base = PINMUX_REG_BASE;


}
chip_reg::~chip_reg()
{

}

pinmux_reg_t* chip_reg::get_pinmux_reg_by_pinname(char *pin_name)
{
    int i = 0;
    pinmux_reg_t *reg = g_pinmux_reg;

    for(i=0; i<sizeof(g_pinmux_reg)/sizeof(pinmux_reg_t); i++) {
        if(strcmp(pin_name, reg->pin_name) == 0) {
                return reg;
        }
        reg++;
    }

    return NULL;
}

U32 chip_reg::get_regval_by_funcname(pinmux_reg_t *reg, char *func_name)
{
    int i = 0;

    for(i=0; i<reg->io_share_num; i++) {
        if(strcmp(func_name, reg->io_share[i].io_func_name) == 0) {
            return reg->io_share[i].reg_val | reg->reset_val;
        }
    }
    return 0;
}

pinmux_reg_t* chip_reg::get_pinmux_reg_config_by_funcname(char *func_name, U32 *reg_addr, U32 *reg_val)
{
    int i = 0;
    int j = 0;
    pinmux_reg_t *reg = g_pinmux_reg;

    for(i=0; i<sizeof(g_pinmux_reg)/sizeof(pinmux_reg_t); i++) {
        for(j=0; j<reg->io_share_num; j++) {
            if(strcmp(func_name, reg->io_share[j].io_func_name) == 0) {

                *reg_addr = pinmux_reg_base + reg->offset_addr;
                *reg_val = reg->io_share[j].reg_val | reg->reset_val;
                return reg;
            }
        }
        reg++;
    }
    qDebug()<<"can't find pinmux_reg by func_name! func_name="<<func_name;

    return NULL;
}

pinmux_reg_t* chip_reg::get_pinmux_reg_config(char *pin_name, char *func_name, U32 *reg_addr, U32 *reg_val)
{
    pinmux_reg_t *reg = get_pinmux_reg_by_pinname(pin_name);
    if(!reg) {
        qDebug()<<"can't find pinmux_reg! pinname="<<pin_name<<"func_name"<<func_name;
        qDebug()<<"search_reg_by_funcname";
        reg = get_pinmux_reg_config_by_funcname(func_name, reg_addr, reg_val);
        return reg;
    }
    *reg_addr = pinmux_reg_base + reg->offset_addr;
    *reg_val = get_regval_by_funcname(reg, func_name);

    qDebug()<<"regaddr:"<<QString::number(*reg_addr,16)<<"regval:"<<QString::number(*reg_val,16);

    return reg;
}

