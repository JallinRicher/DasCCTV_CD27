#include "pch.h"
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
