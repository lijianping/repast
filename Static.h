#ifndef REPAST_STATIC_H_
#define REPAST_STATIC_H_

#include <string>
#include <WINDOWS.H>
#include <COMMCTRL.H>
#pragma comment(lib, "comctl32.lib")

class CStatic  
{
public:
	CStatic();
	virtual ~CStatic();
    bool Create(std::string text, DWORD style,
                const RECT &rect, HWND parent_hwnd,
                UINT id = 0xFFFF);

private:
    UINT m_id_;
    HWND m_hwnd_;
};

#endif /* End #define REPAST_STATIC_H_ */
