/////////////////////////////////////////////
//Board specific macro define
//begin--------------------------------------
#define _QTFIRMWARE_NUM_OF_CARD 4//define max number of cards to support
//#define _QTFIRMWARE_QT1125_H_
//#define _QTFIRMWARE_QT1128_H_
//#define _QTFIRMWARE_QT1130_H_
//#define _QTFIRMWARE_QT1135_H_
//#define _QTFIRMWARE_QT1138_H_
//#define _QTFIRMWARE_QT1229_H_
//#define _QTFIRMWARE_QT1238_H_
//#define _QTFIRMWARE_QT156_H_
//#define _QTFIRMWARE_QT8852_H_
//#define _QTFIRMWARE_QT9132_H_
//#define _QTFIRMWARE_QT7350_H_
//#define _QTFIRMWARE_PCIEO_1625_H_
//#define _QTFIRMWARE_QT7135_H_
//#define _QTFIRMWARE_CPCIE161412_H_
//#define _QTFIRMWARE_PCIE16100_H_
#define _QTFIRMWARE_ALLINONE_H_
#define _QTFIRMWARE_ALLINONE_FREF_H_ 100000000//Hz
#define _QTFIRMWARE_ALLINONE_REFDIV_H_ 1//1~(1<<14-1) should always be 1
#define _QTFIRMWARE_PRODUCT_MODEL (QTFM_PRODUCT_MODE_QT1138AC6)
//#define COUPLE_DC
#define COUPLE_AC
#define AUTO_CALIBRATION
//end---------------------------------------

#define MAX_DAC_NUM 8
#define MAX_INPUT_RANGE_NUM 8
#define MAX_GAIN_STEP_NUM 256
#define PENDINGS 8
#define MORE_FILE 8
#if ((defined(_QTFIRMWARE_QT1128_H_)) || (defined(_QTFIRMWARE_QT1130_H_)) || defined(_QTFIRMWARE_QT1238_H_) || defined(_QTFIRMWARE_QT1229_H_) || defined(_QTFIRMWARE_QT156_H_))
    #define _QTFIRMWARE_FORCE_IODELAY_H_//define if no IOdelay calibration is supported
#endif

#ifndef _QTFIRMWARE_COMMON_H_
#define _QTFIRMWARE_COMMON_H_

//PCIE Register
#define REGISTER_PCIE_CONTROL_STATUS                0//Device Control Status Register (DCSR)
#define REGISTER_PCIE_DMA_CONTROL_STATUS            0x04//Device DMA Control Status Register (DDMACR)
#define REGISTER_PCIE_DMA_UP_TLP_ADDRESS_1          0x08//DMA up TLP Address
#define REGISTER_PCIE_DMA_UP_TLP_ADDRESS_2          0x0c//DMA up TLP Address
#define REGISTER_PCIE_DMA_UP_TLP_ADDRESS_3          0x10//DMA up TLP Address
#define REGISTER_PCIE_DMA_UP_TLP_ADDRESS_4          0x14//DMA up TLP Address
#define REGISTER_PCIE_DMA_DOWN_TLP_ADDRESS_1        0x18//DMA down TLP Address
#define REGISTER_PCIE_DMA_DOWN_TLP_ADDRESS_2        0x1c//DMA down TLP Address
#define REGISTER_PCIE_DMA_DOWN_TLP_ADDRESS_3        0x20//DMA down TLP Address
#define REGISTER_PCIE_DMA_DOWN_TLP_ADDRESS_4        0x24//DMA down TLP Address
#define REGISTER_PCIE_MAILBOX_DOWN_TLP_ADDRESS_1    0x50//Mailbox down TLP Address
#define REGISTER_PCIE_MAILBOX_DOWN_TLP_ADDRESS_2    0x54//Mailbox down TLP Address
#define REGISTER_PCIE_MAILBOX_DOWN_TLP_ADDRESS_3    0x58//Mailbox down TLP Address
#define REGISTER_PCIE_MAILBOX_DOWN_TLP_ADDRESS_4    0x5c//Mailbox down TLP Address
#define REGISTER_PCIE_MAILBOX_UP_TLP_ADDRESS_1      0x60//Mailbox up TLP Address
#define REGISTER_PCIE_MAILBOX_UP_TLP_ADDRESS_2      0x64//Mailbox up TLP Address
#define REGISTER_PCIE_MAILBOX_UP_TLP_ADDRESS_3      0x68//Mailbox up TLP Address
#define REGISTER_PCIE_MAILBOX_UP_TLP_ADDRESS_4      0x6c//Mailbox up TLP Address
#define REGISTER_PCIE_TEST_READ_WRITE               0x70//Test register
#define REGISTER_PCIE_SYSTEM_CONTROL                0x74//System Control Register
#define REGISTER_PCIE_DMA_UP_TLP_STATUS             0x78//DMA up TLP Status
#define REGISTER_PCIE_DMA_UP_TX_TIME_LSB            0X88//DMA UP time
#define REGISTER_PCIE_DMA_UP_TX_TIME_MSB            0X8c//DMA UP time
//MicroBlaze Register
#define REGISTER_MICROBLAZE_MAILBOX_DOWN_TLP_ADDR_1 0//Mailbox down TLP Address for MicroBlaze
#define REGISTER_MICROBLAZE_MAILBOX_DOWN_TLP_ADDR_2 0x04//Mailbox down TLP Address for MicroBlaze
#define REGISTER_MICROBLAZE_MAILBOX_DOWN_TLP_ADDR_3 0x08//Mailbox down TLP Address for MicroBlaze
#define REGISTER_MICROBLAZE_MAILBOX_DOWN_TLP_ADDR_4 0x0c//Mailbox down TLP Address for MicroBlaze
#define REGISTER_MICROBLAZE_MAILBOX_UP_TLP_ADDR_1   0x10//Mailbox up TLP Address for MicroBlaze
#define REGISTER_MICROBLAZE_MAILBOX_UP_TLP_ADDR_2   0x14//Mailbox up TLP Address for MicroBlaze
#define REGISTER_MICROBLAZE_MAILBOX_UP_TLP_ADDR_3   0x18//Mailbox up TLP Address for MicroBlaze
#define REGISTER_MICROBLAZE_MAILBOX_UP_TLP_ADDR_4   0x1c//Mailbox up TLP Address for MicroBlaze
#define REGISTER_MICROBLAZE_INTERRUPT               0x20//Interrupt Register for MicroBlaze
//SPI Register
#define REGISTER_SPI_CONTROL                        0
#define REGISTER_SPI_CONFIG                         0x04
#define REGISTER_SPI_GPO_CONFIG                     0x08
#define REGISTER_SPI_ADDRESS                        0x0c//SPI地址(包括命令)，最高两位为2则是写，为1则为读
#define REGISTER_SPI_WRITE                          0x10
#define REGISTER_SPI_READ                           0x14
#define REGISTER_SPI_STROBE_CONFIG                  0x18
//ADDA Register
#define REGISTER_ADDA_BASEADDR                      0x80010000//0x43c10000//基地址
//FIXME!
#define REGISTER_USER_BASEADDR                      0xFFFFFFFF//(undefined)Base address of user specific registers
#define REIGSTER_SYSCTL_BASEADDR                    0x80080000//0x43c20000//system control register base address
#define REGISTER_DAC_BASEADDR                       0x80030000//0x43c40000//DAC control register base address
#define REGISTER_SPI_BASEADDR                       0x80070000//0x43c00000//SPI control register base address

//Perripheral devices
#define REGISTER_ADDA_CONTROL_CONFIG                0//本通道的控制和设置
#define REGISTER_ADDA_TRIGGER_REF_LEVEL             0x04//通道触发上下沿基准电平
#define REGISTER_ADDA_PULSE_PERIOD                  0x08//内部脉冲周期（AD时钟数）
#define REGISTER_ADDA_PULSE_WIDTH                   0x0c//内部脉冲宽度（AD时钟数）
#define REGISTER_ADDA_TRIGGER_LENGTH                0x10//触发长度（AD时钟数）
#define REGISTER_ADDA_TRIGGER_LATENCY_LOW           0x14//触发延时低位（AD时钟数）
#define REGISTER_ADDA_TRIGGER_LATENCY_HIGH          0x18//触发延时高位（AD时钟数）
#define REGISTER_ADDA_TRIGGER_TIMES                 0x1c//触发次数
#define REGISTER_ADDA_TRIGGER_SOURCE_LOW            0x20//触发源设置低位,16个触发源的设置
#define REGISTER_ADDA_TRIGGER_SOURCE_HIGH           0x24//触发源设置高位,16个触发源的设置
#define REGISTER_ADDA_CURRENT_TIME_LOW              0x28//当前时间设置低位
#define REGISTER_ADDA_CURRENT_TIME_HIGH             0x2c//当前时间设置高位
#define REGISTER_ADDA_IODELAY_CONTROL               0x30//用于调整AD数据总线上的IODELAY
#define REGISTER_ADDA_DMA_LENGTH                    0x34//AD DMA长度,单位为DMA位宽，用于产生tlast信号
#define REGISTER_ADDA_TIMESTAMP_LENGTH              0x38//时间戳DMA长度,单位为DMA位宽，用于产生tlast信号
#define REGISTER_ADDA_MAX_DMA_LEGNTH                0x3c//最大DMA长度限制，单位为AD时钟数，单次工作总数据量（不包括最后的tlast）达到此长度时强制停止，并产生一个中断。设为0时禁用此功能。
#define REGISTER_ADDA_POST_TRIGGER_LENGTH           0x40//触发结束后继续采集的长度（AD时钟数），仅用于电平触发
#define REGISTER_ADDA_TRIGGER_CHANNEL_SELECT        0x44//通道出发模式时通道选择寄存器
#define REGISTER_ADDA_PLL_CONFIG                    0x48//PLL configuration
#define REGISTER_ADDA_CFG_OFST                      0x4C
#define REGISTER_ADDA_CONTROL_3                     0x70//data format convertion, freq_div,data_reverse
#define REGISTER_ADDA_DMA_COUNT                     0x78//DMA计数,DMA发送长度计数
#define REGISTER_ADDA_STATUS_ERROR                  0x7c//状态及错误
#define REGISTER_ADDA_CONTROL_CONFIG_CONT           0x50//控制和设置续
#define REGISTER_ADDA_DC_OFFSET_TUNE                0x54//各个通道直流电平量化值配置寄存器
#define REGISTER_ADDA_GPS_SECOND                    0x58//GPS second config
#define REGISTER_ADDA_TS_COUNTING_PERIOD            0x5c//(Period of AD clock)/(2^248)
#define REGISTER_ADDA_ACCUMULATOR_SET               0x60//Accumulator setting
#define REGISTER_ADDA_ABAMODE_SET                   0x64//ABA mode setting
#define REGISTER_ADDA_PRETRIGGER_SET                0x68//Setup pre-trigger length
#define REGISTER_ADDA_AVERAGE_SET                   0x6c//average and gain
#define REGISTER_ADDA_STATUS                        0x7c//status
//SOC system registers
#define REGISTER_SOC_STATUS                         0x7c//系统状态及错误
//PCIe AXI registers
#define REGISTER_PCIE_AXI_STATUS                    0x7c//状态寄存器
#define REGISTER_PCIE_AXI_TRIGLENGTH                0x78//计数器模式下multiple模式的segment Length
//Commands
//Commit
#define CMD_MB_GET_DEVICE_INFO                      0x30000000//read:PlatForm version,product code part1,product code part2
#define CMD_MB_GET_DEVICE_VERSION1                  0x30000001//read:Hardware version,RTL version,Driver version
#define CMD_MB_GET_DEVICE_VERSION2                  0x30000002//read:UI Version,EDK Version,APP Version
#define CMD_MB_GET_DEVICE_EXCEPTION_STATUS          0x30000003//read:get exception status in edk during transfer
#define CMD_MB_GET_CURRENT_RXDATA_LEN               0x30000004//Get current rx data length in buffer which is ready for transfer
#define CMD_MB_TRIGGER_SOURCE_READ                  0x30000315//Read registers that AD_INTF_CFG6 command writes to//Read command with its tag starts with 0x3xxxxxxx
#define CMD_MB_READ_32BIT_REGISTER                  0x30000a01//read 32 bit register
#define CMD_MB_GET_RXBUF_LEN                        0x30000601//Return PCIe axi dma buffer length in Byte
#define CMD_MB_READ_FLASH_U32                       0x30000325//Read specific flash address and return int16 data
#define CMD_MB_GPIO_READ                            0x30000326//Set direction, read current values on GPIO line
#define CMD_MB_READ_FLASH_DBL                       0x30000327//Read data of double from XCF or SPI flash
#define CMD_MB_READ_FLASH_DEVICE_INFO               0x30000328//Read flash device ID and manufactory code from edk
#define CMD_MB_READ_SPI_REGISTER                    0x30000329//Read back register value through SPI 
#define CMD_MB_GET_DEVICE_FPGA_DMA                  0x10000130//读取FPGA-Dma版本信息
#define CMD_MB_CLOCK_CONFIG                         0x300//时钟配置命令
#define CMD_MB_ALLINONE_CLOCK_CONFIG                0x318//Configure AllInOne Clock board
#define CMD_MB_CLOCK_INITIAL                        0x319//Initialize AllInOne Clock board before configuration
#define CMD_MB_SOFT_TRIGGER_PULSE                   0x309//Feed in a soft trigger pulse into ADC interface if soft trigger mode is enabled
#define CMD_MB_ENABLE_PULSE                         0x30a//enable internal pulse generator(offset=0x0) bit[20]
#define CMD_MB_USER_STOP                            0x30b//Send this command to board to disable trig_en if user  press stop button
#define CMD_MB_GET_TIMESTAMP                        0x30d//Get Timestamp Data
#define CMD_MB_READY_TO_GET_DATA                    0x30e//This command is an acknowledge to board that PC is ready to receive new type of data. It indicates that the last pcie TX DMA is completed gracefully by PC then get pcie ready to receive new type of data.
#define CMD_MB_RESET_ADC_INTERFACE                  0x313//To reset ADC interface logic.The command should be executed every time when ADC work mode changes.
#define CMD_MB_RESET_ADC_DEVICE                     0x314//To reset ADC device.Rarely used.
#define CMD_MB_RESET_BOARD                          0x900//board system global soft-reset
#define CMD_MB_TX_DMA_COMPLETE                      0x20000000//Send information to PC indicating that TX DMA transfer is done. Note that there might be datas not aligned with 128-byte to comprise of a TLP
#define CMD_MB_TIMESTAMP_READY                      0x20000001//Write this command to PC indicating that a Timestamp DMA is just completed and require a pcie DMA slot to read these data out.
#define CMD_MB_WORK_MODE_SELECT                     0x600//Choose transfer/trigger mode
#define CMD_MB_WORK_MODE_CONFIG                     0x601//setup work mode step2
#define CMD_MB_AD_ENABLE                            0x800//AD ENABLE and get ready to start transfer. Samples are sent to memory once RX DMA is commenced
#define CMD_MB_WRITE_32BIT_REGISTER                 0xa00//write 32 bit register
#define CMD_MB_WRITE_SPI_REGISTER                   0xa02//write spi register
#define CMD_MB_SEND_32BIT_REGISTER                  0x20000002//send read value of 32bit register to pc
#define CMD_MB_WRITE_IO_DELAY_REGISTER              0xa04//write IO delay register
#define CMD_MB_SET_IO_DELAY_OFFSET                  0xa05//Set IO delay offset for a individual data bus
#define CMD_MB_DDS_CONFIG                           0xb00//Configurate DDS chip(AD9912) for ADC amplitue and phase calibration purpose.
#define CMD_MB_TUNE_DAC_OFFSET                      0x400//offset dac tuning command
#define CMD_MB_TUNE_PGA                             0x401//PGA tuning
#define CMD_MB_TUNE_ADC_GAIN                        0x402//tune digital gain in ADC
#define CMD_MB_PLL_PHASE_SHIFT                      0x31b//Config MMCM in FPGA to shift clock phase for QT1125 only
#define CMD_MB_FORCE_TLAST                          0x31c//Force a tlast signal asserted to RX DMA
#define CMD_MB_ADDA_CONTROL_CONFIG_CONT             0x31d//ADDA control(con't)
#define CMD_MB_TIMESTAMP_SELECT                     0x31e//Select timestamp source between system and user logic
#define CMD_MB_AUTO_SYNC                            0x331//IO delay auto-sync
//Config
#define CMD_MB_ADC_SETUP                            0x301//ADC Channel Setup
#define CMD_MB_ADC_INTF_MODE_CONFIG                 0x302//ADC Work Mode Setup
#define CMD_MB_EDGE_VOLTAGE                         0x303//rise/fall-ing edge  reference voltage level(0x4)
#define CMD_MB_PULSE_PERIOD_WIDTH                   0x304//internal pulse period & width
#define CMD_MB_TRIGGER_LATENCY                      0x305//Trigger latency
#define CMD_MB_TRIGGER_SOURCE                       0x307//Trigger Source
#define CMD_MB_CURRENT_TIME                         0x308//Current Time
#define CMD_MB_TIMESTAMP_CONFIG                     0x30c//Enable/Disable Timestamp mode
#define CMD_MB_TRIGGER_MODE                         0x30f//Trigger Mode
#define CMD_MB_TRIGGER_HOLD                         0x310//Trigger Hold
#define CMD_MB_TRIGGER_MASK                         0x311//Trigger Mask('or','and')
#define CMD_MB_DATA_COMPRESS                        0x312//Data Width Convert, internal data compression is enabled to save bandwidth
#define CMD_MB_START_RX_DMA                         0x700//Start RX DMA
#define CMD_MB_START_DDS                            0x701//Start DDS
#define CMD_MB_START_REPLAY                         0x702//start replay
#define CMD_MB_SET_DA_PLAYBACK_MODE                 0xc00//Setup DA play back mode
#define CMD_MB_TRIGGER_SOURCE_CONFIG                0x315//Enable/disable one trigger source each time this command is executed.
#define CMD_MB_TRIGGER_CHANNEL_SELECT               0x316//Choose which physical channel as trigger source
#define CMD_MB_SETUP_INPUT_CHANNEL                  0x31a//choose active input physical channel
#define CMD_MB_CALIB_STATUS_CONFIG                  0x317//Flag calibration status to control other command behavior, such as 0x301, 0x900(3), etc.
#define CMD_MB_CREATE_WAVEFORM                      0x500//Create waveform with its attributes such like index, length and loop count.
#define CMD_MB_POSTTRIGGER_LENGTH                   0x31f//Write post-trigger length, in samples, for level trigger only
#define CMD_MB_GPIO_SET                             0x320//Configure GPIO, direction, digital acquisitions
#define CMD_MB_ABAMODE_SET                          0x321//Setup ABA mode
#define CMD_MB_DIGIN_LATENCY                        0x322//Change digital input latency by AD clock cycles
#define CMD_MB_DATA_FORMAT                          0x323//offset binary or Two's complement code
#define CMD_MB_GPIO_WRITE                           0x324//Set direction, write user define values
#define CMD_MB_WRITE_FLASH_DBL                      0x328//Write data of double to XCF or SPI flash
#define CMD_MB_ERASE_FLASH                          0x329//Write data of double to XCF or SPI flash
#define CMD_MB_NOTIFY_SIZEB                         0x330//Minimize notified size in bytes
#define CMD_MB_ENABLE_REPLAY_MODE                   0x332
#define CMD_MB_DMA_LENGTH                           0x333//Set DMA length in bytes for HV/MV
#define CMD_MB_DA_DDS_CONFIG                        0x334
#define CMD_MB_MUTE_ADDA_CLK                        0x335//shutdown LO1/LO2 of HMC835
#define CMD_MB_SPI2GPIO                             0x336//convert spi to GPIO bus
#define CMD_MB_MODULATION                           0x337//set DAC modulation
//BPI flash
#define FLASH_BASE_ADDR                             (0x07FFFC0*2)//Byte address
#define FLASH_DATA_LEN                              0x24/2
//SPI flash(@ADDA card)
#define SPI_FLASH_BASE_ADDR                         0x01000000//Byte address

//To be revised
#define DMABUFCNT                                   PENDINGS
#define DRV_MALLOC_LEN_FOR_DMA                      0x1000000 //0x100000 is 32 MB
#define EACH_DMA_MAX_LEN                            (32*1024*1024)//(8*1024*1024) //tx max len is 8MB.
#define EACH_DMA_RX_MAX_LEN                         (EACH_DMA_MAX_LEN) //rx max len is 4MB.
#define EACH_DMA_MIN_LEN                            0x40//64 bytes per transaction on axis
//To be revised

typedef enum _tag_QTfm_Common_BoardID
{
    QTFM_COMMON_BOARDID_1125,
    QTFM_COMMON_BOARDID_1138
}QTFM_COMMON_BOARDID,*PQTFM_COMMON_BOARDID;
typedef enum _tag_QTfm_Common_Clock_Reference
{
    QTFM_COMMON_CLOCK_REF_MODE_0                    = 0,//OCXO as reference clock with higher clock quality
    QTFM_COMMON_CLOCK_REF_MODE_1,                       //External reference clock input from panel
    QTFM_COMMON_CLOCK_REF_MODE_2,                       //TCXO as reference clock

    QTFM_COMMON_CLOCK_VCO_MODE_0,                       //Internal VCO mode
    QTFM_COMMON_CLOCK_VCO_MODE_1,                       //External VCO mode
    QTFM_COMMON_CLOCK_INTERNAL_VCO_MIN              = 2000000000,//Internal VCO minimum frequency
    QTFM_COMMON_CLOCK_INTERNAL_VCO_MAX              = 4100000000L,//Internal VCO maximum frequency    
    QTFM_COMMON_CLOCK_EXTERNAL_VCO_FREQUENCY        = 2500000000L,//Hz

    QTFM_COMMON_CLOCK_FREQUENCY_MIN                 = 33064516,//Hz
    QTFM_COMMON_CLOCK_FREQUENCY_MAX                 = 4100000000L,//Hz
    QTFM_COMMON_CLOCK_FREQUENCY_GRANULARITY         = 10,//Hz
    QTFM_COMMON_CLOCK_INTERNAL_LF_BANDWIDTH         = 200000//Hz, bandwidth of internal pll loop filter
}QTFM_COMMON_CLOCK_REFERENCE,*PQTFM_COMMON_CLOCK_REFERENCE;
typedef enum _tag_QTfm_Common_ADC_Clock
{
    QTFM_COMMON_ADC_CLOCK_MODE_0                    = 0,//Choose on-board PLL as clock source
    QTFM_COMMON_ADC_CLOCK_MODE_1,                       //Choose external clock from panel as clock source
}QTFM_COMMON_ADC_CLOCK,*PQTFM_COMMON_ADC_CLOCK;
typedef enum _tag_QTfm_Common_Clock_Frequency
{
    QTFM_COMMON_CLOCK_FREQUENCY_DEVIDE_6            = 1,//416.67MHz
    QTFM_COMMON_CLOCK_FREQUENCY_DEVIDE_5,               //500MHz
    QTFM_COMMON_CLOCK_FREQUENCY_DEVIDE_4,               //625MHz
    QTFM_COMMON_CLOCK_FREQUENCY_DEVIDE_3,               //833.33MHz
    QTFM_COMMON_CLOCK_FREQUENCY_DEVIDE_2,               //1250MHz
    QTFM_COMMON_CLOCK_FREQUENCY_DEVIDE_1,               //2500MHz

    QTFM_COMMON_CLOCK_FREQUENCY_DEVIDE_1_VALUE      = 2500//MHz
}QTFM_COMMON_CLOCK_FREQUENCY,*PQTFM_COMMON_CLOCK_FREQUENCY;
typedef enum _tag_QTfm_Common_Trigger_Source
{
    QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_1           = 1,//External Trigger
    QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_2,              //External Trigger
    QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_3,              //External Trigger
    QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_4,              //External Trigger
    QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_5,              //External Trigger
    QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_6,              //External Trigger
    QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_7,              //External Trigger
    QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_8,              //External Trigger
    QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_9,              //External Trigger
    QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_10,             //External Trigger
    QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_11,             //External Trigger
    QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_12,             //External Trigger
    QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_13,             //External Trigger
    QTFM_COMMON_TRIGGER_SOURCE_CHANNEL,                 //Channel Trigger
    QTFM_COMMON_TRIGGER_SOURCE_PULSE,                   //Pulse Trigger
    QTFM_COMMON_TRIGGER_SOURCE_SOFTWARE,                //Software Trigger

    QTFM_COMMON_TRIGGER_SOURCE_MAX                      //Caution:Change this
}QTFM_COMMON_TRIGGER_SOURCE,*PQTFM_COMMON_TRIGGER_SOURCE;
typedef enum _tag_QTfm_Common_Transmit_Direction
{
    QTFM_COMMON_TRANSMIT_DIRECTION_BRD2PC,               //tx
    QTFM_COMMON_TRANSMIT_DIRECTION_PC2BRD                //rx
}QTFM_COMMON_TRANSMIT_DIRECTION,*PQTFM_COMMON_TRANSMIT_DIRECTION;
typedef enum _tag_QTfm_Common_AD_Work_Mode
{
    QTFM_COMMON_AD_WORK_MODE_NORMAL                 = 0,//Normal
    QTFM_COMMON_AD_WORK_MODE_RAMP,                      //Ramp
    QTFM_COMMON_AD_WORK_MODE_FLASH_11,                  //Flash 11
    QTFM_COMMON_AD_WORK_MODE_FLASH_12,                  //Flash 12
    QTFM_COMMON_AD_WORK_MODE_FLASH_16                   //Flash 16
}QTFM_COMMON_AD_WORK_MODE,*PQTFM_COMMON_AD_WORK_MODE;
typedef enum _tag_QTfm_Common_AD_Interface_Mode
{
    QTFM_COMMON_AD_INTERFACE_MODE_NORMAL            = 0,//normal mode, where adc data is received and send to memory
    QTFM_COMMON_AD_INTERFACE_MODE_TEST                  //test mode, a counter will be send to memory
}QTFM_COMMON_AD_INTERFACE_MODE,*PQTFM_COMMON_AD_INTERFACE_MODE;
typedef enum _tag_QTfm_Common_Timestamp_Init_Mode
{
    QTFM_COMMON_TIMESTAMP_INIT_MODE_DISABLE         = 0,//Disable timestamp mode. Timestamp counter keep no change and values is param2 and param3 are ignored
    QTFM_COMMON_TIMESTAMP_INIT_MODE_ENABLE          = 1,//Enable timestamp and initialize timestamp counter to the values contains in Param2 and Parame3 column
    QTFM_COMMON_TIMESTAMP_INIT_MODE_NO_CONFIG       = 2//Enable timestamp but not re-configurate timestamp counter values.
}QTFM_COMMON_TIMESTAMP_INIT_MODE,*PQTFM_COMMON_TIMESTAMP_INIT_MODE;
typedef enum _tag_QTfm_Common_Trigger_Mode
{
    QTFM_COMMON_TRIGGER_MODE_EDGE                   = 0x50000000,//边沿触发
    QTFM_COMMON_TRIGGER_MODE_LEVEL                  = 0x60000000    //电平触发，此时触发延时和长度都无效
}QTFM_COMMON_TRIGGER_MODE,*PQTFM_COMMON_TRIGGER_MODE;
typedef enum _tag_QTfm_Common_Trigger_Type
{
    QTFM_COMMON_TRIGGER_TYPE_FALLING_EDGE           = 0,
    QTFM_COMMON_TRIGGER_TYPE_RISING_EDGE,
    QTFM_COMMON_TRIGGER_TYPE_LOW_LEVEL,
    QTFM_COMMON_TRIGGER_TYPE_HIGH_LEVEL,
    QTFM_COMMON_TRIGGER_TYPE_DOUBLE_EDGE,
    QTFM_COMMON_TRIGGER_TYPE_WINDOW_LEAVE,
    QTFM_COMMON_TRIGGER_TYPE_WINDOW_ENTER,
    QTFM_COMMON_TRIGGER_TYPE_ENHANCED_DOUBLE_EDGE
}QTFM_COMMON_TRIGGER_TYPE,*PQTFM_COMMON_TRIGGER_TYPE;
typedef enum _tag_QTfm_Common_Trigger_Hold_Mode
{
    QTFM_COMMON_TRIGGER_KEEP_MODE_DISABLE           = 0,//禁止触发保持功能
    QTFM_COMMON_TRIGGER_KEEP_MODE_ENABLE
}QTFM_COMMON_TRIGGER_HOLD_MODE,*PQTFM_COMMON_TRIGGER_HOLD_MODE;
typedef enum _tag_QTfm_Common_Trigger_Source_Mask//触发源间逻辑关系
{
    QTFM_COMMON_TRIGGER_SOURCE_MASK_OR              = 0,//'or'
    QTFM_COMMON_TRIGGER_SOURCE_MASK_AND                 //'and'
}QTFM_COMMON_TRIGGER_SOURCE_MASK,*PQTFM_COMMON_TRIGGER_SOURCE_MASK;
typedef enum _tag_QTfm_Common_DWidth_Convert_Mode//位宽转换方式
{
    QTFM_COMMON_DWIDTH_CONVERT_MODE_0_COMPLEMENT       = 0,//高位补0
    QTFM_COMMON_DWIDTH_CONVERT_MODE_COMPRESS               //'拼位
}QTFM_COMMON_DWIDTH_CONVERT_MODE,*PQTFM_COMMON_DWIDTH_CONVERT_MODE;
typedef enum _tag_QTfm_Common_Board_Work_Mode
{
    QTFM_COMMON_BOARD_WORK_MODE_STD_SIGNLE          = 0,
    QTFM_COMMON_BOARD_WORK_MODE_STD_MULTI,
    QTFM_COMMON_BOARD_WORK_MODE_FIFO_SINGLE,
    QTFM_COMMON_BOARD_WORK_MODE_FIFO_MULTI,
    QTFM_COMMON_BOARD_REPLAY_MODE_STD_SINGLE,
    QTFM_COMMON_BOARD_REPLAY_MODE_STD_CONTINUOUS,
    QTFM_COMMON_BOARD_REPLAY_MODE_STD_SINGLE_START,
    QTFM_COMMON_BOARD_REPLAY_MODE_STD_MULTIPLE,
    QTFM_COMMON_BOARD_REPLAY_MODE_FIFO_SINGLE,
    QTFM_COMMON_BOARD_REPLAY_MODE_FIFO_CONTINUOUS,
    QTFM_COMMON_BOARD_REPLAY_MODE_FIFO_MULTIPLE,
    QTFM_COMMON_BOARD_WORK_MODE_FIFO_SINGLE_LOOPBUF,
    QTFM_COMMON_BOARD_WORK_MODE_FIFO_MULTIPLE_LOOPBUF,
    QTFM_COMMON_BOARD_WORK_MODE_STD_SINGLE_PLUS_LOOPBUF,
    QTFM_COMMON_BOARD_WORK_MODE_TIMED_TRANS         = 0x70000000,
    QTFM_COMMON_BOARD_WORK_MODE_COUNTER             = 0X90000000
}QTFM_COMMON_BOARD_WORK_MODE,*PQTFM_COMMON_BOARD_WORK_MODE;
typedef enum _tag_QTfm_Common_IOOffset_Bus_Index
{
    QTFM_COMMON_IOOFFSET_BUS_INDEX_0                = 0,//Bus a
    QTFM_COMMON_IOOFFSET_BUS_INDEX_1,                   //Bus b
    QTFM_COMMON_IOOFFSET_BUS_INDEX_2,                   //Bus c
    QTFM_COMMON_IOOFFSET_BUS_INDEX_3                    //Bus d
}QTFM_COMMON_IOOFFSET_BUS_INDEX,*PQTFM_COMMON_IOOFFSET_BUS_INDEX;
typedef enum _tag_QTfm_Common_DDS_Index//DDS configuration index
{
    QTFM_COMMON_DDS_INDEX_0                         = 0,//DDS setting for 2.5GHz/500MHz input clock frequency to ADC
    QTFM_COMMON_DDS_INDEX_1,                            //DDS setting for 1.25GHz input clock frequency to ADC
    QTFM_COMMON_DDS_INDEX_2                             //DDS setting for 625MHz input clock frequency to ADC
}QTFM_COMMON_DDS_INDEX,*PQTFM_COMMON_DDS_INDEX;
typedef enum _tag_QTfm_DA_Playback_Mode
{
    QTFM_DA_PLAYBACK_MODE_STD_SINGLE                = 0,
    QTFM_DA_PLAYBACK_MODE_STD_CONTINUOUS,
    QTFM_DA_PLAYBACK_MODE_STD_SINGLE_START,
    QTFM_DA_PLAYBACK_MODE_STD_MULTIPLE,
    QTFM_DA_PLAYBACK_MODE_FIFO_SINGLE,
    QTFM_DA_PLAYBACK_MODE_FIFO_CONTINUOUS,
    QTFM_DA_PLAYBACK_MODE_FIFO_MULTIPLE
}QTFM_DA_PLAYBACK_MODE,*PQTFM_DA_PLAYBACK_MODE;
typedef enum _tag_QTfm_Product_Model
{
    QTFM_PRODUCT_MODE_QT1125AC1                     = 0,
    QTFM_PRODUCT_MODE_QT1125AC2,
    QTFM_PRODUCT_MODE_QT1125AC4,
    QTFM_PRODUCT_MODE_QT1125DC1,
    QTFM_PRODUCT_MODE_QT1125DC2,
    QTFM_PRODUCT_MODE_QT1125DC4,
    QTFM_PRODUCT_MODE_QT1128AC1,
    QTFM_PRODUCT_MODE_QT1128AC2,
    QTFM_PRODUCT_MODE_QT1128DC1,
    QTFM_PRODUCT_MODE_QT1128DC2,
    QTFM_PRODUCT_MODE_QT1130AC1,
    QTFM_PRODUCT_MODE_QT1130AC2,
    QTFM_PRODUCT_MODE_QT1130AC4,
    QTFM_PRODUCT_MODE_QT1130DC1,
    QTFM_PRODUCT_MODE_QT1130DC2,
    QTFM_PRODUCT_MODE_QT1130DC4,
    QTFM_PRODUCT_MODE_QT1135AC1,
    QTFM_PRODUCT_MODE_QT1135AC2,
    QTFM_PRODUCT_MODE_QT1135AC4,
    QTFM_PRODUCT_MODE_QT1135DC1,
    QTFM_PRODUCT_MODE_QT1135DC2,
    QTFM_PRODUCT_MODE_QT1135DC4,
    QTFM_PRODUCT_MODE_QT1138AC2,
    QTFM_PRODUCT_MODE_QT1138AC4,
    QTFM_PRODUCT_MODE_QT1138AC6,
    QTFM_PRODUCT_MODE_QT1138AC8,
    QTFM_PRODUCT_MODE_QT1138DC4,
    QTFM_PRODUCT_MODE_QT1138DC3,
    QTFM_PRODUCT_MODE_QT1138DC2,
    QTFM_PRODUCT_MODE_QT1138DC1,
    QTFM_PRODUCT_MODE_QT1229AC2,
    QTFM_PRODUCT_MODE_QT1238AC8,
    QTFM_PRODUCT_MODE_QT156AC1,
	QTFM_PRODUCT_MODE_QT156AC2
}QTFM_PRODUCT_MODEL,*PQTFM_PRODUCT_MODEL;
typedef enum _tag_QTfm_Couple_Type
{
    QTFM_COUPLE_AC                                  = 0,
    QTFM_COUPLE_DC,
}QTFM_COUPLE_TYPE,*PQTFM_COUPLE_TYPE;
typedef union _tag_QTfm_Gain_Type
{
  float f_value;
  unsigned long i_value;
}QTFM_GAIN_TYPE, *PQTFM_GAIN_TYPE;
typedef enum _tag_QTfm_Input_Channel
{
    CHANNEL_0                     = 0, //Physical channel 0
    CHANNEL_1,                         //Physical channel 1
    CHANNEL_2,                         //Physical channel 2
    CHANNEL_3,                         //Physical channel 3
    CHANNEL_4,                         //Physical channel 4
    CHANNEL_5,                         //Physical channel 5
    CHANNEL_6,                         //Physical channel 6
    CHANNEL_7,                         //Physical channel 7
    CHANNEL_8,                         //Physical channel 8
    CHANNEL_9,                         //Physical channel 9
    CHANNEL_10,                        //Physical channel 10
    CHANNEL_11,                        //Physical channel 11
    CHANNEL_12,                        //Physical channel 12
    CHANNEL_13,                        //Physical channel 13
    CHANNEL_14,                        //Physical channel 14
    CHANNEL_15,                        //Physical channel 15
    TRIG_CHANNEL_HIZ              = 0x80000000,     //Trig channel with HIZ
    TRIG_CHANNEL_50OHM            = 0x80000001      //Trig channel with 50 ohm
}QTFM_INPUT_CHANNEL,*PQTFM_INPUT_CHANNEL;
typedef enum _tag_QTfm_ABA_Mode
{
  ABA_NORMAL_MODE                 = 0,//ABA mode is disabled
  ABA_DUAL_MODE,                      //ABA dual clock mode
  ABA_SLOW_MODE                       //ABA slow clock mode
}QTFM_ABA_MODE,*PQTFM_ABA_MODE;

typedef union _tag_QTfm_Flash_dbl
{
  double dbl_value;
  //unsigned __int64 i_value;
  unsigned long long i_value;
}QTFM_FLASH_DBL, *PQTFM_FLASH_DBL;
//输入档位选择
//对于QT1138VG，QTFM_INPUT_RANGE_1~4分别表示±0.5V，±1V，±2.5V，±5V，其他值保留；
//对于QT114x系列（除QT1140），QTFM_INPUT_RANGE_1~4分别表示±0.25V，±0.5V，±1V，±2V，其他值保留；
//对于QT1125VG，QTFM_INPUT_RANGE_1~4分别表示±50mV，±100mV，±200mV，±500mV，其他值保留；
//对于QT1140，在高阻时，QTFM_INPUT_RANGE_1~6分别表示±0.5V，±1V，±2V，±5V，±10V，±20V；
//            在50欧姆时，QTFM_INPUT_RANGE_1~4分别表示±0.25V，±0.5V，±1V，±2V，其他值保留；
typedef enum _tag_QTfm_Input_Range
{
  QTFM_INPUT_RANGE_1                     = 0,  //
  QTFM_INPUT_RANGE_2,                          //
  QTFM_INPUT_RANGE_3,                          //
  QTFM_INPUT_RANGE_4,                          //
  QTFM_INPUT_RANGE_5,                          //
  QTFM_INPUT_RANGE_6                           //
}QTFM_INPUT_RANGE,*PQTFM_INPUT_RANGE;

//板卡上安装的feature，如DDC、FFT、累加平均、长预触发等
typedef enum _tag_QTfm_Feature
{
  QT_FEAT_ACC                     = 0x00000001,//accumulator with average
  QT_FEAT_PRETRIG                 = 0x00000002,//large pre-trigger length
  QT_FEAT_DDC                     = 0x00000004,//DDC on FPGA
  QT_FEAT_FFT                     = 0x00000008,//FFT on FPGA
  QT_FEAT_PD                      = 0x00000010,//pulse peak detect on FPGA
  QT_FEAT_PWM                     = 0x00000020,//pulse width modulate on FPGA
  QT_FEAT_GPS                     = 0x00000040,//GPS timestamp feature
  QT_FEAT_SCAN                    = 0x00000080,//x-y or a-b scan trigger
  QT_FEAT_NR                      = 0x00000100,//navigation radar based application with Heading/Bearing/pulse trigger feature
  QT_FEAT_GPIO                    = 0x00000200//extended GPIOs with 20-pin
}QTFM_FEATURE,*PQTFM_FEATURE;

//输入档位选择
//对于QT1138VG，QTFM_INPUT_RANGE_1~4分别表示±0.5V，±1V，±2.5V，±5V；
//对于QT114x系列，QTFM_INPUT_RANGE_1~4分别表示±0.25V，±0.5V，±1V，±2V
//对于QT1125VG，QTFM_INPUT_RANGE_1~4分别表示±50mV，±100mV，±200mV，±500mV；
//QTFM_INPUT_RANGE_5:暂时保留，无定义；
typedef enum _tag_QTfm_Term
{
  TERM_50_OHM                     = 0x80000000,  //50 ohm
  TERM_HIZ                        = 0x80000001   //Hi-Z
}QTFM_TERM,*PQTFM_TERM;

#endif

//typedef struct {
//	unsigned int BaseAddress;
//	unsigned int reg[4];
//	unsigned int PackageLen;
//	unsigned int ResetBit;
//} TestData_Config;


#define CHECK_RETURN_VALUE(value) \
  if (RES_SUCCESS != (nRet = value))\
{\
  char szText[MAX_PATH] = {0};\
  sprintf_s (szText,"Error %s:%#x(Line:%d)\n",#value,nRet,__LINE__);\
  if (&szText) {printf(szText); return 0;} else return -1;\
}

// ***********************************************************************
// macros for kilo, Mega or Giga as standard version or binary (_B) (2^x)
// ***********************************************************************

#define KILO(k)     ((uint64) 1000 * (k))
#define MEGA(m)     ((uint64) 1000 * 1000 * (m))
#define GIGA(g)     ((uint64) 1000 * 1000 * 1000 * (g))
#define KILO_B(k)   ((uint64) 1024 * (k))
#define MEGA_B(m)   ((uint64) 1024 * 1024 * (m))
#define GIGA_B(g)   ((uint64) 1024 * 1024 * 1024 * (g))
