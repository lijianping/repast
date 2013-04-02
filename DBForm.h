/*
 * file: DBForm.h
 * 说明: 该类定义了程序在数据库中获取表的基本操作，
 *       需要在子类中重写BindingParameter函数。
 **/

#ifndef REPAST_DBFORM_H_
#define REPAST_DBFORM_H_

#include "Err.h"
#include <WINDOWS.H>
#include <SQLEXT.H>
#include <SQLTYPES.H>
#include <string>
#include <sql.h>
#include <odbcss.h>



class CDBForm  
{
public:
	bool AllocHandleStmt();
	CDBForm();
	CDBForm(std::string dns, std::string name, std::string password);
	virtual ~CDBForm();
    bool IsEOF();
    bool GetRecordSet();
    bool ExecuteSQL(const char *sql_statement, std::string &error_info);
    virtual bool BindingParameter();
	virtual bool BindingParameter(bool is_out, std::string error);
    bool ReportError(SQLHANDLE &hdbc, int handle_type, std::string &error_info);
	bool CDBForm::ReportError(SQLHSTMT &hdbc, int handle_type);
	virtual void SetSQLStatement(const std::string statement);
	int GetYear();
	std::string GetYearString();
	int GetMonth();
	std::string GetMonthString();
	int GetDay();
	std::string GetDayString();
	int GetHour();
	std::string GetHourString();
	int GetMinute();
	std::string GetMinuteString();
	int GetSecond();
	std::string GetSecondString();
	bool Connect(const char *dsn, const char *id, 
	             const char *password, std::string &information);
    void Disconnect();
	void DeleteSpace(const char * src, char * des);
	bool SetAutoCommit(bool is_auto_commit);
	bool Commit();
	bool RollBack();
	bool ExecSQLProc(const char * sql_proc, std::string &error);
	bool ExecSQLProc(const char * sql_proc);
    bool IsSQLProcRetRight(std::string &error);
	bool IsSQLProcRetRight();
	bool BindReturn();
	bool FetchData();
	bool CloseCursor();
	bool FreeStatemetHandle();
	bool BackUp(const char *file_path);
	bool Restore(const char *file_path);
	void ProcessLogMessages(SQLSMALLINT plm_handle_type,
		SQLHANDLE plm_handle,
		char *logstring, int ConnInd);
	char *GetServerDateTime();


protected:
	inline bool is_connect();
    inline SQLHENV henv() const;
    inline SQLHDBC hdbc() const;
	int GetDatePart(char* datepart);
	char *GetDatePartString(const char *datepart);


protected:
	ULONG m_auto_commit_;      /* 事务自动提交指针*/
	SQLHENV m_henv_;           /* 环境句柄 */
    SQLHDBC m_hdbc_;           /* 连接句柄 */ 
	SQLHSTMT m_hstmt_;         /* 语句句柄 */
    SQLRETURN m_return_code_;  /* 执行SQL语句返回码 */ 
	bool m_is_connect_;        /* 是否连接数据库，true表示已连上 */
    std::string m_query_sql_;  /* SQL查询语句 */
	SQLINTEGER m_sql_pro_ret;     /* the return of procedure in database*/
	short m_pro_ret;              /* the return of procedure*/
private:
    char m_datetime_[20];         /* 日期时间 */
	SQLINTEGER m_sql_datetime_;  /**/
	int m_datepart_;
	char m_server_datatime[32];
	SQLINTEGER m_server_datetime_len_;
};

/*
 * 功能: 获取数据库连接状态
 * 返回值: 返回当前数据库连接状态
 **/
bool CDBForm::is_connect()
{
    return m_is_connect_;
}

/*
 * 功能: 获取数据源环境句柄
 * 返回值: 返回数据源环境句柄
 **/
SQLHENV CDBForm::henv() const
{
    return m_henv_;
}

/*
 * 功能: 获取数据源连接句柄
 * 返回值: 返回数据源连接句柄
 **/
SQLHDBC CDBForm::hdbc() const
{
    return m_hdbc_;
}
#endif /* end #define REPAST_DBFORM_H_ */