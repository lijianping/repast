#ifndef REPAST_CDBConnect_H_
#define REPAST_CDBConnect_H_
/* ͷ�ļ��İ���˳���Ӱ����� 
 * Ӧ�Ȱ���windows.h�ڰ���
 * SQLϵ��ͷ�ļ�
 */
#include <WINDOWS.H>          
#include <SQLEXT.H>
#include <string>
class CDBConnect  
{
public:
	CDBConnect();
	virtual ~CDBConnect();  
	bool Connect(CHAR *dsn, CHAR *id, CHAR *password, std::string &information);
    inline bool is_connect();
    inline SQLHENV henv() const;
    inline SQLHDBC hdbc() const;
    void Disconnect();

private:
    SQLHENV m_henv_;           /* ������� */
    SQLHDBC m_hdbc_;           /* ���Ӿ�� */
    SQLRETURN m_return_code_;  /* ִ��SQL��䷵���� */
    bool m_is_connect_;        /* �Ƿ��������ݿ⣬true��ʾ������ */
};

/*
 * ����: ��ȡ���ݿ�����״̬
 * ����ֵ: ���ص�ǰ���ݿ�����״̬
 **/
bool CDBConnect::is_connect()
{
    return m_is_connect_;
}

/*
 * ����: ��ȡ����Դ�������
 * ����ֵ: ��������Դ�������
 **/
SQLHENV CDBConnect::henv() const
{
    return m_henv_;
}

/*
 * ����: ��ȡ����Դ���Ӿ��
 * ����ֵ: ��������Դ���Ӿ��
 **/
SQLHDBC CDBConnect::hdbc() const
{
    return m_hdbc_;
}

#endif /* end #define REPAST_CDBConnect_H_ */
