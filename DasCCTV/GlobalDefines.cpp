#include "pch.h"
#include "JSDCCTV.h"
#include "GlobalDefines.h"

void _TypeGateway_::SetData(int DisableEvent, int MaxVod, const CString& Name, const CString& Title)
{
	disableEvent = DisableEvent;
	maxVod = MaxVod;
	name = Name;
	title = Title;
}


void _TypeGateway_::GetData(int& DisableEvent, int& MaxVod, CString& Name, CString& Title) const
{
	DisableEvent = disableEvent;
	MaxVod = maxVod;
	Name = name;
	Title = title;
}


void _TypeDevice_::SetData(const CString& Name, const CString& Title, const CString& Url)
{
	name = Name;
	title = Title;
	url = Url;
}


void _TypeDevice_::GetData(CString& Name, CString& Title, CString& Url) const
{
	Name = name;
	Title = title;
	Url = url;
}


void _TypeCamera_::SetData(const CString& Addr, const CString& Host, const CString& Name, const CString& Path, const CString& Title)
{
	addr = Addr;
	host = Host;
	name = Name;
	path = Path;
	title = Title;
}


void _TypeCamera_::GetData(CString& Addr, CString& Host, CString& Name, CString& Path, CString& Title) const
{
	Addr = addr;
	Host = host;
	Name = name;
	Path = path;
	Title = title;
}


void _TypeMonitor_::SetData(const CString& Name, const CString& Title)
{
	name = Name;
	title = Title;
}


void _TypeMonitor_::GetData(CString& Name, CString& Title) const
{
	Name = name;
	Title = title;
}


void _TypeAudio_::SetData(const CString& Addr, int AudioIn, int AudioOut, const CString& HostUrl, const CString& Name, const CString& Title)
{
	addr = Addr;
	audioin = AudioIn;
	audioout = AudioOut;
	hostUrl = HostUrl;
	name = Name;
	title = Title;
}


void _TypeAudio_::GetData(CString& Addr, int& AudioIn, int& AudioOut, CString& HostUrl, CString& Name, CString& Title) const
{
	Addr = addr;
	AudioIn = audioin;
	AudioOut = audioout;
	HostUrl = hostUrl;
	Name = name;
	Title = title;
}


void _RealStream::ClearAllContent()
{
	realEventHd = nullptr;
	realTransferHd = nullptr;
	realLiveHd = nullptr;
	realPlayerHd = nullptr;
	realZoomHd = nullptr;
	decodInfohd = nullptr;

	isSeverRecoding = FALSE;
	isLocalRecoding = FALSE;

	isStream = FALSE;

	hwnd = nullptr;
	hwndZoom = nullptr;
	simpleName = "";
	name = "";
	title = "";
	path = "";
	level = -1;
	target = "";

	addr = "";
	host = "";

	hItem = nullptr;
	isHWDeocder = FALSE;
	isshow = false;
	isHwDec = FALSE;
}


void CharToWideChar(LPSTR pChar, ULONG ulCharSize, BOOL bIsUTF8, LPCWSTR pWideChar)
{
	LONG lOrigsize = 0;
	LONG lConvertedChars = 0;
	LONG lCodePage = CP_ACP;
	if (NULL == pChar)
	{
		return;
	}

	lOrigsize = (LONG)strlen((CHAR*)pChar);
	if (0 == lOrigsize)
	{
		memset((void*)pWideChar, 0, ulCharSize);
		return;
	}

	if (TRUE == bIsUTF8)
	{
		lCodePage = CP_UTF8;
	}
	else
	{
		lCodePage = CP_ACP;
	}

	lConvertedChars = MultiByteToWideChar(lCodePage, 0, (LPCSTR)pChar, lOrigsize, (LPWSTR)pWideChar, (LONG)ulCharSize - 1);
	if (0 == lConvertedChars)
	{
		return;
	}
}


void WideCharToChar(LPCWSTR pWideChar, ULONG ulCharSize, BOOL bIsUTF8, LPSTR pChar)
{
	LONG lOrigsize = 0;
	LONG lConvertedChars = 0;
	LONG lCodePage = CP_ACP;
	if (NULL == pWideChar)
	{
		return;
	}

	lOrigsize = (LONG)wcslen((WCHAR*)pWideChar);
	if (0 == lOrigsize)
	{
		memset(pChar, 0, ulCharSize + 1);
		return;
	}

	if (TRUE == bIsUTF8)
	{
		lCodePage = CP_UTF8;
	}
	else
	{
		lCodePage = CP_ACP;
	}

	lConvertedChars = WideCharToMultiByte(lCodePage, WC_COMPOSITECHECK | WC_DEFAULTCHAR, (LPCWSTR)pWideChar, lOrigsize, pChar, (LONG)ulCharSize - 1, 0, 0);

	if (0 == lConvertedChars)
	{
		return;
	}
	pChar[lConvertedChars] = '\0';
}


void ConvertUTF8ToUnicode(LPSTR pSrcChar, LPSTR pcDestChar, int length)
{
	WCHAR* pWchar;
	pWchar = (WCHAR*)malloc(length * sizeof(WCHAR));
	if (NULL == pWchar)
	{
		return;
	}
	memset(pWchar, 0, length * sizeof(WCHAR));

	CharToWideChar(pSrcChar, length, TRUE, pWchar);
	WideCharToChar(pWchar, length, FALSE, pcDestChar);
	free(pWchar);
}


void ConvertUnicodeToUTF8(LPSTR pSrcChar, LPSTR pcDestChar, int length)
{
	WCHAR* pWchar;
	pWchar = (WCHAR*)malloc(length * sizeof(WCHAR));
	if (NULL == pWchar)
	{
		return;
	}
	memset(pWchar, 0, length * sizeof(WCHAR));

	CharToWideChar(pSrcChar, length, FALSE, pWchar);
	WideCharToChar(pWchar, length, TRUE, pcDestChar);
	free(pWchar);
}


void ConvertStringToCtime(char* pcStr, CTime* pTime)
{
	int iYear, iMonth, iDay, iHour, iMin, iSec;
	char temp[5] = { 0 };

	strncpy_s(temp, 5, pcStr, 4);
	iYear = atoi(temp);

	memset(temp, 0, 5);
	strncpy_s(temp, 5, pcStr + 5, 2);
	iMonth = atoi(temp);

	memset(temp, 0, 5);
	strncpy_s(temp, 5, pcStr + 8, 2);
	iDay = atoi(temp);

	memset(temp, 0, 5);
	strncpy_s(temp, 5, pcStr + 11, 2);
	iHour = atoi(temp);

	memset(temp, 0, 5);
	strncpy_s(temp, 5, pcStr + 14, 2);
	iMin = atoi(temp);

	memset(temp, 0, 5);
	strncpy_s(temp, 5, pcStr + 17, 2);
	iSec = atoi(temp);

	*pTime = CTime(iYear, iMonth, iDay, iHour, iMin, iSec);
}