/*
 * 文件: Wind.h
 * 说明: 该文件是关于CWind类的定义，在创建CWind对象时，可通过set_ 系列函数对其初始化，
 *       也可以通过SetWindowInfo函数对其初始化，每个对象都拥有一个缺省的窗口处理过程函数，
 *       通常情况下，该缺省的窗口处理过程函数并不能满足你的需求，你需要在外部重写该函数，
 *       你可以定义一个窗口处理过程函数，在创建CWind实例对象时调用set_window_processes
 *       函数即可实现。此外，你必须显示调用set_show_state函数，以便窗口正常显示。以上
 *       工作都将在你调用UserCreateWindow函数之前完成，紧接着，你需要调用MessageLoop函数
 *       捕获窗口的消息。
 */

#ifndef REPAST_WIND_H_
#define REPAST_WIND_H_
#include <WINDOWS.H>
class CWind {
public:
	CWind();
    CWind(HINSTANCE hinstance);
	virtual ~CWind();
    inline void set_hinstance(const HINSTANCE hinstance);
    inline void set_parent_hwnd(const HWND parent_hwnd);
    inline void set_show_state(const int show_state);
    inline void set_window_processes(LONG window_processes);
    inline void set_window_x(const int window_x);
    inline void set_window_y(const int window_y);
    inline void set_window_width(const int window_width);
    inline void set_window_height(const int window_height);
    inline HWND hwnd() const;
    void SetWindowInfo(HINSTANCE hinstance,                  
                       TCHAR *sztitle = TEXT("REPAST"),
                       DWORD style = WS_OVERLAPPEDWINDOW,
                       int x = CW_USEDEFAULT,
                       int y = CW_USEDEFAULT,
                       int width = CW_USEDEFAULT,
		                     int height = CW_USEDEFAULT,
                       HICON hicon = LoadIcon(NULL, IDI_APPLICATION),
                       HMENU hmenu = NULL,
                       HWND parent_hwnd = NULL);
    bool UserCreateWindow();
    int MessageLoop();
protected:
    bool UserRegisterClass();
    

private:
    HINSTANCE m_hinstance_;           /* 程序实例句柄 */
    HWND m_hwnd_;                     /* 窗口句柄 */
    HWND m_parent_hwnd_;              /* 父窗口句柄 */
    TCHAR m_title_[256];              /* 窗口标题 */
    DWORD m_window_style_;            /* 窗口风格 */
    HICON m_window_hicon_;            /* 窗口图标 */
    HMENU m_window_hmenu_;            /* 窗口菜单句柄 */
    LONG m_window_processes_;         /* 窗口处理过程函数 */
    MSG m_message_;                   /* 窗口消息 */
   	int m_window_x_;                  /* 窗口水平位置 */
    int m_window_y_;                  /* 窗口垂直位置 */
    int m_window_width_;              /* 窗口宽度 */
    int m_window_height_;             /* 窗口高度 */
    int m_show_state_;                /* 窗口显示状态 */
    friend LRESULT CALLBACK WindProc(HWND hwnd, UINT message,
                                     WPARAM wParam, LPARAM lParam);
};

/*
 * @作者: 李建平
 * @功能: 设置窗口实例句柄
 */
void CWind::set_hinstance(const HINSTANCE hInstance)
{
    m_hinstance_ = hInstance; 
}

/*
 * @作者: 李建平
 * @功能: 设置父窗口句柄
 */
void CWind::set_parent_hwnd(const HWND parent_hwnd) 
{
    m_parent_hwnd_ = parent_hwnd;
}

/*
 * @作者: 李建平
 * @功能: 设置窗口显示状态
 */
void CWind::set_show_state(const int show_state)
{
	   m_show_state_ = show_state;
}

/*
 * @作者: 李建平
 * @功能: 设置窗口处理过程函数
 */
void CWind::set_window_processes(LONG window_processes)
{
    m_window_processes_ = window_processes;
}

/*
 * @作者: 李建平
 * @功能: 设置窗口x起点
 */
void CWind::set_window_x(const int window_x)
{
    m_window_x_ = window_x;
}

/*
 * @作者: 李建平
 * @功能: 设置窗口y起点
 */
void CWind::set_window_y(const int window_y)
{
    m_window_y_ = window_y;
}

/*
 * @作者: 李建平
 * @功能: 设置窗口宽度
 */
void CWind::set_window_width(const int window_width)
{
    m_window_width_ = window_width;
}

/*
 * @作者: 李建平
 * @功能: 设置窗口高度
 */
void CWind::set_window_height(const int window_height)
{
    m_window_height_ = window_height;
}

/*
 * @作者: 李建平
 * @功能: 获取窗口句柄
 */
HWND CWind::hwnd() const
{
    return m_hwnd_;
}

#endif /* end #define REPAST_WIND_H_ */
