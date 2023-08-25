#ifndef _QTFIRMWARE_1125_H_
#define _QTFIRMWARE_1125_H_


typedef enum _tag_QTfm_1125_BytesPerSample  //Bytes per sample
{
    QTFM_1125_BPSAMPLE                              = 2,
}QTFM_1125_BYTESPERSAMPLE,*PQTFM_1125_BYTESPERSAMPLE;
typedef enum _tag_QTfm_1125_Type  //QT1125 subtype  //TODO:Check
{
    QTFM_1125_TYPE_AC4                              = 1,
    QTFM_1125_TYPE_AC8                              = 2,
    QTFM_1125_TYPE_DC4                              = 4,
    QTFM_1125_TYPE_MAX                              = 3  //Modify this
}QTFM_1125_TYPE,*PQTFM_1125_TYPE;
typedef enum _tag_QTfm_1125_Trigger_Source
{
    QTFM_1125_TRIGGER_SOURCE_EXTERNAL_1             = 1, //External Trigger
    QTFM_1125_TRIGGER_SOURCE_CHANNEL                = 14, //Channel Trigger
    QTFM_1125_TRIGGER_SOURCE_PULSE,                      //Pulse Trigger
    QTFM_1125_TRIGGER_SOURCE_SOFTWARE                    //Software Trigger
}QTFM_1125_TRIGGER_SOURCE,*PQTFM_1125_TRIGGER_SOURCE;
typedef enum _tag_QTfm_1125_Term_Input //Non-adjustable
{
    QTFM_1125_TERM_INPUT_50                         = 50 //50 ohm
}QTFM_1125_TERM_INPUT,*PQTFM_1125_TERM_INPUT;
typedef enum _tag_QTfm_1125_Range_Input //Non-adjustable
{
    QTFM_1125_RANGE_INPUT_MIN                       = -250, //-250 mv
    QTFM_1125_RANGE_INPUT_MAX                       = 250 //250 mv
}QTFM_1125_RANGE_INPUT,*PQTFM_1125_RANGE_INPUT;
typedef enum _tag_QTfm_1125_Offset //TODO:Check
{
    QTFM_1125_OFFSET_0                             = 0 //mV
}QTFM_1125_OFFSET,*PQTFM_1125_OFFSET;
typedef enum _tag_QTfm_1125_Memory_Size
{
    QTFM_1125_MEMORY_SIZE_MIN                       = 64, //64 Bytes
    QTFM_1125_MEMORY_SIZE_MAX                       = 2*1024, //2*1024 MBytes = 2G

    QTFM_1125_MEMORY_SIZE_STEP                      = 64 //Step=64 Bytes
}QTFM_1125_MEMORY_SIZE,*PQTFM_1125_MEMORY_SIZE;
typedef enum _tag_QTfm_1125_Pre_Trigger
{
    QTFM_1125_PRE_TRIGGER_MIN                       = 0,
    QTFM_1125_PRE_TRIGGER_MAX                       = 8*1024, //8k Sample

    QTFM_1125_PRE_TRIGGER_GRANULARITY               = 16 //Step=32 Sample
}QTFM_1125_PRE_TRIGGER,*PQTFM_1125_PRE_TRIGGER;
typedef enum _tag_QTfm_1125_Sample_Rate
{
    QTFM_1125_SAMPLE_RATE_ACDC484                   = 5000 //5000 Msps = 5 Gsps
}QTFM_1125_SAMPLE_RATE,*PQTFM_1125_SAMPLE_RATE;
typedef enum _tag_QTfm_1125_Segment
{
    QTFM_1125_SEGMENT_MIN                           = 32, //32 Samples
    QTFM_1125_SEGMENT_MAX                           = 1024, //1024 M Samples = 1G Samples

    QTFM_1125_SEGMENT_GRANULARITY                   = 32 //32 Samples
}QTFM_1125_SEGMENT,*PQTFM_1125_SEGMENT;
typedef enum _tag_QTfm_1125_Clock_Mode
{
    QTFM_1125_CLOCK_MODE_INTERNAL                   = 0 //Internal Sampling clock
}QTFM_1125_CLOCK_MODE,*PQTFM_1125_CLOCK_MODE;
typedef enum _tag_QTfm_1125_Pulse_Width
{
    QTFM_1125_PULSE_WIDTH_MIN                       = 16, //Bytes
    QTFM_1125_PULSE_WIDTH_MAX                       = 0x7fffffc0 , //2G-64 Bytes

    QTFM_1125_PULSE_WIDTH_GRANULARITY               = 16 //Step=16 Bytes
}QTFM_1125_PULSE_WIDTH,*PQTFM_1125_PULSE_WIDTH;
typedef enum _tag_QTfm_1125_Trigger_Delay
{
    QTFM_1125_TRIGGER_DELAY_MIN                     = 0, //
    QTFM_1125_TRIGGER_DELAY_MAX                     = -1, //64bit counter,Clock Frequency/8

    QTFM_1125_TRIGGER_DELAY_GRANULARITY             = 1 //Step=1 Clock Cycle (Clock Frequency/8)
}QTFM_1125_Trigger_Delay,*PQTFM_1125_Trigger_Delay;
typedef enum _tag_QTfm_1125_AD_Width
{
    QTFM_1125_AD_WIDTH_BIT                          = 10 //Bit
}QTFM_1125_AD_WIDTH,*PQTFM_1125_AD_WIDTH;
typedef enum _tag_QTfm_1125_AD_Value
{
    QTFM_1125_AD_VALUE_MIN                          = 0, //
    QTFM_1125_AD_VALUE_MAX                          = 0x3ff, //10bit counter

    QTFM_1125_AD_VALUE_STEP                         = 1 //Step=1
}QTFM_1125_AD_VALUE,*PQTFM_1125_AD_VALUE;
typedef enum _tag_QTfm_1125_Channel_Mode
{
    QTFM_1125_CHANNEL_MODE_4_CHANNEL                = 0x100, //Four-channel mode (1.25 Gsps per channel)
    QTFM_1125_CHANNEL_MODE_2_CHANNEL_AC             = 0x104, //Two-channel mode (channel A and channel C, 2.5 Gsps per channel)
    QTFM_1125_CHANNEL_MODE_2_CHANNEL_BC             = 0x105, //Two-channel mode (channel B and channel C, 2.5 Gsps per channel)
    QTFM_1125_CHANNEL_MODE_2_CHANNEL_AD             = 0x106, //Two-channel mode (channel A and channel D, 2.5 Gsps per channel)
    QTFM_1125_CHANNEL_MODE_2_CHANNEL_BD             = 0x107, //Two-channel mode (channel B and channel D, 2.5 Gsps per channel)
    QTFM_1125_CHANNEL_MODE_1_CHANNEL_A              = 0x108, //One-channel mode (channel A, 5 Gsps)
    QTFM_1125_CHANNEL_MODE_1_CHANNEL_B              = 0x109, //One-channel mode (channel B, 5 Gsps)
    QTFM_1125_CHANNEL_MODE_1_CHANNEL_C              = 0x10a, //One-channel mode (channel C, 5 Gsps)
    QTFM_1125_CHANNEL_MODE_1_CHANNEL_D              = 0x10b, //One-channel mode (channel D, 5 Gsps)
    QTFM_1125_CHANNEL_MODE_1125_SIMULTANEOUS_A      = 0x10c, //Common input mode, simultaneous sampling (channel A)
    QTFM_1125_CHANNEL_MODE_1125_SIMULTANEOUS_B      = 0x10d, //Common input mode, simultaneous sampling (channel B)
    QTFM_1125_CHANNEL_MODE_1125_SIMULTANEOUS_C      = 0x10e, //Common input mode, simultaneous sampling (channel C)
    QTFM_1125_CHANNEL_MODE_1125_SIMULTANEOUS_D      = 0x10f  //Common input mode, simultaneous sampling (channel D)
}QTFM_1125_CHANNEL_MODE,*PQTFM_1125_CHANNEL_MODE;
typedef enum _tag_QTfm_1125_Trigger_Channel
{
    QTFM_1125_TRIGGER_CHANNEL_0                     = 0, //Physical channel 0
    QTFM_1125_TRIGGER_CHANNEL_1,                         //Physical channel 2
	  QTFM_1125_TRIGGER_CHANNEL_2,                         //Physical channel 1
	  QTFM_1125_TRIGGER_CHANNEL_3,                         //Physical channel 3
}QTFM_1125_TRIGGER_CHANNEL,*PQTFM_1125_TRIGGER_CHANNEL;
typedef enum _tag_QTfm_1125DC_Range
{
  QTFM_1125DC_RANGE_0                     =0,//= 25, //X1,+full_scale in mV
  QTFM_1125DC_RANGE_1,                       //= 50, //X2,+full_scale in mV
  QTFM_1125DC_RANGE_2,                       //= 100,//X4,+full_scale in mV
  QTFM_1125DC_RANGE_3                        //= 250 //X10,+full_scale in mV
}QTFM_1125DC_RANGE,*PQTFM_1125DC_RANGE;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _QTFIRMWARE_1128_H_
#define _QTFIRMWARE_1128_H_


typedef enum _tag_QTfm_1128_BytesPerSample  //Bytes per sample
{
    QTFM_1128_BPSAMPLE                              = 2,
}QTFM_1128_BYTESPERSAMPLE,*PQTFM_1128_BYTESPERSAMPLE;
typedef enum _tag_QTfm_1128_Type  //QT1128 subtype  //TODO:Check
{
    QTFM_1128_TYPE_AC4                              = 1,
    QTFM_1128_TYPE_AC8                              = 2,
    QTFM_1128_TYPE_DC4                              = 4,
    QTFM_1128_TYPE_MAX                              = 3  //Modify this
}QTFM_1128_TYPE,*PQTFM_1128_TYPE;
typedef enum _tag_QTfm_1128_Trigger_Source
{
    QTFM_1128_TRIGGER_SOURCE_EXTERNAL_1             = 1, //External Trigger
    QTFM_1128_TRIGGER_SOURCE_CHANNEL                = 14, //Channel Trigger
    QTFM_1128_TRIGGER_SOURCE_PULSE,                      //Pulse Trigger
    QTFM_1128_TRIGGER_SOURCE_SOFTWARE                    //Software Trigger
}QTFM_1128_TRIGGER_SOURCE,*PQTFM_1128_TRIGGER_SOURCE;
typedef enum _tag_QTfm_1128_Term_Input //Non-adjustable
{
    QTFM_1128_TERM_INPUT_50                         = 50 //50 ohm
}QTFM_1128_TERM_INPUT,*PQTFM_1128_TERM_INPUT;
typedef enum _tag_QTfm_1128_Range_Input //Non-adjustable
{
    QTFM_1128_RANGE_INPUT_MIN                       = -250, //-250 mv
    QTFM_1128_RANGE_INPUT_MAX                       = 250 //250 mv
}QTFM_1128_RANGE_INPUT,*PQTFM_1128_RANGE_INPUT;
typedef enum _tag_QTfm_1128_Offset //TODO:Check
{
    QTFM_1128_OFFSET_0                             = 0 //mV
}QTFM_1128_OFFSET,*PQTFM_1128_OFFSET;
typedef enum _tag_QTfm_1128_Memory_Size
{
    QTFM_1128_MEMORY_SIZE_MIN                       = 64, //64 Bytes
    QTFM_1128_MEMORY_SIZE_MAX                       = 2*1024, //2*1024 MBytes = 2G

    QTFM_1128_MEMORY_SIZE_STEP                      = 64 //Step=64 Bytes
}QTFM_1128_MEMORY_SIZE,*PQTFM_1128_MEMORY_SIZE;
typedef enum _tag_QTfm_1128_Pre_Trigger
{
    QTFM_1128_PRE_TRIGGER_MIN                       = 0,
    QTFM_1128_PRE_TRIGGER_MAX                       = 8*1024, //8k Sample

    QTFM_1128_PRE_TRIGGER_GRANULARITY               = 16 //Step=32 Sample
}QTFM_1128_PRE_TRIGGER,*PQTFM_1128_PRE_TRIGGER;
typedef enum _tag_QTfm_1128_Sample_Rate
{
    QTFM_1128_SAMPLE_RATE_ACDC484                   = 5000 //5000 Msps = 5 Gsps
}QTFM_1128_SAMPLE_RATE,*PQTFM_1128_SAMPLE_RATE;
typedef enum _tag_QTfm_1128_Segment
{
    QTFM_1128_SEGMENT_MIN                           = 32, //32 Samples
    QTFM_1128_SEGMENT_MAX                           = 1024, //1024 M Samples = 1G Samples

    QTFM_1128_SEGMENT_GRANULARITY                   = 32 //32 Samples
}QTFM_1128_SEGMENT,*PQTFM_1128_SEGMENT;
typedef enum _tag_QTfm_1128_Clock_Mode
{
    QTFM_1128_CLOCK_MODE_INTERNAL                   = 0 //Internal Sampling clock
}QTFM_1128_CLOCK_MODE,*PQTFM_1128_CLOCK_MODE;
typedef enum _tag_QTfm_1128_Pulse_Width
{
    QTFM_1128_PULSE_WIDTH_MIN                       = 16, //Bytes
    QTFM_1128_PULSE_WIDTH_MAX                       = 0x7fffffc0 , //2G-64 Bytes

    QTFM_1128_PULSE_WIDTH_GRANULARITY               = 16 //Step=16 Bytes
}QTFM_1128_PULSE_WIDTH,*PQTFM_1128_PULSE_WIDTH;
typedef enum _tag_QTfm_1128_Trigger_Delay
{
    QTFM_1128_TRIGGER_DELAY_MIN                     = 0, //
    QTFM_1128_TRIGGER_DELAY_MAX                     = -1, //64bit counter,Clock Frequency/8

    QTFM_1128_TRIGGER_DELAY_GRANULARITY             = 1 //Step=1 Clock Cycle (Clock Frequency/8)
}QTFM_1128_Trigger_Delay,*PQTFM_1128_Trigger_Delay;
typedef enum _tag_QTfm_1128_AD_Width
{
    QTFM_1128_AD_WIDTH_BIT                          = 12 //Bit
}QTFM_1128_AD_WIDTH,*PQTFM_1128_AD_WIDTH;
typedef enum _tag_QTfm_1128_AD_Value
{
    QTFM_1128_AD_VALUE_MIN                          = 0, //-full_scale
    QTFM_1128_AD_VALUE_MAX                          = 0xfff,//offset binary, +full_scale

    QTFM_1128_AD_VALUE_STEP                         = 1 //Step=1
}QTFM_1128_AD_VALUE,*PQTFM_1128_AD_VALUE;
typedef enum _tag_QTfm_1128_Trigger_Channel
{
    QTFM_1128_TRIGGER_CHANNEL_0                     = 0, //Physical channel 0
    QTFM_1128_TRIGGER_CHANNEL_1,                         //Physical channel 1
}QTFM_1128_TRIGGER_CHANNEL,*PQTFM_1128_TRIGGER_CHANNEL;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _QTFIRMWARE_1130_H_
#define _QTFIRMWARE_1130_H_


typedef enum _tag_QTfm_1130_BytesPerSample  //Bytes per sample
{
    QTFM_1130_BPSAMPLE                              = 2,
}QTFM_1130_BYTESPERSAMPLE,*PQTFM_1130_BYTESPERSAMPLE;
typedef enum _tag_QTfm_1130_Type  //QT1130 subtype  //TODO:Check
{
    QTFM_1130_TYPE_AC4                              = 1,
    QTFM_1130_TYPE_AC8                              = 2,
    QTFM_1130_TYPE_DC4                              = 4,
    QTFM_1130_TYPE_MAX                              = 3  //Modify this
}QTFM_1130_TYPE,*PQTFM_1130_TYPE;
typedef enum _tag_QTfm_1130_Trigger_Source
{
    QTFM_1130_TRIGGER_SOURCE_EXTERNAL_1             = 1, //External Trigger
    QTFM_1130_TRIGGER_SOURCE_CHANNEL                = 14, //Channel Trigger
    QTFM_1130_TRIGGER_SOURCE_PULSE,                      //Pulse Trigger
    QTFM_1130_TRIGGER_SOURCE_SOFTWARE                    //Software Trigger
}QTFM_1130_TRIGGER_SOURCE,*PQTFM_1130_TRIGGER_SOURCE;
typedef enum _tag_QTfm_1130_Term_Input //Non-adjustable
{
    QTFM_1130_TERM_INPUT_50                         = 50 //50 ohm
}QTFM_1130_TERM_INPUT,*PQTFM_1130_TERM_INPUT;
typedef enum _tag_QTfm_1130_Range_Input //Non-adjustable
{
    QTFM_1130_RANGE_INPUT_MIN                       = -250, //-250 mv
    QTFM_1130_RANGE_INPUT_MAX                       = 250 //250 mv
}QTFM_1130_RANGE_INPUT,*PQTFM_1130_RANGE_INPUT;
typedef enum _tag_QTfm_1130_Offset //TODO:Check
{
    QTFM_1130_OFFSET_0                             = 0 //mV
}QTFM_1130_OFFSET,*PQTFM_1130_OFFSET;
typedef enum _tag_QTfm_1130_Memory_Size
{
    QTFM_1130_MEMORY_SIZE_MIN                       = 64, //64 Bytes
    QTFM_1130_MEMORY_SIZE_MAX                       = 2*1024, //2*1024 MBytes = 2G

    QTFM_1130_MEMORY_SIZE_STEP                      = 64 //Step=64 Bytes
}QTFM_1130_MEMORY_SIZE,*PQTFM_1130_MEMORY_SIZE;
typedef enum _tag_QTfm_1130_Pre_Trigger
{
    QTFM_1130_PRE_TRIGGER_MIN                       = 0,
    QTFM_1130_PRE_TRIGGER_MAX                       = 8*1024, //8k Sample

    QTFM_1130_PRE_TRIGGER_GRANULARITY               = 16 //Step=32 Sample
}QTFM_1130_PRE_TRIGGER,*PQTFM_1130_PRE_TRIGGER;
typedef enum _tag_QTfm_1130_Sample_Rate
{
    QTFM_1130_SAMPLE_RATE_ACDC484                   = 5000 //5000 Msps = 5 Gsps
}QTFM_1130_SAMPLE_RATE,*PQTFM_1130_SAMPLE_RATE;
typedef enum _tag_QTfm_1130_Segment
{
    QTFM_1130_SEGMENT_MIN                           = 32, //32 Samples
    QTFM_1130_SEGMENT_MAX                           = 1024, //1024 M Samples = 1G Samples

    QTFM_1130_SEGMENT_GRANULARITY                   = 32 //32 Samples
}QTFM_1130_SEGMENT,*PQTFM_1130_SEGMENT;
typedef enum _tag_QTfm_1130_Clock_Mode
{
    QTFM_1130_CLOCK_MODE_INTERNAL                   = 0 //Internal Sampling clock
}QTFM_1130_CLOCK_MODE,*PQTFM_1130_CLOCK_MODE;
typedef enum _tag_QTfm_1130_Pulse_Width
{
    QTFM_1130_PULSE_WIDTH_MIN                       = 16, //Bytes
    QTFM_1130_PULSE_WIDTH_MAX                       = 0x7fffffc0 , //2G-64 Bytes

    QTFM_1130_PULSE_WIDTH_GRANULARITY               = 16 //Step=16 Bytes
}QTFM_1130_PULSE_WIDTH,*PQTFM_1130_PULSE_WIDTH;
typedef enum _tag_QTfm_1130_Trigger_Delay
{
    QTFM_1130_TRIGGER_DELAY_MIN                     = 0, //
    QTFM_1130_TRIGGER_DELAY_MAX                     = -1, //64bit counter,Clock Frequency/8

    QTFM_1130_TRIGGER_DELAY_GRANULARITY             = 1 //Step=1 Clock Cycle (Clock Frequency/8)
}QTFM_1130_Trigger_Delay,*PQTFM_1130_Trigger_Delay;
typedef enum _tag_QTfm_1130_AD_Width
{
    QTFM_1130_AD_WIDTH_BIT                          = 12 //Bit
}QTFM_1130_AD_WIDTH,*PQTFM_1130_AD_WIDTH;
typedef enum _tag_QTfm_1130_AD_Value
{
    QTFM_1130_AD_VALUE_MIN                          = 0, //-full_scale
    QTFM_1130_AD_VALUE_MAX                          = 0xfff,//offset binary, +full_scale

    QTFM_1130_AD_VALUE_STEP                         = 1 //Step=1
}QTFM_1130_AD_VALUE,*PQTFM_1130_AD_VALUE;
typedef enum _tag_QTfm_1130_Trigger_Channel
{
    QTFM_1130_TRIGGER_CHANNEL_0                     = 0, //Physical channel 0
    QTFM_1130_TRIGGER_CHANNEL_1,                         //Physical channel 1
	QTFM_1130_TRIGGER_CHANNEL_2,                         //Physical channel 2
	QTFM_1130_TRIGGER_CHANNEL_3,                         //Physical channel 3
}QTFM_1130_TRIGGER_CHANNEL,*PQTFM_1130_TRIGGER_CHANNEL;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _QTFIRMWARE_1135_H_
#define _QTFIRMWARE_1135_H_

typedef enum _tag_QTfm_1135_BytesPerSample  //Bytes per sample
{
    QTFM_1135_BPSAMPLE                        = 2,
}QTFM_1135_BYTESPERSAMPLE,*PQTFM_1135_BYTESPERSAMPLE;
typedef enum _tag_QTfm_1135_Type  //QT1135 subtype  //TODO:Check
{
    QTFM_1135_TYPE_AC4                              = 1,
    QTFM_1135_TYPE_AC8                              = 2,
    QTFM_1135_TYPE_DC4                              = 4,
    QTFM_1135_TYPE_MAX                              = 3  //Modify this
}QTFM_1135_TYPE,*PQTFM_1135_TYPE;
typedef enum _tag_QTfm_1135_Trigger_Source
{
    QTFM_1135_TRIGGER_SOURCE_EXTERNAL_1             = 1, //External Trigger
    QTFM_1135_TRIGGER_SOURCE_CHANNEL                = 14, //Channel Trigger
    QTFM_1135_TRIGGER_SOURCE_PULSE,                      //Pulse Trigger
    QTFM_1135_TRIGGER_SOURCE_SOFTWARE                    //Software Trigger
}QTFM_1135_TRIGGER_SOURCE,*PQTFM_1135_TRIGGER_SOURCE;
typedef enum _tag_QTfm_1135_Term_Input //Non-adjustable
{
    QTFM_1135_TERM_INPUT_50                         = 50 //50 ohm
}QTFM_1135_TERM_INPUT,*PQTFM_1135_TERM_INPUT;
typedef enum _tag_QTfm_1135_Range_Input //Non-adjustable
{
    QTFM_1135_RANGE_INPUT_MIN                       = -1000, //-1000 mv
    QTFM_1135_RANGE_INPUT_MAX                       = 1000 //1000 mv
}QTFM_1135_RANGE_INPUT,*PQTFM_1135_RANGE_INPUT;
typedef enum _tag_QTfm_1135_Offset //TODO:Check
{
    QTFM_1135_OFFSET_0V                             = 0, //non-adjustable
    //QTFM_1135_OFFSET_1V                             = 1, //1v
    //QTFM_1135_OFFSET_2V                             = 2 //2v
}QTFM_1135_OFFSET,*PQTFM_1135_OFFSET;
typedef enum _tag_QTfm_1135_Memory_Size
{
    QTFM_1135_MEMORY_SIZE_MIN                       = 64, //64 Bytes
    QTFM_1135_MEMORY_SIZE_MAX                       = 2*1024, //2*1024 MBytes = 2G

    QTFM_1135_MEMORY_SIZE_STEP                      = 64 //Step=64 Bytes
}QTFM_1135_MEMORY_SIZE,*PQTFM_1135_MEMORY_SIZE;
typedef enum _tag_QTfm_1135_Pre_Trigger
{
    QTFM_1135_PRE_TRIGGER_MIN                       = 0,
    QTFM_1135_PRE_TRIGGER_MAX                       = 8*1024, //8k Sample

    QTFM_1135_PRE_TRIGGER_GRANULARITY               = 16 //Step=32 Sample
}QTFM_1135_PRE_TRIGGER,*PQTFM_1135_PRE_TRIGGER;
typedef enum _tag_QTfm_1135_Sample_Rate
{
    QTFM_1135_SAMPLE_RATE_ACDC                      = 250  // Msps
}QTFM_1135_SAMPLE_RATE,*PQTFM_1135_SAMPLE_RATE;
typedef enum _tag_QTfm_1135_Segment
{
    QTFM_1135_SEGMENT_MIN                           = 8, //8 Samples
    QTFM_1135_SEGMENT_MAX                           = 1024, //1024 M Samples = 1G Samples

    QTFM_1135_SEGMENT_GRANULARITY                   = 8 //32 Samples
}QTFM_1135_SEGMENT,*PQTFM_1135_SEGMENT;
typedef enum _tag_QTfm_1135_Clock_Mode
{
    QTFM_1135_CLOCK_MODE_INTERNAL                   = 0 //Internal Sampling clock
}QTFM_1135_CLOCK_MODE,*PQTFM_1135_CLOCK_MODE;
typedef enum _tag_QTfm_1135_Pulse_Width
{
    QTFM_1135_PULSE_WIDTH_MIN                       = 16, //Bytes
    QTFM_1135_PULSE_WIDTH_MAX                       = 0x7fffffc0 , //2G-64 Bytes

    QTFM_1135_PULSE_WIDTH_GRANULARITY               = 16 //Step=16 Bytes
}QTFM_1135_PULSE_WIDTH,*PQTFM_1135_PULSE_WIDTH;
typedef enum _tag_QTfm_1135_Trigger_Delay
{
    QTFM_1135_TRIGGER_DELAY_MIN                     = 0, //
    QTFM_1135_TRIGGER_DELAY_MAX                     = -1, //64bit counter,Clock Frequency/8

    QTFM_1135_TRIGGER_DELAY_GRANULARITY             = 1 //Step=1 Clock Cycle (Clock Frequency/8)
}QTFM_1135_Trigger_Delay,*PQTFM_1135_Trigger_Delay;
typedef enum _tag_QTfm_1135_AD_Width
{
    QTFM_1135_AD_WIDTH_BIT                          = 14 //Bit
}QTFM_1135_AD_WIDTH,*PQTFM_1135_AD_WIDTH;
typedef enum _tag_QTfm_1135_AD_Value
{
    QTFM_1135_AD_VALUE_MIN                          = 0, //
    QTFM_1135_AD_VALUE_MAX                          = 0x3FFF, //14bit counter

    QTFM_1135_AD_VALUE_STEP                         = 1 //Step=1
}QTFM_1135_AD_VALUE,*PQTFM_1135_AD_VALUE;
typedef enum _tag_QTfm_1135_Trigger_Channel
{
    QTFM_1135_TRIGGER_CHANNEL_0                     = 0, //Physical channel 0
    QTFM_1135_TRIGGER_CHANNEL_1,                         //Physical channel 1
	QTFM_1135_TRIGGER_CHANNEL_2,                         //Physical channel 2
	QTFM_1135_TRIGGER_CHANNEL_3,                         //Physical channel 3
}QTFM_1135_TRIGGER_CHANNEL,*PQTFM_1135_TRIGGER_CHANNEL;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _QTFIRMWARE_1138_H_
#define _QTFIRMWARE_1138_H_


typedef enum _tag_QTfm_1138_BytesPerSample  //Bytes per sample
{
    QTFM_1138_BPSAMPLE                              = 2,
}QTFM_1138_BYTESPERSAMPLE,*PQTFM_1138_BYTESPERSAMPLE;
typedef enum _tag_QTfm_1138_Type  //QT1138 subtype  //TODO:Check
{
    QTFM_1138_TYPE_AC4                              = 1,
    QTFM_1138_TYPE_AC8                              = 2,
    QTFM_1138_TYPE_DC4                              = 4,
    QTFM_1138_TYPE_MAX                              = 3  //Modify this
}QTFM_1138_TYPE,*PQTFM_1138_TYPE;
typedef enum _tag_QTfm_1138_Trigger_Source
{
    QTFM_1138_TRIGGER_SOURCE_EXTERNAL_1             = 1, //External Trigger
    QTFM_1138_TRIGGER_SOURCE_CHANNEL                = 14, //Channel Trigger
    QTFM_1138_TRIGGER_SOURCE_PULSE,                      //Pulse Trigger
    QTFM_1138_TRIGGER_SOURCE_SOFTWARE                    //Software Trigger
}QTFM_1138_TRIGGER_SOURCE,*PQTFM_1138_TRIGGER_SOURCE;
typedef enum _tag_QTfm_1138_Term_Input //Non-adjustable
{
    QTFM_1138_TERM_INPUT_50                         = 50 //50 ohm
}QTFM_1138_TERM_INPUT,*PQTFM_1138_TERM_INPUT;
typedef enum _tag_QTfm_1138_Range_Input //Non-adjustable
{
    QTFM_1138_RANGE_INPUT_MIN                       = -1000, //-1000 mv
    QTFM_1138_RANGE_INPUT_MAX                       = 1000 //1000 mv
}QTFM_1138_RANGE_INPUT,*PQTFM_1138_RANGE_INPUT;
typedef enum _tag_QTfm_1138_Offset //TODO:Check
{
    QTFM_1138_OFFSET_0V                             = 0, //non-adjustable
    //QTFM_1138_OFFSET_1V                             = 1, //1v
    //QTFM_1138_OFFSET_2V                             = 2 //2v
}QTFM_1138_OFFSET,*PQTFM_1138_OFFSET;
typedef enum _tag_QTfm_1138_Memory_Size
{
    QTFM_1138_MEMORY_SIZE_MIN                       = 64, //64 Bytes
    QTFM_1138_MEMORY_SIZE_MAX                       = 2*1024, //2*1024 MBytes = 2G

    QTFM_1138_MEMORY_SIZE_STEP                      = 64 //Step=64 Bytes
}QTFM_1138_MEMORY_SIZE,*PQTFM_1138_MEMORY_SIZE;
typedef enum _tag_QTfm_1138_Pre_Trigger
{
    QTFM_1138_PRE_TRIGGER_MIN                       = 0,
    QTFM_1138_PRE_TRIGGER_MAX                       = 8*1024, //8k Sample

    QTFM_1138_PRE_TRIGGER_GRANULARITY               = 16 //Step=32 Sample
}QTFM_1138_PRE_TRIGGER,*PQTFM_1138_PRE_TRIGGER;
typedef enum _tag_QTfm_1138_Sample_Rate
{
    QTFM_1138_SAMPLE_RATE_ACDC                      = 250  // Msps
}QTFM_1138_SAMPLE_RATE,*PQTFM_1138_SAMPLE_RATE;
typedef enum _tag_QTfm_1138_Segment
{
    QTFM_1138_SEGMENT_MIN                           = 8, //8 Samples
    QTFM_1138_SEGMENT_MAX                           = 1024, //1024 M Samples = 1G Samples

    QTFM_1138_SEGMENT_GRANULARITY                   = 8 //32 Samples
}QTFM_1138_SEGMENT,*PQTFM_1138_SEGMENT;
typedef enum _tag_QTfm_1138_Clock_Mode
{
    QTFM_1138_CLOCK_MODE_INTERNAL                   = 0 //Internal Sampling clock
}QTFM_1138_CLOCK_MODE,*PQTFM_1138_CLOCK_MODE;
typedef enum _tag_QTfm_1138_Pulse_Width
{
    QTFM_1138_PULSE_WIDTH_MIN                       = 16, //Bytes
    QTFM_1138_PULSE_WIDTH_MAX                       = 0x7fffffc0 , //2G-64 Bytes

    QTFM_1138_PULSE_WIDTH_GRANULARITY               = 16 //Step=16 Bytes
}QTFM_1138_PULSE_WIDTH,*PQTFM_1138_PULSE_WIDTH;
typedef enum _tag_QTfm_1138_Trigger_Delay
{
    QTFM_1138_TRIGGER_DELAY_MIN                     = 0, //
    QTFM_1138_TRIGGER_DELAY_MAX                     = -1, //64bit counter,Clock Frequency/8

    QTFM_1138_TRIGGER_DELAY_GRANULARITY             = 1 //Step=1 Clock Cycle (Clock Frequency/8)
}QTFM_1138_Trigger_Delay,*PQTFM_1138_Trigger_Delay;
typedef enum _tag_QTfm_1138_AD_Width
{
    QTFM_1138_AD_WIDTH_BIT                          = 16 //Bit
}QTFM_1138_AD_WIDTH,*PQTFM_1138_AD_WIDTH;
typedef enum _tag_QTfm_1138_AD_Value
{
    QTFM_1138_AD_VALUE_MIN                          = 0, //
    QTFM_1138_AD_VALUE_MAX                          = 0xFFFF, //10bit counter

    QTFM_1138_AD_VALUE_STEP                         = 1 //Step=1
}QTFM_1138_AD_VALUE,*PQTFM_1138_AD_VALUE;
typedef enum _tag_QTfm_1138_Trigger_Channel
{
    QTFM_1138_TRIGGER_CHANNEL_0                     = 0, //Physical channel 0
    QTFM_1138_TRIGGER_CHANNEL_1,                         //Physical channel 1
    QTFM_1138_TRIGGER_CHANNEL_2,                         //Physical channel 2
    QTFM_1138_TRIGGER_CHANNEL_3,                         //Physical channel 3
    QTFM_1138_TRIGGER_CHANNEL_4,                         //Physical channel 4
    QTFM_1138_TRIGGER_CHANNEL_5,                         //Physical channel 5
    QTFM_1138_TRIGGER_CHANNEL_6,                         //Physical channel 6
    QTFM_1138_TRIGGER_CHANNEL_7,                         //Physical channel 7
}QTFM_1138_TRIGGER_CHANNEL,*PQTFM_1138_TRIGGER_CHANNEL;
typedef enum _tag_QTfm_1138DC_Range
{
  QTFM_1138DC_RANGE_1                     = 0,  //1X +full_scale in mV
  QTFM_1138DC_RANGE_2,                          //2X +full_scale in mV
  QTFM_1138DC_RANGE_3,                          //5X +full_scale in mV
  QTFM_1138DC_RANGE_4,                          //10X +full_scale in mV
  QTFM_1138DC_RANGE_5                           //10X +full_scale in mV
}QTFM_1138DC_RANGE,*PQTFM_1138DC_RANGE;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _QTFIRMWARE_1229_H_
#define _QTFIRMWARE_1229_H_


typedef enum _tag_QTfm_1229_BytesPerSample  //Bytes per sample
{
    QTFM_1229_BPSAMPLE                              = 2,
}QTFM_1229_BYTESPERSAMPLE,*PQTFM_1229_BYTESPERSAMPLE;
typedef enum _tag_QTfm_1229_Type  //QT1229 subtype  //TODO:Check
{
    QTFM_1229_TYPE_AC4                              = 1,
    QTFM_1229_TYPE_AC8                              = 2,
    QTFM_1229_TYPE_DC4                              = 4,
    QTFM_1229_TYPE_MAX                              = 3  //Modify this
}QTFM_1229_TYPE,*PQTFM_1229_TYPE;
typedef enum _tag_QTfm_1229_Trigger_Source
{
    QTFM_1229_TRIGGER_SOURCE_EXTERNAL_1             = 1, //External Trigger
    QTFM_1229_TRIGGER_SOURCE_CHANNEL                = 14, //Channel Trigger
    QTFM_1229_TRIGGER_SOURCE_PULSE,                      //Pulse Trigger
    QTFM_1229_TRIGGER_SOURCE_SOFTWARE                    //Software Trigger
}QTFM_1229_TRIGGER_SOURCE,*PQTFM_1229_TRIGGER_SOURCE;
typedef enum _tag_QTfm_1229_Term_Input //Non-adjustable
{
    QTFM_1229_TERM_INPUT_50                         = 50 //50 ohm
}QTFM_1229_TERM_INPUT,*PQTFM_1229_TERM_INPUT;
typedef enum _tag_QTfm_1229_Range_Input //Non-adjustable
{
    QTFM_1229_RANGE_INPUT_MIN                       = -1000, //-1000 mv
    QTFM_1229_RANGE_INPUT_MAX                       = 1000 //1000 mv
}QTFM_1229_RANGE_INPUT,*PQTFM_1229_RANGE_INPUT;
typedef enum _tag_QTfm_1229_Offset //TODO:Check
{
    QTFM_1229_OFFSET_0V                             = 0, //non-adjustable
    //QTFM_1229_OFFSET_1V                             = 1, //1v
    //QTFM_1229_OFFSET_2V                             = 2 //2v
}QTFM_1229_OFFSET,*PQTFM_1229_OFFSET;
typedef enum _tag_QTfm_1229_Memory_Size
{
    QTFM_1229_MEMORY_SIZE_MIN                       = 64, //64 Bytes
    QTFM_1229_MEMORY_SIZE_MAX                       = 2*1024, //2*1024 MBytes = 2G

    QTFM_1229_MEMORY_SIZE_STEP                      = 64 //Step=64 Bytes
}QTFM_1229_MEMORY_SIZE,*PQTFM_1229_MEMORY_SIZE;
typedef enum _tag_QTfm_1229_Pre_Trigger
{
    QTFM_1229_PRE_TRIGGER_MIN                       = 0,
    QTFM_1229_PRE_TRIGGER_MAX                       = 8*1024, //8k Sample

    QTFM_1229_PRE_TRIGGER_GRANULARITY               = 16 //Step=32 Sample
}QTFM_1229_PRE_TRIGGER,*PQTFM_1229_PRE_TRIGGER;
typedef enum _tag_QTfm_1229_Sample_Rate
{
    QTFM_1229_SAMPLE_RATE_ACDC                      = 250  // Msps
}QTFM_1229_SAMPLE_RATE,*PQTFM_1229_SAMPLE_RATE;
typedef enum _tag_QTfm_1229_Segment
{
    QTFM_1229_SEGMENT_MIN                           = 8, //8 Samples
    QTFM_1229_SEGMENT_MAX                           = 1024, //1024 M Samples = 1G Samples

    QTFM_1229_SEGMENT_GRANULARITY                   = 8 //32 Samples
}QTFM_1229_SEGMENT,*PQTFM_1229_SEGMENT;
typedef enum _tag_QTfm_1229_Clock_Mode
{
    QTFM_1229_CLOCK_MODE_INTERNAL                   = 0 //Internal Sampling clock
}QTFM_1229_CLOCK_MODE,*PQTFM_1229_CLOCK_MODE;
typedef enum _tag_QTfm_1229_Pulse_Width
{
    QTFM_1229_PULSE_WIDTH_MIN                       = 16, //Bytes
    QTFM_1229_PULSE_WIDTH_MAX                       = 0x7fffffc0 , //2G-64 Bytes

    QTFM_1229_PULSE_WIDTH_GRANULARITY               = 16 //Step=16 Bytes
}QTFM_1229_PULSE_WIDTH,*PQTFM_1229_PULSE_WIDTH;
typedef enum _tag_QTfm_1229_Trigger_Delay
{
    QTFM_1229_TRIGGER_DELAY_MIN                     = 0, //
    QTFM_1229_TRIGGER_DELAY_MAX                     = -1, //64bit counter,Clock Frequency/8

    QTFM_1229_TRIGGER_DELAY_GRANULARITY             = 1 //Step=1 Clock Cycle (Clock Frequency/8)
}QTFM_1229_Trigger_Delay,*PQTFM_1229_Trigger_Delay;
typedef enum _tag_QTfm_1229_AD_Width
{
    QTFM_1229_AD_WIDTH_BIT                          = 16 //Bit
}QTFM_1229_AD_WIDTH,*PQTFM_1229_AD_WIDTH;
typedef enum _tag_QTfm_1229_AD_Value
{
    QTFM_1229_AD_VALUE_MIN                          = 0, //
    QTFM_1229_AD_VALUE_MAX                          = 0xFFFF, //10bit counter

    QTFM_1229_AD_VALUE_STEP                         = 1 //Step=1
}QTFM_1229_AD_VALUE,*PQTFM_1229_AD_VALUE;
typedef enum _tag_QTfm_1229_Trigger_Channel
{
    QTFM_1229_TRIGGER_CHANNEL_0                     = 0, //Physical channel 0
    QTFM_1229_TRIGGER_CHANNEL_1,                         //Physical channel 1
}QTFM_1229_TRIGGER_CHANNEL,*PQTFM_1229_TRIGGER_CHANNEL;
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _QTFIRMWARE_1238_H_
#define _QTFIRMWARE_1238_H_


typedef enum _tag_QTfm_1238_BytesPerSample  //Bytes per sample
{
    QTFM_1238_BPSAMPLE                              = 2,
}QTFM_1238_BYTESPERSAMPLE,*PQTFM_1238_BYTESPERSAMPLE;
typedef enum _tag_QTfm_1238_Type  //QT1238 subtype  //TODO:Check
{
    QTFM_1238_TYPE_AC4                              = 1,
    QTFM_1238_TYPE_AC8                              = 2,
    QTFM_1238_TYPE_DC4                              = 4,
    QTFM_1238_TYPE_MAX                              = 3  //Modify this
}QTFM_1238_TYPE,*PQTFM_1238_TYPE;
typedef enum _tag_QTfm_1238_Trigger_Source
{
    QTFM_1238_TRIGGER_SOURCE_EXTERNAL_1             = 1, //External Trigger
    QTFM_1238_TRIGGER_SOURCE_CHANNEL                = 14, //Channel Trigger
    QTFM_1238_TRIGGER_SOURCE_PULSE,                      //Pulse Trigger
    QTFM_1238_TRIGGER_SOURCE_SOFTWARE                    //Software Trigger
}QTFM_1238_TRIGGER_SOURCE,*PQTFM_1238_TRIGGER_SOURCE;
typedef enum _tag_QTfm_1238_Term_Input //Non-adjustable
{
    QTFM_1238_TERM_INPUT_50                         = 50 //50 ohm
}QTFM_1238_TERM_INPUT,*PQTFM_1238_TERM_INPUT;
typedef enum _tag_QTfm_1238_Range_Input //Non-adjustable
{
    QTFM_1238_RANGE_INPUT_MIN                       = -1000, //-1000 mv
    QTFM_1238_RANGE_INPUT_MAX                       = 1000 //1000 mv
}QTFM_1238_RANGE_INPUT,*PQTFM_1238_RANGE_INPUT;
typedef enum _tag_QTfm_1238_Offset //TODO:Check
{
    QTFM_1238_OFFSET_0V                             = 0, //non-adjustable
    //QTFM_1238_OFFSET_1V                             = 1, //1v
    //QTFM_1238_OFFSET_2V                             = 2 //2v
}QTFM_1238_OFFSET,*PQTFM_1238_OFFSET;
typedef enum _tag_QTfm_1238_Memory_Size
{
    QTFM_1238_MEMORY_SIZE_MIN                       = 64, //64 Bytes
    QTFM_1238_MEMORY_SIZE_MAX                       = 2*1024, //2*1024 MBytes = 2G

    QTFM_1238_MEMORY_SIZE_STEP                      = 64 //Step=64 Bytes
}QTFM_1238_MEMORY_SIZE,*PQTFM_1238_MEMORY_SIZE;
typedef enum _tag_QTfm_1238_Pre_Trigger
{
    QTFM_1238_PRE_TRIGGER_MIN                       = 0,
    QTFM_1238_PRE_TRIGGER_MAX                       = 8*1024, //8k Sample

    QTFM_1238_PRE_TRIGGER_GRANULARITY               = 16 //Step=32 Sample
}QTFM_1238_PRE_TRIGGER,*PQTFM_1238_PRE_TRIGGER;
typedef enum _tag_QTfm_1238_Sample_Rate
{
    QTFM_1238_SAMPLE_RATE_ACDC                      = 250  // Msps
}QTFM_1238_SAMPLE_RATE,*PQTFM_1238_SAMPLE_RATE;
typedef enum _tag_QTfm_1238_Segment
{
    QTFM_1238_SEGMENT_MIN                           = 8, //8 Samples
    QTFM_1238_SEGMENT_MAX                           = 1024, //1024 M Samples = 1G Samples

    QTFM_1238_SEGMENT_GRANULARITY                   = 8 //32 Samples
}QTFM_1238_SEGMENT,*PQTFM_1238_SEGMENT;
typedef enum _tag_QTfm_1238_Clock_Mode
{
    QTFM_1238_CLOCK_MODE_INTERNAL                   = 0 //Internal Sampling clock
}QTFM_1238_CLOCK_MODE,*PQTFM_1238_CLOCK_MODE;
typedef enum _tag_QTfm_1238_Pulse_Width
{
    QTFM_1238_PULSE_WIDTH_MIN                       = 16, //Bytes
    QTFM_1238_PULSE_WIDTH_MAX                       = 0x7fffffc0 , //2G-64 Bytes

    QTFM_1238_PULSE_WIDTH_GRANULARITY               = 16 //Step=16 Bytes
}QTFM_1238_PULSE_WIDTH,*PQTFM_1238_PULSE_WIDTH;
typedef enum _tag_QTfm_1238_Trigger_Delay
{
    QTFM_1238_TRIGGER_DELAY_MIN                     = 0, //
    QTFM_1238_TRIGGER_DELAY_MAX                     = -1, //64bit counter,Clock Frequency/8

    QTFM_1238_TRIGGER_DELAY_GRANULARITY             = 1 //Step=1 Clock Cycle (Clock Frequency/8)
}QTFM_1238_Trigger_Delay,*PQTFM_1238_Trigger_Delay;
typedef enum _tag_QTfm_1238_AD_Width
{
    QTFM_1238_AD_WIDTH_BIT                          = 16 //Bit
}QTFM_1238_AD_WIDTH,*PQTFM_1238_AD_WIDTH;
typedef enum _tag_QTfm_1238_AD_Value
{
    QTFM_1238_AD_VALUE_MIN                          = 0, //
    QTFM_1238_AD_VALUE_MAX                          = 0xFFFF, //10bit counter

    QTFM_1238_AD_VALUE_STEP                         = 1 //Step=1
}QTFM_1238_AD_VALUE,*PQTFM_1238_AD_VALUE;
typedef enum _tag_QTfm_1238_Trigger_Channel
{
    QTFM_1238_TRIGGER_CHANNEL_0                     = 0, //Physical channel 0
    QTFM_1238_TRIGGER_CHANNEL_1,                         //Physical channel 1
    QTFM_1238_TRIGGER_CHANNEL_2,                         //Physical channel 2
    QTFM_1238_TRIGGER_CHANNEL_3,                         //Physical channel 3
    QTFM_1238_TRIGGER_CHANNEL_4,                         //Physical channel 4
    QTFM_1238_TRIGGER_CHANNEL_5,                         //Physical channel 5
    QTFM_1238_TRIGGER_CHANNEL_6,                         //Physical channel 6
    QTFM_1238_TRIGGER_CHANNEL_7,                         //Physical channel 7
}QTFM_1238_TRIGGER_CHANNEL,*PQTFM_1238_TRIGGER_CHANNEL;
#endif
