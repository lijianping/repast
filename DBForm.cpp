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
 * 说明: 初始化基类
 * 参数:
 *       hdbc    [in] 数据库连接句柄
 * 返回值: 执行成功返回true，否则返回false
 */
bool CDBForm::Initialize(SQLHDBC hdbc)
{
    if (NULL == hdbc)
    {
        MessageBox(NULL, TEXT("连接断开，请先连接数据库！"),
                   TEXT("DBForm"), MB_OK | MB_ICONERROR);
        return false;
    }
    m_hdbc_ = hdbc;
    /* 分配语句句柄 */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc_, &m_hstmt_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        MessageBox(NULL, TEXT("分配数据库语句句柄失败！"),
                   TEXT("DBForm"), MB_OK | MB_ICONERROR);
        return false;
    }
    /* 设置滚动游标 */
    m_return_code_ = SQLSetStmtAttr(m_hstmt_, SQL_ATTR_CURSOR_TYPE,
                                    (SQLPOINTER)SQL_CURSOR_DYNAMIC, 
                                    SQL_IS_INTEGER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        MessageBox (NULL, TEXT("设置数据库滚动游标失败！"),
                    TEXT("DBForm"), MB_OK | MB_ICONERROR);
        return false;
	}
    /*设置并发性*/
    m_return_code_ = SQLSetStmtAttr(m_hstmt_, SQL_ATTR_CONCURRENCY,
                                    (SQLPOINTER)SQL_CONCUR_ROWVER, 
                                    SQL_IS_INTEGER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        MessageBox (NULL, TEXT("设置数据库并发性失败！"),
                    TEXT("DBForm"), MB_OK | MB_ICONERROR);
        return false;
    }
	return true;
}

/*
 * 说明: 判断是否到了记录集的结尾
 * 返回值: 到了结尾返回true，否则返回false
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
 * 说明: 移动到记录集的第一条数据
 * 返回值: 执行成功返回true,否则返回false。
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
 * 说明: 移动到记录集的下一条数据
 * 返回值: 执行成功返回true,否则返回false。
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
 * 说明: 移动到记录集的上一条数据
 * 返回值: 执行成功返回true,否则返回false。
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
 * 说明: 移动到记录集的最后一条数据
 * 返回值: 执行成功返回true,否则返回false。
 */
bool CDBForm::MoveLast()
{
	m_return_code_ = SQLFetchScroll(m_hstmt_, SQL_FETCH_LAST,0);
	return true;
}

/*
 * 说明: 移动到记录集的最后一条数据
 * 返回值: 执行成功返回true，否则返回false
 */
bool CDBForm::GetRecordSet()
{
    /* 执行查询语句 */
    m_return_code_ = SQLExecDirect(m_hstmt_,
                                   (unsigned char*)m_query_sql_.c_str(),
                                   SQL_NTS);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        MessageBox(NULL, TEXT("执行数据库查询语句失败！"),
                   TEXT("DBForm"), MB_OK| MB_ICONERROR);
        return false;
    }
    /* 绑定参数 */
    BindingParameter(); 
    return true;
}

/*
 * 说明: 绑定记录集参数，该函数用于子类完成具体操作。
 * 返回值: 执行成功返回true, 否则返回false
 */
bool CDBForm::BindingParameter()
{
    MessageBox(NULL, TEXT("数据库表基类记录集绑定参数函数！"),
               TEXT("提示"), MB_OK | MB_ICONINFORMATION);
	return true;
}

/*
 * 说明: 执行数据库结构化查询语句
 * 参数:
 *       sql_statement [in]  结构化查询语句
 * 返回值: 执行成功返回true,否则返回false。
 */
bool CDBForm::ExecuteSQL(char *sql_statement)
{
    /* 执行语句 */
    m_return_code_ = SQLExecDirect(m_hstmt_, 
                                   (unsigned char *)sql_statement,
                                   SQL_NTS);
    if ((m_return_code_ != SQL_SUCCESS) && 
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        MessageBox(NULL, TEXT("执行数据库操作语句失败！"),
                   TEXT("错误"), MB_OK| MB_ICONERROR);
		return false;
    }
    return true;
}

/*
 * 说明: 报告错误信息
 **/
bool CDBForm::ReportError(SQLHSTMT &hstmt, int handle_type, char *alert)
{
    unsigned char *sql_state = new unsigned char[6];
    if (NULL == sql_state)
    {
        MessageBox(NULL, TEXT("报告错误发生的原因是，分配sqlstate内存失败"),
                   TEXT("错误"), MB_OK | MB_ICONERROR);
		return false;
    }
    char message[500] = "\0";
    short message_length(0);
    char error_info[100] = "\0";
    SQLGetDiagRec(handle_type, hstmt, 1, sql_state, NULL,
                  (unsigned char *)message, 500, &message_length);
    sprintf(error_info, "%s, %s", alert, message);
    MessageBox(NULL, error_info, TEXT("执行SQL时发生错误"),
               MB_OK | MB_ICONERROR);
    delete [] sql_state;
    sql_state = NULL;
    return true;
}