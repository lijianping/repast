// DBForm.cpp: implementation of the CDBForm class.
//
//////////////////////////////////////////////////////////////////////

#include "DBForm.h"
#include <STDIO.H>   /* use sprintf function */
#include <ASSERT.H>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBForm::CDBForm()
	: m_henv_(SQL_NULL_HENV),
      m_hdbc_(SQL_NULL_HDBC),
	  m_hstmt_(SQL_NULL_HSTMT),
	  m_sql_pro_ret(SQL_NTS),
	  m_pro_ret(0),
	  m_return_code_(0)
{
	std::string error;
	assert(true == this->Connect("repast", "repast", "repast", error));
}

CDBForm::CDBForm(std::string dns, std::string name, std::string password)
	: m_hdbc_(SQL_NULL_HDBC),
      m_hstmt_(SQL_NULL_HSTMT),
	  m_return_code_(NULL)
{
	std::string error;
	assert(true == this->Connect(dns.c_str(), name.c_str(), password.c_str(), error));
}

CDBForm::~CDBForm()
{
	this->Disconnect();
}

/*
 * 说明：分配语句句柄
 * 返回值：分配成功返回true,否则返回false
 **/
bool CDBForm::SQLAllocHandleStmt(std::string &error_info)
{
	std::string error;
	if (NULL != m_hstmt_)
	{
		SQLFreeStmt(m_hstmt_, SQL_UNBIND);/*释放绑定*/
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt_);
		m_hstmt_ = NULL;
	}
	/* 分配语句句柄 */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc_, &m_hstmt_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "分配数据库语句句柄失败！";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }

	/* 设置游标属性：用行版本控制乐观并发设置动态游标类型 */
    m_return_code_ = SQLSetStmtAttr(m_hstmt_, SQL_ATTR_CURSOR_TYPE,
		(SQLPOINTER)SQL_CURSOR_DYNAMIC, 
		SQL_IS_INTEGER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "设置数据库滚动游标失败！";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
	}
    m_return_code_ = SQLSetStmtAttr(m_hstmt_, SQL_ATTR_CONCURRENCY,
		(SQLPOINTER)SQL_CONCUR_ROWVER, 
		SQL_IS_INTEGER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "设置数据库滚动游标失败！";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
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
	std::string error;
	m_return_code_ = SQLFetchScroll(m_hstmt_, SQL_FETCH_FIRST, 0);
	if ((m_return_code_ == SQL_ERROR) ||
        (m_return_code_ == SQL_INVALID_HANDLE))
    {
		error = "获取第一条记录出错：";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
		MessageBox(NULL, error.c_str(), TEXT("错误"), MB_OK|MB_ICONERROR);
		return false;
	}
	return true;
}

/*
 * 说明: 移动到记录集的下一条数据
 * 返回值: 执行成功返回true,否则返回false。
 */
bool CDBForm::MoveNext()
{
	std::string error;
	m_return_code_ = SQLFetchScroll(m_hstmt_, SQL_FETCH_NEXT,0);
	if ((m_return_code_ == SQL_ERROR) ||
        (m_return_code_ == SQL_INVALID_HANDLE))
    {
		error = "获取下一条记录出错：";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
		MessageBox(NULL, error.c_str(), TEXT("错误"), MB_OK|MB_ICONERROR);
		return false;
	}
	return true;
}

/*
 * 说明: 移动到记录集的上一条数据
 * 返回值: 执行成功返回true,否则返回false。
 */
bool CDBForm::MovePrior()
{
	std::string error;
    m_return_code_ = SQLFetchScroll(m_hstmt_, SQL_FETCH_PRIOR, 0);
	if ((m_return_code_ == SQL_ERROR) ||
        (m_return_code_ == SQL_INVALID_HANDLE))
    {
		error = "获取上一条记录出错：";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
		MessageBox(NULL, error.c_str(), TEXT("错误"), MB_OK|MB_ICONERROR);
		return false;
	}
	return true;
}

/*
 * 说明: 移动到记录集的最后一条数据
 * 返回值: 执行成功返回true,否则返回false。
 */
bool CDBForm::MoveLast()
{
	std::string error;
	m_return_code_ = SQLFetchScroll(m_hstmt_, SQL_FETCH_LAST,0);
	if ((m_return_code_ == SQL_ERROR) ||
        (m_return_code_ == SQL_INVALID_HANDLE))
    {
		error = "获取最后一条记录出错：";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
    	MessageBox(NULL, error.c_str(), TEXT("错误"), MB_OK|MB_ICONERROR);
		return false;
	}
	return true;
}

/*
 * 说明: 移动到记录集的最后一条数据
 * 返回值: 执行成功返回true，否则返回false
 */
bool CDBForm::GetRecordSet()
{
	std::string error_info;
	/*分配语句句柄*/
    if (false == SQLAllocHandleStmt(error_info))
	{
		return false;
	}
    /* 执行查询语句 */
    m_return_code_ = SQLExecDirect(m_hstmt_,
                                   (unsigned char*)m_query_sql_.c_str(),
                                   SQL_NTS);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        MessageBox(NULL, error_info.c_str(),
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
 * 说明: 
 *       绑定记录集参数,用于获取存储过程返回值,该函数用于子类完成具体操作
 * 参数：
 *       is_add       [in]  标志是否是添加员工功能的参数绑定函数：是为true,否则为false
 *       error_info   [out] 获取错误信息
 * 返回值: 
 *       执行成功返回true, 否则返回false
 */
bool CDBForm::BindingParameter(bool is_out, std::string error)
{
    MessageBox(NULL, TEXT("数据库表基类记录集绑定参数函数！用于获取返回值"),
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
	/*分配语句句柄*/
    if (false == SQLAllocHandleStmt(error_info))
	{
		return false;
	}
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
	sql_state = 0;
	
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
//     /*just for test*/
	char tmp[200]="\0";
	sprintf(tmp, "%s, %ld", sql_state, native_error);
	MessageBox(NULL, tmp, "sql_state, native_error", MB_OK);
	MessageBox(NULL, error_info.c_str(), "error", 0);

// 	/////
    delete [] sql_state;
    sql_state = NULL;
    return true;
}

/*
 * 说明: 设置sql语句
 * 参数:
 *       statement [in] 待执行的sql语句
 **/
void CDBForm::SetSQLStatement(const std::string statement)
{
	m_query_sql_ = statement;
}

bool CDBForm::Connect(const char *dsn, const char *id, 
					  const char *password, std::string &information)
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
	/*设置连接属性（登录超时：5s)*/
    m_return_code_ = SQLSetConnectAttr(m_hdbc_, SQL_ATTR_LOGIN_TIMEOUT, (void *)5, 0);
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
	/*分配语句句柄*/
    if (false == SQLAllocHandleStmt(information))
	{
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



/*
 *  @说明: 获取服务器日期中的部分
 *  @参数：datepart [in] 指明返回日期中的哪一部分
 *          year,month,day,hour,minute,second
 *  @返回值: 若成功日期的部分，否则返回-1
**/
int CDBForm::GetDatePart(char *sql_selectdate)
{
	std::string error;
	/*分配语句句柄*/
    if (false == SQLAllocHandleStmt(error))
	{
		return -1;
	}
	if (false==this->ExecuteSQL(sql_selectdate, error))
	{
		MessageBox(NULL,error.c_str(), TEXT("错误"), MB_OK|MB_ICONINFORMATION);
		return -1;
	}
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_LONG, &m_datepart_, sizeof(m_datepart_), &m_sql_datetime_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		error = "绑定参数出错：";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
		MessageBox(NULL, error.c_str(), TEXT("绑定错误"), MB_OK);
		return -1;
	}
	this->MoveFirst();
	return m_datepart_;
}

char *CDBForm::GetDatePartString(const char *datepart) {
	std::string error;
	/*分配语句句柄*/
    if (false == SQLAllocHandleStmt(error))
	{
		return NULL;
	}
	if (false==this->ExecuteSQL(datepart, error))
	{
		MessageBox(NULL,error.c_str(), TEXT("错误"), MB_OK|MB_ICONINFORMATION);
		return NULL;
	}
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, &m_server_datatime, 
		                        sizeof(m_server_datatime), &m_server_datetime_len_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		error = "绑定参数出错：";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error);
		MessageBox(NULL, error.c_str(), TEXT("绑定错误"), MB_OK);
		return NULL;
	}
	this->MoveFirst();
	return m_server_datatime;
}

/*
 *  @说明: 获取服务器日期中的年份
 *  @返回值: 年份
**/
int CDBForm::GetYear()
{
   return GetDatePart("select DATEPART(year,getdate())");
}

/*
 *  @说明: 获取服务器日期中的月份
 *  @返回值: 月份
**/
int CDBForm::GetMonth()
{
	return GetDatePart("select DATEPART(month,getdate())");
}

/*
 *  @说明: 获取服务器日期中的天日期
 *  @返回值: 天日期
**/
int CDBForm::GetDay()
{
	return GetDatePart("select DATEPART(day,getdate())");
}

/*
 *  @说明: 获取服务器日期中的小时
 *  @返回值: 小时
**/
int CDBForm::GetHour()
{
	return GetDatePart("select DATEPART(hour,getdate())");
}

/*
 *  @说明: 获取服务器日期中的分钟
 *  @返回值: 分钟
**/
int CDBForm::GetMinute()
{
	return GetDatePart("select DATEPART(minute,getdate())");
}
/*
 *  @说明: 获取服务器日期中的秒
 *  @返回值: 秒
**/
int CDBForm::GetSecond()
{
	return GetDatePart("select DATEPART(second,getdate())");
}

/*
 * @ brief: 获取服务器时间-年
 * @ return: 年
 * */
std::string CDBForm::GetYearString() {
	std::string server_year(GetDatePartString("select datename(year, getdate())"));
	return server_year;
}

/*
 * @ brief: 获取服务器时间-月
 * @ return: 月
 * */
std::string CDBForm::GetMonthString() {
	std::string server_month(GetDatePartString("select datename(month, getdate())"));
	if (1 == server_month.length()) {
		server_month = "0" + server_month;
	}
	return server_month;
}

/*
 * @ brief: 获取服务器时间-日
 * @ return: 日
 * */
std::string CDBForm::GetDayString() {
	std::string server_day(GetDatePartString("select datename(day, getdate())"));
	if (1 == server_day.length()) {
		server_day = "0" + server_day;
	}
	return server_day;
}

/*
 * @ brief: 获取服务器时间-时
 * @ return: 时
 * */
std::string CDBForm::GetHourString() {
	std::string server_hour(GetDatePartString("select datename(hour, getdate())"));
	if (1 == server_hour.length()) {
		server_hour = "0" + server_hour;
	}
	return server_hour;
}

/*
 * @ brief: 获取服务器时间-分
 * @ return: 分
 * */
std::string CDBForm::GetMinuteString() {
	std::string server_minute(GetDatePartString("select datename(minute, getdate())"));
	if (1 == server_minute.length()) {
		server_minute = "0" + server_minute;
	}
	return server_minute;
}

/*
 * @ brief: 获取服务器时间-秒
 * @ return: 秒
 * */
std::string CDBForm::GetSecondString() {
	std::string server_second(GetDatePartString("select datename(second, getdate())"));
	if (1 == server_second.length()) {
		server_second = "0" + server_second;
	}
	return server_second;
}

/*
 * 说明：
 *      删除字符串中的空格
 * 参数：
 *      src    [in]  需要删除空格的字符串
 *      des    [out]  删除空格后的字符串
 * 返回值：
 *       void
 */
void CDBForm::DeleteSpace(const char * src, char * des)
{
	while(*src!=' ')
	{
		*des++=*src++;
	}
	*des='\0';
}