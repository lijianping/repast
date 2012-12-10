/*
 * �ļ�: Wind.h
 * ˵��: ���ļ��ǹ���CWind��Ķ��壬�ڴ���CWind����ʱ����ͨ��set_ ϵ�к��������ʼ����
 *       Ҳ����ͨ��SetWindowInfo���������ʼ����ÿ������ӵ��һ��ȱʡ�Ĵ��ڴ�����̺�����
 *       ͨ������£���ȱʡ�Ĵ��ڴ�����̺������������������������Ҫ���ⲿ��д�ú�����
 *       ����Զ���һ�����ڴ�����̺������ڴ���CWindʵ������ʱ����set_window_processes
 *       ��������ʵ�֡����⣬�������ʾ����set_show_state�������Ա㴰��������ʾ������
 *       ���������������UserCreateWindow����֮ǰ��ɣ������ţ�����Ҫ����MessageLoop����
 *       ���񴰿ڵ���Ϣ��
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
    HINSTANCE m_hinstance_;           /* ����ʵ����� */
    HWND m_hwnd_;                     /* ���ھ�� */
    HWND m_parent_hwnd_;              /* �����ھ�� */
    TCHAR m_title_[256];              /* ���ڱ��� */
    DWORD m_window_style_;            /* ���ڷ�� */
    HICON m_window_hicon_;            /* ����ͼ�� */
    HMENU m_window_hmenu_;            /* ���ڲ˵���� */
    LONG m_window_processes_;         /* ���ڴ�����̺��� */
    MSG m_message_;                   /* ������Ϣ */
   	int m_window_x_;                  /* ����ˮƽλ�� */
    int m_window_y_;                  /* ���ڴ�ֱλ�� */
    int m_window_width_;              /* ���ڿ�� */
    int m_window_height_;             /* ���ڸ߶� */
    int m_show_state_;                /* ������ʾ״̬ */
    friend LRESULT CALLBACK WindProc(HWND hwnd, UINT message,
                                     WPARAM wParam, LPARAM lParam);
};

/*
 * @����: �ƽ
 * @����: ���ô���ʵ�����
 */
void CWind::set_hinstance(const HINSTANCE hInstance)
{
    m_hinstance_ = hInstance; 
}

/*
 * @����: �ƽ
 * @����: ���ø����ھ��
 */
void CWind::set_parent_hwnd(const HWND parent_hwnd) 
{
    m_parent_hwnd_ = parent_hwnd;
}

/*
 * @����: �ƽ
 * @����: ���ô�����ʾ״̬
 */
void CWind::set_show_state(const int show_state)
{
	   m_show_state_ = show_state;
}

/*
 * @����: �ƽ
 * @����: ���ô��ڴ�����̺���
 */
void CWind::set_window_processes(LONG window_processes)
{
    m_window_processes_ = window_processes;
}

/*
 * @����: �ƽ
 * @����: ���ô���x���
 */
void CWind::set_window_x(const int window_x)
{
    m_window_x_ = window_x;
}

/*
 * @����: �ƽ
 * @����: ���ô���y���
 */
void CWind::set_window_y(const int window_y)
{
    m_window_y_ = window_y;
}

/*
 * @����: �ƽ
 * @����: ���ô��ڿ��
 */
void CWind::set_window_width(const int window_width)
{
    m_window_width_ = window_width;
}

/*
 * @����: �ƽ
 * @����: ���ô��ڸ߶�
 */
void CWind::set_window_height(const int window_height)
{
    m_window_height_ = window_height;
}

/*
 * @����: �ƽ
 * @����: ��ȡ���ھ��
 */
HWND CWind::hwnd() const
{
    return m_hwnd_;
}

#endif /* end #define REPAST_WIND_H_ */
