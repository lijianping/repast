// DBForm.cpp: implementation of the CDBForm class.
//
//////////////////////////////////////////////////////////////////////

#include "DBForm.h"
#include <STDIO.H>   /* use sprintf function */
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBForm::CDBForm()
    : m_hdbc_(SQL_NULL_HDBC),
      m_hstmt_(SQL_NULL_HSTMT),
      m_return_code_(NULL)
{

}

CDBForm::~CDBForm()
{

}

/*
 * ˵��: ��ʼ������
 * ����:
 *       hdbc    [in] ���ݿ����Ӿ��
 *       information [out] ���Ӵ�����Ϣ
 * ����ֵ: ִ�гɹ�����true�����򷵻�false
 */
bool CDBForm::Initialize(SQLHDBC hdbc, std::string &information)
{
    if (NULL == hdbc)
    {
        information = "���ӶϿ��������������ݿ⣡";
        return false;
    }
    m_hdbc_ = hdbc;
    /* ��������� */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc_, &m_hstmt_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "�������ݿ������ʧ�ܣ�";
        return false;
    }
    /* ���ù����α� */
    m_return_code_ = SQLSetStmtAttr(m_hstmt_, SQL_ATTR_CURSOR_TYPE,
                                    (SQLPOINTER)SQL_CURSOR_DYNAMIC, 
                                    SQL_IS_INTEGER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "�������ݿ�����α�ʧ�ܣ�";
        return false;
	}
    /*���ò�����*/
    m_return_code_ = SQLSetStmtAttr(m_hstmt_, SQL_ATTR_CONCURRENCY,
                                    (SQLPOINTER)SQL_CONCUR_ROWVER, 
                                    SQL_IS_INTEGER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "�������ݿⲢ����ʧ�ܣ�";
        return false;
    }
	return true;
}

/*
 * ˵��: �ж��Ƿ��˼�¼���Ľ�β
 * ����ֵ: ���˽�β����true�����򷵻�false
 */
bool CDBForm::IsEOF()
{
    if (SQL_NO_DATA == m_return_code_)
    {
        return true;
    }
    return false;
}

/*
 * ˵��: �ƶ�����¼���ĵ�һ������
 * ����ֵ: ִ�гɹ�����true,���򷵻�false��
 */
bool CDBForm::MoveFirst()
{
	m_return_code_ = SQLFetchScroll(m_hstmt_, SQL_FETCH_FIRST, 0);
    if (m_return_code_ != SQL_ERROR &&
        m_return_code_ != SQL_INVALID_HANDLE)
    {
        return true;
    }
    return false;
}

/*
 * ˵��: �ƶ�����¼������һ������
 * ����ֵ: ִ�гɹ�����true,���򷵻�false��
 */
bool CDBForm::MoveNext()
{
	m_return_code_ = SQLFetchScroll(m_hstmt_, SQL_FETCH_NEXT,0);
    if (m_return_code_ != SQL_ERROR &&
        m_return_code_ != SQL_INVALID_HANDLE)
    {
        return true;
    }
    return false;
}

/*
 * ˵��: �ƶ�����¼������һ������
 * ����ֵ: ִ�гɹ�����true,���򷵻�false��
 */
bool CDBForm::MovePrior()
{
    m_return_code_ = SQLFetchScroll(m_hstmt_, SQL_FETCH_PRIOR, 0);
    if (m_return_code_ != SQL_ERROR &&
        m_return_code_ != SQL_INVALID_HANDLE)
    {
        return true;
    }
    return false;
}

/*
 * ˵��: �ƶ�����¼�������һ������
 * ����ֵ: ִ�гɹ�����true,���򷵻�false��
 */
bool CDBForm::MoveLast()
{
	m_return_code_ = SQLFetchScroll(m_hstmt_, SQL_FETCH_LAST,0);
	return true;
}

/*
 * ˵��: �ƶ�����¼�������һ������
 * ����ֵ: ִ�гɹ�����true�����򷵻�false
 */
bool CDBForm::GetRecordSet()
{
    /* ִ�в�ѯ��� */
    m_return_code_ = SQLExecDirect(m_hstmt_,
                                   (unsigned char*)m_query_sql_.c_str(),
                                   SQL_NTS);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        MessageBox(NULL, TEXT("ִ�����ݿ��ѯ���ʧ�ܣ�"),
                   TEXT("DBForm"), MB_OK| MB_ICONERROR);
        return false;
    }
    /* �󶨲��� */
    BindingParameter(); 
    return true;
}

/*
 * ˵��: �󶨼�¼���������ú�������������ɾ��������
 * ����ֵ: ִ�гɹ�����true, ���򷵻�false
 */
bool CDBForm::BindingParameter()
{
    MessageBox(NULL, TEXT("���ݿ������¼���󶨲���������"),
               TEXT("��ʾ"), MB_OK | MB_ICONINFORMATION);
	return true;
}

/*
 * ˵��: ִ�����ݿ�ṹ����ѯ���
 * ����:
 *       sql_statement [in]  �ṹ����ѯ���
 * ����ֵ: ִ�гɹ�����true,���򷵻�false��
 */
bool CDBForm::ExecuteSQL(char *sql_statement)
{
    /* ִ����� */
    m_return_code_ = SQLExecDirect(m_hstmt_, 
                                   (unsigned char *)sql_statement,
                                   SQL_NTS);
    if ((m_return_code_ != SQL_SUCCESS) && 
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        MessageBox(NULL, TEXT("ִ�����ݿ�������ʧ�ܣ�"),
                   TEXT("����"), MB_OK| MB_ICONERROR);
		return false;
    }
    return true;
}

/*
 * ˵��: ���������Ϣ
 **/
bool CDBForm::ReportError(SQLHSTMT &hstmt, int handle_type, char *alert)
{
    unsigned char *sql_state = new unsigned char[6];
    if (NULL == sql_state)
    {
        MessageBox(NULL, TEXT("�����������ԭ���ǣ�����sqlstate�ڴ�ʧ��"),
                   TEXT("����"), MB_OK | MB_ICONERROR);
		return false;
    }
    char message[500] = "\0";
    short message_length(0);
    char error_info[100] = "\0";
    SQLGetDiagRec(handle_type, hstmt, 1, sql_state, NULL,
                  (unsigned char *)message, 500, &message_length);
    sprintf(error_info, "%s, %s", alert, message);
    MessageBox(NULL, error_info, TEXT("ִ��SQLʱ��������"),
               MB_OK | MB_ICONERROR);
    delete [] sql_state;
    sql_state = NULL;
    return true;
}