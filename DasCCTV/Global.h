#pragma once

void CCTV_DEBUGMSG(const char* _format, ...);
void CCTV_DEBUGMSG(std::ofstream file, const char* _format, ...);

#ifdef _DEBUG
#define CCTV_DEBUGPRINT(...) CCTV_DEBUGMSG(__VA_ARGS__)
#else
#define CCTV_DEBUGPRINT(file, ...) CCTV_DEBUGMSG(file, __VA_ARGS__)
#endif
