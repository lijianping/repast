// Wind.cpp: implementation of the CWind class.
//
//////////////////////////////////////////////////////////////////////

#include "Wind.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWind::CWind() 
    : m_window_processes_((LONG)WindProc),
      m_window_style_(WS_OVERLAPPEDWINDOW),
      m_window_x_(CW_USEDEFAULT),
      m_window_y_(CW_USEDEFAULT),
      m_window_width_(CW_USEDEFAULT),
      m_window_height_(CW_USEDEFAULT),
      m_window_hicon_(LoadIcon(NULL, IDI_APPLICATION)),
      m_window_hmenu_(NULL),
      m_parent_hwnd_(NULL)
{
      memcpy(m_title_, "repast", 256);
}

CWind::CWind(HINSTANCE hinstance) 
    : m_hinstance_(hinstance),
      m_window_processes_((LONG)WindProc),
      m_window_style_(WS_OVERLAPPEDWINDOW),
      m_window_x_(CW_USEDEFAULT),
      m_window_y_(CW_USEDEFAULT),
      m_window_width_(CW_USEDEFAULT),
      m_window_height_(CW_USEDEFAULT),
      m_window_hicon_(LoadIcon(NULL, IDI_APPLICATION)),
      m_window_hmenu_(NULL),
      m_parent_hwnd_(NULL)
{
      memcpy(m_title_, "repast", 256);
}


CWind::~CWind()
{

}

/*
 * @����: �ƽ
 * @����: ���ô�������ʱ����Ϣ
 */
void CWind::SetWindowInfo(HINSTANCE hinstance, TCHAR *sztitle /* = TEXT */,
                          DWORD style /* = WS_OVERLAPPEDWINDOW */,
                          int x /* = CW_USERDEFAULT */, int y /* = CW_USERDEFAULT */,
                          int width /* = CW_USERDEFAULT */, int height /* = CW_USERDEFAULT */,
                          HICON hicon /* = LoadIcon(NULL, IDI_APPLICATION */,
                          HMENU hmenu /* = NULL */, HWND parent_hwnd /* = NULL */)
{
    m_hinstance_ = hinstance;
    memcpy(m_title_, sztitle, 256);
    m_window_style_ = style;
    m_window_x_ = x;
    m_window_y_ = y;
    m_window_width_ = width;
    m_window_height_ = height;
    m_window_hicon_ = hicon;
    m_window_hmenu_ = hmenu;
    m_parent_hwnd_ = parent_hwnd;
}

/*
 * @����: �ƽ
 * @����: ��������
 * @˵��: ��Ҫ�ڴ˺���֮ǰ����set_show_state����������
 *        �����޷�������ʾ
 * @����ֵ: ���ɹ�����true�����򷵻�false
 */
bool CWind::UserCreateWindow()
{
    if (!UserRegisterClass())
    {
        MessageBox(NULL, TEXT("ע�ᴰ��ʧ��!"), TEXT("ERROR"), MB_OK);
        return false;
    }
    m_hwnd_ = CreateWindow(m_title_, m_title_, m_window_style_,
                           m_window_x_, m_window_y_, m_window_width_,
                           m_window_height_, m_parent_hwnd_,
                           m_window_hmenu_, m_hinstance_, NULL);
    if (!m_hwnd_)
    {
        MessageBox(NULL, TEXT("��������ʧ��!"), TEXT("ERROR"), MB_OK);
	      	return false;
    }
    if (!ShowWindow(m_hwnd_, m_show_state_) &&
        !UpdateWindow(m_hwnd_))
    {
        MessageBox(NULL, TEXT("���´���ʧ��!"), TEXT("ERROR"), MB_OK);
        return false;
    }
    return true;
}

/*
 * @����: �ƽ
 * @����˵��: ������Ϣѭ��
 * @����ֵ:
 */
int CWind::MessageLoop()
{
	   while (GetMessage(&m_message_, NULL, 0, 0))
    {
		      TranslateMessage(&m_message_);
		      DispatchMessage(&m_message_);
    }
	   return m_message_.wParam;
}

/*
 * @����: �ƽ
 * @����: ע�ᴰ����
 * @����ֵ:��ע��ɹ�����true�����򷵻�false
 */
bool CWind::UserRegisterClass()
{
    WNDCLASS window_class;
	   window_class.cbClsExtra        =	0;
	   window_class.cbWndExtra		  =	0;
	   window_class.hbrBackground	  =	(HBRUSH)GetStockObject(WHITE_BRUSH);
	   window_class.hCursor		      =	LoadCursor(NULL, IDC_ARROW);
	   window_class.hIcon			  =	m_window_hicon_;
	   window_class.hInstance		  =	m_hinstance_;
   	   window_class.lpfnWndProc	      =	(WNDPROC)m_window_processes_;
	   window_class.lpszClassName	  =	m_title_;
	   window_class.lpszMenuName	  =	NULL;
	   window_class.style			      =	CS_HREDRAW | CS_VREDRAW;
	   if (RegisterClass(&window_class))
    {
		     return true;
	   }
	   return false;
}

/*
 * @����: �ƽ
 * @����: Ĭ�ϵĴ��ڴ�����
 */
LRESULT CALLBACK WindProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
    {
   	case WM_LBUTTONDOWN:
		      MessageBox(hwnd, TEXT("Ĭ�ϴ��ڴ�����"), TEXT("WIND"), MB_OK);
		      return 0;
	   case WM_DESTROY:
		      PostQuitMessage(0);
		      return 0;
	   }
	   return DefWindowProc(hwnd, message, wParam, lParam);
}