#include "pch.h"
#include "RandomStuff.h"

using namespace Platform;

RandomStuff::RandomStuff()
{
}


RandomStuff::~RandomStuff()
{
}


Platform::String^ RandomStuff::convertStdString(std::string e) {
	std::wstring widestr = std::wstring(e.begin(), e.end());

	const wchar_t* wchart = widestr.c_str();
	return ref new String(wchart);

}