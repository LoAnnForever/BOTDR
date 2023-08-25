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
      unsigned int DMA_LENGTH;//每次获取数据长度
      unsigned int DELAY_TAP_STEPNUM;//时钟抽头index
      unsigned int CHANNEL_COUNT;//物理通道数
      unsigned int NUM_DATA_CLK;//随路时钟数
      unsigned int CALDATA_BASE;//flash首地址
      double GAIN_GRANULARITY;//PGA增益步长
      unsigned int ChMask;//不同型号板卡的物理通道标志，每个bit对应一个通道，为1则存在，为0则不存在
      unsigned int dac_cs[4];//DAC芯片片选
      unsigned int pga_cs[4];//PGA芯片片选
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
      unsigned int uncompressMode;          //bit[0]=1:使能数据压缩模块,0:禁止数据压缩功能;//bit[1]=1:使能数据解压缩功能，0：禁止数据解压缩功能
      unsigned int CounterMode;             //Internal counter mode for test only
      //parameters regarding time stamp
      unsigned int TimeStampEn;             //Enable/Disable Timestamp mode. The following list valid values:
                                            //       0x0: Disable timestamp mode. Timestamp counter keep no change and values is param2 and param3 are ignored.
                                            //       0x3: Enable GPS mode, internal clock is used to counting.Accumulative error could impact on precision of timestamp along the time.
                                            //       0x13: Enable GPS mode, external 1pps clock is required to counting. This is a more accurate way vs. 0x3 mode.
      unsigned int TimeStampSegmentLen;
      unsigned int TimeStampSel;            //时间戳数据选择。0：选择GPS时间戳数据；1：选择用户时间戳数据
      unsigned int GpsScond;

      //parameters regarding dual-sample-rate DAQ
      QTFM_ABA_MODE ABAMode;                // ABA mode selection
      unsigned int ABADivider;              //In step of 16
      unsigned int NoChnInUse;              //Number of active channel in use
      unsigned int AccCnt;                  //Number of segment to accumulate
      unsigned int MeanMode;                //0:16bit mode 1:32bit mode
      unsigned int MeanEn;                  //0:禁止平均 1：使能平均
      unsigned int FeatureBitMap;           //增强功能bit mask

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
      unsigned int  V_number      ;           //平台V版本号
      unsigned int  R_number      ;           //平台R版本号
      unsigned int  M_number      ;           //平台M版本号
      unsigned int  product_line  ;           //产品线标，1:PCI；3:VPX；7:FMC
      unsigned int  product_series;           //子产品标识，1:AD产品；2:DA产品
      unsigned int  model_numbel_h;           //型号高位
      unsigned int  model_numbel_l;           //型号低位
      unsigned int  couple_type_h ;           //耦合方式高位
      unsigned int  couple_type_l ;           //耦合方式低位
      unsigned int  part_number   ;           //具体编号，用于区分不同性能
      unsigned int  channel_number;           //AD/DA物理通道数目
      unsigned int  serial_number ;           //板卡编号。每个板卡的编号都是唯一的
      unsigned int  carry_revision;           //载板版本
      unsigned int  adda_revision ;           //AD/DA板版本
      unsigned int  clock_revision;           //时钟板版本
      unsigned int  RTL_revision  ;           //RTL版本信息
      unsigned int  EDK_revision  ;           //EDK版本信息
      unsigned int  VSP_revision  ;           //VSP版本信息
      unsigned int  product_week  ;           //生产日期，日历周数
      unsigned int  product_year  ;           //生产日期，日历年份
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
        V_number       = 0xFFFF;               //平台V版本号
        R_number       = 0xFFFF;               //平台R版本号
        M_number       = 0xFF;                 //平台M版本号
        product_line   = 0xFF;                 //产品线标，1:PCI；3:VPX；7:FMC
        product_series = 0xFF;                 //子产品标识，1:AD产品；2:DA产品
        model_numbel_h = 0xFF;                 //型号高位
        model_numbel_l = 0xFF;                 //型号低位
        couple_type_h  = 0xFF;                 //耦合方式高位
        couple_type_l  = 0xFF;                 //耦合方式低位
        part_number    = 0xFF;                 //具体编号，用于区分不同性能
        channel_number = 0xFF;                 //AD/DA物理通道数目
        serial_number  = 0xFFFFFFFF;           //板卡编号。每个板卡的编号都是唯一的
        carry_revision = 0xFF;                 //载板版本
        adda_revision  = 0xFF;                 //AD/DA板版本
        clock_revision = 0xFF;                 //时钟板版本
        RTL_revision   = 0xFFFFFFFF;           //RTL版本信息
        EDK_revision   = 0xFFFFFFFF;           //EDK版本信息
        VSP_revision   = 0xFFFFFFFF;           //VSP版本信息
        product_week   = 0xFF;                 //生产日期，日历周数
        product_year   = 0xFF;                 //生产日期，日历年份
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
            unsigned int NumGain;               //增益档位个数 AC:1; DC:>=1
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


    //初始化板卡，自动复位板卡
    //输入参数：
    //pstCardInfo：板卡信息块
    //unCardIdx：板卡序号，从0开始;
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
    //TODO:获取板卡相关信息(ID，版本号，序列号)到pstCardInfo
#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTInitCardByIdx (ST_CARDINFO *pstCardInfo,unsigned int unCardIdx);
    //复位板卡
    //输入参数：
    //pstCardInfo：板卡信息块
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTResetCard (ST_CARDINFO *pstCardInfo);
    //快速设置
    //输入参数：
    //pstCardInfo：板卡信息块
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTFastSet (ST_CARDINFO *pstCardInfo,unsigned int Frequency);
    //关闭板卡
    //输入参数：
    //pstCardInfo：板卡信息块
    //返回值：
    //无
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTCloseCard (ST_CARDINFO *pstCardInfo);
    //写寄存器
    //输入参数：
    //pstCardInfo：板卡信息块
    //unRegOffset：寄存器地址
    //unRegValue：值
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTWrtReg (ST_CARDINFO *pstCardInfo,unsigned int unRegOffset,unsigned int unRegValue);
    //读寄存器
    //输入参数：
    //pstCardInfo：板卡信息块
    //unRegOffset：寄存器地址
    //punRegValue：值
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTReadReg (ST_CARDINFO *pstCardInfo,unsigned int unRegOffset,unsigned int *punRegValue);
    //通过Mailbox设置参数
    //输入参数：
    //pstCardInfo：板卡信息块
    //unCmd：命令;
    //unParam1：要设置参数1;
    //unParam2：要设置参数2;
    //unParam3：要设置参数3;
    //unTimeOut:超时，默认为0xffffffff，单位为毫秒。
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
    //TODO:每个SET操作逻辑都需要写四个返回寄存器，内容为逻辑的执行结果
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetParam (ST_CARDINFO *pstCardInfo,unsigned int unCmd,unsigned int unParam1,unsigned int unParam2,unsigned int unParam3,unsigned int unTimeOut);
    //通过Mailbox获取参数值
    //输入参数：
    //pstCardInfo：板卡信息块
    //unCmd：命令;
    //punParam1：要获取参数1;
    //punParam2：要获取参数2;
    //punParam3：要获取参数3;
    //unTimeOut:超时，默认为0xffffffff，单位为毫秒
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
    //TODO:需要不需要ReadReady这个中断
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetParam (ST_CARDINFO *pstCardInfo,unsigned int *punCmd,unsigned int *punParam1,unsigned int *punParam2,unsigned int *punParam3,unsigned int unTimeOut);
  //配置ADC器件工作模式
    //输入参数：
    //pstCardInfo：板卡信息块
    //unChOpt：对于QT1125，unChOpt为通道模式使能:QTFM_1125_CHANNEL_MODE；对于其他板卡，该参数为片选，目前已定义的取值为8,9,0xa,0xb
    //unModeFlg：对于所有板卡，用户模式下固定为0
    //ClockDivider:针对QT1138,时钟频率低于QTFM_COMMON_CLOCK_FREQUENCY_MIN时，可设置ClockDivider为2或者4分频，使ADC能够工作在更低的采样速率
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupADCMode (ST_CARDINFO *pstCardInfo,unsigned int unChOpt,unsigned int unModeFlg,unsigned int ClockDivider/*=0*/);
    //对于不支持自动IOdelay校准的板卡（QT1128，QT1130)，根据手动校准结果设置IO delay
    //输入参数：
    //pstCardInfo：板卡信息块
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在RES_ERROR_BAD_PARAMETER中定义
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTForceIOdelay(ST_CARDINFO *pstCardInfo);
    //配置工作模式
    //输入参数：
    //pstCardInfo：板卡信息块
    //unChOpt：通道使能:QTFM_1125_CHANNEL_MODE
    //unSegmentSize：所有使能通道的段长和，以QTFM_1125_SEGMENT_GRANULARITY为单位，默认QTFM_1125_SEGMENT_GRANULARITY
    //unPreSamples：所有使能通道的预触发点数和，单位是QTFM_1125_PRE_TRIGGER_GRANULARITY，默认为0
    //unSegmentCnt：段个数，1：表示单次触发，其他为多次触发。0：表示4G次触发。默认为1
    //unModeFlg：QTFM_COMMON_BOARD_WORK_MODE，默认为QTFM_COMMON_BOARD_WORK_MODE_STD_SIGNLE
    //unCompressorMode:数据压缩\解压缩模块工作模式。bit[0]:压缩模块工作模式;bit[1]:解压缩模块工作模式.bit[n]为1表示使能压缩或者解压缩,为0则禁止
    //unPostSamples:后触发长度，触发结束后继续采集的长度（samples），仅用于电平触发
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupWorkMode (ST_CARDINFO *pstCardInfo,unsigned int unSegmentSize,unsigned int unPreSamples,unsigned int unSegmentCnt,unsigned int unModeFlg,unsigned int unCompressorMode,unsigned int unPostSamples);
    //设置内时钟
    //输入参数：
    //pstCardInfo：板卡信息块
    //unSamplerate：期望的采样率，QTFM_COMMON_CLOCK_FREQUENCY
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupClockInternal (ST_CARDINFO *pstCardInfo,unsigned int unSamplerate);
  //设置内时钟
    //输入参数：
    //pstCardInfo：板卡信息块
    //Fref:参考时钟频率,Hz
    //RefDiv:参考时钟频率系数,0~(1^14-1)
    //Frequency：期望的采样率，分辨率为QTFM_COMMON_CLOCK_FREQUENCY_GRANULARITY
  //VCOMode: 内部VCO or 外部VCO，QTFM_COMMON_CLOCK_VCO_MODE_0~1
  //RefClkMode:QTFM_COMMON_CLOCK_REF_MODE_0~2
  //ADCClkMode:QTFM_COMMON_ADC_CLOCK_MODE_0~1
    //RstADC:复位ADC指示，置1表示函数执行过程中复位ADC芯片；置0则不复位ADC芯片，只修改时钟频率
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupClock (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int Frequency,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int RstADC/*=1*/);
    //设置软触发。
    //输入参数：
    //pstCardInfo：板卡信息块
    //unTrigtype：QTFM_COMMON_TRIGGER_TYPE
    //unEnable：是否使能
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupTrigSoftware (ST_CARDINFO *pstCardInfo,unsigned int unTrigType,unsigned int unEnable);
    //设置外触发电平。此版没有实现。
    //输入参数：
    //pstCardInfo：板卡信息块
    //unExtIdx：QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_1 to QTFM_COMMON_TRIGGER_SOURCE_EXTERNAL_13
    //unTrigType：QTFM_COMMON_TRIGGER_TYPE
    //unEnable：是否使能
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupTrigExternal (ST_CARDINFO *pstCardInfo,unsigned int unExtIdx,unsigned int unTrigType,unsigned int unEnable);
  //设置触发通道。
  //输入参数：
  //pstCardInfo：板卡信息块
  //unChannel：通道编号，CHANNEL_0~7，对于QT1140V2,选择面板上trig通道作为模拟触发时，unChannel用作高阻和50ohm选择控制(TRIG_CHANNEL_HIZ or TRIG_CHANNEL_50OHM)
  //unTrigtype：QTFM_COMMON_TRIGGER_TYPE
  //unRiseEdgeLevel：上升沿触发电平量化值.
  //unFallEdgeLevel：下降沿触发电平量化值
  //对于QT1140V2产品，trig通道在高阻输入时，满量程±10V，50欧姆输入时满量程±2.5V。unRiseEdgeLevel和unFallEdgeLevel的范围是0x8000±0x6666对应满量程。
  //unEnable：是否使能 1：使能；0：禁止
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupTrigChannel (ST_CARDINFO *pstCardInfo,unsigned int unChannel,unsigned int unTrigType,/*unsigned */int unRiseEdgeLevel,/*unsigned */int unFallEdgeLevel,unsigned int unEnable);
    //设置触发脉冲
    //输入参数： 
    //pstCardInfo：板卡信息块
    //unTrigType：QTFM_COMMON_TRIGGER_TYPE,  external trigger mode，Rising edge,Falling Edge,double Edge,high level,Low level, enable bit
    //unPulsewidth：QTFM_1125_PULSE_WIDTH,programmable pulse width for channel,unit:number of sample clock cycles
    //unPulsePeriod：internal pulse period(offset=0x8), unit:number of sample clock cycles
    //unEnable：是否使能
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupTrigPulse (ST_CARDINFO *pstCardInfo,unsigned int unTrigType,unsigned int unPulsewidth,unsigned int unPulsePeriod,unsigned int unEnable);
    //设置触发源与或和触发延迟。
    //输入参数：
    //pstCardInfo：板卡信息块
    //unMask：标记,QTFM_COMMON_TRIGGER_SOURCE_MASK。默认为QTFM_COMMON_TRIGGER_SOURCE_MASK_OR。
    //unDelay_LowPart：触发延迟低32位，默认为0，单位：number of AD clocks.
    //unDelay_HighPart：触发延迟高32位，默认为0，单位：number of AD clocks.
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupTrigSourcesOrAndDelay (ST_CARDINFO *pstCardInfo,unsigned int unMask,unsigned int unDelay_LowPart,unsigned int unDelay_HighPart); 
    //设置输入通道。
    //输入参数：
    //pstCardInfo：板卡信息块
    //unChannel：要设置的通道，取值范围：CHANNEL_0~CHANNEL_7，分别对应通道0~7
    //unInputRange：input range in mV  +/-1V range
    //bTerm = true：set input termination (50 ohm) if available
    //unInputOffset = 0：programmable input offset as listed in the manual
    //bDiffInput = false：set differential input if available
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupInputChannel (ST_CARDINFO *pstCardInfo,unsigned int unChannel,unsigned int unInputRange,unsigned int unTerm,unsigned int unInputOffset,unsigned int unDiffInput,unsigned int unChEn);
    //配置时间戳模式和具体参数
    //输入参数：
    //pstCardInfo：板卡信息块
    //输入参数
    //TimeStampEn:时间戳使能:
    //       0x0: Disable timestamp mode. Timestamp counter keep no change and values is param2 and param3 are ignored.
    //       0x3: Enable GPS mode, internal clock is used to counting.Accumulative error could impact on precision of timestamp along the time.
    //       0x13: Enable GPS mode,   external 1pps clock is required to counting. This is a more accurate way vs. 0x3 mode.
    //       others: illegal value
    //TimeStampSegmentLen: if GPS mode is enabled, it is length of a segment in samples. Timestamp information is inserted at the head of each segment;
    //                     if GPS mode is not enabled, it is LSB of current time;
    //GPSSecond:if GPS mode is enabled, it is GPS second from 1900';
    //          if GPS mode is not enabled, it is MSB of current time;
    //Freq:每个ADC的采样率，单位Hz
    //TimeStampSel：时间戳数据选择
    //              0：选择GPS时间戳数据
    //              1：选择用户时间戳数据
    //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetupTimestamp (ST_CARDINFO *pstCardInfo, unsigned int TimeStampEn,unsigned int TimeStampSegmentLen,unsigned int GPSSecond,unsigned int Freq,unsigned int TimeStampSel);
    //开始数据传输。
    //输入参数：
    //pstCardInfo：板卡信息块
    //unDirection传输方向，QTFM_COMMON_TRANSMIT_DIRECTION，默认QTFM_COMMON_TRANSMIT_DIRECTION_TX
    //bDmaEn  = true：使能或停止。[运行时，先DMA，后ADC，结束时，先Disable ADC，再停止DMA。]
    //unTimeOut: 超时设置，默认为0xffffffff;
    //TimedModeEn: 固定配置为false;
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStart (ST_CARDINFO *pstCardInfo,unsigned int unDirection,int bDmaEn,unsigned int unTimeOut,int TimedModeEn);

    //通知嵌入式开始接收上位机的数据
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStartReplay(ST_CARDINFO *pstCardInfo);
    //等待一次Dma数据
    //输入参数：
    //pstCardInfo：板卡信息块
    //unDirection  = 0：传输方向，QTFM_COMMON_TRANSMIT_DIRECTION，默认QTFM_COMMON_TRANSMIT_DIRECTION_TX
    //unTimeOut:超时时间，单位为毫秒，默认0xFFFFFFFF
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTWaitForDmaDoneEvt (ST_CARDINFO *pstCardInfo,unsigned int unDirection/* = 0 */,unsigned int unTimeOut/* = 0xFFFFFFFF*/);
    //处理数据完成后通知
    //输入参数：
    //pstCardInfo：板卡信息块
    //unDirection  = 0：传输方向，QTFM_COMMON_TRANSMIT_DIRECTION，默认QTFM_COMMON_TRANSMIT_DIRECTION_TX
    //返回值：
    //成功返回RES_SUCCESS，否则返回值在DRV_RESULT_CODE中定义
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetDataHandleDoneEvt (ST_CARDINFO *pstCardInfo,unsigned int unDirection);
    //得到采集的数据
    //输入参数：
    //pstCardInfo：板卡信息块
    //pBufDest：目标Buffer
    //unLen：长度单位为字节
    //unTimeOut：超时，单位为毫秒
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetData (ST_CARDINFO *pstCardInfo,unsigned char *pBufDest,unsigned int unLen,unsigned int unTimeOut/*=0xFFFFFFFF*/);
    //发送波形数据
    //输入参数：
    //pstCardInfo：板卡信息块
    //pBufDest：原始Buffer
    //unLen：长度单位为字节
    //unTimeOut：超时，单位为毫秒
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSendData (ST_CARDINFO *pstCardInfo, void *pBufSrc, unsigned int unLen,unsigned int *bytes_sent, unsigned int unTimeOut/*=0xFFFFFFFF*/);

    //查询板卡的传输和异常状态
    //输入参数：
    //pstCardInfo：板卡信息块
    //返回值：
    //      bit[0]:ADC接口模块reset sequence超时标志，为1表示ADC工作时钟异常，0正常；
    //      bit[1]:为1表示fifo模式下buffer溢出，说明数据采集速率超出了PCIe传输速率，0正常
    //      bit[2]:为1表示ADC接口逻辑中DMA fifo溢出，需降低采样率，0正常
    //      bit[3]:为1表示fifo模式下time-stamp buffer溢出，0正常
    //      bit[4]:为1表示传输完成，0表示数据传输未开始或者正在传输过程中；
    //      bit[5]:ADC采样时钟异常标志,1:ADC采样时钟频率异常，需检查时钟设置; 0:时钟状态正常;
    //      bit[6]:单板pcie Rx DMA buffer ready状态：1:buffer已经准备好接收数据; 0:buffer未准备好，上位机不能下发新的数据;
    //      bit[7]:AD接口逻辑工作在计数器模式时的数据校验结果: 1:数据校验错; 0:数据校验正确;
  //      bit[8]:TX/RX DMA engine 工作异常标志位：1:TX或者RX DMA engine工作异常；0：二者工作正常；
    //返回值：如果bit[8:7],bit[5],bit[3:0]任何一位为1，说明工作异常,返回RES_ERROR_BOARD_EXCEPTION，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetBrdStatus (ST_CARDINFO *pstCardInfo,unsigned int Frequency, unsigned int *status);
    //查询PCIe AXI DMA buffer长度（单位Byte）
    //输入参数：
    //pstCardInfo：板卡信息块
    //RxBufLen:buffer长度
    //返回值：如果长度为0，则返回RES_ERROR_BOARD_EXCEPTION，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetRxBufLen (ST_CARDINFO *pstCardInfo,unsigned int *RxBufLen);
    //IODelay校准,每次上电工作后，都要进行此校准。结果保存在当前目录下IODelayCal.dat文件中
    //输入参数：
    //pstCardInfo：板卡信息块
    //unCal_Frq:校准时的时钟频率
    //unChOpt:_tag_QTfm_1125_Channel_Mode->*
    //IOWindowMode:取值0或1，用于控制数据IO bus delay与时钟IO delay间可调窗口大小
    //SampleRateGrade:当Sample Rate低于QTFM_COMMON_CLOCK_FREQUENCY_MIN时，取值为1，否则为0
    //ucArrayClock:时钟校准值
    //usArrayOffset:Offfset校准值
    //punChIoDelayRes：通道校准标志
    //punProgress：进度
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTIODelayCal (ST_CARDINFO *pstCardInfo,unsigned int unCalFrq,unsigned int unChOpt,unsigned int IOWindowMode,unsigned int SampleRateGrade,unsigned char ucArrayClock[4],unsigned short usArrayOffset[4],unsigned int *punChIoDelayRes,unsigned int *punProgress,unsigned int TimeOut);
    //ADC interleaving calibration process，结果保存在当前目录下ADCCal.dat文件中
    //输入参数：
    //pstCardInfo：板卡信息块
    //Fref:时钟芯片的参考时钟频率(10~350MHz)，单位Hz
    //RefDiv:参考时钟分频系数,1~(1<<14-1) should always be 1
    //VCOMode:选择内置VCO或者外置VCO，取值QTFM_COMMON_CLOCK_VCO_MODE_0 or QTFM_COMMON_CLOCK_VCO_MODE_1
    //RefClkMode:选择参考时钟来源，取值QTFM_COMMON_CLOCK_REF_MODE_0~2
    //ADCClkMode:选择ADC采样时钟来源，取值QTFM_COMMON_ADC_CLOCK_MODE_0~1
    //unCalFrq：ADC芯片输入时钟频率
    //unChOpt：仅对QT1125有意义，设置ADC芯片通道模式_tag_QTfm_1125_Channel_Mode->*
    //SampleRateGrade:当Sample Rate低于QTFM_COMMON_CLOCK_FREQUENCY_MIN时，取值为1，否则为0
#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTADCCal (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int unCalFrq,unsigned int unChOpt,unsigned int SampleRateGrade);
#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTXcal (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int unCalFrq,unsigned int unChOpt,unsigned int SampleRateGrade);
    //调节信号偏置
    //输入参数：
    //pstCardInfo：板卡信息块
    //cs:For qt1125, it is 16,17,18,19;
    //   For QT1135,QT1130,QT1138, valid value should be 16,17,18,19;
    //   For QT1128, valid value is 16,17
    //ReqOffset:required offset value in uV unit.
    //          For QT1125, valid range is {-4.096V,4.096V}  with 62.5uV step;
    //返回值：执行错误返回RES_ERROR_BOARD_EXCEPTION，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTTuneOffset (ST_CARDINFO *pstCardInfo, unsigned int cs,double ReqOffset);
    //调节信号增益
    //输入参数：
    //pstCardInfo：板卡信息块
    //输入参数
    //cs:For qt1125, it is 24,25,26,27;
    //   For QT1135,QT1130,valid value should be 24,25,26,27;
    //   For QT1138, valid value should be 16,17,18,19
    //   For QT1128, valid value is 24,25
    //ReqGain: required gain value in dB unit:
    //         For QT1125, valid range is [6,26]dB with 0.25dB step;
    //         For QT1138DC it is a enumeric number according to variable input full-scale:
    //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTTuneGain (ST_CARDINFO *pstCardInfo, unsigned int cs,double ReqGain);

    //调节信号增益
    //输入参数：
    //pstCardInfo：板卡信息块
    //输入参数
    //cs:CHANNEL_0~CHANNEL_7
    //ReqGain: required gain value in dB unit:
    //         For QT1125, undefined;
    //         For QT1138AC/DC/VG, ReqGain is among [-2.0~6]dB with 0.5dB step;
    //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTTuneDigitalGain (ST_CARDINFO *pstCardInfo, unsigned int cs,double ReqGain);

    //计算某一PGA增益时，0电平对应的偏置值
    //输入参数：
    //pstCardInfo：板卡信息块
    //输入参数
    //dac_cs:For qt1125, it is 16,17,18,19;
    //   For QT1135,QT1130,QT1138, valid value should be 16,17,18,19;
    //   For QT1128, valid value is 16,17
    //pga_cs:For qt1125, it is 24,25,26,27;
    //   For QT1135,QT1130,QT1138, valid value should be 24,25,26,27;
    //   For QT1128, valid value is 24,25
    //CurrGain:当前增益值。For QT1125, valid range is [6,26]dB with 0.25dB step;
    //InitOffset:初始offset value
    //ResultOffset:程序返回的偏置值结果
    //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetZeroLevelDCOffsetForGain(ST_CARDINFO *pstCardInfo,unsigned int dac_cs,unsigned pga_cs,double CurrGain,double InitOffset,double *ResultOffset);
    //计算某一PGA增益时，0电平对应的偏置值
    //输入参数：
    //pstCardInfo：板卡信息块
    //输入参数
    //dac_cs:For qt1125, it is 16,17,18,19;
    //   For QT1135,QT1130,QT1138, valid value should be 16,17,18,19;
    //   For QT1128, valid value is 16,17
    //pga_cs:For qt1125, it is 24,25,26,27;
    //   For QT1135,QT1130,QT1138, valid value should be 24,25,26,27;
    //   For QT1128, valid value is 24,25
    //CurrGain:当前增益值。For QT1125, valid range is [6,26]dB with 0.25dB step;
    //InitOffset:设置的初始offset值，程序从此初值开始自动调整offset，直到采样数据的均值与ExpectMean相等
    //ExpectMean:期望程序自动调整DAC offset后，ADC采样数据平局值
    //ResultOffset:程序返回的偏置值结果
    //ResultMean:返回值，当量化平均值与ExpectMean最接近时的平均值
    //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSetDCOffsetForGain(ST_CARDINFO *pstCardInfo,unsigned int dac_cs,unsigned pga_cs,double CurrGain,double InitOffset,double ExpectMean,double *ResultOffset,double *ResultMean);
    //计算PGA所有档位下，对于每个输入范围的{偏置校准值，增益值}，并存为文件
    //输入参数：
    //pstCardInfo：板卡信息块
    //输入参数
    //OffsetScale:DC校准之后，偏置调整参数：Ydac=OffsetScale*x+b
    //FileName:文件名指针，用于存储直流偏置校准结果
    //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTDCOffsetPGACal(ST_CARDINFO *pstCardInfo,double *ArrayOffsetScale,char *FileName);
    //DC耦合单板模拟前端校准程序
    //输入参数：
    //pstCardInfo：板卡信息块
    //CalDACEn:使能DAC校准,0:disable,程序自动读取上次的校准结果;1:enable
    //CalInputRangeEn:使能输入量程校准,0:disable,程序自动读取上次的校准结果;1:enable
    //返回值：
    //FileName:文件名指针，用于存储直流偏置校准结果
    //ArrayZeroLevelDCOffset:二维数组[DAC_NUM][GAIN_STEP_NUM].
    //                       对于QT1125DC，DAC_NUM=4，GAIN_STEP_NUM=80;
    //                       对于QT1138DC, DAC_NUM=4, GAIN_STEP_NUM=4
    //ArrayPGAGain:三维数组[DAC_NUM][GAIN_STEP_NUM][INPUT_RANGE_NUM].
    //                       对于QT1125DC，DAC_NUM=4，GAIN_STEP_NUM=80,INPUT_RANGE_NUM=4
    //                       对于QT1138DC, DAC_NUM=4, GAIN_STEP_NUM=4,INPUT_RANGE_NUM=4
    //ArrayDACCoeff:一维数组[DAC_NUM]，用于存放直流偏置校准系数
    //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTDCCal (ST_CARDINFO *pstCardInfo,unsigned CalDACEn,unsigned int CalInputRangeEn,char *FileName,double *ArrayZeroLevelDCOffset,double *ArrayPGAGain,double *ArrayDACCoeff);
    //在波形回放之前，将波形的配置参数下发给板卡
    //输入参数：
    //pstCardInfo：板卡信息块
    //输入参数
    //Index:当前波形编号
    //WaveformLen:每个波形的长度，单位：Byte
    //LoopCnt:每个波形的循环次数
    //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
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

  //高速存储初始化
  //输入参数：
  //pstCardInfo：板卡信息块
  //FileName：文件名，长度128字节
  //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStoreInit (ST_CARDINFO *pstCardInfo);

  //存储相关的用户参数设置接口
  //输入参数：
  //pstCardInfo：板卡信息块
  //输入参数
  //NameRule:        0(by default): {Data}_{Time}_{Index}; 1:User specified file name {User_spec_name}_{Index}
  //FileLocation:    Specify file location in windows style to store files. Files are stored in current working directory by default
  //UsrFileName:     User specified file name
  //SplitFileSizeMB: Split at file size in MB. 0 means don't split file
  //MaxNumFiles:     Max number of files to stop storing files. 0 means unlimited. MaxNumFiles has priority over MaxFileSizeMB.
  //MaxFileSizeMB:   Max file size in 1024*1024 bytes to stop writing file. 0 means unlimited.
  //PPDATABUFLEN:    Ping-pang buffer size in byte
  //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStoreParamSet (ST_CARDINFO *pstCardInfo,unsigned int NameRule,char *FileLocation,char *UsrFileName,unsigned int SplitFileSizeMB,unsigned int MaxNumFiles,unsigned int MaxFileSizeMB,unsigned int PPDATABUFLEN);
  
  //开始采集存储数据
  //输入参数：
  //pstCardInfo：板卡信息块
  //CNT：触发模式，软触发模式存储数据时Cnt输入0，外触发模式存储数据时Cnt输入1
  //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStoreData (ST_CARDINFO *pstCardInfo, char *FileName, int TrigMode);
  //停止采集存储数据
  //输入参数：
  //pstCardInfo：板卡信息块
  //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStoreStop (ST_CARDINFO *pstCardInfo);
  //开始采集数据,做FFT运算时防止数据堵塞，专开一个线程收数据
  //输入参数：
  //pstCardInfo：板卡信息块
  //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStartGetFFTData (ST_CARDINFO *pstCardInfo);
  //停止采集数据
  //输入参数：
  //pstCardInfo：板卡信息块
  //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTStopGetFFTData (ST_CARDINFO *pstCardInfo);
    //获取磁盘容量大小
    //输入参数:
  //pstCardInfo：板卡信息块
    //输出参数:
    //ToatalSpace:磁盘总容量大小, FreeSpace:剩余磁盘容量大小,单位大小是MB
  //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetDiskSpace (ST_CARDINFO *pstCardInfo, double *ToatalSpace, double *FreeSpace);
    //获取显示FFT数据
    //输入参数:
    //pstCardInfo：板卡信息块
    //pDataBuf:数据指针, DataLen:获取数据长度,目前默认大小是4M
    //unTimeout:超时时间
    //输出参数:
    //pDataBuf:获取到的数据指针
  //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGetDataToFFT (ST_CARDINFO *pstCardInfo, unsigned char *pDataBuf, unsigned int DataLen, unsigned int unTimeOut);

  //外触发模式下查询板卡获取数据状态，获取数据结束后即开始下一次
  //输入参数：
    //pstCardInfo：板卡信息块
  //返回值：执行错误返回RES_STORE_DATA_BUZY，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTPollGetDataStatus (ST_CARDINFO *pstCardInfo);
  //等待写文件完成
  //输入参数：
    //pstCardInfo：板卡信息块
  //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTWaitForWriteFileDoneEvt (ST_CARDINFO *pstCardInfo);
  //释放存储数据过程中申请的内存
  //输入参数：
    //pstCardInfo：板卡信息块
  //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTFreeMemrory (ST_CARDINFO *pstCardInfo);
  //增益校准
  //输入参数：
    //pstCardInfo：板卡信息块
  //ReqGain：增益控制值-37~3，步进为1
  //输入输出参数：
  //*cs：输入时为滤波器选通，0表示不选通，1表示选通，输出时表示PA的状态，0表示PA没选通，1表示PA选通
  //*CalValue：输出ADC的校准值
  //返回值：执行错误返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGainCal (ST_CARDINFO *pstCardInfo, unsigned int *cs,double ReqGain, double *CalValue);

  //设置GPIO的方向，以及采集时，每个模拟通道的采样数据中，digital bit的分配
  //GPIODirection：方向控制。板卡前面板上的4个GPIO信号X1~4分两组分别控制方向。其中:
  //               GPIO 3和4的方向相同，由GPIODirection[1]控制方向。0：输入;1：输出；
  //               GPIO 1和2的方向相同，由GPIODirection[0]控制方向。0：输入;1：输出；
  //GPIODispatch:控制每个模拟通到的采样数据中，插入的digital bit个数，覆盖采样数据的相应bit；
  //             取值范围为0~N：
  //             0:不插入digital bit，屏蔽此功能；
  //             1:每个通道插入1 digital bit。此时，各个通道的采样数据中，
  //               data_chn_0[0]=X1;
  //               data_chn_1[0]=X2;
  //               data_chn_2[0]=X3;
  //               data_chn_3[0]=X4;
  //               data_chn_4[0]=X1;
  //               data_chn_5[0]=X2;
  //               data_chn_6[0]=X3;
  //               data_chn_7[0]=X4;
  //             2:每个通道插入2 digital bits。此时，各个通道的采样数据中，
  //               data_chn_0[1:0]={X2,X1};
  //               data_chn_1[1:0]={X4,X3};
  //               data_chn_2[1:0]={X2,X1};
  //               data_chn_3[1:0]={X4,X3};
  //               data_chn_4[1:0]={X2,X1};
  //               data_chn_5[1:0]={X4,X3};
  //               data_chn_6[1:0]={X2,X1};
  //               data_chn_7[1:0]={X4,X3};
  //             3:每个通道插入3 digital bits。此时，各个通道的采样数据中，
  //               data_chn_0[2:0]={X3,X2,X1};
  //               data_chn_1[2:0]={X2,X1,X4};
  //               data_chn_2[2:0]={X1,X4,X3};
  //               data_chn_3[2:0]={X4,X3,X2};
  //               data_chn_4[2:0]={X3,X2,X1};
  //               data_chn_5[2:0]={X2,X1,X4};
  //               data_chn_6[2:0]={X1,X4,X3};
  //               data_chn_7[2:0]={X4,X3,X2};
  //             4:每个通道插入4 digital bits。此时，各个通道的采样数据中，
  //               data_chn_{i}[3:0]={X4,X3,X2,X1}; i取值范围0~7；
  //DigitalOnlyEn:使能与禁止纯数字采集。
  //              1：使能纯数字采集，此时上位机的数据中全部是数字IO信号的值，没有任何模拟信号的量化值。
  //              0：禁止纯数字采集，如果此时GPIODispatch值大于0，模拟采样数据中包括了GPIODispatch位的数字信号。
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGPIOSet (ST_CARDINFO *pstCardInfo, unsigned int GPIODirection,unsigned int GPIODispatch,unsigned int DigitalOnlyEn/*=0*/);

  //提供软件的方式调节GPIO传输路径延时，与调整线长效果等效。
  //GPIOSel:选择当前命令的操作对象。取值：-1~3。
  //                              -1：所有GPIO管脚；
  //                               0：GPIO 1；
  //                               1：GPIO 2；
  //                               2：GPIO 3；
  //                               3：GPIO 4；
  //Delay:延时值，单位ns,取值范围：0~5ns,精度为5/32 ns
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGPIODelaySet (ST_CARDINFO *pstCardInfo, int GPIOSel,double Delay);

  //设置模拟通道的直流偏置
  //ChnIdx:通道编号，取值CHANNEL_0~CHANNEL_7。当ChnIdx=-1时，设置所有的通道
  //OffsetVolt:通道偏置电压，单位uV
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTChannelOffsetSet (ST_CARDINFO *pstCardInfo, int ChnIdx,double OffsetVolt);

  //设置模拟通道的输入范围
  //ChnIdx:通道编号，取值CHANNEL_0~CHANNEL_7。当ChnIdx=-1时，设置所有的通道
//RangeVolt:通道输入范围选择，取值范围0~(N-1)，其中N是板卡支持的输入范围档位个数，分别对应1X,2X,5X,10X放大。
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTChannelRangeSet (ST_CARDINFO *pstCardInfo,int ChnIdx,double RangeVolt);

  //获取采集过程中数据相关的信息，包括数据缓存buffer中有效的数据长度、是否溢出、以及溢出的数据量。
  //如果buffer已经溢出，则有一部分数据被改写了，这部分数据无法取回。请适当加快读取buffer的速度，
  //或者降低采样率。
  //pDataLenB:当前buffer中的有效数据量，单位bytes；
  //pBufOverflow: 1：buffer溢出； 0：buffer状态正常；
  //pNoBytesOverwritten:从上一次读取buffer到现在，有多少数据由于溢出被覆盖了；
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTBufStatusGet (ST_CARDINFO *pstCardInfo,__int64  *pDataLenB,int *pBufOverflow,unsigned int *pNoBytesOverwritten);

  //从buffer中获取一定长度的数据，并拷贝到用户指定的buffer中。
  //开始拷贝数据之前，程序内部自动判断当前buffer的状态，若发现异常（buffer溢出、空、有效数据不足），程序退出并返回异常代码
  //pDestBuf:指向目标buffer的地址指针；
  //NoBytesLen: 需要拷贝的采样数据长度，单位bytes；
//#ifdef __cplusplus
//  extern "C"
//#endif
//  QTAPI int __stdcall nQTBufDataGet (ST_CARDINFO *pstCardInfo,unsigned char *pDestBuf,unsigned int NoBytesLen);
#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTBufDataGet(ST_CARDINFO *pstCardInfo, void *pDestBuf, unsigned int NoBytesLen);

  //根据量化值计算并返回模拟量
  //输入参数：
  //pstCardInfo：板卡信息块
  //DI：量化值
  //AO: 转换之后的模拟量
  //返回值：double类型
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI double __stdcall nQTFCVT (ST_CARDINFO *pstCardInfo, unsigned int DI,double AO);

  //设置ABA模式的相关参数
  //pstCardInfo：板卡信息块
  //ABAMode:ABA模式控制： 0：正常模式; 1：ABA模式; 2：分频模式;
  //ABADivider: 用于采集低速数据的分频系数，步长=16，取值范围1~65536
  //NoChn:用户实际使能的模拟通道个数，与QTInputChannelSet命令使用的通道个数未必相等。
  //      如QT1125XX，1通道模式时，用户只能使用1个模拟通道，NoChn=1；
  //                  2通道模式时，用户最多可使用2个模拟通道，如果QTInputChannelSet命令使能了对应的模拟通道，NoChn=2；
  //                  4通道模式时，用户最多可使用4个模拟通道，QTInputChannelSet命令使能了n个通道，NoChn=n;
  //      对其他型号的所有板卡，QTInputChannelSet使能了n个通道，NoChn=n;
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTABAModeSet (ST_CARDINFO *pstCardInfo, unsigned int ABAMode,unsigned int ABADivider,unsigned int NoChn);

  //调节数字IO的传输路径上的latency,达到与模拟信号同步的目的。
  //pstCardInfo：板卡信息块
  //DigLatency:数字输入延时，单位为AD时钟数
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTDigInLatency(ST_CARDINFO *pstCardInfo,unsigned int DigLatency);

  //配置数据格式： offset binary or two's complement code.
  //对于QT1128，QT1125XX板卡，只支持offset binary code;
  //对于QT1130，QT1135，QT1138板卡，二者都支持，默认offset binary
  //pstCardInfo：板卡信息块
  //DataFormat:数据格式，0:offset binary; 1: Two's complement
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTDataFormatSet(ST_CARDINFO *pstCardInfo,unsigned int DataFormat);

  //ADC interleaving calibration process
  //输入参数：
  //pstCardInfo:板卡信息
  //FpDelayTapVal:文件名。执行nQTADCCal成功后，程序自动保存一个名为DelayTapVal_card{card number}_{Frequency}.dat文件，里面保存了所有校准数据。
  //         FpDelayTapVal指向该文件，由nQTCalDataSet回读文件并完成设置。
  //FpADCCalData:仅对QT1125XX板卡有效，其他板卡，可输入NULL。文件名。执行nQTADCCal成功后，程序自动保存一个名为ADCCal_card{card number}_{Frequency}.dat的文件，里面保存了QT1125 ADC芯片的配置参数。
  //         FpADCCalData指向该文件，由nQTCalDataSet回读文件并完成设置。
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTCalDataSet (ST_CARDINFO *pstCardInfo,char *FpDelayTapVal,char *FpADCCalData);

  //设置GPIO的方向，每个gpio的输出值
  //GPIOSel:管脚选择信号。取值0~3时，分别对应面板上的I/0 1~4;
  //                     取值-1时，同时操作4个GPIO管脚；
  //GPIOOutput：输出控制。取值范围：
  //           0：输出0；
  //           1：输出1；
  //           2：输出通道触发信号;
  //           3：输出内部脉冲触发信号;
  //           4：输出软触发信号;
  //           5：输出最终触发信号;
  //           6：保留，禁止使用；
  //           7：将面板上从x1输入的触发信号输出;
  //           8：将面板上从x2输入的触发信号输出;
  //           9：将面板上从x3输入的触发信号输出;
  //           10：将面板上从x4输入的触发信号输出;
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTGPIOWrite (ST_CARDINFO *pstCardInfo, int GPIOSel/*,unsigned int GPIODirection*/,unsigned int GPIOOutput);

  //设置GPIO的方向，每个gpio的输出值
  //GPIOSel:管脚选择信号。取值0~3时，分别对应面板上的I/0 1~4;
  //                     取值-1时，同时操作4个GPIO管脚；
  //GPIOInput： GPIO 管脚当前逻辑值，0 或者 1；
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

  //擦除指定基地址的16KBflash空间，禁止用户调用
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTEraseXCalData(ST_CARDINFO *pstCardInfo,unsigned int BaseAddr);

#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTSyncOp (ST_CARDINFO *pstCardInfo,unsigned int Fref,unsigned int RefDiv,unsigned int VCOMode,unsigned int RefClkMode,unsigned int ADCClkMode,unsigned int unCalFrq,unsigned int unChOpt,unsigned int SampleRateGrade);

  //阻塞式等待指定的数据量是否已经准备好
//返回值：如果已经准备好足够的数据量，返回WAIT_OBJECT_0；返回其他值说明超时
//NoByteLen:用户指定的数据量
//unTimeout：超时设置，单位ms
#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTWaitDataReady(ST_CARDINFO *pstCardInfo,unsigned int NoByteLen,unsigned int unTimeout);

  //设置PCIe DMA中断长度，产生的作用是上位机每收到设置长度的数据会收到一次中断事件，用户能及时收到这次DMA的数据。
//返回值：如果用户设置的值非法，则返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
//NotifySizeB:用户指定的DMA中断长度，单位byte。该参数必须同时满足以下三个条件：
// a) 2的n次幂(n>0);
// b) 128的整数倍;
// c) 不大于4*1024*1024.
//NotifySizeB值越大，PCIe DMA传输速度越快
#ifdef __cplusplus
  extern "C"
#endif
    QTAPI int __stdcall nQTSetNotifySizeB(ST_CARDINFO *pstCardInfo,unsigned int NotifySizeB);

//升级flash固件。
//返回值：如果用户设置的值非法，则返回RES_ERROR_BAD_PARAMETER，否则返回RES_SUCCESS
//FpBin:指向flash固件的文件指针
#ifdef __cplusplus
  extern "C"
#endif
  QTAPI int __stdcall nQTUpdateFirmware(ST_CARDINFO *pstCardInfo,char *FpBin);

  //读取板卡的SPI寄存器
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

///设置回放文件目录，文件名关键词，回放文件个数
//filepath:文件所在目录
//keywords:关键词，回放文件名的构成：{filepath}\\{keywords}\\{index}.bin，字符长度不超过260 bytes
//StartIndex:起始编号
//EndIndex:最后一个文件编号
#ifdef __cplusplus
    extern "C"
#endif
    QTAPI int __stdcall nLDSetRepParam(ST_CARDINFO *pstCardInfo, char *filepath, char *keywords, int StartIndex, int EndIndex);


///回放例程初始化
#ifdef __cplusplus
    extern "C"
#endif
      QTAPI int __stdcall nLDReplayInit(ST_CARDINFO *pstCardInfo);

//回放文件列表
#ifdef __cplusplus
    extern "C"
#endif
      QTAPI int __stdcall nLDReplayData(ST_CARDINFO *pstCardInfo);

    //停止回放流程
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
