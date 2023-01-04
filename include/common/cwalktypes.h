/***
 *cwalktypes.h - Basic data types
 *    Copyright (c) 2000-2012, CloudWalk Technologies,Ltd. All rights reserved.
 *Purpose:
 **************************************************************************************/

#ifndef _cwalktypes_h_
#define _cwalktypes_h_

#if _MSC_VER > 1000
	#pragma once
#endif

#include "cwslbbase.h"
#if defined(WIN32)
	#include <tchar.h>
#elif defined(_CWALK_IS_LINUX)
	#include <errno.h>
	#include <unistd.h>
	#include <netinet/in.h>
	#include <pthread.h>
	#include <time.h>
	#include <sys/types.h>
	#include <sys/time.h>
	#include <sys/times.h>
#endif
#include "cwalkbasetypes.h"
#if defined(__cplusplus)
	#include <string>
	/* 提醒使用修正stl版本 */
	#if defined(_CWALK_IS_VC6)
		#include <list>
		#include <xtree>
		#if !defined(THREAD_SAFED_STD_BASIC_STRING_FOR_VC6) \
			|| !defined(BUG_FIXED_STD_LIST_FOR_VC6) \
			|| !defined(BUG_FIXED_STD_BASE_TREE_FOR_VC6) \
			|| !defined(OPTIMIZED_STD_BASE_TREE_FOR_VC6)
			#error "请拷贝 vc6_patch\VC98\Include\* 到VC6系统include目录覆盖之"
			#error "请拷贝 vc6_patch\VC98\Lib\* 到VC6系统lib目录覆盖之，然后rebuild all"
		#endif
	#endif

	#if defined(_CWALK_IS_VC2010)
		#include <list>
		#include <xtree>
		#if !defined(BUG_FIXED_STD_LIST_FOR_VC2010) \
			|| !defined(BUG_FIXED_STD_XTREE_FOR_VC2010)
			#error "请拷贝 vc2010_patch\Include\* 到VC2010系统include目录覆盖之，然后rebuild all"
		#endif
	#endif

	#define empty_string		string()
#endif

#if !defined(_T)
	#if defined(_UNICODE) || defined(UNICODE)
		#define _T(s)			L ## s
	#else
		#define _T(s)			s
	#endif
#endif

/* SOCKET相关 */
#ifndef INVALID_SOCKET
	#define INVALID_SOCKET		-1
#endif
#ifndef SOCKET_ERROR
	#define SOCKET_ERROR		-1
#endif

#undef INADDR_NONE
#define INADDR_NONE				(DWORD)0xffffffff

#undef INADDR_ANY
#define INADDR_ANY				(DWORD)0x00000000

#undef ADDR_ANY
#define ADDR_ANY				INADDR_ANY

#undef INADDR_LOOPBACK
#define INADDR_LOOPBACK			(DWORD)0x7f000001

#define INADDR_LOOPBACK_NET		htonl(INADDR_LOOPBACK)

#undef INADDR_BROADCAST
#define INADDR_BROADCAST		(DWORD)0xffffffff

/* bool SockValid(SOCKET sock); */
#define SockValid(sock)			((INT_PTR)(sock) >= 0)

/* bool FDValid(FD_TYPE fd); */
#define FDValid(fd)				((INT_PTR)(fd) >= 0)

/* 离散SOCKET读写结构类型 */
struct SockReadBuf
{
	void* buf;
	INT_PTR len;
};
struct SockWriteBuf
{
	const void* data;
	INT_PTR len;
};
#ifndef __cplusplus
	typedef struct SockReadBuf SockReadBuf;
	typedef struct SockWriteBuf SockWriteBuf;
#endif

typedef DWORD COLORREF;
#ifndef RGB
	#define RGB(r,g,b)			((COLORREF)(((BYTE)(r) | ((WORD)((BYTE)(g))<<8)) | (((DWORD)(BYTE)(b))<<16)))
#endif

#if defined(WIN32)
	/* tlhelp32.h里用到了MAX_PATH，先包含它 */
	#include <tlhelp32.h>
#endif

#if defined(MAX_PATH)
	#undef MAX_PATH
#endif
#define MAX_PATH	512
typedef char PathNameA[MAX_PATH];
typedef WCHAR PathNameW[MAX_PATH];
typedef TCHAR PathName[MAX_PATH];

/* 描述时间毫秒数(64位)，没有时区之分，即没有系统时间和本地时间的区分 */
/* 绝对时间：[MIN_UTC_MSEL, MAX_UTC_MSEL] */
/* 相对时间：[-MAX_UTC_MSEL, MAX_UTC_MSEL] */
typedef INT64 LTMSEL;

/* 最小UTC LTMSEL时间，GMT: 1970/01/01 00:00:00; BEIJING: 1970/01/01 08:00:00 */
#define MIN_UTC_MSEL			((LTMSEL)0)
/* 最大UTC LTMSEL时间，GMT: 2038/01/18 16:00:00; BEIJING: 2038/01/19 00:00:00 */
#define MAX_UTC_MSEL			((LTMSEL)0x7fff6200 * 1000)

/* 非法UTC LTMSEL时间 */
#define INVALID_UTC_MSEL		((LTMSEL)-1)

#if defined(WIN32)
	typedef HANDLE			OSThread;
#elif defined(_CWALK_IS_LINUX)
	typedef pthread_t		OSThread;
#endif
#ifndef OSTHREADID_DEFINED
	#define OSTHREADID_DEFINED
	#if defined(WIN32)
		typedef DWORD		OSThreadID;
	#elif defined(_CWALK_IS_LINUX)
		typedef pthread_t	OSThreadID;
	#endif
#endif
typedef void*				OSThreadRealID;

#define INVALID_OSTHREAD			((OSThread)0)
#define INVALID_OSTHREADID			((OSThreadID)0)
#define INVALID_OSTHREAD_REAL_ID	((OSThreadRealID)0)

#if defined(_MSC_VER)
	#pragma warning(disable: 4201)	/* nonstandard extension used : nameless struct/union */
#endif

/* 线程ID联合类型，用于调试辅助 */
struct DebugTID
{
	union
	{
	OSThreadID id;
	void* id_hex;	/* 调试时，在调试器中总显示为16进制 */
	INT_PTR id_int;	/* 调试时，在调试器中总显示为有符号数 */
	};
#ifdef __cplusplus
	bool operator< (const DebugTID& r) const
		{	return this->id < r.id;	}
	DebugTID() : id_int(0) {}
	DebugTID(OSThreadID i) : id_int(0) { id = i; }
#endif
};

typedef IF_WIN32_(DWORD, int)		OSProcessID;

/* 注：必须和INVALID_OSTHREADID相等，在'PIDT.h'中需要统一处理它们， */
/*     WIN32的idle线程ID也被当做无效PID */
#define INVALID_OSPROCESSID			((OSProcessID)0)

typedef IF_WIN32_(HANDLE, int)		OSPollHandle;	/* 参考class COSPoll */
#define INVALID_OSPOLL_HANDLE		IF_WIN32_(((OSPollHandle)NULL), ((OSPollHandle)-1))
#define OSPollHandleValid(hd)		IF_WIN32_((INVALID_OSPOLL_HANDLE!=(hd)), ((hd)>=0))

#ifdef __cplusplus
	#define CHAR_TYPE_static		template<typename CHAR_TYPE> static
	#define CHAR_TYPE_inline		CHAR_TYPE_static inline
	#define XCHAR_TYPE				CHAR_TYPE
#else
	#define CHAR_TYPE_inline		inline
	#define XCHAR_TYPE				TCHAR
#endif

#ifdef __cplusplus
	struct NullClass {};
#endif

/* 向上规整，如果v为指针的使用方法 p2 = (void*)AlignTo((UINT)p, (UINT)align) */
#define ALIGN_TO(v, align)			(((v) + (align)-1) / (align) * (align))
#ifdef __cplusplus
	template<typename TYPE, typename T2>
	inline TYPE AlignTo(TYPE v, T2 align)
		{	/*ASSERT(v >= 0 && align > 0);*/ return ALIGN_TO(v, align);	}
#endif

/* 向下规整 */
#define ALIGN_BACK(v, align)		((v) / (align) * (align))
#ifdef __cplusplus
	template<typename TYPE, typename T2>
	inline TYPE AlignBack(TYPE v, T2 align)
		{	/*ASSERT(v >= 0 && align > 0);*/ return ALIGN_BACK(v, align);	}
#endif

/* DWORD MAKEFOURCC(ch0, ch1, ch2, ch3); */
#undef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)		\
		((DWORD)(BYTE)(ch0)					\
		| ((DWORD)(BYTE)(ch1) << 8)			\
		| ((DWORD)(BYTE)(ch2) << 16)		\
		| ((DWORD)(BYTE)(ch3) << 24))

/* 字序环境判断 */
BOOL IsSmallEndian();

void MakeTU32(BYTE* dataPtr, DWORD v);
DWORD GetTU32(const BYTE* dataPtr);

/* 得到调用此函数的线程ID */
/* 注意：linux环境需要长时间记录一个线程的ID，最好用OSThreadRealID() */
OSThreadID OSThreadSelf();

/* 得到真实线程ID，linux下的线程OSThreadSelf()可能并不是真实ID */
OSThreadRealID OSThreadIDToRealID(OSThreadID id);

#if defined(WIN32)
	struct WindowsModuleVersion
	{
		WORD major;
		WORD minor;
		WORD hotfix;
		WORD other;
	};
	#ifndef __cplusplus
		typedef struct WindowsModuleVersion WindowsModuleVersion;
	#endif
	/* 获取Windows进程模块版本信息 */
	#ifdef __cplusplus
		BOOL GetWindowsProcessModuleVersion(IN const char* filename, OUT WindowsModuleVersion* ver);
		BOOL GetWindowsProcessModuleVersion(IN const WCHAR* filename, OUT WindowsModuleVersion* ver);
	#else
		BOOL GetWindowsProcessModuleVersion(IN LPCTSTR filename, OUT WindowsModuleVersion* ver);
	#endif

	/* 获取Windows版本信息 */
	enum WindowsVersion
	{
		Invalid_WinVer = -1,
		Unknown_WinVer = 0,
		Win32s,
		Windows_95_98,
		Windows_NT,
		Windows_2000,
		Windows_XP,
		Windows_Longhorn,
		Windows_Vista,
		Windows_7,
		Windows_8,
		Windows_9,
		Windows_10,
	};
	#ifndef __cplusplus
		typedef enum WindowsVersion WindowsVersion;
	#endif
	WindowsVersion GetWindowsVersion();
	const char* GetWindowsVersionText();
#endif

#if defined(_CWALK_IS_LINUX)
	/* Linux平台获取绝对时间的原始实现, 建议总使用GetMsel() */
	LTMSEL LinuxGetMsel();

	/* Linux平台获取GetTickCount的原始实现, 建议总使用GetTickCount() */
	DWORD LinuxGetTickCount();

	/* 与Windows的Sleep()完全等价, 建议总使用Sleep() */
	void LinuxSleep(DWORD ms);
#endif

/* 获取当前编译器名 */
const char* GetCompilerName();

/* 获取当前模块的编译器二进制类型 */
const char* GetCompileBinaryType();

#if defined(WIN32)
	/* 获取控制窗口句柄，失败返回NULL */
	HWND GetConsoleWindow_();
#endif

/* 判断当前进程是否为控制台类型程序 */
BOOL IsConsoleApplication();

#if defined(WIN32)
	/* 判断当前进程是否处于被调试状态 */
	BOOL IsByDebugging();
#endif

#ifdef __cplusplus
	/// 线程池任务基类
	struct CWALKBaseTask
	{
		CWALKBaseTask* m_nextPoolTask; ///< 连接到下一个任务，线程池需要，见"taskpool.h"
		virtual ~CWALKBaseTask() {}
		/// 线程池调度到这个任务时执行
		virtual void OnPoolTask() = 0;
	};

	/// 基础timer相关类型
	struct OSTimerID__ { void* dummy; };
	typedef OSTimerID__* CWALKTimerID;
	typedef void (*CWALKTimerCallback)(void* param, CWALKTimerID id);
#endif /* #ifdef __cplusplus */

#if defined(_MSC_VER) && (32==cwslb_SYS_BITS && !defined(GetWindowLongPtr))
	#define GetWindowLongPtrA		GetWindowLongA
	#define GetWindowLongPtrW		GetWindowLongW
	#define GetWindowLongPtr		IF_UNICODE_(GetWindowLongPtrW, GetWindowLongPtrA)

	#define SetWindowLongPtrA		SetWindowLongA
	#define SetWindowLongPtrW		SetWindowLongW
	#define SetWindowLongPtr		IF_UNICODE_(SetWindowLongPtrW, SetWindowLongPtrA)
#endif

#ifndef EXTERN_C
	#ifdef __cplusplus
		#define EXTERN_C	extern "C"
	#else
		#define EXTERN_C	extern
	#endif
#endif

#ifdef __cplusplus
	struct IXAllocator
	{
		virtual ~IXAllocator() {}
		virtual void* Alloc(INT_PTR si) = 0;
		virtual void Free(void* p) = 0;
	};
#endif

/* 基本内存分配函数指针类型 */
typedef void* (*XAllocFN)(INT_PTR bytes);
typedef void (*XFreeFN)(void* ptr);

#if defined(_MSC_VER)
	#pragma warning(disable: 4201)	/* nonstandard extension used : nameless struct/union */
#endif

/* 基本内存分配器，可以用分配器对象更改内存池
 * 注意：不需要自定义内存分配时，建议总用"cwalk_allocator.h"里的
 *       struct sys_allocator_traits，以利于编译器优化
 */
struct XAllocator
{
#ifdef __cplusplus
	union
	{
		IXAllocator* xa_;
		struct
		{
			XAllocFN fnAlloc_;
			XFreeFN fnFree_;
		};
	};

	XAllocator()
		: fnAlloc_(NULL), fnFree_(NULL)
		{}
	XAllocator(XAllocFN fAlloc, XFreeFN fFree) // fAlloc, fFree都必须指定
		: fnAlloc_(fAlloc), fnFree_(fFree)
		{}
	explicit XAllocator(IXAllocator* xa)
		: fnAlloc_((XAllocFN)xa), fnFree_(NULL)
		{}

	void* Alloc(INT_PTR si)
		{	return (fnAlloc_&&fnFree_ ? fnAlloc_(si) : (xa_ ? xa_->Alloc(si) : ::malloc(si)));	}
	void Free(void* p)
		{	(fnAlloc_&&fnFree_ ? fnFree_(p) : (xa_ ? xa_->Free(p) : ::free(p)));	}

	bool operator== (const XAllocator& r) const
		{	return (this->fnAlloc_==r.fnAlloc_ && this->fnFree_==r.fnFree_);	}
	bool operator!= (const XAllocator& r) const
		{	return (this->fnAlloc_!=r.fnAlloc_ || this->fnFree_!=r.fnFree_);	}
#else
	union
	{
		XAllocFN fnAlloc_;
		XAllocFN Alloc;
	};
	union
	{
		XFreeFN fnFree_;
		XFreeFN Free;
	};
#endif
};
#ifndef __cplusplus
	typedef struct XAllocator XAllocator;
#endif

/* 依附类型: 供XArray、XBinary、XString等类使用 */
enum XAttachType
{
	xat_hold,	/* 把指针完全给对象管理，注意内存分配器的一致性 */
	xat_attach,	/* 临时附着，在任何内容更改之前，或析构之前，必须调用Drop()，否则触发assert错误 */
	xat_bind,	/* 临时附着，不负责管理传入的指针 */
};
#ifndef __cplusplus
	typedef enum XAttachType XAttachType;
#endif

#ifdef __cplusplus
	template<typename CHAR_TYPE, int chars /*= 32*/>
	struct StackTempCharBuf_ { CHAR_TYPE ch[chars]; };
#endif

/* tstring */
#ifdef __cplusplus
	#if defined(_UNICODE) || defined(UNICODE)
		#ifndef NO_WSTRING
			typedef std::wstring tstring;
		#endif
	#else
		typedef std::string tstring;
	#endif
	#define empty_tstring	tstring()
#endif

/* struct IPP */
#if defined(_MSC_VER)
	#pragma warning(disable: 4201)	/* nonstandard extension used : nameless struct/union */
#endif
#pragma pack(push, 1)
/* 用于统一记录IP和port，方便统一使用、管理、调试 */
struct IPP
{
	union
	{
		struct
		{
			union
			{
				DWORD ip_; /* 如果不作特别说明，ip_使用网络字节序 */
				struct
				{
					BYTE bip0_, bip1_, bip2_, bip3_;
				};
			};
			union
			{
				INT32 port_; /* 如果不作特别说明，port_使用本地字节序 */
				BYTE bport_[sizeof(INT32)/sizeof(BYTE)];
			};
		};
		INT64 i64_;
	};

#ifdef __cplusplus
	IPP() : ip_(INADDR_NONE), port_(-1) {}
	IPP(DWORD ip, int port) : ip_(ip), port_((INT32)port) {}

	IPP(const char* ippStr, int default_port); /* 实现见"ipcvt.cpp" */
	IPP(const WCHAR* ippStr, int default_port);

	bool IsValid() const
		{	return INADDR_NONE!=ip_ && port_>=0;	}

	bool operator< (const IPP& r) const
		{	return i64_ < r.i64_;	}
	bool operator<= (const IPP& r) const
		{	return i64_ <= r.i64_;	}
	bool operator> (const IPP& r) const
		{	return i64_ > r.i64_;	}
	bool operator>= (const IPP& r) const
		{	return i64_ >= r.i64_;	}
	bool operator== (const IPP& r) const
		{	return i64_ == r.i64_;	}
	bool operator!= (const IPP& r) const
		{	return i64_ != r.i64_;	}
#endif	/* #ifdef __cplusplus */
};
#pragma pack(pop)

#ifndef __cplusplus
	typedef struct IPP IPP;
#endif

#if defined(_MSC_VER)
	static INT64 volatile s_INVALID_IPP_ = -1;
	#define INVALID_IPP		(*(const IPP*)&s_INVALID_IPP_)
#else
	union IPP_union_
	{
		INT64 volatile* pi64;
		IPP volatile* pipp;
	};
	static INT64 volatile s_INVALID_IPP_ = -1;
	static union IPP_union_ const s_IPP_union_ = {&s_INVALID_IPP_};
	#define INVALID_IPP		(*(const IPP*)(s_IPP_union_.pipp))
#endif

/* YUV420帧 */
struct YuvFrame
{
	const BYTE* y;
	const BYTE* u;
	const BYTE* v;
	void* alignDummy; /* 结构体对齐占位成员 */
	INT32 w;
	INT32 h;
	INT32 stride_y;
	INT32 stride_uv;
/*
#ifdef __cplusplus
	YuvFrame()
	{
		y = u = v = NULL;
		alignDummy = NULL;
		w = h = stride_y = stride_uv = 0;
	}
#endif*/
};

/* 使用OS_FILENAME_MATCH_CASE以解决平台路径名大小写区分差异 */
#define OS_FILENAME_MATCH_CASE		IF_WIN32_(false, true)

/* 默认trim字符集 */
#define STRDK_TRIM_CHARS_A			"\x20\r\n\t"
#define STRDK_TRIM_CHARS_W			L"\x20\r\n\t"
#define STRDK_TRIM_CHARS			_T("\x20\r\n\t")

/* 默认路径保留字符集 */
#define PATH_FILE_INVALID_CHARS_A	"<>:|/\\\""
#define PATH_FILE_INVALID_CHARS_W	L"<>:|/\\\""
#define PATH_FILE_INVALID_CHARS		_T("<>:|/\\\"")

#define IF_STR_A(cond, cstr)		((cond) ? (cstr) : "")
#define IF_STR_W(cond, cstr)		((cond) ? (cstr) : L"")
#define IF_STR(cond, cstr)			((cond) ? (cstr) : _T(""))

/* 全局名字检查（文件名、Windows命名互斥、命名信号量、命名事件、命名页面映射、文件名等等） */
#ifdef __cplusplus
	BOOL OSGlobalNameCheck(const char* name);
	BOOL OSGlobalNameCheck(const WCHAR* name);
#else
	BOOL OSGlobalNameCheck(LPCTSTR name);
#endif


/* 静态ASSERT（编译期ASSERT）
 * STATIC_ASSERT(const_exp)，const_exp==0时会导致编译失败
 * 例如: STATIC_ASSERT(sizeof(int) == sizeof(long)); */
#if defined(__cplusplus) && defined(_CWALK_IS_LINUX)
	namespace npt
	{
		template<bool TYPE> struct StaticAssertFailed_;
		template<> struct StaticAssertFailed_<true> {};
	}
  #if defined(IOS6)
	#define STATIC_ASSERT(const_exp) /* iOS平台如何待实现... */
  #else
	#define STATIC_ASSERT(const_exp) npt::StaticAssertFailed_< !!(const_exp) > ()
  #endif
#else
	#if defined(ACMELIB_COMPILER_IS_GCC) || defined(ACMELIB_COMPILER_IS_INTEL)
		#define STATIC_ASSERT(const_exp)  \
			{ typedef int ai[(const_exp) ? 1 : -1];	}
	#else
		#define STATIC_ASSERT(const_exp)  \
			{ typedef int ai[(const_exp) ? 1 : 0];	}
	#endif
#endif

#ifdef __cplusplus
	/* 判断两个类型是否为相同类型
	 * 判断是否相同类型
	 * bool IS_SAME_TYPE(T1, T2); */
	namespace npt
	{
	#if defined(_CWALK_IS_VC6)
		template<typename T1, typename T2>
		class IsSameType
		{
			template<typename> struct In
				{ enum { is = false }; };

			template<>	struct In<T1>
				{ enum { is = true }; };
		public:
			enum { is = In<T2>::is };
		};
	#else
		template<typename T1, typename T2>
		struct IsSameType
			{ enum { is = false }; };
		template<typename TYPE>
		struct IsSameType<TYPE, TYPE>
			{ enum { is = true }; };
	#endif
	}
	#define IS_SAME_TYPE(T1, T2)	(!!npt::IsSameType<T1, T2 >::is)
#endif

/* 判断类型TYPE是否可以自动转化为类型T_TARGET『包括TYPE = T_TARGET』
 * bool CAN_CONVERT(TYPE, T_TARGET);『编译期常量』
 * 注：VC和gcc4.0及以上版本支持 class TypeConvertibleCheck_; */
#if defined(__cplusplus) && (defined(_MSC_VER) || (defined(_CWALK_IS_LINUX) && (__GNUC__ >= 4)))
	namespace npt
	{
		template<typename TYPE, typename T_TARGET>
		class TypeConvertibleCheck_
		{
			typedef char Small;
			typedef short Big;
			static Big Test(...);
			static Small Test(T_TARGET);
			static TYPE MakeT();
		public:
			/* 使用MakeT()相比于TYPE()，保证了当TYPE没有默认构造函数时也能使用 */
			enum { can = (sizeof(Small) == sizeof(Test(MakeT()))) };
		};
	}
	#define CAN_CONVERT(TYPE, T_TARGET)	(!!npt::TypeConvertibleCheck_<TYPE, T_TARGET >::can)
#endif

/* C++ POD(plain-old-data)类型约束、判断、声明相关支持
 * C++ 简单类型类型判断、声明相关支持（简单类型定义见'CWALKIntelligentArray.h'） */
#ifdef __cplusplus
	/* POD类型编译约束
	 * void MUST_BE_POD_TYPE(TYPE);
	 * void MUST_BE_POD_OBJ(TYPE obj); */
	namespace npt
	{
		typedef const volatile void* const_volatile_void_ptr;
		template<typename TYPE>
		struct PodTypeConstraint_
		{
			static inline void constraints()
			{
				union POD_check_union
				{
					TYPE T_is_not_POD_type;
				};
			}
		};
	}
	#define MUST_BE_POD_TYPE(TYPE)		npt::PodTypeConstraint_<TYPE >::constraints();
	template<typename TYPE>
	inline void MUST_BE_POD_OBJ(const TYPE&) { MUST_BE_POD_TYPE(TYPE); }

	/* POD类型判断
	 * bool IS_POD_TYPE(TYPE); */
	namespace npt
	{
#if defined(_MSC_VER) && _MSC_VER<=1200 /* <=VC6 */
		template<typename TYPE>
		struct PodTypeCheck_
			{ enum { is = CAN_CONVERT(TYPE, npt::const_volatile_void_ptr) }; };
#else
		typedef char pod_one;
		typedef char pod_two[2];

		template<typename TYPE>
			pod_one pod_test_func(int TYPE::*);
		template<typename TYPE>
			pod_two& pod_test_func(...);

		template<typename TYPE>
		struct PodTypeCheck_
		{
			enum
			{
				is =
	#ifdef CWALK_IS_POD_TYPE_
					CWALK_IS_POD_TYPE_(TYPE) ||
	#endif
					sizeof(npt::pod_test_func<TYPE>(0)) != sizeof(pod_one)
			};
		};
#endif
	}
	#define IS_POD_TYPE(TYPE)	(!!npt::PodTypeCheck_<TYPE >::is)

	/* 判断是否为简单类型
	 * bool IS_SIMPLE_TYPE(TYPE); */
	namespace npt
	{
		template<typename TYPE>
		struct SimpleTypeCheck_
			{ enum { is = IS_POD_TYPE(TYPE) }; };
	}
	#define IS_SIMPLE_TYPE(TYPE)	(!!npt::SimpleTypeCheck_<TYPE >::is)

	/* 明确声明类型TYPE为POD类型
	 * EXPLICIT_POD_TYPE(TYPE)
	 * 例：
			struct Stru
			{
				int n;
				Stru()
				{
				}
			};
			EXPLICIT_POD_TYPE(Stru)
	 */
	#define EXPLICIT_POD_TYPE(TYPE)					\
		namespace npt								\
		{											\
			template<> struct PodTypeCheck_<TYPE >	\
				{ enum { is = 1 }; };				\
		}

	/* 明确声明类型TYPE为非POD简单类型
	 * EXPLICIT_NPOD_SIMPLE_TYPE(TYPE)
	 * 注：因为POD类型一定是简单类型，无须特别声明
	 *     所以此宏要求TYPE一定是非POD类型
	 * 例：
			struct Stru
			{
				int n;
				Stru()
				{
				}
			};
			EXPLICIT_NPOD_SIMPLE_TYPE(Stru)
	 */
	#define EXPLICIT_NPOD_SIMPLE_TYPE(TYPE)				\
		namespace npt									\
		{												\
			template<> struct PodTypeCheck_<TYPE >		\
				{ enum { is = 0 }; };					\
			template<> struct SimpleTypeCheck_<TYPE >	\
				{ enum { is = 1 }; };					\
		}

	/* 对一些常见的编译器无法自动判断的类型做明确声明 */
	#if defined(_MSC_VER) && _MSC_VER<=1200 /* <=VC6 */
		#define EXPLICIT_POD_TYPE_VC6__(TYPE)	\
			EXPLICIT_POD_TYPE(TYPE)				\
			EXPLICIT_POD_TYPE(unsigned TYPE)
		EXPLICIT_POD_TYPE_VC6__(char)
		EXPLICIT_POD_TYPE_VC6__(short)
		EXPLICIT_POD_TYPE_VC6__(long)
		EXPLICIT_POD_TYPE_VC6__(int)
		EXPLICIT_POD_TYPE_VC6__(__int8)
		EXPLICIT_POD_TYPE_VC6__(__int16)
		EXPLICIT_POD_TYPE_VC6__(__int32)
		EXPLICIT_POD_TYPE_VC6__(__int64)
		#undef EXPLICIT_POD_TYPE_VC6__
		EXPLICIT_POD_TYPE(float)
		EXPLICIT_POD_TYPE(double)
		EXPLICIT_POD_TYPE(long double)
		EXPLICIT_POD_TYPE(bool)
	#endif

	EXPLICIT_NPOD_SIMPLE_TYPE(std::string)
	#ifndef NO_WSTRING
		EXPLICIT_NPOD_SIMPLE_TYPE(std::wstring)
	#endif

	#if defined(__AFX_H__)
		#if defined(_MSC_VER) && (_MSC_VER >= 1500) /* >= VC2008 */
			EXPLICIT_NPOD_SIMPLE_TYPE(CStringA)
			#ifndef NO_WSTRING
				EXPLICIT_NPOD_SIMPLE_TYPE(CStringW)
			#endif
		#else
			EXPLICIT_NPOD_SIMPLE_TYPE(CString)
		#endif
	#endif

	#if defined(__AFXWIN_H__)
		EXPLICIT_POD_TYPE(CRect)
		EXPLICIT_POD_TYPE(CPoint)
		EXPLICIT_POD_TYPE(CSize)
	#endif

	EXPLICIT_POD_TYPE(IPP)

	/*-------------------------------------------------------------------------*/
	/* 整数类型判断 */
	namespace npt
	{
		template<typename TYPE> struct IsIntType	{ enum { is = false }; };
		#define special_IsIntType(TYPE)		\
				template<> struct IsIntType<TYPE >	{ enum { is = true }; }
		special_IsIntType(char);
		special_IsIntType(BYTE);
		special_IsIntType(short);
		special_IsIntType(WORD);
		special_IsIntType(long);
		special_IsIntType(DWORD);
		special_IsIntType(int);
	#if (64!=cwslb_SYS_BITS || !defined(_CWALK_IS_LINUX))
		special_IsIntType(UINT);
	#endif
		special_IsIntType(INT64);
		special_IsIntType(UINT64);
		#undef special_IsIntType
	}
	/* bool IS_INT_TYPE(TYPE);『编译期常量』 */
	#define IS_INT_TYPE(TYPE)				(!!npt::IsIntType<TYPE >::is)

	/*-------------------------------------------------------------------------*/
	/* 浮点数类型判断 */
	namespace npt
	{
		template<typename TYPE> struct IsFloatType	{ enum { is = false }; };
		template<> struct IsFloatType<float>		{ enum { is = true }; };
		template<> struct IsFloatType<double>		{ enum { is = true }; };
		template<> struct IsFloatType<long double>	{ enum { is = true }; };
	}
	/* bool IS_FLOAT_TYPE(TYPE);『编译期常量』 */
	#define IS_FLOAT_TYPE(TYPE)			(!!npt::IsFloatType<TYPE >::is)

	/*-------------------------------------------------------------------------*/
	/* bool类型判断 */
	namespace npt
	{
		template<typename TYPE> struct IsBoolType	{ enum { is = false }; };
		template<> struct IsBoolType<bool>			{ enum { is = true }; };
	}
	/* bool IS_BOOL_TYPE(TYPE);『编译期常量』 */
	#define IS_BOOL_TYPE(TYPE)				(!!npt::IsBoolType<TYPE >::is)

	/*-------------------------------------------------------------------------*/
	/* 类型TYPE的符号类型判断 */
	namespace npt
	{
		template<typename TYPE> struct IsSignedType { enum { is = ((TYPE)((TYPE)0 - 1) < 0) }; };
	}
	/* bool IS_SIGNED_TYPE(TYPE);『编译期常量』 */
	#define IS_SIGNED_TYPE(TYPE)			(!!npt::IsSignedType<TYPE>::is)

	/*-------------------------------------------------------------------------*/
	/* 指针类型转换 */
	namespace npt
	{
		template<typename T1, typename T2>
		struct PtrCast
		{
			union TCast
			{
				T1 p1;
				T2 p2;
			};
			TCast site;
			explicit PtrCast(T1 p)
			{
				STATIC_ASSERT(CAN_CONVERT(T1, npt::const_volatile_void_ptr));
				STATIC_ASSERT(CAN_CONVERT(T2, npt::const_volatile_void_ptr));
				STATIC_ASSERT(sizeof(T1) == sizeof(T2));
				site.p1 = p;
			}
		};
		template<typename T1, typename T2>
		inline T2 PtrCastF(T1 p1, T2 /*p2*/)
			{	return PtrCast<T1, T2>(p1).site.p2;	}
	}

	// 例：
	// char ch[sizeof(int)];
	// char* pc = ch;
	// int* p = PTR_CAST(pc, int*);
	// p = PTR_CAST2(pc, p);
	#define PTR_CAST(p, d_ptr_type)		npt::PtrCastF((p), (d_ptr_type)0)
	#define PTR_CAST2(p, d_ptr_dummy)	npt::PtrCastF((p), (d_ptr_dummy))

#endif	/* #ifdef __cplusplus */

#ifdef __cplusplus
	/* 字符串对象统一访问类策略 */
	template<typename STRING>
	struct StrUniTraits_
	{
		enum { is_string = 0, };
	};

	template<typename STRING>
	struct STD_StrUniTraits_
	{
		enum
		{
			is_string = 1,
			is_zero_terminal = 1,
		};
		typedef typename STRING::value_type CharT;
		static inline const CharT* Ptr(const STRING& str)
			{	return str.c_str();	}
		static inline int Len(const STRING& str)
			{	return (int)str.length();	}
		static inline void AssignChars(STRING& str, CharT ch, INT_PTR count)
			{	str.assign(count, ch);	}
		static inline void AssignString(STRING& str, const CharT* rstr, INT_PTR len /*= -1*/)
		{
			if(len < 0)
				str = rstr;
			else
				str.assign(rstr, len);
		}
	};
	template<> struct StrUniTraits_<std::string> : public STD_StrUniTraits_<std::string> {};
	#ifndef NO_WSTRING
		template<> struct StrUniTraits_<std::wstring> : public STD_StrUniTraits_<std::wstring> {};
	#endif
#endif	/* #ifdef __cplusplus */

#ifdef __cplusplus
	/// 整数流水序列号生成器
	template<typename LockBase /*= CLocker, CNullLocker...*/,
			typename IntType /*= INT32, INT64, INT_PTR ...*/
			>
	class IntSerialKeyGenerater : private LockBase
	{
	private:
		IntSerialKeyGenerater(const IntSerialKeyGenerater&);
		IntSerialKeyGenerater& operator= (const IntSerialKeyGenerater&);

		IntType nextKey_;

	public:
		explicit IntSerialKeyGenerater(DWORD spinCount = 0)
			: LockBase(spinCount)
			, nextKey_(1)
			{}

		// 获取下一个流水序列号（不包括0，0一般可作为无效流水序列号用）
		IntType GetNext()
		{
			this->LockBase::Lock();
			IntType key = nextKey_;
			++nextKey_;
			if(0 == nextKey_)
				nextKey_ = 1;
			this->LockBase::Unlock();
			return key;
		}
	};
#endif


/* 单链表支持（双链表函数模板见'cwalklist.h'） */
typedef struct SLListNode__ {
	struct SLListNode__* next;
} SLListNode;
typedef struct SLList__ {
	SLListNode* head;
} SLList;

/* 初始化单链表 */
void SLListInit(SLList* sl);

/* 在单链表头部插入节点，并返回旧的头结点指针 */
SLListNode* SLListPush(SLList* sl, SLListNode* newNode);

/* 删除单链表的头结点，并返回此结点指针 */
SLListNode* SLListPop(SLList* sl);


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++ 内联函数实现 ++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

union endian_check_union_
{
	WORD w;
	BYTE ch[2];
};

inline BOOL IsSmallEndian()
{
	union endian_check_union_ check;
	check.w = 0x1234;
	return (0x34 == check.ch[0]);
}

inline void MakeTU32(BYTE* dataPtr, DWORD v)
{
	BYTE* vp = (BYTE*)&v;
	if(IsSmallEndian())
	{
		dataPtr[0] = vp[0];
		dataPtr[1] = vp[1];
		dataPtr[2] = vp[2];
		dataPtr[3] = vp[3];
	}
	else
	{
		dataPtr[0] = vp[3];
		dataPtr[1] = vp[2];
		dataPtr[2] = vp[1];
		dataPtr[3] = vp[0];
	}
}

inline DWORD GetTU32(const BYTE* dataPtr)
{
	DWORD v=0;
	BYTE* vp = (BYTE*)&v;
	if(IsSmallEndian())
	{
		vp[0] = dataPtr[0];
		vp[1] = dataPtr[1];
		vp[2] = dataPtr[2];
		vp[3] = dataPtr[3];
	}
	else
	{
		vp[0] = dataPtr[3];
		vp[1] = dataPtr[2];
		vp[2] = dataPtr[1];
		vp[3] = dataPtr[0];
	}
	return v;
}

inline OSThreadID OSThreadSelf()
	{	return IF_WIN32_(GetCurrentThreadId(), pthread_self());	}

inline OSThreadRealID OSThreadIDToRealID(OSThreadID id)
{
#if defined(_CWALK_IS_LINUX)
	#if __GNUC__>=4 && 32==cwslb_SYS_BITS
		return (OSThreadRealID)((DWORD*)id)[18];
	#else
		return (OSThreadRealID)id;
	#endif
#else
	return (OSThreadRealID)(INT_PTR)id;
#endif
}

#if defined(WIN32)
	#ifdef __cplusplus
		static inline HMODULE GetModuleHandle_Traits_(const char* filename)
			{	return GetModuleHandleA(filename);	}
		static inline HMODULE GetModuleHandle_Traits_(const WCHAR* filename)
			{	return GetModuleHandleW(filename);	}
		static inline DWORD GetModuleFileName_Traits_(HMODULE mod, char* filename, DWORD size)
			{	return GetModuleFileNameA(mod, filename, size);	}
		static inline DWORD GetModuleFileName_Traits_(HMODULE mod, WCHAR* filename, DWORD size)
			{	return GetModuleFileNameW(mod, filename, size);	}
		static inline DWORD GetFileVersionInfoSize_Traits_(const char* filename, LPDWORD dwHD)
			{	return GetFileVersionInfoSizeA((char*)filename, dwHD);	}
		static inline DWORD GetFileVersionInfoSize_Traits_(const WCHAR* filename, LPDWORD dwHD)
			{	return GetFileVersionInfoSizeW((WCHAR*)filename, dwHD);	}
		static inline BOOL GetFileVersionInfo_Traits_(const char* filename, DWORD hd, DWORD len, LPVOID data)
			{	return GetFileVersionInfoA((char*)filename, hd, len, data);	}
		static inline BOOL GetFileVersionInfo_Traits_(const WCHAR* filename, DWORD hd, DWORD len, LPVOID data)
			{	return GetFileVersionInfoW((WCHAR*)filename, hd, len, data);	}
	#else
		inline HMODULE GetModuleHandle_Traits_(const TCHAR* filename)
			{	return GetModuleHandle(filename);	}
		inline DWORD GetModuleFileName_Traits_(HMODULE mod, TCHAR* filename, DWORD size)
			{	return GetModuleFileName(mod, filename, size);	}
		inline DWORD GetFileVersionInfoSize_Traits_(const TCHAR* filename, LPDWORD dwHD)
			{	return GetFileVersionInfoSize((TCHAR*)filename, dwHD);	}
		inline BOOL GetFileVersionInfo_Traits_(const TCHAR* filename, DWORD hd, DWORD len, LPVOID data)
			{	return GetFileVersionInfo((TCHAR*)filename, hd, len, data);	}
	#endif

	CHAR_TYPE_inline BOOL GetWindowsProcessModuleVersion_Tmpl_(IN const XCHAR_TYPE* filename, OUT WindowsModuleVersion* ver)
	{
		HMODULE mod = NULL;
		DWORD verSize = 0;
		BYTE* buf = NULL;
		VS_FIXEDFILEINFO* info = NULL;
		UINT infoLen = 0;
		XCHAR_TYPE path[MAX_PATH];

		if(NULL==filename || NULL==ver)
			return false;

		mod = GetModuleHandle_Traits_(filename);
		if(NULL == mod)
			return false;

		memset(path, 0, sizeof(path));
		GetModuleFileName_Traits_(mod, path, MAX_PATH);

		verSize = GetFileVersionInfoSize_Traits_(path, NULL);
		if(0 == verSize)
			return false;

		buf = (BYTE*)malloc(verSize);

		if(!GetFileVersionInfo_Traits_(path, 0, verSize, buf))
		{
			free(buf);
			return false;
		}

		if(!VerQueryValue(buf, _T("\\"), (LPVOID*)&info, &infoLen))
		{
			free(buf);
			return false;
		}

		ver->major = (WORD)((info->dwFileVersionMS >> 16) & 0xffff);
		ver->minor = (WORD)((info->dwFileVersionMS) & 0xffff);
		ver->hotfix = (WORD)((info->dwFileVersionLS >> 16) & 0xffff);
		ver->other = (WORD)((info->dwFileVersionLS) & 0xffff);

		free(buf);
		return true;
	}
	#ifdef __cplusplus
		inline BOOL GetWindowsProcessModuleVersion(IN const char* filename, OUT WindowsModuleVersion* ver)
			{	return GetWindowsProcessModuleVersion_Tmpl_(filename, ver);	}
		inline BOOL GetWindowsProcessModuleVersion(IN const WCHAR* filename, OUT WindowsModuleVersion* ver)
			{	return GetWindowsProcessModuleVersion_Tmpl_(filename, ver);	}
	#else
		inline BOOL GetWindowsProcessModuleVersion(IN const TCHAR* filename, OUT WindowsModuleVersion* ver)
			{	return GetWindowsProcessModuleVersion_Tmpl_(filename, ver);	}
	#endif

	struct OSVERSIONINFOEXW__
	{
		DWORD dwOSVersionInfoSize;
		DWORD dwMajorVersion;
		DWORD dwMinorVersion;
		DWORD dwBuildNumber;
		DWORD dwPlatformId;
		WCHAR szCSDVersion[128]; /* Maintenance string for PSS usage */
		WORD  wServicePackMajor;
		WORD  wServicePackMinor;
		WORD  wSuiteMask;
		BYTE  wProductType;
		BYTE  wReserved;
	};
	#ifndef __cplusplus
		typedef struct OSVERSIONINFOEXW__ OSVERSIONINFOEXW__;
	#endif
	inline BOOL RtlGetVersion__(OSVERSIONINFOEXW__* ver)
	{
		typedef LONG (NTAPI* FNRtlGetVersion)(OSVERSIONINFOEXW__* ver);
		static FNRtlGetVersion fn = NULL;
		LONG ret;

		if(NULL == ver)
			return false;
		memset(ver, 0, sizeof(*ver));
		ver->dwOSVersionInfoSize = sizeof(*ver);
		if(NULL == fn)
		{
			fn = (FNRtlGetVersion)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "RtlGetVersion");
			if(NULL == fn)
				return false;
		}
		ret = fn(ver);
		return 0==ret;
	}

	inline WindowsVersion GetWindowsVersion()
	{
		static WindowsVersion sWinVer = Invalid_WinVer;
		if(Invalid_WinVer != sWinVer)
			return sWinVer;

	#if defined(_WINBASE_)
		{
			DWORD ver;
			OSVERSIONINFOEX osvi;
			osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
			if(!GetVersionEx((OSVERSIONINFO*)&osvi))
			{
				osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
				if(!GetVersionEx((OSVERSIONINFO*)&osvi))
					return (sWinVer=Unknown_WinVer);
			}

		#if defined(_MSC_VER) && (_MSC_VER >= 1500) /* >=VC2008 */
			if(VER_PLATFORM_WIN32_NT == osvi.dwPlatformId)
			{
				if(osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
				{
					if(osvi.wProductType == VER_NT_WORKSTATION)
						return (sWinVer=Windows_Vista);
					else
						return (sWinVer=Windows_Longhorn);
				}
				else if(osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 2)
				{
					OSVERSIONINFOEXW__ verInfo;
					if(!RtlGetVersion__(&verInfo))
						return (sWinVer=Windows_8);
					if(9 == verInfo.dwMajorVersion)
						return (sWinVer=Windows_9);
					else if(10 == verInfo.dwMajorVersion)
						return (sWinVer=Windows_10);
					else
						return (sWinVer=Windows_8);
				}
				else if(osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1)
					return (sWinVer=Windows_7);
				else if(osvi.dwMajorVersion == 5)
				{
					if(osvi.dwMinorVersion == 0)
						return (sWinVer=Windows_2000);
					else
						return (sWinVer=Windows_XP);
				}
				return (sWinVer=Windows_NT);
			}
		#endif

			ver = GetVersion();

			if(ver < 0x80000000)
			{
				if((WORD)ver == 0x0206)
				{
					OSVERSIONINFOEXW__ verInfo;
					if(!RtlGetVersion__(&verInfo))
						return (sWinVer=Windows_8);
					if(9 == verInfo.dwMajorVersion)
						return (sWinVer=Windows_9);
					else if(10 == verInfo.dwMajorVersion)
						return (sWinVer=Windows_10);
					else
						return (sWinVer=Windows_8);
				}
				else if((WORD)ver == 0x0106)
					return (sWinVer=Windows_7);
				else if((WORD)ver == 0x0006)
					return (sWinVer=Windows_Vista); /* 忽略 Windows_Longhorn */
				else if(osvi.dwMajorVersion == 5)
				{
					if(osvi.dwMinorVersion == 0)
						return (sWinVer=Windows_2000);
					else
						return (sWinVer=Windows_XP);
				}
				return (sWinVer=Windows_NT);
			}
			else if((DWORD)(LOBYTE(LOWORD(ver))) < 4)
				return (sWinVer=Win32s);
			else
				return (sWinVer=Windows_95_98);
		}
	#else
		ASSERT(false);
		return (sWinVer=Unknown_WinVer);
	#endif
	}

	inline const char* GetWindowsVersionText()
	{
		WindowsVersion ver = GetWindowsVersion();
		const char* verTexts[] =
		{
			"Unknown_WinVer",
			"Win32s",
			"Windows_95/98",
			"Windows_NT",
			"Windows_2000",
			"Windows_XP",
			"Windows_Longhorn",
			"Windows_Vista",
			"Windows_7",
			"Windows_8",
			"Windows_9",
			"Windows_10",
		};
		if(0<=ver && ver<(int)(sizeof(verTexts)/sizeof(verTexts[0])))
			return verTexts[ver];
		return "Invalid_WinVer";
	}
#endif

#if defined(_CWALK_IS_LINUX)
	inline LTMSEL LinuxGetMsel()
	{
	  #if 0 /*!defined(IOS6)*/
		static int clock_id = 5; /* CLOCK_REALTIME_COARSE */
		struct timespec tp;
		if(0 == clock_gettime(clock_id, &tp))
			return (LTMSEL)tp.tv_sec*1000 + (tp.tv_nsec+(500*1000))/(1000*1000);
		clock_id = CLOCK_REALTIME;
		clock_gettime(clock_id, &tp);
		return (LTMSEL)tp.tv_sec*1000 + (tp.tv_nsec+(500*1000))/(1000*1000);
	  #else
		/* 使用gettimeofday()实现 */
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return (LTMSEL)tv.tv_sec*1000 + (tv.tv_usec+500)/1000;
	  #endif
	}

	/* 得到Linux系统的启动时间，失败返回INVALID_UTC_MSEL（实现见"CWALKTime.cpp"） */
  #ifdef __cplusplus
	extern "C"
  #endif
		LTMSEL GetLinuxBootMsel();

	inline DWORD LinuxGetTickCount()
	{
		/* 使用times()实现，可能精度偏低 */
	#if 0
		static DWORD clocks_sec = 0; /* 操作系统时间片频率（时间片数/每秒） */
		clock_t clocks;
		struct tms dummy;
		if(0 == clocks_sec)
			clocks_sec = sysconf(_SC_CLK_TCK); /* 常见系统版本都为100 */
		clocks = times(&dummy);		/* glibc有bug，不能传NULL */
		if(-1 == clocks)
			clocks = -1 * errno;	/* mips和arms均需要这样，系统bug？？？ */
		if(100 == clocks_sec)
			return (DWORD)(clocks * 10); /* 此情况，精度为10ms */
		else
			return (DWORD)((INT64)clocks * 1000 / clocks_sec);
	#else
		/* 使用gettimeofday()实现，效率稍低，但精度能保证达到1ms */
		LTMSEL lt, ltBoot;
		lt = LinuxGetMsel();
		ltBoot = GetLinuxBootMsel();
		if(INVALID_UTC_MSEL != ltBoot) /* 若无法获取系统启动时间，则忽略 */
			lt -= ltBoot;
		return (DWORD)lt;
	#endif
	}

	inline void LinuxSleep(DWORD ms)
	{
		struct timeval tv;

		if(0 == ms)
		{
	#if !defined(_CWALK_IS_MIPS_ARM) && !defined(IOS6)
			pthread_yield();
	#endif
			sched_yield();
		}
		else if(INFINITE == ms)
		{
			tv.tv_sec = 1;
			tv.tv_usec = 0;
			while(1)
				select(0, NULL, NULL, NULL, &tv);
		}
		else
		{
			if(ms < 1000)
			{
				tv.tv_sec = 0;
				tv.tv_usec = ms*1000;
			}
			else
			{
				tv.tv_sec = ms/1000;
				tv.tv_usec = (ms%1000)*1000;
			}
			select(0, NULL, NULL, NULL, &tv);
		}
	}
#endif

inline const char* GetCompilerName()
{
	const char* compiler =
#if defined(_CWALK_IS_VC6)
				"VC6"
#elif defined(_CWALK_IS_VC2008)
				"VC2008"
#elif defined(_CWALK_IS_VC2010)
				"VC2010"
#elif defined(_CWALK_IS_VC2012)
				"VC2012"
#elif defined(_CWALK_IS_VC2013)
				"VC2013"
#elif defined(_CWALK_IS_VC2015)
				"VC2015"
#elif defined(_CWALK_IS_LINUX)
	#ifdef _CWALK_IS_MIPS_ARM
				"MIPS_ARM_"
	#endif
				"GCCx.x"
#else
				"UNKNOWN_COMPILER"
#endif
				;

#if defined(_CWALK_IS_LINUX)
	{
		/* 改写为GCC的正确版本号 */
		static int sInited = 0;
		static char ch[32];
		if(0 == sInited)
		{
			int l = (int)strlen(compiler);
			strcpy(ch, compiler);
			ch[l-3] = (char)('0' + __GNUC__);
			ch[l-1] = (char)('0' + __GNUC_MINOR__);
			sInited = 1;
		}
		return ch;
	}
#else
	return compiler;
#endif
}

inline const char* GetCompileBinaryType()
{
	return IF_64BITS_("64Bits", "32Bits")
			IF_UNICODE_("_Unicode", "_Multi-Byte")
			IF_DEBUG_("_Debug", "_Release");
}

#if defined(WIN32)
	inline HWND GetConsoleWindow_()
	{
		static BOOL inited = false;
		static HWND wnd = NULL;
		if(!inited)
		{
			typedef HWND (WINAPI* FNGetConsoleWindow)();
			HMODULE mod = GetModuleHandle(_T("kernel32.dll"));
			FNGetConsoleWindow fnGetConsoleWindow = (FNGetConsoleWindow)GetProcAddress(mod, "GetConsoleWindow");
			if(fnGetConsoleWindow)
				wnd = fnGetConsoleWindow();
			inited = true;
		}
		return wnd;
	}
#endif

inline BOOL IsConsoleApplication()
	{	return IF_WIN32_((NULL!=GetConsoleWindow_()), true);	}

#if defined(WIN32)
	inline BOOL IsByDebugging()
	{
		typedef BOOL (WINAPI* FNIsDebuggerPresent)();
		static FNIsDebuggerPresent fnIsDebuggerPresent = NULL;
		if(NULL == fnIsDebuggerPresent)
		{
			HMODULE mod = GetModuleHandle(_T("kernel32.dll"));
			fnIsDebuggerPresent = (FNIsDebuggerPresent)GetProcAddress(mod, "IsDebuggerPresent");
		}
		return (fnIsDebuggerPresent && fnIsDebuggerPresent());
	}
#endif

	CHAR_TYPE_inline BOOL OSGlobalNameCheck_Tmpl_(const XCHAR_TYPE* name)
	{
		const XCHAR_TYPE* tp = name;
		while(*tp)
		{
			const XCHAR_TYPE* pc = (sizeof(char) == sizeof(XCHAR_TYPE)
								? (const XCHAR_TYPE*)PATH_FILE_INVALID_CHARS_A
								: (const XCHAR_TYPE*)PATH_FILE_INVALID_CHARS_W);
			while(*pc)
			{
				if(*tp == *pc)
					return false; /* 发现非法字符 */
				++pc;
			}
			++tp;
			if(tp-name >= MAX_PATH-32)
				return false;
		}

		return true;
	}
#ifdef __cplusplus
	inline BOOL OSGlobalNameCheck(const char* name)
		{	return OSGlobalNameCheck_Tmpl_(name);	}
	inline BOOL OSGlobalNameCheck(const WCHAR* name)
		{	return OSGlobalNameCheck_Tmpl_(name);	}
#else
	inline BOOL OSGlobalNameCheck(LPCTSTR name)
		{	return OSGlobalNameCheck_Tmpl_(name);	}
#endif

inline void SLListInit(SLList* sl)
	{	sl->head = NULL;	}

inline SLListNode* SLListPush(SLList* sl, SLListNode* newNode)
{
	SLListNode* old_head = sl->head;
	newNode->next = sl->head;
	sl->head = newNode;
	return old_head;
}

inline SLListNode* SLListPop(SLList* sl)
{
	SLListNode* old_head;
	if(NULL == sl->head)
		return NULL;
	old_head = sl->head;
	sl->head = sl->head->next;
	return old_head;
}

#endif /* #ifndef _cwalktypes_h_ */
