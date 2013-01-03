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
 *       information [out] 连接错误信息
 * 返回值: 执行成功返回true，否则返回false
 */
bool CDBForm::Initialize(SQLHDBC hdbc, std::string &information)
{
    if (NULL == hdbc)
    {
        information = "连接断开，请先连接数据库！";
        return false;
    }
    m_hdbc_ = hdbc;
    /* 分配语句句柄 */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc_, &m_hstmt_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "分配数据库语句句柄失败！";
        return false;
    }
    /* 设置滚动游标 */
    m_return_code_ = SQLSetStmtAttr(m_hstmt_, SQL_ATTR_CURSOR_TYPE,
                                    (SQLPOINTER)SQL_CURSOR_DYNAMIC, 
                                    SQL_IS_INTEGER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "设置数据库滚动游标失败！";
        return false;
	}
    /*设置并发性*/
    m_return_code_ = SQLSetStmtAttr(m_hstmt_, SQL_ATTR_CONCURRENCY,
                                    (SQLPOINTER)SQL_CONCUR_ROWVER, 
                                    SQL_IS_INTEGER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "设置数据库并发性失败！";
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
 *
 */
bool CDBForm::ExecuteSQL(const char *sql_statement, std::string &error_info )
{
    /* 执行语句 */
    m_return_code_ = SQLExecDirect(m_hstmt_, 
                                   (unsigned char *)sql_statement,
                                   SQL_NTS);
    if ((m_return_code_ != SQL_SUCCESS) && 
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		error_info = "执行数据库操作语句失败: ";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
		return false;
    }
    return true;
}

/*
 * 说明: 报告错误信息
 **/
bool CDBForm::ReportError(SQLHSTMT &hdbc, int handle_type, std::string &error_info)
{
	char message[500] = "\0";
	short message_length(0);
	SQLINTEGER native_error = 0;
    SQLSMALLINT record_number = 1;
     unsigned char *sql_state = new unsigned char[6];
    if (NULL == sql_state)
    {
		error_info = TEXT("报告错误发生的原因是，分配sqlstate内存失败");
		return false;
    }
	/*获取错误*/
    SQLGetDiagRec(handle_type, hdbc, record_number, sql_state, &native_error,
                  (unsigned char *)message, 500, &message_length);
	switch(native_error)
	{
	case 2627:
		{
			error_info +=  TEXT("不能输入重复的编号");
	    	break;
		}
		/*TODO: Add other error information*/
	default:
		{
			error_info += message;
			break;
		}
	}
    /*just for test*/
	char tmp[200]="\0";
	sprintf(tmp, "%s, %ld", sql_state, native_error);
	MessageBox(NULL, tmp, "sql_state, native_error", MB_OK);
	/////
    delete [] sql_state;
    sql_state = NULL;
    return true;
}

bool CDBForm::Connect(CHAR *dsn, CHAR *id, CHAR *password, std::string &information)
{
	/* 分配环境句柄 */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &m_henv_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "分配环境句柄失败!";
        return false;
    }
    /* 设置ODBC版本的环境属性 */
    m_return_code_ = SQLSetEnvAttr(m_henv_, SQL_ATTR_ODBC_VERSION,
        (void *)SQL_OV_ODBC3, 0);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "设置ODBC版本的环境属性失败!";
        return false;
    }
    /* 分配连接句柄 */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_DBC, m_henv_, &m_hdbc_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		information = "分配连接句柄失败!";
        return false;
    }
	/*设置连接属性（登录超时：10s)*/
    m_return_code_ = SQLSetConnectAttr(m_hdbc_, SQL_ATTR_LOGIN_TIMEOUT, (void *)10, 0);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "设置数据库并发性失败！";
        return false;
    }
    /* 连接数据源 */
    m_return_code_ = SQLConnect(m_hdbc_, (SQLCHAR *)dsn, 
        SQL_NTS,(SQLCHAR *)id, SQL_NTS,
        (SQLCHAR *)password, SQL_NTS);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "连接数据源失败!";
		ReportError(m_hdbc_, SQL_HANDLE_DBC, information);
        return false;
    }
	/* 分配语句句柄 */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc_, &m_hstmt_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "分配数据库语句句柄失败！";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, information);
        return false;
    }
    /* 设置滚动游标 */
    m_return_code_ = SQLSetStmtAttr(m_hstmt_, SQL_ATTR_CURSOR_TYPE,
		(SQLPOINTER)SQL_CURSOR_DYNAMIC, 
		SQL_IS_INTEGER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "设置数据库滚动游标失败！";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, information);
        return false;
	}
    /*设置并发性*/
    m_return_code_ = SQLSetStmtAttr(m_hstmt_, SQL_ATTR_CONCURRENCY,
		(SQLPOINTER)SQL_CONCUR_ROWVER, 
		SQL_IS_INTEGER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "设置数据库并发性失败！";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, information);
        return false;
    }
	m_is_connect_ = true;
    return m_is_connect_;
}


/*
 * 功能: 断开与数据源的连接，释放资源
 **/
void CDBForm::Disconnect()
{
    /*
     * HIT: There has something that we are not 
     *      clear. When you disconnect database,
     *      if has something wrong, you can check
     *      here.
     **/
	if (NULL != m_hstmt_)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt_);
		m_hstmt_ = NULL;
	}
    if (NULL != m_hdbc_)
    {
        SQLDisconnect(m_hdbc_);
        SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc_);
		m_hdbc_ = NULL;
		m_is_connect_ = false;
    }
    if (NULL != m_henv_)
    {
        SQLFreeHandle(SQL_HANDLE_ENV, m_henv_);
		m_henv_ = NULL;
    }
}
