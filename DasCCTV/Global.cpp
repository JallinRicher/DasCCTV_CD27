#include "pch.h"

void CCTV_DEBUGMSG(const char* _format, ...)
{
	va_list args;
	va_start(args, _format);
	int len = _vscprintf(_format, args) + 1;
	char* buffer = new char[len];
	vsprintf_s(buffer, len, _format, args);
	OutputDebugStringA(buffer);
	delete[] buffer;
	va_end(args);
}
