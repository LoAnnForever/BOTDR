#ifndef _QT_API_H
#define _QT_API_H

#include "QTfmCommon.h"
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <queue>
#include "xdma_public.h"

#ifdef __cplusplus
namespace QTApi {
#endif
  using namespace std;

#ifdef QTAPI_EXPORTS
#define QTAPI __declspec(dllexport)
#else
#define QTAPI __declspec(dllimport)
#endif

#define QTAPI_DLL_NAME              "QTApi.dll"

#define ERRORTEXTLEN 0x200
// #define MBCMDMAXLEN 100
// #define ONEMBCMDLEN 4
		//typedef struct _PollResult
	//{
	//  UINT head;//start pointer
	//  UINT tail;//end pointer
	//  UINT32 descCredits;//valid BD
	//  UINT32 length[XDMA_RING_NUM_BLOCKS];//result length per BD
	//}PollResult, *PPollResult;

  typedef struct FileInfo
  {
    char FileName[MAX_PATH];
    LARGE_INTEGER size;
  } FILEINFO, *PFILEINFO;

	typedef struct _DmaInfo
	{
		DmaDataBufAddr DmaAdd[XDMA_RING_NUM_BLOCKS];// dma data buffer address
		HANDLE DmaEvent;//event to indicate dma event
	}DmaInfo, *PDmaInfo;
	typedef struct
	{
		UINT param[4];
	}MBOXMSG, *PMBOXMSG;
	/**
	 * This typedef contains configuration information for the device.
	 */

	typedef struct {
		UINT16 DeviceId;		/**< Unique ID of device */
		UINT32 BaseAddress;	/**< Register base address */
		UINT8 UseFSL;		/**< use the FSL for the interface. */
		UINT8 SendID;		/**< FSL link for the write i/f mailbox. */
		UINT8 RecvID;		/**< FSL link for the read i/f mailbox. */

	} XMbox_Config;
	/**
	 * The XMbox driver instance data. The user is required to allocate a
	 * variable of this type for every mbox device in the system. A
	 * pointer to a variable of this type is then passed to the driver API
	 * functions.
	 */
	typedef struct {
		XMbox_Config Config;	/**< Configuration data, includes base address
					  */
		UINT32 IsReady;		/**< Device is initialized and ready */
	} XMbox;
	typedef struct {
		UINT32 BaseAddress;
		UINT32 reg[4];
		UINT32 PackageLen;
		UINT32 ResetBit;
	} TestData_Config;


	typedef struct _xdma_device
	{
		PollResult xdma_PollResult;
		DmaInfo xdma_DmaInfo;
		XMbox xbox;
		TestData_Config TestData;
		HANDLE control;
		HANDLE user;
		HANDLE user_event;
		HANDLE h2c0;
		HANDLE c2h0;
    volatile UINT head;

	}xdma_device, *Pxdma_device;

    typedef enum CARDFNC {AnalogIn, AnalogOut, DigitalOut, DigitalIn, DigitalIO} Carfnc;
    typedef enum DRV_RESULT_CODE
    {
        RES_SUCCESS = 0,
        RES_ALREADY_OPEN,
        RES_OPEN_FAILURE = 0X80000000,
        RES_RESET_FAILURE,
        RES_IOCTL_READREG_FAILURE, //0X80000002
        RES_IOCTL_WRITEREG_FAILURE,
        RES_IOCTL_CREATE_INTERRUPT_EVENT_FAILURE, //0X80000004
        RES_IOCTL_MAP_MEMORY_FAILURE,
        RES_IOCTL_UNMAPADDR_FAILURE, //0x80000006
        //DMA OPERATION ERROR CODE
        RES_DMATX_LEN_LARGER_MAX,
        RES_DMA_LEN_IS_ZERO, //0X80000008
        RES_DMA_LENGTH_128BYTE_ALIGNMENT_ERR,
        RES_DMA_LENGTH_ALIGNMENT_ERROR, //min 4kBytes//0x8000000a
        RES_DMA_BUF_UNALLOC,
        RES_DATA_READY_TIMEOUT, //0X8000000c
        RES_DMA_TIMEOUT,
        RES_DMARX_LEN_LARGER_MAX,
        RES_FPGABUF_READY_FOR_DMARX_TIMEOUT, //0x8000000f
        //stream mode
        RES_STREAM_MODE_ENABLE_TX_ALREADY, //0x80000010
        RES_STREAM_MODE_ENABLE_RX_ALREADY,
        RES_STREAM_MODE_THREAD_TX_FALSE, //0x80000012
        RES_STREAM_MODE_THREAD_RX_FALSE,
        RES_WAITFOR_STREAM_DMA_DONE_EVENT_TIMEOUT_TX, //0x80000014
        RES_WAITFOR_STREAM_DMA_DONE_EVENT_TIMEOUT_RX,
        RES_WAITFOR_STREAM_DMA_APP_DONE_EVENT_TIMEOUT_TX,//0x80000016
        RES_WAITFOR_STREAM_DMA_APP_DONE_EVENT_TIMEOUT_RX,
        RES_DMA_TX_OVER, //0x80000018
        RES_DMA_RX_OVER,
        //auto set configure file
        RES_CREATE_OR_OPEN_CNF_FAILURE, //0x8000001a
        RES_READ_CNF_FAILURE,
        RES_CNF_IS_EMPTY, //0x8000001c
        RES_CNF_IS_LARGER,
        RES_SET_BATCH_REGS_WRITEREG_FAILURE, //0x8000001e
        RES_SET_BATCH_REGS_READREG_FAILURE,
        RES_AUTO_SET_MAILBOX_REG_TIMEOUT, //0x80000020
        RES_MAILBOX_SETPARAM_TIMEOUT,
        RES_MAILBOX_GETPARAM_TIMEOUT, //0x80000022
        RES_MBCMD_CNT_LARGER_THAN_MAXLEN,
        RES_READ_SETUP_FROM_ARRY_BY_INDEX_FALSE, //0x80000024
        RES_MONITORTXINT_WAIT_FAILED,
        RES_NOT_TX_INT, //0x80000026
        RES_IO_DELAY_CAL_SET_74_FALSE,
        //Added by zhangwenchao
        RES_ERROR_UNKNOWN,
        RES_ERROR_BAD_PARAMETER,
        RES_ERROR_NOT_ENOUGH_RESOURCE,//0x8000002a
        RES_ERROR_UNSUPPORTED,
        RES_ERROR_UNEXPECTED,
        RES_ERROR_FILE_NOT_FOUND,
        RES_ERROR_IODELAY_NO_EYE,
        //Added by BaiLi@20150711
        RES_ERROR_CLOCK_FREQ_ILLEGAL,//0x800002f
        //Added by BaiLi@20150806
        RES_ERROR_BOARD_EXCEPTION,
        RES_CALIB_TIMEOUT,
        RES_MBCMD_TIMEOUT,
        RES_MBCMD_FAILED,
        //Added by zhangwenchao
        RES_STORE_DATA_BUZY,
        RES_ERROR_NO_RANGE_SET,//0x80000035
        RES_ERROR_NOT_VALID_RANGE,
        RES_ERROR_NOT_VALID_CHNIDX,
        RES_ERROR_VFIFO_IS_FULL,
        RES_ERROR_VFIFO_IS_EMPTY,
        RES_ERROR_VFIFO_EXCEPTION,//0x8000003a
        RES_NOT_ENOUGH_DATA_IN_VFIFO,
        RES_ERROR_ALLOC_BUF,
        RES_ERROR_PRETRIGLEN_ILLEGAL,
        RES_ERROR_FLASH_OUT_BLOCK,//Address of BPI flash is out of block
        RES_ERROR_PRODUCT_INFO_UNDEF,//no product information found in flash
        RES_IOCTL_MAP_EVENT_FAILURE,
        RES_ELEVATE_PRIVILEGE_FAILURE,
        RES_EXTEND_FILE_FAILURE,
		RES_ERROR_NOT_ENGOUGH_FREESPACE,
        RES_ERROR_DAC_INIT_FAILED,
        RES_ERROR_PATH_NOT_EXIST,
        RES_ERROR_FILE_OPEN_FAILED,
        RES_ERROR_REPLAY_SIZE_UNMATCH,
		RES_ERROR_DDR_INIT_FAILED
    }QT_ERROR_CODE;

    /*!
* The IOCompletionPort class wraps the functions of I/O completion port.
*/
    class IOCompletionPort
    {
    private:
      HANDLE m_hIOCP;

    public:
      LARGE_INTEGER FilePointOffset;
       queue<int> outstanding_queue;
       CRITICAL_SECTION qlock;
      IOCompletionPort() : m_hIOCP(NULL)
      {
        FilePointOffset.QuadPart = 0;
        InitializeCriticalSection(&qlock);
      }

      ~IOCompletionPort()
      {
        DeleteCriticalSection(&qlock);
        Close();
      }

      /*!
      * Create a new completion port that is not associated with any I/O
      * devices, and set the maximum number of threads that the operating
      * system can allow to concurrently process I/O completion packets for
      * the I/O completion port.
      *
      * \param dwNumberOfConcurrentThreads
      * The maximum number of threads that the operating system can allow to
      * concurrently process I/O completion packets for the I/O completion
      * port. If this parameter is zero, the system allows as many concurrently
      * running threads as there are processors in the system.
      */
      BOOL Create(DWORD dwNumberOfConcurrentThreads = 0)
      {
        m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0,
          dwNumberOfConcurrentThreads);
        return (m_hIOCP != NULL);
      }

      BOOL Close()
      {
        // Ensure that the handle of the I/O completion port is closed
        if (m_hIOCP != NULL && CloseHandle(m_hIOCP))
        {
          m_hIOCP = NULL;
          return TRUE;
        }
        return FALSE;
      }

      /*!
      * Associate a device with the port. The system appends this information
      * to the completion port's device list. To have the results of
      * asynchronous I/O requests queued to the completion port you need to
      * associate the file handles with the completion port.
      *
      * When an asynchronous I/O request for a device completes, the system
      * checks to see whether the device is associated with a completion port
      * and, if it is, the system appends the completed I/O request entry to
      * the end of the completion port's I/O completion queue.
      *
      * \param hDevice
      * An open device handle to be associated with the I/O completion port.
      * The handle has to have been opened for overlapped I/O completion.
      *
      * \param CompKey
      * A value that has meaning to you; the operating system does not care
      * what you pass here. We may use this parameter to differentiate the
      * different devices associated to the completion port. One completion key
      * stands for a device handle. The value is included in the completion
      * packet for any I/O requests for the given file handle.
      */
      BOOL AssociateDevice(HANDLE hDevice, ULONG_PTR CompKey)
      {
        HANDLE h = CreateIoCompletionPort(hDevice, m_hIOCP, CompKey, 0);
        return h == m_hIOCP;
      }

      /*!
      * Queue your own completion packets. Although completion packets are
      * normally queued by the operating system as asynchronous I/O requests
      * are completed, you can also queue your own completion packets. This is
      * achieved using the PostQueuedCompletionStatus function.
      *
      * \param CompKey
      * The value to be returned through the lpCompletionKey parameter of the
      * GetQueuedCompletionStatus function.
      *
      * \param dwNumBytes
      * The value to be returned through the lpNumberOfBytesTransferred
      * parameter of the GetQueuedCompletionStatus function.
      *
      * \param po
      * The value to be returned through the lpOverlapped parameter of the
      * GetQueuedCompletionStatus function.
      */
      BOOL QueuePacket(ULONG_PTR CompKey, DWORD dwNumBytes = 0,
        OVERLAPPED* po = NULL)
      {
        return PostQueuedCompletionStatus(m_hIOCP, dwNumBytes, CompKey, po);
      }

      /*!
      * Attempts to dequeue an I/O completion packet from the specified I/O
      * completion port. If there is no completion packet queued, the function
      * waits for a pending I/O operation associated with the completion port
      * to complete. You can dequeue completion packets on any thread in the
      * process that created the completion port. All that the thread needs is
      * the port handle.
      *
      * \param pCompKey
      * A pointer to a variable that receives the completion key value
      * associated with the file handle whose I/O operation has completed. A
      * completion key is a per-file key that is specified in a call to
      * AssociateDevice.
      *
      * \param pdwNumBytes
      * A pointer to a variable that receives the number of bytes transferred
      * during an I/O operation that has completed.
      *
      * \param ppo
      * A pointer to a variable that receives the address of the OVERLAPPED
      * structure that was specified when the completed I/O operation was
      * started.
      *
      * \param dwMilliseconds
      * The number of milliseconds that the caller is willing to wait for a
      * completion packet to appear at the completion port. If a completion
      * packet does not appear within the specified time, the function times
      * out, returns FALSE, and sets *lpOverlapped to NULL.
      */
      BOOL DequeuePacket(ULONG_PTR* pCompKey, PDWORD pdwNumBytes,
        OVERLAPPED** ppo, DWORD dwMilliseconds = INFINITE)
      {
        return GetQueuedCompletionStatus(m_hIOCP, pdwNumBytes, pCompKey, ppo,
          dwMilliseconds);
      }
    };

    /*!
    * The ReqIOCompletionPort class wraps the functions of I/O completion port.
    */
    class ReqIOCompletionPort
    {
    private:
      HANDLE m_hIOCP;

    public:
      LARGE_INTEGER FilePointOffset;
      queue<int> outstanding_queue;
      CRITICAL_SECTION qlock;
      ReqIOCompletionPort() : m_hIOCP(NULL)
      {
        FilePointOffset.QuadPart = 0;
        InitializeCriticalSection(&qlock);
      }

      ~ReqIOCompletionPort()
      {
        DeleteCriticalSection(&qlock);
        Close();
      }

      /*!
      * Create a new completion port that is not associated with any I/O
      * devices, and set the maximum number of threads that the operating
      * system can allow to concurrently process I/O completion packets for
      * the I/O completion port.
      *
      * \param dwNumberOfConcurrentThreads
      * The maximum number of threads that the operating system can allow to
      * concurrently process I/O completion packets for the I/O completion
      * port. If this parameter is zero, the system allows as many concurrently
      * running threads as there are processors in the system.
      */
      BOOL Create(DWORD dwNumberOfConcurrentThreads = 0)
      {
        m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0,
          dwNumberOfConcurrentThreads);
        return (m_hIOCP != NULL);
      }

      BOOL Close()
      {
        // Ensure that the handle of the I/O completion port is closed
        if (m_hIOCP != NULL && CloseHandle(m_hIOCP))
        {
          m_hIOCP = NULL;
          return TRUE;
        }
        return FALSE;
      }

      /*!
      * Associate a device with the port. The system appends this information
      * to the completion port's device list. To have the results of
      * asynchronous I/O requests queued to the completion port you need to
      * associate the file handles with the completion port.
      *
      * When an asynchronous I/O request for a device completes, the system
      * checks to see whether the device is associated with a completion port
      * and, if it is, the system appends the completed I/O request entry to
      * the end of the completion port's I/O completion queue.
      *
      * \param hDevice
      * An open device handle to be associated with the I/O completion port.
      * The handle has to have been opened for overlapped I/O completion.
      *
      * \param CompKey
      * A value that has meaning to you; the operating system does not care
      * what you pass here. We may use this parameter to differentiate the
      * different devices associated to the completion port. One completion key
      * stands for a device handle. The value is included in the completion
      * packet for any I/O requests for the given file handle.
      */
      BOOL AssociateDevice(HANDLE hDevice, ULONG_PTR CompKey)
      {
        HANDLE h = CreateIoCompletionPort(hDevice, m_hIOCP, CompKey, 0);
        return h == m_hIOCP;
      }

      /*!
      * Queue your own completion packets. Although completion packets are
      * normally queued by the operating system as asynchronous I/O requests
      * are completed, you can also queue your own completion packets. This is
      * achieved using the PostQueuedCompletionStatus function.
      *
      * \param CompKey
      * The value to be returned through the lpCompletionKey parameter of the
      * GetQueuedCompletionStatus function.
      *
      * \param dwNumBytes
      * The value to be returned through the lpNumberOfBytesTransferred
      * parameter of the GetQueuedCompletionStatus function.
      *
      * \param po
      * The value to be returned through the lpOverlapped parameter of the
      * GetQueuedCompletionStatus function.
      */
      BOOL QueuePacket(ULONG_PTR CompKey, DWORD dwNumBytes = 0,
        OVERLAPPED* po = NULL)
      {
        return PostQueuedCompletionStatus(m_hIOCP, dwNumBytes, CompKey, po);
      }

      /*!
      * Attempts to dequeue an I/O completion packet from the specified I/O
      * completion port. If there is no completion packet queued, the function
      * waits for a pending I/O operation associated with the completion port
      * to complete. You can dequeue completion packets on any thread in the
      * process that created the completion port. All that the thread needs is
      * the port handle.
      *
      * \param pCompKey
      * A pointer to a variable that receives the completion key value
      * associated with the file handle whose I/O operation has completed. A
      * completion key is a per-file key that is specified in a call to
      * AssociateDevice.
      *
      * \param pdwNumBytes
      * A pointer to a variable that receives the number of bytes transferred
      * during an I/O operation that has completed.
      *
      * \param ppo
      * A pointer to a variable that receives the address of the OVERLAPPED
      * structure that was specified when the completed I/O operation was
      * started.
      *
      * \param dwMilliseconds
      * The number of milliseconds that the caller is willing to wait for a
      * completion packet to appear at the completion port. If a completion
      * packet does not appear within the specified time, the function times
      * out, returns FALSE, and sets *lpOverlapped to NULL.
      */
      BOOL DequeuePacket(ULONG_PTR* pCompKey, PDWORD pdwNumBytes,
        OVERLAPPED** ppo, DWORD dwMilliseconds = INFINITE)
      {
        return GetQueuedCompletionStatus(m_hIOCP, pdwNumBytes, pCompKey, ppo,
          dwMilliseconds);
      }
    };


    /*!
    * The OVERLAPPEDEX structures appends some members to the VERLAPPED structure
    */
    struct OVERLAPPEDEX : OVERLAPPED
    {
    public:
      OVERLAPPEDEX(int nType = 0, BYTE* pbBuffer = NULL, int nSize = 0, PVOID pBuf = NULL)
      {
        Internal = InternalHigh = 0;
        Offset = OffsetHigh = 0;
        hEvent = NULL;
        Type = nType;
        Buffer = pBuf;
        //Buffer = VirtualAlloc(NULL, BUFFER_SIZE, MEM_COMMIT, PAGE_READWRITE);
        //if (Buffer == NULL)
        //{
        //	printf("VirtualAlloc failed\n");
        //}
        //if (pbBuffer && nSize > 0)
        //{
        //	memcpy_s(Buffer, BUFFER_SIZE, pbBuffer, nSize);
        //}
      }

      // Append some members to the old OVERLAPPED structure
      int Type;
      int BufIdx;
      int BufLen;
      UINT head;
      PVOID Buffer;// = VirtualAlloc(NULL, BUFFER_SIZE, MEM_COMMIT, PAGE_READWRITE);
      //queue<int>*outstanding_queue;

    };
    enum PPSts {
      NotStart = 0,
      Wr2Buf0,Wr2Buf1,
      RdBuf0,RdBuf1};
    enum BufSts {Empty=0, Full,ISOVERFLOW};
    typedef struct _tag_Thread
    {
      HANDLE hThread[4];
      HANDLE hEvent[4];
      unsigned int NoByteLen;
      int DataStatus;
      int KeepAlive;//1: alive; 0: exit
    }QTTHREAD,*PTHREAD;
    typedef struct _tag_QTStorage
    {
      //----global variables for storage applications
      HANDLE hFile[PENDINGS];
      OVERLAPPEDEX osWriteOP[PENDINGS];
      HANDLE Evt_FileIsRdy2Close;//Event will be set when the file is ready to close
      HANDLE hThread_GetDataToWriteFile, hThread_WriteFile, hThread_GetFFTData;
      HANDLE hGetData, hWriteFile, hGetFFTData;
      HANDLE hGetDataDone;
      unsigned int PP_FileId;//file index in Ping-Pang style
      unsigned char *pPPBuf[PENDINGS];//file pointer to Ping-pang buffer
      //Ping-pang buffer read/write status
      //volatile enum PPSts WrPpSts;
      //volatile enum PPSts RdPpSts;
      //volatile enum BufSts Buf0Sts;
      //volatile enum BufSts Buf1Sts;
      volatile unsigned int WrPpIdx;
      volatile unsigned int RdPpIdx;
      volatile enum BufSts BufStatus[PENDINGS];//empty,full or overflow
      volatile unsigned int KeepRun;
      volatile int TriMode;
      volatile unsigned __int64 GetDataCnt;
      volatile int Position;
      volatile unsigned int DataOver;
      volatile unsigned int GetFFTData, StartGet;
      unsigned char *FFTDataBuf;
      unsigned int TimeOut_ms;//ms
      //unsigned int EACHLEN;//Granularity to write file in Bytes
      unsigned int WRITECNT;//Number of EACHLEN per PPDATABUFLEN
      unsigned int PingPangBufIsOverFlow;//true is overflow
      char NextFileName[MAX_PATH];//next file name to create
      unsigned int FileIndex;//file index in split file mode
      //User control parameters
      unsigned int SplitFileSizeMB;//Split at file size in MB. 0 means don't split file
      char FileLocation[MAX_PATH];//Specify file location in windows style to store files. Files are stored in current working directory by default
      char UsrFileName[MAX_PATH];//User specified file name
      unsigned int NameRule;//0(by default): {Data}_{Time}_{Index}; 1:User specified file name {User_spec_name}_{Index}
      unsigned int MaxNumFiles;//Max number of files to stop storing files. 0 means unlimited. MaxNumFiles has priority over MaxFileSizeMB.
      unsigned int MaxFileSizeMB;//Max file size in 1024*1024 bytes to stop writing file. 0 means unlimited.
      unsigned int PPDATABUFLEN;//Ping-pang buffer size in byte
      unsigned long long TotalMB;//Total data has been written in MB
      IOCompletionPort port;
      HANDLE hIOCompletionThread;
      volatile LONG nWritesInProgress;
      volatile LONG nWriteInSync;
      volatile int ReqFFTLen;//Request FFT samples
	  DWORD_PTR processAffinity;
	  DWORD_PTR systemAffinity;
      volatile int EnableStreaming;//true is streaming feature is enabled
#ifdef __cplusplus
      void Reset (void)
      {
        for (unsigned int i=0;i<PENDINGS;i++)
        {
          hFile[i] = INVALID_HANDLE_VALUE;
          pPPBuf[i] = NULL;
          BufStatus[i] = Empty;
        }
        memset(osWriteOP,0,PENDINGS*sizeof(OVERLAPPEDEX));
        hThread_GetDataToWriteFile = NULL;
        hThread_WriteFile = NULL;
        hThread_GetFFTData = NULL;
        hGetData = NULL;
        hWriteFile = NULL;
        hGetFFTData = NULL;
        hGetDataDone = NULL;
        PP_FileId = 0;
        //WrPpSts=NotStart;
        //RdPpSts=NotStart;
        //Buf0Sts=Empty;
        //Buf1Sts=Empty;
        WrPpIdx=0;
        RdPpIdx=0;
        KeepRun = false;
        TriMode = 0;
        GetDataCnt = 0;
        Position = 0;
        DataOver = 0;
        GetFFTData = 0;
        StartGet = 0;
        FFTDataBuf = NULL;
        TimeOut_ms = INFINITE;
        //EACHLEN = 0x400000;
        //WRITECNT = (PPDATABUFLEN/EACHLEN);
        PingPangBufIsOverFlow = 0;
        FileIndex = 0;
        SplitFileSizeMB = 0;
        NameRule = 0;
        MaxNumFiles = 0;
        MaxFileSizeMB = 0;
        PPDATABUFLEN = 0x20000000;
        TotalMB = 0;
        hIOCompletionThread = NULL;
        nWritesInProgress = 0;
        nWriteInSync = 0;
        EnableStreaming = 0;
        sprintf_s(FileLocation,".\\");
        sprintf_s(UsrFileName,"autosave");
      }
      _tag_QTStorage ()
      {
        Reset ();
      }
#endif
    }QTSTORAGE,*PQTSTORAGE;

    typedef struct _tag_Replay
    {
      //----global variables for storage applications
      HANDLE hFile[PENDINGS];
      OVERLAPPEDEX osWriteOP[PENDINGS];
      HANDLE Evt_FileIsRdy2Close;//Event will be set when the file is ready to close
      HANDLE hThread_GetDataToWriteFile, hThread_WriteFile, hThread_GetFFTData;
      HANDLE hGetData, hWriteFile, hGetFFTData;
      HANDLE hGetDataDone;
      unsigned int PP_FileId;//file index in Ping-Pang style
      unsigned char *pPPBuf[PENDINGS];//file pointer to Ping-pang buffer
                                      //Ping-pang buffer read/write status
                                      //volatile enum PPSts WrPpSts;
                                      //volatile enum PPSts RdPpSts;
                                      //volatile enum BufSts Buf0Sts;
                                      //volatile enum BufSts Buf1Sts;
      volatile unsigned int WrPpIdx;
      volatile unsigned int RdPpIdx;
      volatile enum BufSts BufStatus[PENDINGS];//empty,full or overflow
      volatile unsigned int KeepRun;
      volatile int TriMode;
      volatile unsigned __int64 GetDataCnt;
      volatile int Position;
      volatile unsigned int DataOver;
      volatile unsigned int GetFFTData, StartGet;
      unsigned char *FFTDataBuf;
      unsigned int TimeOut_ms;//ms
                              //unsigned int EACHLEN;//Granularity to write file in Bytes
      unsigned int WRITECNT;//Number of EACHLEN per PPDATABUFLEN
      unsigned int PingPangBufIsOverFlow;//true is overflow
      char NextFileName[MAX_PATH];//next file name to create
      unsigned int FileIndex;//file index in split file mode
                             //User control parameters
      unsigned int SplitFileSizeMB;//Split at file size in MB. 0 means don't split file
      char FileLocation[MAX_PATH];//Specify file location in windows style to store files. Files are stored in current working directory by default
      char UsrFileName[MAX_PATH];//User specified file name
      unsigned int NameRule;//0(by default): {Data}_{Time}_{Index}; 1:User specified file name {User_spec_name}_{Index}
      unsigned int MaxNumFiles;//Max number of files to stop storing files. 0 means unlimited. MaxNumFiles has priority over MaxFileSizeMB.
      unsigned int MaxFileSizeMB;//Max file size in 1024*1024 bytes to stop writing file. 0 means unlimited.
      unsigned int PPDATABUFLEN;//Ping-pang buffer size in byte
      unsigned long long TotalMB;//Total data has been written in MB
      ReqIOCompletionPort port;
      HANDLE hIOCompletionThread;
      volatile LONG nWritesInProgress;
      volatile LONG nWriteInSync;
      volatile int ReqFFTLen;//Request FFT samples
      DWORD_PTR processAffinity;
      DWORD_PTR systemAffinity;
      //queue<FileInfo> Filelist;
      int StartIndex;
      int EndIndex;
      int IQ_en;//replay I/Q data
      int IF;//Intermediate frequency
      int LoopMode;//>0 if enable loop in replay mode

#ifdef __cplusplus
      void Reset(void)
      {
        for (unsigned int i = 0; i<PENDINGS; i++)
        {
          hFile[i] = INVALID_HANDLE_VALUE;
          pPPBuf[i] = NULL;
          BufStatus[i] = Empty;
        }
        Evt_FileIsRdy2Close = NULL;
        memset(osWriteOP, 0, PENDINGS * sizeof(OVERLAPPEDEX));
        hThread_GetDataToWriteFile = NULL;
        hThread_WriteFile = NULL;
        hThread_GetFFTData = NULL;
        hGetData = NULL;
        hWriteFile = NULL;
        hGetFFTData = NULL;
        hGetDataDone = NULL;
        PP_FileId = 0;
        //WrPpSts=NotStart;
        //RdPpSts=NotStart;
        //Buf0Sts=Empty;
        //Buf1Sts=Empty;
        WrPpIdx = 0;
        RdPpIdx = 0;
        KeepRun = false;
        TriMode = 0;
        GetDataCnt = 0;
        Position = 0;
        DataOver = 0;
        GetFFTData = 0;
        StartGet = 0;
        FFTDataBuf = NULL;
        TimeOut_ms = INFINITE;
        //EACHLEN = 0x400000;
        //WRITECNT = (PPDATABUFLEN/EACHLEN);
        PingPangBufIsOverFlow = 0;
        FileIndex = 0;
        SplitFileSizeMB = 0;
        NameRule = 0;
        MaxNumFiles = 0;
        MaxFileSizeMB = 0;
        PPDATABUFLEN = 0x20000000;
        TotalMB = 0;
        hIOCompletionThread = NULL;
        nWritesInProgress = 0;
        nWriteInSync = 0;
        sprintf_s(FileLocation, ".\\");
        sprintf_s(UsrFileName, "autosave");
        IQ_en = 0;
        IF = 0;
        LoopMode = 0;
      }
      _tag_Replay()
      {
        Reset();
      }
#endif
    }LDREPLAY, *PREPLAY;

    typedef struct _tag_QTIntermedium
    {
      unsigned int DMA_LENGTH;//ÿ�λ�ȡ���ݳ���
      unsigned int DELAY_TAP_STEPNUM;//ʱ�ӳ�ͷindex
      unsigned int CHANNEL_COUNT;//����ͨ����
      unsigned int NUM_DATA_CLK;//��·ʱ����
      unsigned int CALDATA_BASE;//flash�׵�ַ
      double GAIN_GRANULARITY;//PGA���沽��
      unsigned int ChMask;//��ͬ�ͺŰ忨������ͨ����־��ÿ��bit��Ӧһ��ͨ����Ϊ1����ڣ�Ϊ0�򲻴���
      unsigned int dac_cs[4];//DACоƬƬѡ
      unsigned int pga_cs[4];//PGAоƬƬѡ
      double InputRange[MAX_INPUT_RANGE_NUM];
      int GainCode[MAX_INPUT_RANGE_NUM];
      unsigned int PosSlope[MAX_DAC_NUM];
      int gGPIODelayTapSel[4];
      unsigned char DelayTapVal[128];//Store all tap values
      int GainStepIdx[MAX_GAIN_STEP_NUM];
      unsigned int adda_baseaddr;// = REGISTER_ADDA_BASEADDR;
      //unsigned short usDataBusOffset[4];//data bus offset

#ifdef __cplusplus
      void Reset (void)
      {
        DMA_LENGTH=0;
        DELAY_TAP_STEPNUM=0;
        CHANNEL_COUNT=0;
        NUM_DATA_CLK=128;
        CALDATA_BASE = SPI_FLASH_BASE_ADDR;
        GAIN_GRANULARITY = 0;
        ChMask = 0xff;
        dac_cs[0] = 16;
        dac_cs[1] = 17;
        dac_cs[2] = 18;
        dac_cs[3] = 19;
        pga_cs[0] = 16;
        pga_cs[1] = 17;
        pga_cs[2] = 18;
        pga_cs[3] = 19;
        InputRange[0] = 500;
        InputRange[1] = 1000;
        InputRange[2] = 2500;
        InputRange[3] = 5000;
        GainCode[0] = 3;
        GainCode[1] = 2;
        GainCode[2] = 1;
        GainCode[3] = 0;
        PosSlope[0] = 1;
        PosSlope[1] = 0;
        PosSlope[2] = 1;
        PosSlope[3] = 0;
        gGPIODelayTapSel[0] = 68;
        gGPIODelayTapSel[1] = 69;
        gGPIODelayTapSel[2] = 70;
        gGPIODelayTapSel[3] = 71;
        memset(DelayTapVal,0,128);
        memset(GainStepIdx,-1,MAX_GAIN_STEP_NUM);
        //usDataBusOffset[0] = 8;
        //usDataBusOffset[1] = 8;
        //usDataBusOffset[2] = 8;
        //usDataBusOffset[3] = 8;
      }
      _tag_QTIntermedium ()
      {
        Reset ();
      }
#endif
    }QTINTERMEDIUM,*PQTINTERMEDIUM;


    typedef struct _tag_QTCalData
    {
      double ArrayZeroLevelDCOffset[MAX_DAC_NUM][MAX_GAIN_STEP_NUM];
      double ArrayPGAGain[MAX_DAC_NUM][MAX_INPUT_RANGE_NUM];
      double ArrayDACCoeff[MAX_DAC_NUM][MAX_GAIN_STEP_NUM];
#ifdef __cplusplus
      void Reset (void)
      {
        memset(ArrayZeroLevelDCOffset,0,sizeof(double)*(MAX_DAC_NUM*MAX_GAIN_STEP_NUM));
        memset(ArrayPGAGain,0,sizeof(double)*(MAX_DAC_NUM*MAX_INPUT_RANGE_NUM));
        memset(ArrayDACCoeff,0,sizeof(double)*(MAX_DAC_NUM*MAX_GAIN_STEP_NUM));
      }
      _tag_QTCalData ()
      {
        Reset ();
      }
#endif
    }QTCALDATA,*PQTCALDATA;

    typedef struct _tag_QTDIO
    {
      unsigned int DigitalInOnly;         //1 if digital-only acquisition mode is enabled;
      unsigned int NumDIBitsPerChannel;   //Number of digital bit per channel;
      unsigned int Direction[256];        //0: input;1: output
      double Delay[256];            //IO delay per bit
      unsigned int Latency[256];          //latency per bit
#ifdef __cplusplus
      void Reset (void)
      {
        DigitalInOnly = 0;
        NumDIBitsPerChannel = 0;
        memset(Direction,0,256);
        memset(Delay,0,256);
        memset(Latency,0,256);
      }
      _tag_QTDIO ()
      {
        Reset ();
      }
#endif
    }QTDIO,*PQTDIO;


    typedef struct _tag_QTDAQParams
    {
      //parameters regarding DAQ
      QTFM_COMMON_BOARD_WORK_MODE WorkMode; //Work mode enumeration
      QTFM_COMMON_TRIGGER_MODE TrigMode;    //Global trigger mode
      unsigned int SegmentLen;              //number of samples per segment of all enabled channels
      unsigned int PreTriggerLen;           //pre-trigger length in samples of all enabled channels
      unsigned int PostTriggerLen;          //Post-trigger length in samples for level-trigger mode only
      unsigned int SegmentCnt;              //trigger counter
      unsigned int uncompressMode;          //bit[0]=1:ʹ������ѹ��ģ��,0:��ֹ����ѹ������;//bit[1]=1:ʹ�����ݽ�ѹ�����ܣ�0����ֹ���ݽ�ѹ������
      unsigned int CounterMode;             //Internal counter mode for test only
      //parameters regarding time stamp
      unsigned int TimeStampEn;             //Enable/Disable Timestamp mode. The following list valid values:
                                            //       0x0: Disable timestamp mode. Timestamp counter keep no change and values is param2 and param3 are ignored.
                                            //       0x3: Enable GPS mode, internal clock is used to counting.Accumulative error could impact on precision of timestamp along the time.
                                            //       0x13: Enable GPS mode, external 1pps clock is required to counting. This is a more accurate way vs. 0x3 mode.
      unsigned int TimeStampSegmentLen;
      unsigned int TimeStampSel;            //ʱ�������ѡ��0��ѡ��GPSʱ������ݣ�1��ѡ���û�ʱ�������
      unsigned int GpsScond;

      //parameters regarding dual-sample-rate DAQ
      QTFM_ABA_MODE ABAMode;                // ABA mode selection
      unsigned int ABADivider;              //In step of 16
      unsigned int NoChnInUse;              //Number of active channel in use
      unsigned int AccCnt;                  //Number of segment to accumulate
      unsigned int MeanMode;                //0:16bit mode 1:32bit mode
      unsigned int MeanEn;                  //0:��ֹƽ�� 1��ʹ��ƽ��
      unsigned int FeatureBitMap;           //��ǿ����bit mask

#ifdef __cplusplus
      void Reset (void)
      {
        WorkMode = QTFM_COMMON_BOARD_WORK_MODE_STD_SIGNLE; //Work mode enumeration
        TrigMode = QTFM_COMMON_TRIGGER_MODE_EDGE;
        SegmentLen = 0x400000;
        PreTriggerLen = 0;
        PostTriggerLen = 0;
        SegmentCnt = 1;
        uncompressMode = 0;
        CounterMode = 0;
        TimeStampEn = 0;
        TimeStampSegmentLen = 0;
        TimeStampSel = 0;
        GpsScond = 0;
        ABAMode = ABA_NORMAL_MODE;
        ABADivider = 32;
        NoChnInUse = 1;
        AccCnt = 0;
        MeanMode = 0;
        MeanEn = 1;
      }
      _tag_QTDAQParams ()
      {
        Reset ();
      }
#endif
    }QTDAQPARAMS,*PQTDAQPARAMS;

    typedef struct _tag_QTClock
    {
      unsigned __int64 SRate;                 //Sample rate in Hz
      unsigned __int64 Fclk;                  //Required frequency from clock board to ADC chip in Hz
      unsigned __int64 F_adclk;               //ad clock frequency in FPGA in Hz
      unsigned int Fref;                        //Reference clock frequency in Hz
      QTFM_COMMON_CLOCK_REFERENCE RefClkMode;   //Change to QTFM_COMMON_CLOCK_REF_MODE_1 if external reference clock is required.
      QTFM_COMMON_ADC_CLOCK ADCClkMode;         //Change to QTFM_COMMON_ADC_CLOCK_MODE_1 if external sampling clock is required.
      unsigned int SampleRateGrade;             //(SampleRate < QTFM_COMMON_CLOCK_FREQUENCY_MIN)? 1:0;
#ifdef __cplusplus
      void Reset (void)
      {
        SRate            = 0;
        Fclk             = 0;
        F_adclk          = 0;
        Fref             = 0; 
        RefClkMode       = QTFM_COMMON_CLOCK_REF_MODE_2;
        ADCClkMode       = QTFM_COMMON_ADC_CLOCK_MODE_0;
        SampleRateGrade  = 0;
      }
      _tag_QTClock ()
      {
        Reset ();
      }
#endif
    }QTCLOCK,*PQTCLOCK;

    typedef struct _tag_QTProductInfo
    {
      unsigned int  V_number      ;           //ƽ̨V�汾��
      unsigned int  R_number      ;           //ƽ̨R�汾��
      unsigned int  M_number      ;           //ƽ̨M�汾��
      unsigned int  product_line  ;           //��Ʒ�߱꣬1:PCI��3:VPX��7:FMC
      unsigned int  product_series;           //�Ӳ�Ʒ��ʶ��1:AD��Ʒ��2:DA��Ʒ
      unsigned int  model_numbel_h;           //�ͺŸ�λ
      unsigned int  model_numbel_l;           //�ͺŵ�λ
      unsigned int  couple_type_h ;           //��Ϸ�ʽ��λ
      unsigned int  couple_type_l ;           //��Ϸ�ʽ��λ
      unsigned int  part_number   ;           //�����ţ��������ֲ�ͬ����
      unsigned int  channel_number;           //AD/DA����ͨ����Ŀ
      unsigned int  serial_number ;           //�忨��š�ÿ���忨�ı�Ŷ���Ψһ��
      unsigned int  carry_revision;           //�ذ�汾
      unsigned int  adda_revision ;           //AD/DA��汾
      unsigned int  clock_revision;           //ʱ�Ӱ�汾
      unsigned int  RTL_revision  ;           //RTL�汾��Ϣ
      unsigned int  EDK_revision  ;           //EDK�汾��Ϣ
      unsigned int  VSP_revision  ;           //VSP�汾��Ϣ
      unsigned int  product_week  ;           //�������ڣ���������
      unsigned int  product_year  ;           //�������ڣ��������
               int  product_number;           //1125,1128,1130,1135,1138,1156,etc.-1 if undefined.
      unsigned int  couple_type   ;           //0xAC:AC;0xDC:DC;0xDB:DC and VG supported
      unsigned int  product_model ;           //1125AC4,1125DC1,1125DC2,1125DC4,1128AC1,1128AC2,
                                              //1130AC1,1130AC2,1130AC4,
                                              //1135AC1,1135AC2,1135AC4,
                                              //1138AC1,1138AC2,1138AC4,1138AC6,1138AC8,
                                              //1138DC1,1138DC2,1138DC4
#ifdef __cplusplus
      void Reset (void)
      {
        V_number       = 0xFFFF;               //ƽ̨V�汾��
        R_number       = 0xFFFF;               //ƽ̨R�汾��
        M_number       = 0xFF;                 //ƽ̨M�汾��
        product_line   = 0xFF;                 //��Ʒ�߱꣬1:PCI��3:VPX��7:FMC
        product_series = 0xFF;                 //�Ӳ�Ʒ��ʶ��1:AD��Ʒ��2:DA��Ʒ
        model_numbel_h = 0xFF;                 //�ͺŸ�λ
        model_numbel_l = 0xFF;                 //�ͺŵ�λ
        couple_type_h  = 0xFF;                 //��Ϸ�ʽ��λ
        couple_type_l  = 0xFF;                 //��Ϸ�ʽ��λ
        part_number    = 0xFF;                 //�����ţ��������ֲ�ͬ����
        channel_number = 0xFF;                 //AD/DA����ͨ����Ŀ
        serial_number  = 0xFFFFFFFF;           //�忨��š�ÿ���忨�ı�Ŷ���Ψһ��
        carry_revision = 0xFF;                 //�ذ�汾
        adda_revision  = 0xFF;                 //AD/DA��汾
        clock_revision = 0xFF;                 //ʱ�Ӱ�汾
        RTL_revision   = 0xFFFFFFFF;           //RTL�汾��Ϣ
        EDK_revision   = 0xFFFFFFFF;           //EDK�汾��Ϣ
        VSP_revision   = 0xFFFFFFFF;           //VSP�汾��Ϣ
        product_week   = 0xFF;                 //�������ڣ���������
        product_year   = 0xFF;                 //�������ڣ��������
        product_number = -1;
        couple_type    = 0xFFFFFFFF;
        product_model  = 0xFFFFFFFF;
      }
      _tag_QTProductInfo ()
      {
        Reset ();
      }
#endif
    }QTPRODUCTINFO,*PQTPRODUCTINFO;
    typedef struct _tag_QTVFIFO
    {
      //----Global variables for VFIFO
      volatile __int64 WrPtr,RdPtr,DataLenB;
      volatile __int64 CurWrPtr;
      __int64 PERBUFLEN;//VFIFO size
      __int64 FifoSizeB;   
      volatile __int64 Dma_i;
      __int64 ufill;//dummy variable, make memory align
      volatile unsigned int ByteOffset;
      volatile unsigned int empty,full;
      unsigned int AFullTHD;
      unsigned int AEmpty;
      volatile unsigned int NoBytesOverwritten;//Number data bytes of overwritten samples     
      unsigned int BufNum;      
      volatile unsigned int CurBufIdx,RdBufIdx;
      unsigned char *gpDataBuf[256];
      volatile int EnableVfifo;//set to true if enabled
#ifdef __cplusplus
      void Reset (void)
      {
        WrPtr=0,RdPtr=0,DataLenB=0;
        CurWrPtr=0;
        ByteOffset = 0;
        empty=1,full=0;
        AFullTHD = 0;
        AEmpty = 0;
        NoBytesOverwritten = 0;//Number data bytes of overwritten samples
        PERBUFLEN = 64<<20;//VFIFO size
        BufNum=4;
        FifoSizeB = BufNum*(PERBUFLEN);
        EnableVfifo = 1;
        for(int i=0;i<256;i++)
        {
          gpDataBuf[i] = NULL;
        }
        CurBufIdx=0,RdBufIdx=0;
        Dma_i=0;
    ufill=0;
      }
      _tag_QTVFIFO ()
      {
        Reset ();
      }
#endif
    }QTVFIFO,*PQTVFIFO;

    typedef struct _DmaBufAdd
    {
        unsigned long UserAddr_LowPart;
        unsigned long UserAddr_HighPart;
        unsigned long PhyAddr_LowPart;
        unsigned long PhyAddr_HighPart;
#ifdef __cplusplus
        void Reset (void)
        {
            UserAddr_LowPart = (unsigned long)0;
            UserAddr_HighPart = (unsigned long)0;
            PhyAddr_LowPart = (unsigned long)0;
            PhyAddr_HighPart = (unsigned long)0;
        }
        _DmaBufAdd ()
        {
            Reset ();
        }
#endif
    }DmaBufAdd,*PDmaBufAdd;
    typedef struct DRV_INF_BLOCK
    {
        xdma_device dev;
        void * hCard;
        void * hIntEvt;
        unsigned int iCardNo;
        DmaBufAdd DmaBA[DMABUFCNT];
        unsigned int uiErrCode;
        volatile int bThreadLiving_Rx;//start rx set is true,after done set false
        volatile int bThreadLiving_Tx;//start Tx set is true,after done set false
        void * hThread_Tx;//Tx/Rx thread
        void * hThread_Rx;//Tx/Rx thread
        unsigned int EachTransferLen_Tx;
        unsigned int EachTransferLen_Rx;
        unsigned __int64 ReqTotalLenB;
        unsigned int DmaCnt_Tx;
        unsigned int DmaCnt_Rx;
        unsigned int Remain_Tx;
        unsigned int Remain_Rx;
        unsigned int TransferTimeOut_Tx;
        unsigned int TransferTimeOut_Rx;
        void* CurVa_Tx;
        unsigned int CurTransferLen_Tx;
        void* CurVa_Rx;
        unsigned long CurIntFlg;
        unsigned long CurDataSrc;
        unsigned long PreDataSrc;
        void * hEvtDmaDone_Tx;
        void * hEvtDmaDone_Rx;
        void * hEvtDataHandleDone_Tx;
        void * hEvtDataHandleDone_Rx;
        volatile int KeepRun;//true if board is running; false if data sample and transfer is stopped.
        volatile int bThreadWriteBuf;//true if ThreadWriteBuf is alive; false if ThreadWriteBuf is dead
        unsigned int MaxEachDmaLenB;//DAM length in byte to notify a event
        int EnableReplay;                   // enable DAC replay mode
        int CalMode;//1:timing interleaving calibration; 0:initiate without calibration
        int ReplayDDS;//1: replay dds data with signal frequency of 1/4 update rate
#ifdef __cplusplus
        void Reset (void)
        {
            hCard = (void*)-1;
            hIntEvt = (void*)0;
            iCardNo = 0;
            DmaBA[DMABUFCNT];
            uiErrCode = RES_SUCCESS;
            bThreadLiving_Rx = false;//start rx set is true,after done set false
            bThreadLiving_Tx = false;//start Tx set is true,after done set false
            hThread_Tx = (void*)0;//Tx/Rx thread
            hThread_Rx = (void*)0;//Tx/Rx thread
            EachTransferLen_Tx = 0;
            EachTransferLen_Rx = 0;
            ReqTotalLenB = 0;
            DmaCnt_Tx = 0;
            DmaCnt_Rx = 0;
            Remain_Tx = 0;
            Remain_Rx = 0;
            TransferTimeOut_Tx = 0;
            TransferTimeOut_Rx = 0;
            CurVa_Tx = (void*)0;
            CurTransferLen_Tx = 0;
            CurVa_Rx = (void*)0;
            CurIntFlg = 0;
            CurDataSrc = 0;
            PreDataSrc = 0;
            hEvtDmaDone_Tx = (void*)0;
            hEvtDmaDone_Rx = (void*)0;
            hEvtDataHandleDone_Tx = (void*)0;
            hEvtDataHandleDone_Rx = (void*)0;
            KeepRun = false;
            bThreadWriteBuf = 0;
            MaxEachDmaLenB = 0x400000;
            EnableReplay = 0;
            CalMode = 0;
            ReplayDDS = 0;
        }
        DRV_INF_BLOCK ()
        {
            Reset ();
        }
#endif
    }Dib,*PDib;
    typedef struct _tagCardInfo
    {
        Dib dib;
        QTPRODUCTINFO ProdInfo;
        QTVFIFO vfifo;
        QTCLOCK ClockInfo;
        QTDAQPARAMS DAQParams;
        QTDIO DIO;
        QTCALDATA CalData;
        //Carfnc eCardFunction;          // function of the card
        //unsigned int lSerialNumber;          // serial number of card
        //__int64 llInstMemBytes;         // installed on-board memory in bytes
        //unsigned int lMaxChannels;           // number of channels (analog or digital)
        //unsigned int lBytesPerSample;        // number of bytes for each sample (analog data)
        //unsigned int lLibVersion;            // version of the library
        //unsigned int lKernelVersion;         // version of the kernel driver
        //unsigned int lCtrlFwVersion;         // version of main control firmware
        //unsigned int lBaseHwVersion;         // version of base hardware
        //unsigned int lModHwVersion;          // version of module hardware
        //unsigned int lModFwVersion;          // version of module firmware
        // current settings
        //int bSetError;              // one of the functions generated an error
        //char szError[ERRORTEXTLEN];  // space for the error text  
        //unsigned int qwSetChEnableMap;       // current channel enable map
        //__int64 llSetMemsize;           // programmed memory size
        unsigned int lSetChannels;           // number of used channels for this run
        //unsigned int lSetSamplerate;         // current selected sampling rate (1 for external)
        //unsigned int lOversampling;          // currently active oversampling factor
        unsigned int SegmentCnt;
        unsigned int SegmentSize;              //TODO:change to unsigned __int64 type
        unsigned int PreSamples;
        unsigned int gABAMode;
        //ModeFlg
        // analog input cards
        struct ST_AI
        {
            unsigned int lResolution;           // resolution of analog channels
            unsigned int lMaxADCValue;          // maximum range, normally 2^(Resolution-1) but can be limited
            unsigned int lPathCount;            // number of input paths
            unsigned int lRangeCount;           // number of analog input ranges
            unsigned int NumGain;               //���浵λ���� AC:1; DC:>=1
            double lCurrRangeVpp[256];          // Current Pk-Pk range value per channel
            double lCurrOffset[256];            // Current offset per channels
            int bInputTermAvailable;            // input termination available
            int bDiffModeAvailable;             // differential mode available
            int bACCouplingAvailable;           // AC/DC coupling softwar selectable
            int bBWLimitAvailable;              // bandwidth limit available
            int bOffsPercentMode;               // offset programmed in percent of range
            unsigned int unChOpt;               // ADC channel mode for QT1125 only
            unsigned int InputChannelMask;      // Input Channel selection bit mask
            unsigned int DataFormat;            // 0: offset binary code; 1: two's complement code
            double OffsetVoltVSCode[MAX_DAC_NUM];   //1.0:Pos-proportion; -1.0:Neg-proportion
            unsigned int bForceIOdelay;         //Flag to indicate whether force io delay or not

#ifdef __cplusplus
            void Reset (void)
            {
                lResolution = 0;
                lMaxADCValue = 0;
                lPathCount = 0;
                lRangeCount = 0;
                NumGain = 1;
                memset(lCurrRangeVpp,0,256);
                memset(lCurrOffset,0,256);
                bInputTermAvailable = false;
                bDiffModeAvailable = false;
                bACCouplingAvailable = false;
                bBWLimitAvailable = false;
                bOffsPercentMode = false;
                unChOpt = 0;                     //Added by BaiLi @20160331: to carry channel mode info through QTApi
                InputChannelMask = 0;
                DataFormat = 0;
                memset(OffsetVoltVSCode,1,MAX_DAC_NUM);
                bForceIOdelay = 0;
            }
            ST_AI ()
            {
                Reset ();
            }
#endif
        } stAI;
        // analog output cards
        struct ST_AO
        {
            unsigned int lResolution;           // resolution of analog channels
            unsigned int lMaxDACValue;          // maximum range, normally 2^(Resolution-1) but can be limited
            int bGainProgrammable;              // programmable gain available 
            int bOffsetProgrammable;            // programmable offset available
            int bFilterAvailable;               // programmable filters available
            int bStopLevelProgrammable;         // programmable stop level available
            int bDiffModeAvailable;             // differential mode available
#ifdef __cplusplus
            void Reset (void)
            {
                lResolution = 0;
                lMaxDACValue = 0;
                bGainProgrammable = false;
                bOffsetProgrammable = false;
                bFilterAvailable = false;
                bStopLevelProgrammable = false;
                bDiffModeAvailable = false;
            }
            ST_AO ()
            {
                Reset ();
            }
#endif
        } stAO;
        QTINTERMEDIUM IntMedium;
        QTSTORAGE Storage;
        QTTHREAD WaitDataReady;
        QTTHREAD WriteBuf;
        LDREPLAY Replay;

#ifdef __cplusplus
        void Reset (void)
        {
            dib;
            ProdInfo;
            vfifo;
            ClockInfo;
            DAQParams;
            DIO;
            CalData;
            //eCardFunction = AnalogIn;
            //lSerialNumber = 0;
            //llInstMemBytes = (__int64)0;
            //lMaxChannels = 0;
            //lBytesPerSample = 0;
            //lLibVersion = 0;
            //lKernelVersion = 0;
            //lCtrlFwVersion = 0;
            //lBaseHwVersion = 0;
            //lModHwVersion = 0;
            //lModFwVersion = 0;
            //bSetError = false;
            //szError[0] = 0;
            //qwSetChEnableMap = 0;
            //llSetMemsize = (__int64)0;
            lSetChannels = 0;
            //lSetSamplerate = 0;
            //lOversampling = 0;
            SegmentCnt = 0;
            SegmentSize = 0;
            PreSamples = 0;
            gABAMode = 0;
            stAI;
            stAO;
            IntMedium;
        }
        _tagCardInfo ()
        {
            Reset ();
        }
#endif
    }ST_CARDINFO;


    //��ʼ���忨���Զ���λ�忨
    //���������
    //pstCardInfo���忨��Ϣ��
    //unCardIdx���忨��ţ���0��ʼ;
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
    //TODO:��ȡ�忨�����Ϣ(ID���汾�ţ����к�)��pstCardInfo
#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTInitCardByIdx (ST_CARDINFO *pstCardInfo,unsigned int unCardIdx);
    //��λ�忨
    //���������
    //pstCardInfo���忨��Ϣ��
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTResetCard (ST_CARDINFO *pstCardInfo);
    //��������
    //���������
    //pstCardInfo���忨��Ϣ��
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTFastSet (ST_CARDINFO *pstCardInfo,unsigned int Frequency);
    //�رհ忨
    //���������
    //pstCardInfo���忨��Ϣ��
    //����ֵ��
    //��
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTCloseCard (ST_CARDINFO *pstCardInfo);
    //д�Ĵ���
    //���������
    //pstCardInfo���忨��Ϣ��
    //unRegOffset���Ĵ�����ַ
    //unRegValue��ֵ
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTWrtReg (ST_CARDINFO *pstCardInfo,unsigned int unRegOffset,unsigned int unRegValue);
    //���Ĵ���
    //���������
    //pstCardInfo���忨��Ϣ��
    //unRegOffset���Ĵ�����ַ
    //punRegValue��ֵ
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTReadReg (ST_CARDINFO *pstCardInfo,unsigned int unRegOffset,unsigned int *punRegValue);
    //ͨ��Mailbox���ò���
    //���������
    //pstCardInfo���忨��Ϣ��
    //unCmd������;
    //unParam1��Ҫ���ò���1;
    //unParam2��Ҫ���ò���2;
    //unParam3��Ҫ���ò���3;
    //unTimeOut:��ʱ��Ĭ��Ϊ0xffffffff����λΪ���롣
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
    //TODO:ÿ��SET�����߼�����Ҫд�ĸ����ؼĴ���������Ϊ�߼���ִ�н��
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetParam (ST_CARDINFO *pstCardInfo,unsigned int unCmd,unsigned int unParam1,unsigned int unParam2,unsigned int unParam3,unsigned int unTimeOut);
    //ͨ��Mailbox��ȡ����ֵ
    //���������
    //pstCardInfo���忨��Ϣ��
    //unCmd������;
    //punParam1��Ҫ��ȡ����1;
    //punParam2��Ҫ��ȡ����2;
    //punParam3��Ҫ��ȡ����3;
    //unTimeOut:��ʱ��Ĭ��Ϊ0xffffffff����λΪ����
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
    //TODO:��Ҫ����ҪReadReady����ж�
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetParam (ST_CARDINFO *pstCardInfo,unsigned int *punCmd,unsigned int *punParam1,unsigned int *punParam2,unsigned int *punParam3,unsigned int unTimeOut);
  //����ADC��������ģʽ
    //���������
    //pstCardInfo���忨��Ϣ��
    //unChOpt������QT1125��unChOptΪͨ��ģʽʹ��:QTFM_1125_CHANNEL_MODE�����������忨���ò���ΪƬѡ��Ŀǰ�Ѷ����ȡֵΪ8,9,0xa,0xb
    //unModeFlg���������а忨���û�ģʽ�¹̶�Ϊ0
    //ClockDivider:���QT1138,ʱ��Ƶ�ʵ���QTFM_COMMON_CLOCK_FREQUENCY_MINʱ��������ClockDividerΪ2����4��Ƶ��ʹADC�ܹ������ڸ��͵Ĳ�������
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupADCMode (ST_CARDINFO *pstCardInfo,unsigned int unChOpt,unsigned int unModeFlg,unsigned int ClockDivider/*=0*/);
    //���ڲ�֧���Զ�IOdelayУ׼�İ忨��QT1128��QT1130)�������ֶ�У׼�������IO delay
    //���������
    //pstCardInfo���忨��Ϣ��
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��RES_ERROR_BAD_PARAMETER�ж���
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTForceIOdelay(ST_CARDINFO *pstCardInfo);
    //���ù���ģʽ
    //���������
    //pstCardInfo���忨��Ϣ��
    //unChOpt��ͨ��ʹ��:QTFM_1125_CHANNEL_MODE
    //unSegmentSize������ʹ��ͨ���Ķγ��ͣ���QTFM_1125_SEGMENT_GRANULARITYΪ��λ��Ĭ��QTFM_1125_SEGMENT_GRANULARITY
    //unPreSamples������ʹ��ͨ����Ԥ���������ͣ���λ��QTFM_1125_PRE_TRIGGER_GRANULARITY��Ĭ��Ϊ0
    //unSegmentCnt���θ�����1����ʾ���δ���������Ϊ��δ�����0����ʾ4G�δ�����Ĭ��Ϊ1
    //unModeFlg��QTFM_COMMON_BOARD_WORK_MODE��Ĭ��ΪQTFM_COMMON_BOARD_WORK_MODE_STD_SIGNLE
    //unCompressorMode:����ѹ��\��ѹ��ģ�鹤��ģʽ��bit[0]:ѹ��ģ�鹤��ģʽ;bit[1]:��ѹ��ģ�鹤��ģʽ.bit[n]Ϊ1��ʾʹ��ѹ�����߽�ѹ��,Ϊ0���ֹ
    //unPostSamples:�󴥷����ȣ���������������ɼ��ĳ��ȣ�samples���������ڵ�ƽ����
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupWorkMode (ST_CARDINFO *pstCardInfo,unsigned int unSegmentSize,unsigned int unPreSamples,unsigned int unSegmentCnt,unsigned int unModeFlg,unsigned int unCompressorMode,unsigned int unPostSamples);
    //������ʱ��
    //���������
    //pstCardInfo���忨��Ϣ��
    //unSamplerate�������Ĳ����ʣ�QTFM_COMMON_CLOCK_FREQUENCY
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupClockInternal (ST_CARDINFO *pstCardInfo,unsigned int unSamplerate);
  //������ʱ��
    //���������
    //pstCardInfo���忨��Ϣ��
    //Fref:�ο�ʱ��Ƶ��,Hz
    //RefDiv:�ο�ʱ��Ƶ��ϵ��,0~(1^14-1)
    //Frequency�������Ĳ����ʣ��ֱ���ΪQTFM_COMMON_CLOCK_FREQUENCY_GRANULARITY
  //VCOMode: �ڲ�VCO or �ⲿVCO��QTFM_COMMON_CLOCK_VCO_MODE_0~1
  //RefClkMode:QTFM_COMMON_CLOCK_REF_MODE_0~2
  //ADCClkMode:QTFM_COMMON_ADC_CLOCK_MODE_0~1
    //RstADC:��λADCָʾ����1��ʾ����ִ�й����и�λADCоƬ����0�򲻸�λADCоƬ��ֻ�޸�ʱ��Ƶ��
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupClock (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int Frequency,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int RstADC/*=1*/);
    //����������
    //���������
    //pstCardInfo���忨��Ϣ��
    //unTrigtype��QTFM_COMMON_TRIGGER_TYPE
    //unEnable���Ƿ�ʹ��
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupTrigSoftware (ST_CARDINFO *pstCardInfo,unsigned int unTrigType,unsigned int unEnable);
    //�����ⴥ����ƽ���˰�û��ʵ�֡�
    //���������
    //pstCardInfo���忨��Ϣ��
    //unExtIdx��QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_1 to QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_13
    //unTrigType��QTFM_COMMON_TRIGGER_TYPE
    //unEnable���Ƿ�ʹ��
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupTrigExternal (ST_CARDINFO *pstCardInfo,unsigned int unExtIdx,unsigned int unTrigType,unsigned int unEnable);
  //���ô���ͨ����
  //���������
  //pstCardInfo���忨��Ϣ��
  //unChannel��ͨ����ţ�CHANNEL_0~7������QT1140V2,ѡ�������trigͨ����Ϊģ�ⴥ��ʱ��unChannel���������50ohmѡ�����(TRIG_CHANNEL_HIZ or TRIG_CHANNEL_50OHM)
  //unTrigtype��QTFM_COMMON_TRIGGER_TYPE
  //unRiseEdgeLevel�������ش�����ƽ����ֵ.
  //unFallEdgeLevel���½��ش�����ƽ����ֵ
  //����QT1140V2��Ʒ��trigͨ���ڸ�������ʱ�������̡�10V��50ŷķ����ʱ�����̡�2.5V��unRiseEdgeLevel��unFallEdgeLevel�ķ�Χ��0x8000��0x6666��Ӧ�����̡�
  //unEnable���Ƿ�ʹ�� 1��ʹ�ܣ�0����ֹ
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupTrigChannel (ST_CARDINFO *pstCardInfo,unsigned int unChannel,unsigned int unTrigType,/*unsigned */int unRiseEdgeLevel,/*unsigned */int unFallEdgeLevel,unsigned int unEnable);
    //���ô�������
    //��������� 
    //pstCardInfo���忨��Ϣ��
    //unTrigType��QTFM_COMMON_TRIGGER_TYPE,  external trigger mode��Rising edge,Falling Edge,double Edge,high level,Low level, enable bit
    //unPulsewidth��QTFM_1125_PULSE_WIDTH,programmable pulse width for channel,unit:number of sample clock cycles
    //unPulsePeriod��internal pulse period(offset=0x8), unit:number of sample clock cycles
    //unEnable���Ƿ�ʹ��
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupTrigPulse (ST_CARDINFO *pstCardInfo,unsigned int unTrigType,unsigned int unPulsewidth,unsigned int unPulsePeriod,unsigned int unEnable);
    //���ô���Դ���ʹ����ӳ١�
    //���������
    //pstCardInfo���忨��Ϣ��
    //unMask�����,QTFM_COMMON_TRIGGER_SOURCE_MASK��Ĭ��ΪQTFM_COMMON_TRIGGER_SOURCE_MASK_OR��
    //unDelay_LowPart�������ӳٵ�32λ��Ĭ��Ϊ0����λ��number of AD clocks.
    //unDelay_HighPart�������ӳٸ�32λ��Ĭ��Ϊ0����λ��number of AD clocks.
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupTrigSourcesOrAndDelay (ST_CARDINFO *pstCardInfo,unsigned int unMask,unsigned int unDelay_LowPart,unsigned int unDelay_HighPart); 
    //��������ͨ����
    //���������
    //pstCardInfo���忨��Ϣ��
    //unChannel��Ҫ���õ�ͨ����ȡֵ��Χ��CHANNEL_0~CHANNEL_7���ֱ��Ӧͨ��0~7
    //unInputRange��input range in mV  +/-1V range
    //bTerm = true��set input termination (50 ohm) if available
    //unInputOffset = 0��programmable input offset as listed in the manual
    //bDiffInput = false��set differential input if available
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupInputChannel (ST_CARDINFO *pstCardInfo,unsigned int unChannel,unsigned int unInputRange,unsigned int unTerm,unsigned int unInputOffset,unsigned int unDiffInput,unsigned int unChEn);
    //����ʱ���ģʽ�;������
    //���������
    //pstCardInfo���忨��Ϣ��
    //�������
    //TimeStampEn:ʱ���ʹ��:
    //       0x0: Disable timestamp mode. Timestamp counter keep no change and values is param2 and param3 are ignored.
    //       0x3: Enable GPS mode, internal clock is used to counting.Accumulative error could impact on precision of timestamp along the time.
    //       0x13: Enable GPS mode,   external 1pps clock is required to counting. This is a more accurate way vs. 0x3 mode.
    //       others: illegal value
    //TimeStampSegmentLen: if GPS mode is enabled, it is length of a segment in samples. Timestamp information is inserted at the head of each segment;
    //                     if GPS mode is not enabled, it is LSB of current time;
    //GPSSecond:if GPS mode is enabled, it is GPS second from 1900';
    //          if GPS mode is not enabled, it is MSB of current time;
    //Freq:ÿ��ADC�Ĳ����ʣ���λHz
    //TimeStampSel��ʱ�������ѡ��
    //              0��ѡ��GPSʱ�������
    //              1��ѡ���û�ʱ�������
    //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupTimestamp (ST_CARDINFO *pstCardInfo, unsigned int TimeStampEn,unsigned int TimeStampSegmentLen,unsigned int GPSSecond,unsigned int Freq,unsigned int TimeStampSel);
    //��ʼ���ݴ��䡣
    //���������
    //pstCardInfo���忨��Ϣ��
    //unDirection���䷽��QTFM_COMMON_TRANSMIT_DIRECTION��Ĭ��QTFM_COMMON_TRANSMIT_DIRECTION_TX
    //bDmaEn  = true��ʹ�ܻ�ֹͣ��[����ʱ����DMA����ADC������ʱ����Disable ADC����ֹͣDMA��]
    //unTimeOut: ��ʱ���ã�Ĭ��Ϊ0xffffffff;
    //TimedModeEn: �̶�����Ϊfalse;
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStart (ST_CARDINFO *pstCardInfo,unsigned int unDirection,int bDmaEn,unsigned int unTimeOut,int TimedModeEn);

    //֪ͨǶ��ʽ��ʼ������λ��������
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStartReplay(ST_CARDINFO *pstCardInfo);
    //�ȴ�һ��Dma����
    //���������
    //pstCardInfo���忨��Ϣ��
    //unDirection  = 0�����䷽��QTFM_COMMON_TRANSMIT_DIRECTION��Ĭ��QTFM_COMMON_TRANSMIT_DIRECTION_TX
    //unTimeOut:��ʱʱ�䣬��λΪ���룬Ĭ��0xFFFFFFFF
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTWaitForDmaDoneEvt (ST_CARDINFO *pstCardInfo,unsigned int unDirection/* = 0 */,unsigned int unTimeOut/* = 0xFFFFFFFF*/);
    //����������ɺ�֪ͨ
    //���������
    //pstCardInfo���忨��Ϣ��
    //unDirection  = 0�����䷽��QTFM_COMMON_TRANSMIT_DIRECTION��Ĭ��QTFM_COMMON_TRANSMIT_DIRECTION_TX
    //����ֵ��
    //�ɹ�����RES_SUCCESS�����򷵻�ֵ��DRV_RESULT_CODE�ж���
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetDataHandleDoneEvt (ST_CARDINFO *pstCardInfo,unsigned int unDirection);
    //�õ��ɼ�������
    //���������
    //pstCardInfo���忨��Ϣ��
    //pBufDest��Ŀ��Buffer
    //unLen�����ȵ�λΪ�ֽ�
    //unTimeOut����ʱ����λΪ����
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetData (ST_CARDINFO *pstCardInfo,unsigned char *pBufDest,unsigned int unLen,unsigned int unTimeOut/*=0xFFFFFFFF*/);
    //���Ͳ�������
    //���������
    //pstCardInfo���忨��Ϣ��
    //pBufDest��ԭʼBuffer
    //unLen�����ȵ�λΪ�ֽ�
    //unTimeOut����ʱ����λΪ����
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSendData (ST_CARDINFO *pstCardInfo, void *pBufSrc, unsigned int unLen,unsigned int *bytes_sent, unsigned int unTimeOut/*=0xFFFFFFFF*/);

    //��ѯ�忨�Ĵ�����쳣״̬
    //���������
    //pstCardInfo���忨��Ϣ��
    //����ֵ��
    //      bit[0]:ADC�ӿ�ģ��reset sequence��ʱ��־��Ϊ1��ʾADC����ʱ���쳣��0������
    //      bit[1]:Ϊ1��ʾfifoģʽ��buffer�����˵�����ݲɼ����ʳ�����PCIe�������ʣ�0����
    //      bit[2]:Ϊ1��ʾADC�ӿ��߼���DMA fifo������轵�Ͳ����ʣ�0����
    //      bit[3]:Ϊ1��ʾfifoģʽ��time-stamp buffer�����0����
    //      bit[4]:Ϊ1��ʾ������ɣ�0��ʾ���ݴ���δ��ʼ�������ڴ�������У�
    //      bit[5]:ADC����ʱ���쳣��־,1:ADC����ʱ��Ƶ���쳣������ʱ������; 0:ʱ��״̬����;
    //      bit[6]:����pcie Rx DMA buffer ready״̬��1:buffer�Ѿ�׼���ý�������; 0:bufferδ׼���ã���λ�������·��µ�����;
    //      bit[7]:AD�ӿ��߼������ڼ�����ģʽʱ������У����: 1:����У���; 0:����У����ȷ;
  //      bit[8]:TX/RX DMA engine �����쳣��־λ��1:TX����RX DMA engine�����쳣��0�����߹���������
    //����ֵ�����bit[8:7],bit[5],bit[3:0]�κ�һλΪ1��˵�������쳣,����RES_ERROR_BOARD_EXCEPTION�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetBrdStatus (ST_CARDINFO *pstCardInfo,unsigned int Frequency, unsigned int *status);
    //��ѯPCIe AXI DMA buffer���ȣ���λByte��
    //���������
    //pstCardInfo���忨��Ϣ��
    //RxBufLen:buffer����
    //����ֵ���������Ϊ0���򷵻�RES_ERROR_BOARD_EXCEPTION�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetRxBufLen (ST_CARDINFO *pstCardInfo,unsigned int *RxBufLen);
    //IODelayУ׼,ÿ���ϵ繤���󣬶�Ҫ���д�У׼����������ڵ�ǰĿ¼��IODelayCal.dat�ļ���
    //���������
    //pstCardInfo���忨��Ϣ��
    //unCal_Frq:У׼ʱ��ʱ��Ƶ��
    //unChOpt:_tag_QTfm_1125_Channel_Mode->*
    //IOWindowMode:ȡֵ0��1�����ڿ�������IO bus delay��ʱ��IO delay��ɵ����ڴ�С
    //SampleRateGrade:��Sample Rate����QTFM_COMMON_CLOCK_FREQUENCY_MINʱ��ȡֵΪ1������Ϊ0
    //ucArrayClock:ʱ��У׼ֵ
    //usArrayOffset:OfffsetУ׼ֵ
    //punChIoDelayRes��ͨ��У׼��־
    //punProgress������
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTIODelayCal (ST_CARDINFO *pstCardInfo,unsigned int unCalFrq,unsigned int unChOpt,unsigned int IOWindowMode,unsigned int SampleRateGrade,unsigned char ucArrayClock[4],unsigned short usArrayOffset[4],unsigned int *punChIoDelayRes,unsigned int *punProgress,unsigned int TimeOut);
    //ADC interleaving calibration process����������ڵ�ǰĿ¼��ADCCal.dat�ļ���
    //���������
    //pstCardInfo���忨��Ϣ��
    //Fref:ʱ��оƬ�Ĳο�ʱ��Ƶ��(10~350MHz)����λHz
    //RefDiv:�ο�ʱ�ӷ�Ƶϵ��,1~(1<<14-1) should always be 1
    //VCOMode:ѡ������VCO��������VCO��ȡֵQTFM_COMMON_CLOCK_VCO_MODE_0 or QTFM_COMMON_CLOCK_VCO_MODE_1
    //RefClkMode:ѡ��ο�ʱ����Դ��ȡֵQTFM_COMMON_CLOCK_REF_MODE_0~2
    //ADCClkMode:ѡ��ADC����ʱ����Դ��ȡֵQTFM_COMMON_ADC_CLOCK_MODE_0~1
    //unCalFrq��ADCоƬ����ʱ��Ƶ��
    //unChOpt������QT1125�����壬����ADCоƬͨ��ģʽ_tag_QTfm_1125_Channel_Mode->*
    //SampleRateGrade:��Sample Rate����QTFM_COMMON_CLOCK_FREQUENCY_MINʱ��ȡֵΪ1������Ϊ0
#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTADCCal (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int unCalFrq,unsigned int unChOpt,unsigned int SampleRateGrade);
#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTXcal (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int unCalFrq,unsigned int unChOpt,unsigned int SampleRateGrade);
    //�����ź�ƫ��
    //���������
    //pstCardInfo���忨��Ϣ��
    //cs:For qt1125, it is 16,17,18,19;
    //   For QT1135,QT1130,QT1138, valid value should be 16,17,18,19;
    //   For QT1128, valid value is 16,17
    //ReqOffset:required offset value in uV unit.
    //          For QT1125, valid range is {-4.096V,4.096V}  with 62.5uV step;
    //����ֵ��ִ�д��󷵻�RES_ERROR_BOARD_EXCEPTION�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTTuneOffset (ST_CARDINFO *pstCardInfo, unsigned int cs,double ReqOffset);
    //�����ź�����
    //���������
    //pstCardInfo���忨��Ϣ��
    //�������
    //cs:For qt1125, it is 24,25,26,27;
    //   For QT1135,QT1130,valid value should be 24,25,26,27;
    //   For QT1138, valid value should be 16,17,18,19
    //   For QT1128, valid value is 24,25
    //ReqGain: required gain value in dB unit:
    //         For QT1125, valid range is [6,26]dB with 0.25dB step;
    //         For QT1138DC it is a enumeric number according to variable input full-scale:
    //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTTuneGain (ST_CARDINFO *pstCardInfo, unsigned int cs,double ReqGain);

    //�����ź�����
    //���������
    //pstCardInfo���忨��Ϣ��
    //�������
    //cs:CHANNEL_0~CHANNEL_7
    //ReqGain: required gain value in dB unit:
    //         For QT1125, undefined;
    //         For QT1138AC/DC/VG, ReqGain is among [-2.0~6]dB with 0.5dB step;
    //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTTuneDigitalGain (ST_CARDINFO *pstCardInfo, unsigned int cs,double ReqGain);

    //����ĳһPGA����ʱ��0��ƽ��Ӧ��ƫ��ֵ
    //���������
    //pstCardInfo���忨��Ϣ��
    //�������
    //dac_cs:For qt1125, it is 16,17,18,19;
    //   For QT1135,QT1130,QT1138, valid value should be 16,17,18,19;
    //   For QT1128, valid value is 16,17
    //pga_cs:For qt1125, it is 24,25,26,27;
    //   For QT1135,QT1130,QT1138, valid value should be 24,25,26,27;
    //   For QT1128, valid value is 24,25
    //CurrGain:��ǰ����ֵ��For QT1125, valid range is [6,26]dB with 0.25dB step;
    //InitOffset:��ʼoffset value
    //ResultOffset:���򷵻ص�ƫ��ֵ���
    //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetZeroLevelDCOffsetForGain(ST_CARDINFO *pstCardInfo,unsigned int dac_cs,unsigned pga_cs,double CurrGain,double InitOffset,double *ResultOffset);
    //����ĳһPGA����ʱ��0��ƽ��Ӧ��ƫ��ֵ
    //���������
    //pstCardInfo���忨��Ϣ��
    //�������
    //dac_cs:For qt1125, it is 16,17,18,19;
    //   For QT1135,QT1130,QT1138, valid value should be 16,17,18,19;
    //   For QT1128, valid value is 16,17
    //pga_cs:For qt1125, it is 24,25,26,27;
    //   For QT1135,QT1130,QT1138, valid value should be 24,25,26,27;
    //   For QT1128, valid value is 24,25
    //CurrGain:��ǰ����ֵ��For QT1125, valid range is [6,26]dB with 0.25dB step;
    //InitOffset:���õĳ�ʼoffsetֵ������Ӵ˳�ֵ��ʼ�Զ�����offset��ֱ���������ݵľ�ֵ��ExpectMean���
    //ExpectMean:���������Զ�����DAC offset��ADC��������ƽ��ֵ
    //ResultOffset:���򷵻ص�ƫ��ֵ���
    //ResultMean:����ֵ��������ƽ��ֵ��ExpectMean��ӽ�ʱ��ƽ��ֵ
    //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetDCOffsetForGain(ST_CARDINFO *pstCardInfo,unsigned int dac_cs,unsigned pga_cs,double CurrGain,double InitOffset,double ExpectMean,double *ResultOffset,double *ResultMean);
    //����PGA���е�λ�£�����ÿ�����뷶Χ��{ƫ��У׼ֵ������ֵ}������Ϊ�ļ�
    //���������
    //pstCardInfo���忨��Ϣ��
    //�������
    //OffsetScale:DCУ׼֮��ƫ�õ���������Ydac=OffsetScale*x+b
    //FileName:�ļ���ָ�룬���ڴ洢ֱ��ƫ��У׼���
    //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTDCOffsetPGACal(ST_CARDINFO *pstCardInfo,double *ArrayOffsetScale,char *FileName);
    //DC��ϵ���ģ��ǰ��У׼����
    //���������
    //pstCardInfo���忨��Ϣ��
    //CalDACEn:ʹ��DACУ׼,0:disable,�����Զ���ȡ�ϴε�У׼���;1:enable
    //CalInputRangeEn:ʹ����������У׼,0:disable,�����Զ���ȡ�ϴε�У׼���;1:enable
    //����ֵ��
    //FileName:�ļ���ָ�룬���ڴ洢ֱ��ƫ��У׼���
    //ArrayZeroLevelDCOffset:��ά����[DAC_NUM][GAIN_STEP_NUM].
    //                       ����QT1125DC��DAC_NUM=4��GAIN_STEP_NUM=80;
    //                       ����QT1138DC, DAC_NUM=4, GAIN_STEP_NUM=4
    //ArrayPGAGain:��ά����[DAC_NUM][GAIN_STEP_NUM][INPUT_RANGE_NUM].
    //                       ����QT1125DC��DAC_NUM=4��GAIN_STEP_NUM=80,INPUT_RANGE_NUM=4
    //                       ����QT1138DC, DAC_NUM=4, GAIN_STEP_NUM=4,INPUT_RANGE_NUM=4
    //ArrayDACCoeff:һά����[DAC_NUM]�����ڴ��ֱ��ƫ��У׼ϵ��
    //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTDCCal (ST_CARDINFO *pstCardInfo,unsigned CalDACEn,unsigned int CalInputRangeEn,char *FileName,double *ArrayZeroLevelDCOffset,double *ArrayPGAGain,double *ArrayDACCoeff);
    //�ڲ��λط�֮ǰ�������ε����ò����·����忨
    //���������
    //pstCardInfo���忨��Ϣ��
    //�������
    //Index:��ǰ���α��
    //WaveformLen:ÿ�����εĳ��ȣ���λ��Byte
    //LoopCnt:ÿ�����ε�ѭ������
    //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTCreateWaveform (ST_CARDINFO *pstCardInfo, unsigned int Index,unsigned int WaveformLen,unsigned int LoopCnt);

#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTWriteRegister (ST_CARDINFO *pstCardInfo, unsigned int BaseAddr,unsigned int Offset,unsigned int Value);
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTReadRegister (ST_CARDINFO *pstCardInfo, unsigned int *BaseAddr,unsigned int *Offset,unsigned int *Value);

  //���ٴ洢��ʼ��
  //���������
  //pstCardInfo���忨��Ϣ��
  //FileName���ļ���������128�ֽ�
  //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStoreInit (ST_CARDINFO *pstCardInfo);

  //�洢��ص��û��������ýӿ�
  //���������
  //pstCardInfo���忨��Ϣ��
  //�������
  //NameRule:        0(by default): {Data}_{Time}_{Index}; 1:User specified file name {User_spec_name}_{Index}
  //FileLocation:    Specify file location in windows style to store files. Files are stored in current working directory by default
  //UsrFileName:     User specified file name
  //SplitFileSizeMB: Split at file size in MB. 0 means don't split file
  //MaxNumFiles:     Max number of files to stop storing files. 0 means unlimited. MaxNumFiles has priority over MaxFileSizeMB.
  //MaxFileSizeMB:   Max file size in 1024*1024 bytes to stop writing file. 0 means unlimited.
  //PPDATABUFLEN:    Ping-pang buffer size in byte
  //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStoreParamSet (ST_CARDINFO *pstCardInfo,unsigned int NameRule,char *FileLocation,char *UsrFileName,unsigned int SplitFileSizeMB,unsigned int MaxNumFiles,unsigned int MaxFileSizeMB,unsigned int PPDATABUFLEN);
  
  //��ʼ�ɼ��洢����
  //���������
  //pstCardInfo���忨��Ϣ��
  //CNT������ģʽ������ģʽ�洢����ʱCnt����0���ⴥ��ģʽ�洢����ʱCnt����1
  //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStoreData (ST_CARDINFO *pstCardInfo, char *FileName, int TrigMode);
  //ֹͣ�ɼ��洢����
  //���������
  //pstCardInfo���忨��Ϣ��
  //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStoreStop (ST_CARDINFO *pstCardInfo);
  //��ʼ�ɼ�����,��FFT����ʱ��ֹ���ݶ�����ר��һ���߳�������
  //���������
  //pstCardInfo���忨��Ϣ��
  //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStartGetFFTData (ST_CARDINFO *pstCardInfo);
  //ֹͣ�ɼ�����
  //���������
  //pstCardInfo���忨��Ϣ��
  //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStopGetFFTData (ST_CARDINFO *pstCardInfo);
    //��ȡ����������С
    //�������:
  //pstCardInfo���忨��Ϣ��
    //�������:
    //ToatalSpace:������������С, FreeSpace:ʣ�����������С,��λ��С��MB
  //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetDiskSpace (ST_CARDINFO *pstCardInfo, double *ToatalSpace, double *FreeSpace);
    //��ȡ��ʾFFT����
    //�������:
    //pstCardInfo���忨��Ϣ��
    //pDataBuf:����ָ��, DataLen:��ȡ���ݳ���,ĿǰĬ�ϴ�С��4M
    //unTimeout:��ʱʱ��
    //�������:
    //pDataBuf:��ȡ��������ָ��
  //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetDataToFFT (ST_CARDINFO *pstCardInfo, unsigned char *pDataBuf, unsigned int DataLen, unsigned int unTimeOut);

  //�ⴥ��ģʽ�²�ѯ�忨��ȡ����״̬����ȡ���ݽ����󼴿�ʼ��һ��
  //���������
    //pstCardInfo���忨��Ϣ��
  //����ֵ��ִ�д��󷵻�RES_STORE_DATA_BUZY�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTPollGetDataStatus (ST_CARDINFO *pstCardInfo);
  //�ȴ�д�ļ����
  //���������
    //pstCardInfo���忨��Ϣ��
  //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTWaitForWriteFileDoneEvt (ST_CARDINFO *pstCardInfo);
  //�ͷŴ洢���ݹ�����������ڴ�
  //���������
    //pstCardInfo���忨��Ϣ��
  //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTFreeMemrory (ST_CARDINFO *pstCardInfo);
  //����У׼
  //���������
    //pstCardInfo���忨��Ϣ��
  //ReqGain���������ֵ-37~3������Ϊ1
  //�������������
  //*cs������ʱΪ�˲���ѡͨ��0��ʾ��ѡͨ��1��ʾѡͨ�����ʱ��ʾPA��״̬��0��ʾPAûѡͨ��1��ʾPAѡͨ
  //*CalValue�����ADC��У׼ֵ
  //����ֵ��ִ�д��󷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGainCal (ST_CARDINFO *pstCardInfo, unsigned int *cs,double ReqGain, double *CalValue);

  //����GPIO�ķ����Լ��ɼ�ʱ��ÿ��ģ��ͨ���Ĳ��������У�digital bit�ķ���
  //GPIODirection��������ơ��忨ǰ����ϵ�4��GPIO�ź�X1~4������ֱ���Ʒ�������:
  //               GPIO 3��4�ķ�����ͬ����GPIODirection[1]���Ʒ���0������;1�������
  //               GPIO 1��2�ķ�����ͬ����GPIODirection[0]���Ʒ���0������;1�������
  //GPIODispatch:����ÿ��ģ��ͨ���Ĳ��������У������digital bit���������ǲ������ݵ���Ӧbit��
  //             ȡֵ��ΧΪ0~N��
  //             0:������digital bit�����δ˹��ܣ�
  //             1:ÿ��ͨ������1 digital bit����ʱ������ͨ���Ĳ��������У�
  //               data_chn_0[0]=X1;
  //               data_chn_1[0]=X2;
  //               data_chn_2[0]=X3;
  //               data_chn_3[0]=X4;
  //               data_chn_4[0]=X1;
  //               data_chn_5[0]=X2;
  //               data_chn_6[0]=X3;
  //               data_chn_7[0]=X4;
  //             2:ÿ��ͨ������2 digital bits����ʱ������ͨ���Ĳ��������У�
  //               data_chn_0[1:0]={X2,X1};
  //               data_chn_1[1:0]={X4,X3};
  //               data_chn_2[1:0]={X2,X1};
  //               data_chn_3[1:0]={X4,X3};
  //               data_chn_4[1:0]={X2,X1};
  //               data_chn_5[1:0]={X4,X3};
  //               data_chn_6[1:0]={X2,X1};
  //               data_chn_7[1:0]={X4,X3};
  //             3:ÿ��ͨ������3 digital bits����ʱ������ͨ���Ĳ��������У�
  //               data_chn_0[2:0]={X3,X2,X1};
  //               data_chn_1[2:0]={X2,X1,X4};
  //               data_chn_2[2:0]={X1,X4,X3};
  //               data_chn_3[2:0]={X4,X3,X2};
  //               data_chn_4[2:0]={X3,X2,X1};
  //               data_chn_5[2:0]={X2,X1,X4};
  //               data_chn_6[2:0]={X1,X4,X3};
  //               data_chn_7[2:0]={X4,X3,X2};
  //             4:ÿ��ͨ������4 digital bits����ʱ������ͨ���Ĳ��������У�
  //               data_chn_{i}[3:0]={X4,X3,X2,X1}; iȡֵ��Χ0~7��
  //DigitalOnlyEn:ʹ�����ֹ�����ֲɼ���
  //              1��ʹ�ܴ����ֲɼ�����ʱ��λ����������ȫ��������IO�źŵ�ֵ��û���κ�ģ���źŵ�����ֵ��
  //              0����ֹ�����ֲɼ��������ʱGPIODispatchֵ����0��ģ����������а�����GPIODispatchλ�������źš�
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGPIOSet (ST_CARDINFO *pstCardInfo, unsigned int GPIODirection,unsigned int GPIODispatch,unsigned int DigitalOnlyEn/*=0*/);

  //�ṩ����ķ�ʽ����GPIO����·����ʱ��������߳�Ч����Ч��
  //GPIOSel:ѡ��ǰ����Ĳ�������ȡֵ��-1~3��
  //                              -1������GPIO�ܽţ�
  //                               0��GPIO 1��
  //                               1��GPIO 2��
  //                               2��GPIO 3��
  //                               3��GPIO 4��
  //Delay:��ʱֵ����λns,ȡֵ��Χ��0~5ns,����Ϊ5/32 ns
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGPIODelaySet (ST_CARDINFO *pstCardInfo, int GPIOSel,double Delay);

  //����ģ��ͨ����ֱ��ƫ��
  //ChnIdx:ͨ����ţ�ȡֵCHANNEL_0~CHANNEL_7����ChnIdx=-1ʱ���������е�ͨ��
  //OffsetVolt:ͨ��ƫ�õ�ѹ����λuV
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTChannelOffsetSet (ST_CARDINFO *pstCardInfo, int ChnIdx,double OffsetVolt);

  //����ģ��ͨ�������뷶Χ
  //ChnIdx:ͨ����ţ�ȡֵCHANNEL_0~CHANNEL_7����ChnIdx=-1ʱ���������е�ͨ��
//RangeVolt:ͨ�����뷶Χѡ��ȡֵ��Χ0~(N-1)������N�ǰ忨֧�ֵ����뷶Χ��λ�������ֱ��Ӧ1X,2X,5X,10X�Ŵ�
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTChannelRangeSet (ST_CARDINFO *pstCardInfo,int ChnIdx,double RangeVolt);

  //��ȡ�ɼ�������������ص���Ϣ���������ݻ���buffer����Ч�����ݳ��ȡ��Ƿ�������Լ��������������
  //���buffer�Ѿ����������һ�������ݱ���д�ˣ��ⲿ�������޷�ȡ�ء����ʵ��ӿ��ȡbuffer���ٶȣ�
  //���߽��Ͳ����ʡ�
  //pDataLenB:��ǰbuffer�е���Ч����������λbytes��
  //pBufOverflow: 1��buffer����� 0��buffer״̬������
  //pNoBytesOverwritten:����һ�ζ�ȡbuffer�����ڣ��ж���������������������ˣ�
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTBufStatusGet (ST_CARDINFO *pstCardInfo,__int64  *pDataLenB,int *pBufOverflow,unsigned int *pNoBytesOverwritten);

  //��buffer�л�ȡһ�����ȵ����ݣ����������û�ָ����buffer�С�
  //��ʼ��������֮ǰ�������ڲ��Զ��жϵ�ǰbuffer��״̬���������쳣��buffer������ա���Ч���ݲ��㣩�������˳��������쳣����
  //pDestBuf:ָ��Ŀ��buffer�ĵ�ַָ�룻
  //NoBytesLen: ��Ҫ�����Ĳ������ݳ��ȣ���λbytes��
//#ifdef __cplusplus
//  extern "C"
//#endif
//  QTAPI int __stdcall nQTBufDataGet (ST_CARDINFO *pstCardInfo,unsigned char *pDestBuf,unsigned int NoBytesLen);
#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTBufDataGet(ST_CARDINFO *pstCardInfo, void *pDestBuf, unsigned int NoBytesLen);

  //��������ֵ���㲢����ģ����
  //���������
  //pstCardInfo���忨��Ϣ��
  //DI������ֵ
  //AO: ת��֮���ģ����
  //����ֵ��double����
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI double __stdcall nQTFCVT (ST_CARDINFO *pstCardInfo, unsigned int DI,double AO);

  //����ABAģʽ����ز���
  //pstCardInfo���忨��Ϣ��
  //ABAMode:ABAģʽ���ƣ� 0������ģʽ; 1��ABAģʽ; 2����Ƶģʽ;
  //ABADivider: ���ڲɼ��������ݵķ�Ƶϵ��������=16��ȡֵ��Χ1~65536
  //NoChn:�û�ʵ��ʹ�ܵ�ģ��ͨ����������QTInputChannelSet����ʹ�õ�ͨ������δ����ȡ�
  //      ��QT1125XX��1ͨ��ģʽʱ���û�ֻ��ʹ��1��ģ��ͨ����NoChn=1��
  //                  2ͨ��ģʽʱ���û�����ʹ��2��ģ��ͨ�������QTInputChannelSet����ʹ���˶�Ӧ��ģ��ͨ����NoChn=2��
  //                  4ͨ��ģʽʱ���û�����ʹ��4��ģ��ͨ����QTInputChannelSet����ʹ����n��ͨ����NoChn=n;
  //      �������ͺŵ����а忨��QTInputChannelSetʹ����n��ͨ����NoChn=n;
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTABAModeSet (ST_CARDINFO *pstCardInfo, unsigned int ABAMode,unsigned int ABADivider,unsigned int NoChn);

  //��������IO�Ĵ���·���ϵ�latency,�ﵽ��ģ���ź�ͬ����Ŀ�ġ�
  //pstCardInfo���忨��Ϣ��
  //DigLatency:����������ʱ����λΪADʱ����
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTDigInLatency(ST_CARDINFO *pstCardInfo,unsigned int DigLatency);

  //�������ݸ�ʽ�� offset binary or two's complement code.
  //����QT1128��QT1125XX�忨��ֻ֧��offset binary code;
  //����QT1130��QT1135��QT1138�忨�����߶�֧�֣�Ĭ��offset binary
  //pstCardInfo���忨��Ϣ��
  //DataFormat:���ݸ�ʽ��0:offset binary; 1: Two's complement
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTDataFormatSet(ST_CARDINFO *pstCardInfo,unsigned int DataFormat);

  //ADC interleaving calibration process
  //���������
  //pstCardInfo:�忨��Ϣ
  //FpDelayTapVal:�ļ�����ִ��nQTADCCal�ɹ��󣬳����Զ�����һ����ΪDelayTapVal_card{card number}_{Frequency}.dat�ļ������汣��������У׼���ݡ�
  //         FpDelayTapValָ����ļ�����nQTCalDataSet�ض��ļ���������á�
  //FpADCCalData:����QT1125XX�忨��Ч�������忨��������NULL���ļ�����ִ��nQTADCCal�ɹ��󣬳����Զ�����һ����ΪADCCal_card{card number}_{Frequency}.dat���ļ������汣����QT1125 ADCоƬ�����ò�����
  //         FpADCCalDataָ����ļ�����nQTCalDataSet�ض��ļ���������á�
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTCalDataSet (ST_CARDINFO *pstCardInfo,char *FpDelayTapVal,char *FpADCCalData);

  //����GPIO�ķ���ÿ��gpio�����ֵ
  //GPIOSel:�ܽ�ѡ���źš�ȡֵ0~3ʱ���ֱ��Ӧ����ϵ�I/0 1~4;
  //                     ȡֵ-1ʱ��ͬʱ����4��GPIO�ܽţ�
  //GPIOOutput��������ơ�ȡֵ��Χ��
  //           0�����0��
  //           1�����1��
  //           2�����ͨ�������ź�;
  //           3������ڲ����崥���ź�;
  //           4����������ź�;
  //           5��������մ����ź�;
  //           6����������ֹʹ�ã�
  //           7��������ϴ�x1����Ĵ����ź����;
  //           8��������ϴ�x2����Ĵ����ź����;
  //           9��������ϴ�x3����Ĵ����ź����;
  //           10��������ϴ�x4����Ĵ����ź����;
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGPIOWrite (ST_CARDINFO *pstCardInfo, int GPIOSel/*,unsigned int GPIODirection*/,unsigned int GPIOOutput);

  //����GPIO�ķ���ÿ��gpio�����ֵ
  //GPIOSel:�ܽ�ѡ���źš�ȡֵ0~3ʱ���ֱ��Ӧ����ϵ�I/0 1~4;
  //                     ȡֵ-1ʱ��ͬʱ����4��GPIO�ܽţ�
  //GPIOInput�� GPIO �ܽŵ�ǰ�߼�ֵ��0 ���� 1��
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGPIORead (ST_CARDINFO *pstCardInfo,int GPIOSel/*,unsigned int GPIODirection*/,unsigned int *GPIOInput);

#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTFlashOpTest(ST_CARDINFO *pstCardInfo,unsigned int BaseAddr);

  //Dump all registers in FPGA
  //BaseAddr: base address
  //NoRegs: Number of registers to read
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTDumpRegister(ST_CARDINFO *pstCardInfo,unsigned int BaseAddr,unsigned int NoRegs);
   
  //Get installed card features
  //FeatureBitMap: Returns a bitmap with installed card features
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetFeat(ST_CARDINFO *pstCardInfo,unsigned int *FeatureBitMap);

  //����ָ������ַ��16KBflash�ռ䣬��ֹ�û�����
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTEraseXCalData(ST_CARDINFO *pstCardInfo,unsigned int BaseAddr);

#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSyncOp (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int unCalFrq,unsigned int unChOpt,unsigned int SampleRateGrade);

  //����ʽ�ȴ�ָ�����������Ƿ��Ѿ�׼����
//����ֵ������Ѿ�׼�����㹻��������������WAIT_OBJECT_0����������ֵ˵����ʱ
//NoByteLen:�û�ָ����������
//unTimeout����ʱ���ã���λms
#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTWaitDataReady(ST_CARDINFO *pstCardInfo,unsigned int NoByteLen,unsigned int unTimeout);

  //����PCIe DMA�жϳ��ȣ���������������λ��ÿ�յ����ó��ȵ����ݻ��յ�һ���ж��¼����û��ܼ�ʱ�յ����DMA�����ݡ�
//����ֵ������û����õ�ֵ�Ƿ����򷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
//NotifySizeB:�û�ָ����DMA�жϳ��ȣ���λbyte���ò�������ͬʱ������������������
// a) 2��n����(n>0);
// b) 128��������;
// c) ������4*1024*1024.
//NotifySizeBֵԽ��PCIe DMA�����ٶ�Խ��
#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTSetNotifySizeB(ST_CARDINFO *pstCardInfo,unsigned int NotifySizeB);

//����flash�̼���
//����ֵ������û����õ�ֵ�Ƿ����򷵻�RES_ERROR_BAD_PARAMETER�����򷵻�RES_SUCCESS
//FpBin:ָ��flash�̼����ļ�ָ��
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTUpdateFirmware(ST_CARDINFO *pstCardInfo,char *FpBin);

  //��ȡ�忨��SPI�Ĵ���
#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTSPIRead(ST_CARDINFO *pstCardInfo, unsigned int *cs, unsigned int *Addr, unsigned *RdVal);

#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTCalDataChk(ST_CARDINFO *pstCardInfo, char *FpADCCalData);

#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTRepData(ST_CARDINFO *pstCardInfo, UINT ReqMode, char *RepFile, UINT unLen, UINT *bytes_sent, UINT unTimeOut);

///���ûط��ļ�Ŀ¼���ļ����ؼ��ʣ��ط��ļ�����
//filepath:�ļ�����Ŀ¼
//keywords:�ؼ��ʣ��ط��ļ����Ĺ��ɣ�{filepath}\\{keywords}\\{index}.bin���ַ����Ȳ�����260 bytes
//StartIndex:��ʼ���
//EndIndex:���һ���ļ����
#ifdef __cplusplus
    extern "C"
#endif
    QTAPI int __stdcall nLDSetRepParam(ST_CARDINFO *pstCardInfo, char *filepath, char *keywords, int StartIndex, int EndIndex);


///�ط����̳�ʼ��
#ifdef __cplusplus
    extern "C"
#endif
      QTAPI int __stdcall nLDReplayInit(ST_CARDINFO *pstCardInfo);

//�ط��ļ��б�
#ifdef __cplusplus
    extern "C"
#endif
      QTAPI int __stdcall nLDReplayData(ST_CARDINFO *pstCardInfo);

    //ֹͣ�ط�����
#ifdef __cplusplus
    extern "C"
#endif
      QTAPI int __stdcall nLDReplayStop(ST_CARDINFO *pstCardInfo);

#ifdef __cplusplus
    extern "C"
#endif
      QTAPI int __stdcall nLDDecompress(ST_CARDINFO *pstCardInfo, char *filepath, char *Keyword, int StartIndex, int EndIndex, LONGLONG FileSize);

#ifdef __cplusplus
}
#endif

#endif
