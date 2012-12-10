// DBConnect.cpp: implementation of the CDBConnect class.
//
//////////////////////////////////////////////////////////////////////

#include "DBConnect.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBConnect::CDBConnect()
{

}

CDBConnect::~CDBConnect()
{

}

/*
 * ����: ��������Դ
 * ����:
 *            dsn [in] ����Դ����
 *             id [in] �����û���¼��
 *       password [in] ���ݿ��û�����
 *        string  [out] ����ʧ�ܴ���ԭ��
 * ����ֵ: �������ݿ�����״̬�������ӷ���true�����򷵻�false��
 **/
bool CDBConnect::Connect(CHAR *dsn, CHAR *id, CHAR *password, std::string &information)
{
    /* ���价����� */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &m_henv_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "���价�����ʧ��!";
        return false;
    }
    /* ����ODBC�汾�Ļ������� */
    m_return_code_ = SQLSetEnvAttr(m_henv_, SQL_ATTR_ODBC_VERSION,
        (void *)SQL_OV_ODBC3, 0);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "����ODBC�汾�Ļ�������ʧ��!";
        return false;
    }
    /* �������Ӿ�� */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_DBC, m_henv_, &m_hdbc_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
       information = "�������Ӿ��ʧ��!";
        return false;
    }
    /* ��������Դ */
    /* ���ԣ�������ʧ�ܣ����������ݿ���� */
    m_return_code_ = SQLConnect(m_hdbc_, (SQLCHAR *)dsn, 
        SQL_NTS,(SQLCHAR *)id, SQL_NTS,
        (SQLCHAR *)password, SQL_NTS);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "��������Դʧ��!";
        return false;
    }
    m_is_connect_ = true;
    return m_is_connect_;
}

/*
 * ����: �Ͽ�������Դ�����ӣ��ͷ���Դ
 **/
void CDBConnect::Disconnect()
{
    /*
     * HIT: There has something that we are not 
     *      clear. When you disconnect database,
     *      if has something wrong, you can check
     *      here.
     **/
    if (true == m_is_connect_)
    {
        m_is_connect_ = false;
    }
    if (NULL != m_hdbc_)
    {
        SQLDisconnect(m_hdbc_);
        SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc_);
    }
    if (NULL != m_henv_)
    {
        SQLFreeHandle(SQL_HANDLE_ENV, m_henv_);
    }
}