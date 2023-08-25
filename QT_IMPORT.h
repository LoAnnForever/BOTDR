/********************************************************************
	created:	2016/12/29
	created:	29:12:2016   16:32
	filename: 	H:\tmp\products\C_API\c_header\QTApi.h
	file path:	H:\tmp\products\C_API\c_header
	file base:	QTApi
	file ext:	h
	author:		BaiLi
	
	purpose:	c header
*********************************************************************/
//include file from QT library
#include "QTApi.h"
#ifdef __cplusplus
  using namespace QTApi;
#endif
//include standard header
#include <string.h>
#include <windows.h>
#include <stdio.h>

typedef int (__stdcall *PFUNNQTINITCARDBYIDX) (ST_CARDINFO *pstCardInfo,unsigned int unCardIdx);
typedef int (__stdcall *PFUNNQTRESETCARD) (ST_CARDINFO *pstCardInfo);
typedef int (__stdcall *PFUNNQTFASTSET) (ST_CARDINFO *pstCardInfo,unsigned int Frequency);
typedef int (__stdcall *PFUNNQTCLOSECARD) (ST_CARDINFO *pstCardInfo);
typedef int (__stdcall *PFUNNQTWRTREG) (ST_CARDINFO *pstCardInfo,unsigned int unRegOffset,unsigned int unRegValue);
typedef int (__stdcall *PFUNNQTREADREG) (ST_CARDINFO *pstCardInfo,unsigned int unRegOffset,unsigned int *punRegValue);
typedef int (__stdcall *PFUNNQTSETPARAM) (ST_CARDINFO *pstCardInfo,unsigned int unCmd,unsigned int unParam1,unsigned int unParam2,unsigned int unParam3,unsigned int unTimeOut);
typedef int (__stdcall *PFUNNQTGETPARAM) (ST_CARDINFO *pstCardInfo,unsigned int *punCmd,unsigned int *punParam1,unsigned int *punParam2,unsigned int *punParam3,unsigned int unTimeOut);
typedef int (__stdcall *PFUNNQTSETUPADCMODE) (ST_CARDINFO *pstCardInfo,unsigned int unChOpt,unsigned int unModeFlg,unsigned int ClockDivider);
typedef int (__stdcall *PFUNNQTFORCEIODELAY) (ST_CARDINFO *pstCardInfo);
typedef int (__stdcall *PFUNNQTSETUPWORKMODE) (ST_CARDINFO *pstCardInfo,unsigned int unSegmentSize,unsigned int unPreSamples,unsigned int unSegmentCnt,unsigned int unModeFlg,unsigned int unCompressorMode,unsigned int unPostSamples);
typedef int (__stdcall *PFUNNQTSETUPCLOCKINTERNAL) (ST_CARDINFO *pstCardInfo,unsigned int unSamplerate);
typedef int (__stdcall *PFUNNQTSETUPCLOCK) (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int Frequency,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int RstADC);
typedef int (__stdcall *PFUNNQTSETUPTRIGSOFTWARE) (ST_CARDINFO *pstCardInfo,unsigned int unTrigType,unsigned int unEnable);
typedef int (__stdcall *PFUNNQTSETUPTRIGEXTERNAL) (ST_CARDINFO *pstCardInfo,unsigned int unExtIdx,unsigned int unTrigType,unsigned int unEnable);
typedef int (__stdcall *PFUNNQTSETUPTRIGCHANNEL) (ST_CARDINFO *pstCardInfo,unsigned int unChannel,unsigned int unTrigType,/*unsigned */int unRiseEdgeLevel,/*unsigned */int unFallEdgeLevel,unsigned int unEnable);
typedef int (__stdcall *PFUNNQTSETUPTRIGPULSE) (ST_CARDINFO *pstCardInfo,unsigned int unTrigType,unsigned int unPulsewidth,unsigned int unPulsePeriod,unsigned int unEnable);
typedef int (__stdcall *PFUNNQTSETUPTRIGSOURCESORANDDELAY) (ST_CARDINFO *pstCardInfo,unsigned int unMask,unsigned int unDelay_LowPart,unsigned int unDelay_HighPart);
typedef int (__stdcall *PFUNNQTSETUPINPUTCHANNEL) (ST_CARDINFO *pstCardInfo,unsigned int unChannel,unsigned int unInputRange,unsigned int unTerm,unsigned int unInputOffset,unsigned int unDiffInput,unsigned int unChEn);
typedef int (__stdcall *PFUNNQTSETUPTIMESTAMP) (ST_CARDINFO *pstCardInfo, unsigned int TimeStampEn,unsigned int TimeStampSegmentLen,unsigned int GPSSecond,unsigned int Freq,unsigned int TimeStampSel);
typedef int (__stdcall *PFUNNQTSTART) (ST_CARDINFO *pstCardInfo,unsigned int unDirection,int bDmaEn,unsigned int unTimeOut,int TimedModeEn);
typedef int (__stdcall *PFUNNQTSTARTREPLAY) (ST_CARDINFO *pstCardInfo);
typedef int (__stdcall *PFUNNQTWAITFORDMADONEEVT) (ST_CARDINFO *pstCardInfo,unsigned int unDirection,unsigned int unTimeOut);
typedef int (__stdcall *PFUNNQTSETDATAHANDLEDONEEVT) (ST_CARDINFO *pstCardInfo,unsigned int unDirection);
typedef int (__stdcall *PFUNNQTGETDATA) (ST_CARDINFO *pstCardInfo,unsigned char *pBufDest,unsigned int unLen,unsigned int unTimeOut);
typedef int (__stdcall *PFUNNQTSENDDATA) (ST_CARDINFO *pstCardInfo,void *pBufSrc,unsigned int unLen, unsigned int *bytes_sent,unsigned int unTimeOut);
typedef int (__stdcall *PFUNNQTGETBRDSTATUS) (ST_CARDINFO *pstCardInfo,unsigned int Frequency,unsigned int *status);
typedef int (__stdcall *PFUNNQTGETRXBUFLEN) (ST_CARDINFO *pstCardInfo,unsigned int *RxBufLen);
typedef int (__stdcall *PFUNNQTIODELAYCAL) (ST_CARDINFO *pstCardInfo,unsigned int unCalFrq,unsigned int unChOpt,unsigned int IOWindowMode,unsigned int SampleRateGrade,unsigned char ucArrayClock[4],unsigned short usArrayOffset[4],unsigned int *punChIoDelayRes,unsigned int *punProgress,unsigned int TimeOut);
typedef int (__stdcall *PFUNNQTADCCAL) (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int unCalFrq,unsigned int unChOpt,unsigned int SampleRateGrade);
typedef int (__stdcall *PFUNNQTTUNEOFFSET) (ST_CARDINFO *pstCardInfo,unsigned int cs, double ReqOffset);
typedef int (__stdcall *PFUNNQTTUNEGAIN) (ST_CARDINFO *pstCardInfo,unsigned int cs, double ReqGain);
typedef int (__stdcall *PFUNNQTTUNEDIGITALGAIN) (ST_CARDINFO *pstCardInfo,unsigned int cs, double ReqGain);
typedef int (__stdcall *PFUNNQTRETURNZERO) (ST_CARDINFO *pstCardInfo,unsigned int dac_cs,unsigned pga_cs,double CurrGain,double InitOffset,double *ResultOffset);
typedef int (__stdcall *PFUNNQTSETDCOFFSETFORGAIN) (ST_CARDINFO *pstCardInfo,unsigned int dac_cs,unsigned pga_cs,double CurrGain,double InitOffset,double ExpectMean,double *ResultOffset,double *ResultMean);
typedef int (__stdcall *PFUNNQTDCOFFSETPGACAL) (ST_CARDINFO *pstCardInfo,double *ArrayOffsetScale,char *FileName);
typedef int (__stdcall *PFUNNQTDCCAL) (ST_CARDINFO *pstCardInfo,unsigned int CalDACEn,unsigned int CalInputRangeEn,char *FileName,double *ArrayZeroLevelDCOffset,double *ArrayPGAGain,double *ArrayDACCoeff);
typedef int (__stdcall *PFUNNQTCREATEWAVEFORM) (ST_CARDINFO *pstCardInfo, unsigned int Index,unsigned int WaveformLen,unsigned int LoopCnt);
typedef int (__stdcall *PFUNNQTWRITEREGISTER) (ST_CARDINFO *pstCardInfo, unsigned int BaseAddr,unsigned int Offset,unsigned int Value);
typedef int (__stdcall *PFUNNQTREADREGISTER) (ST_CARDINFO *pstCardInfo, unsigned int *BaseAddr,unsigned int *Offset,unsigned int *Value);
typedef int (__stdcall *PFUNNQTACOFFSETCAL) (ST_CARDINFO *pstCardInfo);
typedef int (__stdcall *PFUNNQTSTOREINIT) (ST_CARDINFO *pstCardInfo);
typedef int (__stdcall *PFUNNQTSTOREPARAMSET) (ST_CARDINFO *pstCardInfo,unsigned int NameRule,char *FileLocation,char *UsrFileName,unsigned int SplitFileSizeMB,unsigned int MaxNumFiles,unsigned int MaxFileSizeMB,unsigned int PPDATABUFLEN);
typedef int (__stdcall *PFUNNQTSTOREDATE) (ST_CARDINFO *pstCardInfo, char *FileName, int TrigMode);
typedef int (__stdcall *PFUNNQTSTORESTOP) (ST_CARDINFO *pstCardInfo);
typedef int (__stdcall *PFUNNQTSTARTGETFFTDATA) (ST_CARDINFO *pstCardInfo);
typedef int (__stdcall *PFUNNQTSTOPGETFFTDATA) (ST_CARDINFO *pstCardInfo);
typedef int	(__stdcall *PFUNNQTGETDISKSPACE) (ST_CARDINFO *pstCardInfo, double *ToatalSpace, double *FreeSpace);
typedef int (__stdcall *PFUNNQTGETDATATOFFT) (ST_CARDINFO *pstCardInfo, unsigned char *pDataBuf, unsigned int DataLen, unsigned int unTimeOut);
typedef int (__stdcall *PFUNNQTPOLLGETDATASTATUS) (ST_CARDINFO *pstCardInfo);
typedef int (__stdcall *PFUNNQTWAITFORWRITEFILEDONEEVT) (ST_CARDINFO *pstCardInfo);
typedef int (__stdcall *PFUNNQTFREEMEMRORY) (ST_CARDINFO *pstCardInfo);
typedef int (__stdcall *PFUNNQTGAINCAL) (ST_CARDINFO *pstCardInfo, unsigned int *cs,double ReqGain, double *CalValue);
typedef int (__stdcall *PFUNNQTGPIOSET) (ST_CARDINFO *pstCardInfo,unsigned int GPIODirection,unsigned int GPIODispatch,unsigned int DigitalOnlyEn);
typedef int (__stdcall *PFUNNQTGPIODELAYSET) (ST_CARDINFO *pstCardInfo,int GPIOSel,double Delay);
typedef int (__stdcall *PFUNNQTCHANNELOFFSETSET) (ST_CARDINFO *pstCardInfo,int ChnIdx,double OffsetVolt);
typedef int (__stdcall *PFUNNQTCHANNELRANGESET) (ST_CARDINFO *pstCardInfo,int ChnIdx,double RangeVolt);
typedef int (__stdcall *PFUNNQTBUFSTATUSGET) (ST_CARDINFO *pstCardInfo,long long  *pDataLenB,int *pBufOverflow,unsigned int *pNoBytesOverwritten);
typedef int (__stdcall *PFUNNQTBUFDATAGET) (ST_CARDINFO *pstCardInfo,unsigned char *pDestBuf,unsigned int NoBytesLen);
typedef double (__stdcall *PFUNNQTFCVT) (ST_CARDINFO *pstCardInfo, unsigned int DI, double AO);
typedef int (__stdcall *PFUNNQTABAMODESET) (ST_CARDINFO *pstCardInfo,unsigned int ABAMode,unsigned int ABADivider,unsigned int NoChn);
typedef int (__stdcall *PFUNNQTDIGINLATENCY) (ST_CARDINFO *pstCardInfo,unsigned int DigLatency);
typedef int (__stdcall *PFUNNQTDATAFORMATSET) (ST_CARDINFO *pstCardInfo,unsigned int DataFormat);
typedef int (__stdcall *PFUNNQTCALDATASET) (ST_CARDINFO *pstCardInfo,char *FpDelayTapVal,char *FpADCCalData);
typedef int (__stdcall *PFUNNQTGPIOWRITE) (ST_CARDINFO *pstCardInfo,int GPIOSel/*,unsigned int GPIODirection*/,unsigned int GPIOOutput);
typedef int (__stdcall *PFUNNQTGPIOREAD) (ST_CARDINFO *pstCardInfo,int GPIOSel/*,unsigned int GPIODirection*/,unsigned int *GPIOInput);
typedef int (__stdcall *PFUNNQTFLASHOPTEST) (ST_CARDINFO *pstCardInfo,unsigned int BaseAddr);
typedef int (__stdcall *PFUNNQTDUMPREGISTER) (ST_CARDINFO *pstCardInfo,unsigned int BaseAddr,unsigned int NoRegs);
typedef int (__stdcall *PFUNNQTGETFEAT) (ST_CARDINFO *pstCardInfo,unsigned int *FeatureBitMap);
typedef int (__stdcall *PFUNNQTERASEXCALDATA) (ST_CARDINFO *pstCardInfo,unsigned int BaseAddr);
typedef int (__stdcall *PFUNNQTSYNCOP) (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int unCalFrq,unsigned int unChOpt,unsigned int SampleRateGrade);
typedef int (__stdcall *PFUNNQTWAITDATAREADY) (ST_CARDINFO *pstCardInfo,unsigned int NoByteLen,unsigned int unTimeout);
typedef int (__stdcall *PFUNNQTSETNOTIFYSIZEB) (ST_CARDINFO *pstCardInfo,unsigned int NotifySizeB);
typedef int (__stdcall *PFUNNQTUPDATEFIRMWARE) (ST_CARDINFO *pstCardInfo,char *FpBin);
//#ifdef __cplusplus
#define IS_FLAG_ON(flag,value)              ((flag) == ((flag) & (value)))
#define COUNT_OF_ITEMS(item)                sizeof (item)/sizeof (item[0])
#define ALLOCITEM(type,pstItemRet,...)      try{pstItemRet=(type*)0;pstItemRet=new type(##__VA_ARGS__);}catch (...){pstItemRet=(type*)0;}
#define ALLOCITEMARRAY(type,pstItemRet,count)      try{pstItemRet=(type*)0;pstItemRet=new type[count];}catch (...){pstItemRet=(type*)0;}
#define INIT_THE_VARIABLE(variable2init)    memset (&variable2init,0,sizeof (variable2init));
#define SAFE_STRING_BY_ZERO_LAST(szString)  szString[sizeof(szString)/sizeof(szString[0])-1]=0;

#ifdef WIN32
//#include "windows.h"
#define CALLFUNCTIONFROMDLL(dllname,functionname,functiontype,returntype,defaultreturnvalue,...) \
    HMODULE hDll = (HMODULE)0;\
    functiontype pFun = (functiontype)0;\
    returntype eRet = (defaultreturnvalue);\
    if (hDll = LoadLibraryA (dllname))\
    {\
        if (pFun = (functiontype)GetProcAddress (hDll,functionname))\
            eRet = pFun (##__VA_ARGS__);\
        hDll = (HMODULE)0;\
    }\
    return eRet;
#endif

#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTOpenBoard (ST_CARDINFO *pstCardInfo,unsigned int unCardIdx);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTResetBoard (ST_CARDINFO *pstCardInfo);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTFastSet (ST_CARDINFO *pstCardInfo, unsigned int Frequency);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTCloseBoard (ST_CARDINFO *pstCardInfo);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTRegisterWrite (ST_CARDINFO *pstCardInfo,unsigned int unRegOffset,unsigned int unRegValue);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTRegisterRead (ST_CARDINFO *pstCardInfo,unsigned int unRegOffset,unsigned int *punRegValue);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTParameterSet (ST_CARDINFO *pstCardInfo,unsigned int unCmd,unsigned int unParam1,unsigned int unParam2,unsigned int unParam3,unsigned int unTimeOut);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTParameterGet (ST_CARDINFO *pstCardInfo,unsigned int *punCmd,unsigned int *punParam1,unsigned int *punParam2,unsigned int *punParam3,unsigned int unTimeOut);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTAdcModeSet (ST_CARDINFO *pstCardInfo,unsigned int unChOpt,unsigned int unModeFlg,unsigned int ClockDivider/*=0*/);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTForceIOdelay (ST_CARDINFO *pstCardInfo);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTWorkModeSet (ST_CARDINFO *pstCardInfo,unsigned int unSegmentSize,unsigned int unPreSamples,unsigned int unSegmentCnt,unsigned int unModeFlg,unsigned int unCompressorMode/*=0*/,unsigned int unPostSamples/*=0*/);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTClockInternalSet (ST_CARDINFO *pstCardInfo,unsigned int unSamplerate);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTClockSet (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int Frequency,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int RstADC/*=1*/);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTSoftTriggerSet (ST_CARDINFO *pstCardInfo,unsigned int unTrigType,unsigned int unEnable);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTExtTriggerSet (ST_CARDINFO *pstCardInfo,unsigned int unExtIdx,unsigned int unTrigType,unsigned int unEnable);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTChannelTriggerSet (ST_CARDINFO *pstCardInfo,unsigned int unChannel,unsigned int unTrigType,/*unsigned */int unRiseEdgeLevel,/*unsigned */int unFallEdgeLevel,unsigned int unEnable);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTPulseTriggerSet (ST_CARDINFO *pstCardInfo,unsigned int unTrigType,unsigned int unPulsewidth,unsigned int unPulsePeriod,unsigned int unEnable);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTTriggerSourceMaskSet (ST_CARDINFO *pstCardInfo,unsigned int unMask,unsigned int unDelay_LowPart,unsigned int unDelay_HighPart);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTInputChannelSet (ST_CARDINFO *pstCardInfo,unsigned int unChannel,unsigned int unInputRange,unsigned int unTerm,unsigned int unInputOffset,unsigned int unDiffInput,unsigned int unChEn);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTTimestampSet (ST_CARDINFO *pstCardInfo, unsigned int TimeStampEn,unsigned int TimeStampSegmentLen,unsigned int GPSSecond,unsigned int Freq,unsigned int TimeStampSel/*=0*/);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTStart (ST_CARDINFO *pstCardInfo,unsigned int unDirection,int bDmaEn,unsigned int unTimeOut,int TimedModeEn/*=false*/);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTStartReplay (ST_CARDINFO *pstCardInfo);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTWaitDMA (ST_CARDINFO *pstCardInfo,unsigned int unDirection,unsigned int unTimeOut/*=0xFFFFFFFF*/);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTDMADone (ST_CARDINFO *pstCardInfo,unsigned int unDirection);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTGetData (ST_CARDINFO *pstCardInfo,unsigned char *pBufDest,unsigned int unLen,unsigned int unTimeOut);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTSendData (ST_CARDINFO *pstCardInfo,void *pBufsrc,unsigned int unLen,unsigned int *bytes_sent,unsigned int unTimeOut);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTGetBrdStatus (ST_CARDINFO *pstCardInfo,unsigned int Frequency,unsigned int *status);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTGetRxBufLen (ST_CARDINFO *pstCardInfo,unsigned int *RxBufLen);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTIODelayCalibration (ST_CARDINFO *pstCardInfo,unsigned int unCalFrq,unsigned int unChOpt,unsigned int IOWindowMode,unsigned int SampleRateGrade,unsigned char ucArrayClock[4],unsigned short usArrayOffset[4],unsigned int *punChIoDelayRes,unsigned int *punProgress,unsigned int TimeOut);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTADCCalibration (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int unCalFrq,unsigned int unChOpt,unsigned int SampleRateGrade);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTTuneOffset (ST_CARDINFO *pstCardInfo,unsigned int cs,double ReqOffset);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTTuneGain (ST_CARDINFO *pstCardInfo,unsigned int cs,double ReqGain);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTTuneDigitalGain (ST_CARDINFO *pstCardInfo,unsigned int cs,double ReqGain);

#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTReturnZero (ST_CARDINFO *pstCardInfo,unsigned int dac_cs,unsigned pga_cs,double CurrGain,double InitOffset,double *ResultOffset);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTSetDCOffsetForGain (ST_CARDINFO *pstCardInfo,unsigned int dac_cs,unsigned pga_cs,double CurrGain,double InitOffset,double ExpectMean,double *ResultOffset,double *ResultMean);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTDCCal (ST_CARDINFO *pstCardInfo,UINT CalDACEn,UINT CalInputRangeEn,char *FileName,double *ArrayZeroLevelDCOffset,double *ArrayPGAGain,double *ArrayDACCoeff);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTCreateWaveform (ST_CARDINFO *pstCardInfo, unsigned int Index,unsigned int WaveformLen,unsigned int LoopCnt);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTWriteRegister (ST_CARDINFO *pstCardInfo, unsigned int BaseAddr,unsigned int Offset,unsigned int Value);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTReadRegister (ST_CARDINFO *pstCardInfo, unsigned int *BaseAddr,unsigned int *Offset,unsigned int *Value);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTACOffsetCal (ST_CARDINFO *pstCardInfo);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTStoreInit (ST_CARDINFO *pstCardInfo);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTStoreParamSet(ST_CARDINFO *pstCardInfo,unsigned int NameRule,char *FileLocation,char *UsrFileName,unsigned int SplitFileSizeMB,unsigned int MaxNumFiles,unsigned int MaxFileSizeMB,unsigned int PPDATABUFLEN);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTStoreData (ST_CARDINFO *pstCardInfo, char *FileName, int TrigMode);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTStoreStop (ST_CARDINFO *pstCardInfo);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTStartGetFFTData (ST_CARDINFO *pstCardInfo);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTStopGetFFTData (ST_CARDINFO *pstCardInfo);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTGetDiskSpace (ST_CARDINFO *pstCardInfo, double *ToatalSpace, double *FreeSpace);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTGetDataToFFT (ST_CARDINFO *pstCardInfo, unsigned char *pDataBuf, unsigned int DataLen, unsigned int unTimeOut);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTPollGetDataStatus (ST_CARDINFO *pstCardInfo);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTWriteFileDone (ST_CARDINFO *pstCardInfo);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTFreeMemrory (ST_CARDINFO *pstCardInfo);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTGainCal (ST_CARDINFO *pstCardInfo, unsigned int *cs,double ReqGain, double *CalValue);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTGPIOSet (ST_CARDINFO *pstCardInfo, unsigned int GPIODirection,unsigned int GPIODispatch,unsigned int DigitalOnlyEn/*=0*/);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTGPIODelaySet (ST_CARDINFO *pstCardInfo, int GPIOSel,double Delay);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTChannelOffsetSet(ST_CARDINFO *pstCardInfo,int ChnIdx,double OffsetVolt);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTChannelRangeSet(ST_CARDINFO *pstCardInfo,int ChnIdx,double RangeVolt);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTBufStatusGet(ST_CARDINFO *pstCardInfo,long long  *pDataLenB,int *pBufOverflow,unsigned int *pNoBytesOverwritten);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTBufSDataGet(ST_CARDINFO *pstCardInfo,unsigned char *pDestBuf,unsigned int NoBytesLen);
#ifdef __cplusplus
extern "C"
#endif
  double __stdcall QTFCVT (ST_CARDINFO *pstCardInfo,unsigned int DI, double AO);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTABAModeSet (ST_CARDINFO *pstCardInfo, unsigned int ABAMode,unsigned int ABADivider,unsigned int NoChn);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTDigInLatency(ST_CARDINFO *pstCardInfo,unsigned int DigLatency);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTDataFormatSet(ST_CARDINFO *pstCardInfo,unsigned int DataFormat);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTCalDataSet(ST_CARDINFO *pstCardInfo,char *FpDelayTapVal,char *FpADCCalData);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTGPIOWrite(ST_CARDINFO *pstCardInfo,int GPIOSel/*,unsigned int GPIODirection*/,unsigned int GPIOOutput);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTGPIORead(ST_CARDINFO *pstCardInfo,int GPIOSel/*,unsigned int GPIODirection*/,unsigned int *GPIOInput);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTFlashOpTest(ST_CARDINFO *pstCardInfo,unsigned int BaseAddr);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTDumpRegister(ST_CARDINFO *pstCardInfo,unsigned int BaseAddr,unsigned int NoRegs);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTGetFeat(ST_CARDINFO *pstCardInfo,unsigned int *FeatureBitMap);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTEraseXCalData(ST_CARDINFO *pstCardInfo,unsigned int BaseAddr);
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTSyncOp (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int unCalFrq,unsigned int unChOpt,unsigned int SampleRateGrade);

#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTWaitDataReady (ST_CARDINFO *pstCardInfo,unsigned int NoByteLen,unsigned int unTimeout);

#ifdef __cplusplus
  extern "C"
#endif
  int __stdcall QTSetNotifySizeB(ST_CARDINFO *pstCardInfo,unsigned int NotifySizeB);

#ifdef __cplusplus
  extern "C"
#endif
    int __stdcall QTUpdateFirmware(ST_CARDINFO *pstCardInfo,char *FpBin);