//include file from QT library
#include "QT_IMPORT.h"
#include "QTApi.h"
#ifdef __cplusplus
using namespace QTApi;
#endif

#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTOpenBoard (ST_CARDINFO *pstCardInfo,unsigned int unCardIdx)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTInitCardByIdx",PFUNNQTINITCARDBYIDX,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unCardIdx)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTResetBoard (ST_CARDINFO *pstCardInfo)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTResetCard",PFUNNQTRESETCARD,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTFastSet (ST_CARDINFO *pstCardInfo, unsigned int Frequency)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTFastSet",PFUNNQTFASTSET,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,Frequency)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTCloseBoard (ST_CARDINFO *pstCardInfo)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTCloseCard",PFUNNQTCLOSECARD,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTRegisterWrite (ST_CARDINFO *pstCardInfo,unsigned int unRegOffset,unsigned int unRegValue)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTWrtReg",PFUNNQTWRTREG,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unRegOffset,unRegValue)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTRegisterRead (ST_CARDINFO *pstCardInfo,unsigned int unRegOffset,unsigned int *punRegValue)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTReadReg",PFUNNQTREADREG,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unRegOffset,punRegValue)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTParameterSet (ST_CARDINFO *pstCardInfo,unsigned int unCmd,unsigned int unParam1,unsigned int unParam2,unsigned int unParam3,unsigned int unTimeOut)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetParam",PFUNNQTSETPARAM,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unCmd,unParam1,unParam2,unParam3,unTimeOut)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTParameterGet (ST_CARDINFO *pstCardInfo,unsigned int *punCmd,unsigned int *punParam1,unsigned int *punParam2,unsigned int *punParam3,unsigned int unTimeOut)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTGetParam",PFUNNQTGETPARAM,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,punCmd,punParam1,punParam2,punParam3,unTimeOut)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTAdcModeSet (ST_CARDINFO *pstCardInfo,unsigned int unChOpt,unsigned int unModeFlg,unsigned int ClockDivider/*=0*/)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetupADCMode",PFUNNQTSETUPADCMODE,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unChOpt,unModeFlg,ClockDivider)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTForceIOdelay (ST_CARDINFO *pstCardInfo)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTForceIOdelay",PFUNNQTFORCEIODELAY,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTWorkModeSet (ST_CARDINFO *pstCardInfo,unsigned int unSegmentSize,unsigned int unPreSamples,unsigned int unSegmentCnt,unsigned int unModeFlg,unsigned int unCompressorMode/*=0*/,unsigned int unPostSamples/*=0*/)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetupWorkMode",PFUNNQTSETUPWORKMODE,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unSegmentSize,unPreSamples,unSegmentCnt,unModeFlg,unCompressorMode,unPostSamples)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTClockInternalSet (ST_CARDINFO *pstCardInfo,unsigned int unSamplerate)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetupClockInternal",PFUNNQTSETUPCLOCKINTERNAL,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unSamplerate)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTClockSet (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int Frequency,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int RstADC/*=1*/)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetupClock",PFUNNQTSETUPCLOCK,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,Fref,RefDiv,Frequency,VCOMode,RefClkMode,ADCClkMode,RstADC)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTSoftTriggerSet (ST_CARDINFO *pstCardInfo,unsigned int unTrigType,unsigned int unEnable)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetupTrigSoftware",PFUNNQTSETUPTRIGSOFTWARE,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unTrigType,unEnable)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTExtTriggerSet (ST_CARDINFO *pstCardInfo,unsigned int unExtIdx,unsigned int unTrigType,unsigned int unEnable)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetupTrigExternal",PFUNNQTSETUPTRIGEXTERNAL,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unExtIdx,unTrigType,unEnable)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTChannelTriggerSet (ST_CARDINFO *pstCardInfo,unsigned int unChannel,unsigned int unTrigType,/*unsigned */int unRiseEdgeLevel,/*unsigned */int unFallEdgeLevel,unsigned int unEnable)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetupTrigChannel",PFUNNQTSETUPTRIGCHANNEL,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unChannel,unTrigType,unRiseEdgeLevel,unFallEdgeLevel,unEnable)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTPulseTriggerSet (ST_CARDINFO *pstCardInfo,unsigned int unTrigType,unsigned int unPulsewidth,unsigned int unPulsePeriod,unsigned int unEnable)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetupTrigPulse",PFUNNQTSETUPTRIGPULSE,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unTrigType,unPulsewidth,unPulsePeriod,unEnable)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTTriggerSourceMaskSet (ST_CARDINFO *pstCardInfo,unsigned int unMask,unsigned int unDelay_LowPart,unsigned int unDelay_HighPart)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetupTrigSourcesOrAndDelay",PFUNNQTSETUPTRIGSOURCESORANDDELAY,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unMask,unDelay_LowPart,unDelay_HighPart)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTInputChannelSet (ST_CARDINFO *pstCardInfo,unsigned int unChannel,unsigned int unInputRange,unsigned int unTerm,unsigned int unInputOffset,unsigned int unDiffInput,unsigned int unChEn)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetupInputChannel",PFUNNQTSETUPINPUTCHANNEL,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unChannel,unInputRange,unTerm,unInputOffset,unDiffInput,unChEn)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTTimestampSet (ST_CARDINFO *pstCardInfo, unsigned int TimeStampEn,unsigned int TimeStampSegmentLen,unsigned int GPSSecond,unsigned int Freq,unsigned int TimeStampSel/*=0*/)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetupTimestamp",PFUNNQTSETUPTIMESTAMP,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,TimeStampEn,TimeStampSegmentLen,GPSSecond,Freq,TimeStampSel)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTStart (ST_CARDINFO *pstCardInfo,unsigned int unDirection,int bDmaEn,unsigned int unTimeOut,int TimedModeEn/*=false*/)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTStart",PFUNNQTSTART,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unDirection,bDmaEn,unTimeOut,TimedModeEn)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTStartReplay (ST_CARDINFO *pstCardInfo)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTStartReplay",PFUNNQTSTARTREPLAY,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTWaitDMA (ST_CARDINFO *pstCardInfo,unsigned int unDirection,unsigned int unTimeOut/*=0xFFFFFFFF*/)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTWaitForDmaDoneEvt",PFUNNQTWAITFORDMADONEEVT,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unDirection,unTimeOut)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTDMADone (ST_CARDINFO *pstCardInfo,unsigned int unDirection)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetDataHandleDoneEvt",PFUNNQTSETDATAHANDLEDONEEVT,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unDirection)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTGetData (ST_CARDINFO *pstCardInfo,unsigned char *pBufDest,unsigned int unLen,unsigned int unTimeOut)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTGetData",PFUNNQTGETDATA,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,pBufDest,unLen,unTimeOut)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTSendData (ST_CARDINFO *pstCardInfo,void *pBufsrc,unsigned int unLen,unsigned int *bytes_sent,unsigned int unTimeOut)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSendData",PFUNNQTSENDDATA,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,pBufsrc,unLen, bytes_sent,unTimeOut)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTGetBrdStatus (ST_CARDINFO *pstCardInfo,unsigned int Frequency,unsigned int *status)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTGetBrdStatus",PFUNNQTGETBRDSTATUS,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,Frequency,status)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTGetRxBufLen (ST_CARDINFO *pstCardInfo,unsigned int *RxBufLen)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTGetRxBufLen",PFUNNQTGETRXBUFLEN,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,RxBufLen)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTIODelayCalibration (ST_CARDINFO *pstCardInfo,unsigned int unCalFrq,unsigned int unChOpt,unsigned int IOWindowMode,unsigned int SampleRateGrade,unsigned char ucArrayClock[4],unsigned short usArrayOffset[4],unsigned int *punChIoDelayRes,unsigned int *punProgress,unsigned int TimeOut)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTIODelayCal",PFUNNQTIODELAYCAL,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,unCalFrq,unChOpt,IOWindowMode,SampleRateGrade,ucArrayClock,usArrayOffset,punChIoDelayRes,punProgress,TimeOut)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTADCCalibration (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int unCalFrq,unsigned int unChOpt,unsigned int SampleRateGrade)
{
  if (pstCardInfo->ProdInfo.product_number==0x1142)
  {
    CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTXcal",PFUNNQTADCCAL,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,Fref,RefDiv,VCOMode,RefClkMode,ADCClkMode,unCalFrq,unChOpt,SampleRateGrade)
  }
  else
  {
    CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTADCCal",PFUNNQTADCCAL,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,Fref,RefDiv,VCOMode,RefClkMode,ADCClkMode,unCalFrq,unChOpt,SampleRateGrade)
  }
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTTuneOffset (ST_CARDINFO *pstCardInfo,unsigned int cs,double ReqOffset)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTTuneOffset",PFUNNQTTUNEOFFSET,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,cs,ReqOffset)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTTuneGain (ST_CARDINFO *pstCardInfo,unsigned int cs,double ReqGain)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTTuneGain",PFUNNQTTUNEGAIN,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,cs,ReqGain)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTTuneDigitalGain (ST_CARDINFO *pstCardInfo,unsigned int cs,double ReqGain)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTTuneDigitalGain",PFUNNQTTUNEDIGITALGAIN,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,cs,ReqGain)
}

#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTReturnZero (ST_CARDINFO *pstCardInfo,unsigned int dac_cs,unsigned pga_cs,double CurrGain,double InitOffset,double *ResultOffset)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTGetZeroLevelDCOffsetForGain",PFUNNQTRETURNZERO,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,dac_cs,pga_cs,CurrGain,InitOffset,ResultOffset)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTSetDCOffsetForGain (ST_CARDINFO *pstCardInfo,unsigned int dac_cs,unsigned pga_cs,double CurrGain,double InitOffset,double ExpectMean,double *ResultOffset,double *ResultMean)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetDCOffsetForGain",PFUNNQTSETDCOFFSETFORGAIN,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,dac_cs,pga_cs,CurrGain,InitOffset,ExpectMean,ResultOffset,ResultMean)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTDCCal (ST_CARDINFO *pstCardInfo,UINT CalDACEn,UINT CalInputRangeEn,char *FileName,double *ArrayZeroLevelDCOffset,double *ArrayPGAGain,double *ArrayDACCoeff)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTDCCal",PFUNNQTDCCAL,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,CalDACEn,CalInputRangeEn,FileName,ArrayZeroLevelDCOffset,ArrayPGAGain,ArrayDACCoeff)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTCreateWaveform (ST_CARDINFO *pstCardInfo, unsigned int Index,unsigned int WaveformLen,unsigned int LoopCnt)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTCreateWaveform",PFUNNQTCREATEWAVEFORM,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,Index,WaveformLen,LoopCnt)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTWriteRegister (ST_CARDINFO *pstCardInfo, unsigned int BaseAddr,unsigned int Offset,unsigned int Value)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTWriteRegister",PFUNNQTWRITEREGISTER,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,BaseAddr,Offset,Value)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTReadRegister (ST_CARDINFO *pstCardInfo, unsigned int *BaseAddr,unsigned int *Offset,unsigned int *Value)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTReadRegister",PFUNNQTREADREGISTER,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,BaseAddr,Offset,Value)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTACOffsetCal (ST_CARDINFO *pstCardInfo)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTACOffsetCal",PFUNNQTACOFFSETCAL,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTStoreInit (ST_CARDINFO *pstCardInfo)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME, "nQTStoreInit", PFUNNQTSTOREINIT, int, RES_ERROR_FILE_NOT_FOUND, pstCardInfo)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTStoreParamSet(ST_CARDINFO *pstCardInfo,unsigned int NameRule,char *FileLocation,char *UsrFileName,unsigned int SplitFileSizeMB,unsigned int MaxNumFiles,unsigned int MaxFileSizeMB,unsigned int PPDATABUFLEN)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME, "nQTStoreParamSet", PFUNNQTSTOREPARAMSET, int, RES_ERROR_FILE_NOT_FOUND, pstCardInfo,NameRule,FileLocation,UsrFileName,SplitFileSizeMB,MaxNumFiles,MaxFileSizeMB,PPDATABUFLEN);
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTStoreData (ST_CARDINFO *pstCardInfo, char *FileName, int TrigMode)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME, "nQTStoreData", PFUNNQTSTOREDATE, int, RES_ERROR_FILE_NOT_FOUND, pstCardInfo, FileName, TrigMode)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTStoreStop (ST_CARDINFO *pstCardInfo)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME, "nQTStoreStop", PFUNNQTSTORESTOP, int, RES_ERROR_FILE_NOT_FOUND, pstCardInfo)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTStartGetFFTData (ST_CARDINFO *pstCardInfo)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME, "nQTStartGetFFTData", PFUNNQTSTARTGETFFTDATA, int, RES_ERROR_FILE_NOT_FOUND, pstCardInfo)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTStopGetFFTData (ST_CARDINFO *pstCardInfo)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME, "nQTStopGetFFTData", PFUNNQTSTOPGETFFTDATA, int, RES_ERROR_FILE_NOT_FOUND, pstCardInfo)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTGetDiskSpace (ST_CARDINFO *pstCardInfo, double *ToatalSpace, double *FreeSpace)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME, "nQTGetDiskSpace", PFUNNQTGETDISKSPACE, int, RES_ERROR_FILE_NOT_FOUND, pstCardInfo, ToatalSpace, FreeSpace)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTGetDataToFFT (ST_CARDINFO *pstCardInfo, unsigned char *pDataBuf, unsigned int DataLen, unsigned int unTimeOut)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME, "nQTGetDataToFFT", PFUNNQTGETDATATOFFT, int, RES_ERROR_FILE_NOT_FOUND, pstCardInfo, pDataBuf, DataLen,unTimeOut)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTPollGetDataStatus (ST_CARDINFO *pstCardInfo)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME, "nQTPollGetDataStatus", PFUNNQTPOLLGETDATASTATUS, int, RES_ERROR_FILE_NOT_FOUND, pstCardInfo)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTWriteFileDone (ST_CARDINFO *pstCardInfo)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME, "nQTWaitForWriteFileDoneEvt", PFUNNQTWAITFORWRITEFILEDONEEVT, int, RES_ERROR_FILE_NOT_FOUND, pstCardInfo)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTFreeMemrory (ST_CARDINFO *pstCardInfo)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME, "nQTFreeMemrory", PFUNNQTFREEMEMRORY, int, RES_ERROR_FILE_NOT_FOUND, pstCardInfo)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTGainCal (ST_CARDINFO *pstCardInfo, unsigned int *cs,double ReqGain, double *CalValue)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTGainCal",PFUNNQTGAINCAL,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,cs,ReqGain,CalValue)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTGPIOSet (ST_CARDINFO *pstCardInfo, unsigned int GPIODirection,unsigned int GPIODispatch,unsigned int DigitalOnlyEn/*=0*/)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTGPIOSet",PFUNNQTGPIOSET,int,RES_MBCMD_FAILED,pstCardInfo,GPIODirection,GPIODispatch,DigitalOnlyEn)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTGPIODelaySet (ST_CARDINFO *pstCardInfo, int GPIOSel,double Delay)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTGPIODelaySet",PFUNNQTGPIODELAYSET,int,RES_MBCMD_FAILED,pstCardInfo,GPIOSel,Delay)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTChannelOffsetSet(ST_CARDINFO *pstCardInfo,int ChnIdx,double OffsetVolt)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTChannelOffsetSet",PFUNNQTCHANNELOFFSETSET,int,RES_MBCMD_FAILED,pstCardInfo,ChnIdx,OffsetVolt)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTChannelRangeSet(ST_CARDINFO *pstCardInfo,int ChnIdx,double RangeVolt)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTChannelRangeSet",PFUNNQTCHANNELRANGESET,int,RES_MBCMD_FAILED,pstCardInfo,ChnIdx,RangeVolt)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTBufStatusGet(ST_CARDINFO *pstCardInfo,long long  *pDataLenB,int *pBufOverflow,unsigned int *pNoBytesOverwritten)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTBufStatusGet",PFUNNQTBUFSTATUSGET,int,RES_ERROR_UNKNOWN,pstCardInfo,pDataLenB,pBufOverflow,pNoBytesOverwritten)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTBufSDataGet(ST_CARDINFO *pstCardInfo,unsigned char *pDestBuf,unsigned int NoBytesLen)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTBufDataGet",PFUNNQTBUFDATAGET,int,RES_ERROR_UNKNOWN,pstCardInfo,pDestBuf,NoBytesLen)
}
#ifdef __cplusplus
extern "C"
#endif
double __stdcall QTFCVT (ST_CARDINFO *pstCardInfo,unsigned int DI, double AO)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTFCVT",PFUNNQTFCVT,double,RES_ERROR_BAD_PARAMETER,pstCardInfo,DI,AO)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTABAModeSet (ST_CARDINFO *pstCardInfo, unsigned int ABAMode,unsigned int ABADivider,unsigned int NoChn)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTABAModeSet",PFUNNQTABAMODESET,int,RES_MBCMD_FAILED,pstCardInfo,ABAMode,ABADivider,NoChn)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTDigInLatency(ST_CARDINFO *pstCardInfo,unsigned int DigLatency)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTDigInLatency",PFUNNQTDIGINLATENCY,int,RES_MBCMD_FAILED,pstCardInfo,DigLatency)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTDataFormatSet(ST_CARDINFO *pstCardInfo,unsigned int DataFormat)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTDataFormatSet",PFUNNQTDATAFORMATSET,int,RES_MBCMD_FAILED,pstCardInfo,DataFormat)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTCalDataSet(ST_CARDINFO *pstCardInfo,char *FpDelayTapVal,char *FpADCCalData)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTCalDataSet",PFUNNQTCALDATASET,int,RES_OPEN_FAILURE,pstCardInfo,FpDelayTapVal,FpADCCalData)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTGPIOWrite(ST_CARDINFO *pstCardInfo,int GPIOSel/*,unsigned int GPIODirection*/,unsigned int GPIOOutput)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTGPIOWrite",PFUNNQTGPIOWRITE,int,RES_MBCMD_FAILED,pstCardInfo,GPIOSel/*,GPIODirection*/,GPIOOutput)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTGPIORead(ST_CARDINFO *pstCardInfo,int GPIOSel/*,unsigned int GPIODirection*/,unsigned int *GPIOInput)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTGPIORead",PFUNNQTGPIOREAD,int,RES_MBCMD_FAILED,pstCardInfo,GPIOSel/*,GPIODirection*/,GPIOInput)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTFlashOpTest(ST_CARDINFO *pstCardInfo,unsigned int BaseAddr)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTFlashOpTest",PFUNNQTFLASHOPTEST,int,RES_MBCMD_FAILED,pstCardInfo,BaseAddr)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTDumpRegister(ST_CARDINFO *pstCardInfo,unsigned int BaseAddr,unsigned int NoRegs)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTDumpRegister",PFUNNQTDUMPREGISTER,int,RES_MBCMD_FAILED,pstCardInfo,BaseAddr,NoRegs)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTGetFeat(ST_CARDINFO *pstCardInfo,unsigned int *FeatureBitMap)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTGetFeat",PFUNNQTGETFEAT,int,RES_MBCMD_FAILED,pstCardInfo,FeatureBitMap)
}
#ifdef __cplusplus
extern "C"
#endif
int __stdcall QTEraseXCalData(ST_CARDINFO *pstCardInfo,unsigned int BaseAddr)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTEraseXCalData",PFUNNQTERASEXCALDATA,int,RES_MBCMD_FAILED,pstCardInfo,BaseAddr)
}
#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTSyncOp (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int unCalFrq,unsigned int unChOpt,unsigned int SampleRateGrade)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSyncOp",PFUNNQTSYNCOP,int,RES_ERROR_FILE_NOT_FOUND,pstCardInfo,Fref,RefDiv,VCOMode,RefClkMode,ADCClkMode,unCalFrq,unChOpt,SampleRateGrade)
}

#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTWaitDataReady (ST_CARDINFO *pstCardInfo,unsigned int NoByteLen,unsigned int unTimeout)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTWaitDataReady",PFUNNQTWAITDATAREADY,int,1,pstCardInfo,NoByteLen,unTimeout)
}

#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTSetNotifySizeB(ST_CARDINFO *pstCardInfo,unsigned int NotifySizeB)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTSetNotifySizeB",PFUNNQTSETNOTIFYSIZEB,int,RES_ERROR_BAD_PARAMETER,pstCardInfo,NotifySizeB)
}

#ifdef __cplusplus
extern "C"
#endif
  int __stdcall QTUpdateFirmware(ST_CARDINFO *pstCardInfo,char *FpBin)
{
  CALLFUNCTIONFROMDLL (QTAPI_DLL_NAME,"nQTUpdateFirmware",PFUNNQTUPDATEFIRMWARE,int,RES_ERROR_BAD_PARAMETER,pstCardInfo,FpBin)
}
