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
	m_auto_commit_ = SQL_AUTOCOMMIT_ON;
	std::string error;
	this->Connect("repast", "repast", "repast", error);
}

CDBForm::CDBForm(std::string dns, std::string name, std::string password)
	: m_hdbc_(SQL_NULL_HDBC),
      m_hstmt_(SQL_NULL_HSTMT),
	  m_return_code_(NULL)
{
	std::string error;
	m_auto_commit_ = SQL_AUTOCOMMIT_ON;
	this->Connect(dns.c_str(), name.c_str(), password.c_str(), error);
}

CDBForm::~CDBForm()
{
	this->Disconnect();
}

/*
 * 说明：分配语句句柄
 * 返回值：分配成功返回true,否则返回false
 **/
bool CDBForm::AllocHandleStmt()
{
	std::string error;
	if (NULL != m_hstmt_) {
		SQLFreeStmt(m_hstmt_, SQL_UNBIND);/*释放绑定*/
		FreeStatemetHandle();
	}
	/* 分配语句句柄 */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc_, &m_hstmt_);
    if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(ALLOCATE_STATEMENT_HANDLE_ERROR)
	return true;
}

/*
 * 说明: 判断是否到了记录集的结尾
 * 返回值: 若没有数据返回true，有数据返回false
 */
bool CDBForm::IsEOF()
{
	return FetchData();
}

/*
 * 说明: 移动到记录集的最后一条数据
 * 返回值: 执行成功返回true，否则返回false
 */
bool CDBForm::GetRecordSet()
{
	std::string error_info;
	/*分配语句句柄*/
    if (false == AllocHandleStmt())
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
    if (false == AllocHandleStmt())
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
/*	sql_state = 0;*/
	
	/*获取错误*/
    SQLGetDiagRec(handle_type, hdbc, record_number, sql_state, &native_error,
                  (unsigned char *)message, 500, &message_length);
	switch(native_error)
	{
	case 2627:
		{
		//	LTHROW(INPUT_EXIST_ERROR)
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
 * 说明: 报告错误信息(抛出异常方式)
 **/
bool CDBForm::ReportError(SQLHSTMT &hdbc, int handle_type)
{
	char message[500] = "\0";
	short message_length(0);
	SQLINTEGER native_error = 0;
	SQLSMALLINT record_number = 1;
	unsigned char *sql_state = new unsigned char[6];
	if (NULL == sql_state)
	{
		return false;
	}
	/*	sql_state = 0;*/

	/*获取错误*/
	SQLGetDiagRec(handle_type, hdbc, record_number, sql_state, &native_error,
		(unsigned char *)message, 500, &message_length);
	switch(native_error)
	{
	case 2627:
		{
			LTHROW(INPUT_EXIST_ERROR)
			break;
		}
		/*TODO: Add other error information*/
	default:
		{
			LTHROW(EXEC_SQL_PROC_ERROR)
			break;
		}
	}
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
    if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(ALLOCATE_HANDLE_ERROR)

    /* 设置ODBC版本的环境属性 */
    m_return_code_ = SQLSetEnvAttr(m_henv_, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);
    if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(SET_ODBC_VERSION_ERROR)
    /* 分配连接句柄 */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_DBC, m_henv_, &m_hdbc_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(ALLOCATE_CONNECT_HANDLE_ERROR)
    /* 设置数据库事务提交方式，默认为自动提交方式*/
	m_return_code_ = SQLSetConnectAttr(m_hdbc_, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)m_auto_commit_, SQL_IS_POINTER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "设置数据库手动提交失败！";
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
    if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(CONNECT_ERROR)
    
	/*分配语句句柄*/
    if (false == AllocHandleStmt())
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
 *  说明:
 *      关闭游标，用于在同一个连接上多次执行语句。
 *      执行完一条语句后需要关闭游标，否则可能会出现“无效的游标状态”        
 *  参数：
 *      无
 *  返回值:
 *      成功返回true,失败返回false;
**/
bool CDBForm::CloseCursor()
{
	m_return_code_ = SQLCloseCursor(m_hstmt_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(CLOSE_CURSOR_ERROR)
		return true;
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
    if (false == AllocHandleStmt())
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
	FetchData();
	return m_datepart_;
}

char *CDBForm::GetDatePartString(const char *datepart) {
	std::string error;
	/*分配语句句柄*/
    if (false == AllocHandleStmt())
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
	FetchData();
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
 * @ brief: 删除字符串末尾空格
 * @ param: src [in] 源字符串
 * @ param: des [out] 返回的目标字符串
 */
void CDBForm::DeleteSpace(const char * src, char * des)
{
	int i = 0;
	int len = strlen(src);
	char* buffer = new char[len];
	strncpy(buffer, src, len);
	memset(des, 0, len);
	char *temp = (buffer + len - 1);
	while (*temp-- == ' ') {
		i++;
	}
	strncpy(des, buffer, len - i);
	delete [] buffer;
}


 /*
  * 说明：
  *       设置事务提交方式，默认为自动提交
  * 参数：
  *       is_auto_commit   [in]  ture为自动提交，false为手动提交
  * 返回值：
  *       成功返回true, 否则返回false
  */
bool CDBForm::SetAutoCommit(bool is_auto_commit)
{
	if (true == is_auto_commit)
	{
		m_auto_commit_ = SQL_AUTOCOMMIT_ON;
	}
	else
	{
		m_auto_commit_ = SQL_AUTOCOMMIT_OFF;
	}
	/* 设置数据库事务提交方式，默认为自动提交方式*/
	m_return_code_ = SQLSetConnectAttr(m_hdbc_, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)m_auto_commit_, SQL_IS_POINTER);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		std::string error;
		ReportError(m_hdbc_, SQL_HANDLE_DBC, error);
        return false;
    }
	return true;
}


 /*
  * 说明：
  *       事务提交，用于在程序中控制SQL语句的执行，使用前需要设置事务的提交方式为手动提交
  * 返回值：
  *       成功返回true, 否则返回false
  */
bool CDBForm::Commit()
{
	m_return_code_ = SQLEndTran(SQL_HANDLE_DBC, m_hdbc_, SQL_COMMIT);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		std::string error;
		ReportError(m_hdbc_, SQL_HANDLE_DBC, error);
        return false;
    }
	return true;
}

 /*
  * 说明：
  *       事务回滚，用于在程序中回滚执行的SQL语句，使用前需要设置事务的提交方式为手动提交
  * 返回值：
  *       成功返回true, 否则返回false
  */
bool CDBForm::RollBack()
{
	m_return_code_ = SQLEndTran(SQL_HANDLE_DBC, m_hdbc_, SQL_ROLLBACK);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
		std::string error;
		ReportError(m_hdbc_, SQL_HANDLE_DBC, error);
        return false;
    }
	return true;
}


 /*
  * 说明：
  *      执行需要返回参数的存储过程
  * 参数：
  *      sql_proc [in] 执行的存储过程语句， 形如：“{? = call 存储过程名(?,?.........)}”
  *      error    [out] 记录错误信息
  * 返回值：
  *       成功返回true, 否则返回false
  */
 bool CDBForm::ExecSQLProc(const char * sql_proc, std::string &error)
 {
	// 执行存储过程
	m_return_code_ = SQLExecDirect(m_hstmt_, (unsigned char *)sql_proc, SQL_NTS);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) {
		ReportError(m_hstmt_, SQL_HANDLE_STMT);  
	  //  LTHROW(EXEC_SQL_PROC_ERROR)
	}
 	return true;
 }

 bool CDBForm::ExecSQLProc(const char * sql_proc)
 {
	 // 执行存储过程
	 std::string error;
	 m_return_code_ = SQLExecDirect(m_hstmt_, (unsigned char *)sql_proc, SQL_NTS); 
	 if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
     {
		 ReportError(m_hstmt_,SQL_HANDLE_STMT);//ReportError有抛出异常
		 LTHROW(EXEC_SQL_PROC_ERROR)
			 return false;
	 }
		
		 return true;
 }

 /*
  * 说明：
  *      判断存储过程执行是否成功
         若是存储过程的返回值和其他数据记录集一起返回，
  *      请先取数据记录集里的数据，再调用此函数判断存储过程的执行是否成功
  * 参数：
  *      error    [out] 记录错误信息
  * 返回值：
  *       成功返回true, 否则返回false
  */
bool CDBForm::IsSQLProcRetRight(std::string &error)
{
	while ( ( m_return_code_ = SQLMoreResults(m_hstmt_) ) != SQL_NO_DATA )
	{
	}
	if (0 == m_pro_ret)
	{
		return true;
	}
	else if (2627 == m_pro_ret )
	{
		error="字段重复！请更正为不同的值！";
		return false;
	}
	else
	{
		char ret[10];
		sprintf(ret, "%d",m_pro_ret);
		error="未处理错误：存储过程返回值->";
		error+=ret;
		return false;
	}
	return true;
}

 /*
  * 说明：（换为抛出异常）
  *      判断存储过程执行是否成功
  *      若是存储过程的返回值和其他数据记录集一起返回，
  *      请先取数据记录集里的数据，再调用此函数判断存储过程的执行是否成功
  * 参数：
  *      error    [out] 记录错误信息
  * 返回值：
  *       成功返回true, 否则返回false
  */
bool CDBForm::IsSQLProcRetRight()
{
// 	std::string err_info;
// 	ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);   // HIT: 调试用
	while ( ( m_return_code_ = SQLMoreResults(m_hstmt_) ) != SQL_NO_DATA )
	{
	}
	if (0 == m_pro_ret) {
		return true;
	} else if (2627 == m_pro_ret ) {
		LTHROW(INPUT_EXIST_ERROR)
	} else if (-1 == m_pro_ret) {   // 房间名称重复
		LTHROW(NAME_EXIST_ERROR)
	} else if (-2 == m_pro_ret) {   // 房间下有台号正在使用
		LTHROW(TABLE_IN_ROOM_USER_ERROR)
	} else if (-111 == m_pro_ret)
	{
		LTHROW(OPERATION_REFUSE_ERRORR)//拒绝操作，该项正在被使用，请稍后再试
	}
	else {
		LTHROW(EXEC_SQL_PROC_ERROR)
	}
	return true;
}

/*
 * @ brief: 绑定返回值
 * @ return: 若成功返回true，否则返回false
 *           当执行失败时，可立即通过ReportError函数获取错误信息
 **/
bool CDBForm::BindReturn() {
	m_return_code_ = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT,\
		                              SQL_SMALLINT, 0, 0, &m_pro_ret, 0, &m_sql_pro_ret);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RETURN_ERROR)
	return true;
}

bool CDBForm::FetchData() {
	m_return_code_ = SQLFetch(m_hstmt_);
	if (m_return_code_ == SQL_NO_DATA) {
		return true;
	}else if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(FETCH_ROWSET_ERROR)
	return false;
}

bool CDBForm::FreeStatemetHandle() {
	if (NULL != m_hstmt_) {
		SQLRETURN sql_ret = SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt_);
		if (SQL_SUCCESS != sql_ret && SQL_SUCCESS_WITH_INFO != sql_ret)
			LTHROW(FREE_STATEMENT_HANDLE_ERROR)
		m_hstmt_ = NULL;
	}
	return true;
}

/*
 * @ brief: 数据库备份
 * @ param: file_path [in] 备份文件名称，在sql服务器上,
 *          现固定备份时间为备份文件名，保存在SQL服务器安装目录的BACKUP目录下
 * @ return: 成功返回true
 **/
bool CDBForm::BackUp(const char *file_path) {
	std::string file_name;
	file_name += GetYearString();
	file_name += GetMonthString();
	file_name += GetDayString();
	file_name += GetHourString();
	file_name += GetMinuteString();
	file_name += GetSecondString();
	char backup_statement[1024];
	memset(backup_statement, 0, sizeof(backup_statement));
	sprintf(backup_statement, "backup database repaset to disk = '%s'", file_name.c_str()/*file_path*/);
	std::string err_info;
	if (!ExecuteSQL(backup_statement, err_info))
		LTHROW(BACKUP_DATABASE_ERROR)
	return true;
}

/*
 * @ brief: 数据库恢复
 * @ param: file_path [in] 文件名称
 * @ return: 若成功返回true
 **/
bool CDBForm::Restore(const char *file_path) {
	char restore_statement[1024];
	memset(restore_statement, 0, sizeof(restore_statement));
	sprintf(restore_statement, "restore database repaset from disk = '%s'", file_path);
	std::string err_info;
	if (!ExecuteSQL(restore_statement, err_info))
		LTHROW(RESTORE_DATABASE_ERROR)
	return true;
}



#define MAXBUFLEN 256


/*
 * 说明：
 *     获取更详细的错误信息
 * 参数：
 *     plm_handle_type [in] 句柄类型
 *     plm_handle      [in] 句柄
 *     logstring       [out] 可用于存储错误信息，暂时没有使用
 *     ConnInd         [in] 标志：是否获取具体错误消息
 * 返回值：
 *     无
 */
void CDBForm::ProcessLogMessages(SQLSMALLINT plm_handle_type,
	SQLHANDLE plm_handle,
	char *logstring, int ConnInd)
{
	RETCODE      plm_retcode = SQL_SUCCESS;
	UCHAR      plm_szSqlState[MAXBUFLEN] = "",
		plm_szErrorMsg[MAXBUFLEN] = "";
	SDWORD      plm_pfNativeError = 0L;
	SWORD      plm_pcbErrorMsg = 0;
	SQLSMALLINT   plm_cRecNmbr = 1;
	SDWORD      plm_SS_MsgState = 0, plm_SS_Severity = 0;
	SQLINTEGER   plm_Rownumber = 0;
	USHORT      plm_SS_Line;
	SQLSMALLINT   plm_cbSS_Procname, plm_cbSS_Srvname;
	SQLCHAR      plm_SS_Procname[MAXNAME], plm_SS_Srvname[MAXNAME];


	while (plm_retcode != SQL_NO_DATA_FOUND) {
		plm_retcode = SQLGetDiagRec(plm_handle_type, plm_handle,
			plm_cRecNmbr, plm_szSqlState, &plm_pfNativeError,
			plm_szErrorMsg, MAXBUFLEN - 1, &plm_pcbErrorMsg);

		// Note that if the application has not yet made a
		// successful connection, the SQLGetDiagField
		// information has not yet been cached by ODBC
		// Driver Manager and these calls to SQLGetDiagField
		// will fail.
		if (plm_retcode != SQL_NO_DATA_FOUND) {
			if (ConnInd) {
				plm_retcode = SQLGetDiagField(
					plm_handle_type, plm_handle, plm_cRecNmbr,
					SQL_DIAG_ROW_NUMBER, &plm_Rownumber,
					SQL_IS_INTEGER,
					NULL);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, plm_handle, plm_cRecNmbr,
					SQL_DIAG_SS_LINE, &plm_SS_Line,
					SQL_IS_INTEGER,
					NULL);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, plm_handle, plm_cRecNmbr,
					SQL_DIAG_SS_MSGSTATE, &plm_SS_MsgState,
					SQL_IS_INTEGER,
					NULL);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, plm_handle, plm_cRecNmbr,
					SQL_DIAG_SS_SEVERITY, &plm_SS_Severity,
					SQL_IS_INTEGER,
					NULL);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, plm_handle, plm_cRecNmbr,
					SQL_DIAG_SS_PROCNAME, &plm_SS_Procname,
					sizeof(plm_SS_Procname),
					&plm_cbSS_Procname);
				plm_retcode = SQLGetDiagField(
					plm_handle_type, plm_handle, plm_cRecNmbr,
					SQL_DIAG_SS_SRVNAME, &plm_SS_Srvname,
					sizeof(plm_SS_Srvname),
					&plm_cbSS_Srvname);
			}
			//just for test
			char m1[1024];
			sprintf(m1,"szSqlState = %s\n,pfNativeError = %d\n,szErrorMsg = %s\n,pcbErrorMsg = %d\n",\
				plm_szSqlState,plm_pfNativeError,plm_szErrorMsg,plm_pcbErrorMsg);
			MessageBox(NULL,m1,TEXT("m1"),0);
			if (ConnInd) {
				char m2[1024];
				sprintf(m2,"ODBCRowNumber = %d\n,SSrvrLine = %d\n,SSrvrMsgState = %d\n,\
						   SSrvrSeverity = %d\n,SSrvrProcname = %s\n,SSrvrSrvname = %s\n",\
						   plm_Rownumber, plm_Rownumber,plm_SS_MsgState,\
						   plm_SS_Severity,plm_SS_Procname,plm_SS_Srvname);
				MessageBox(NULL,m2,TEXT("m1"),0);
			}
		}
		plm_cRecNmbr++; //Increment to next diagnostic record.
	} // End while.
}
