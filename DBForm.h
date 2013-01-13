/*
 * file: DBForm.h
 * 说明: 该类定义了程序在数据库中获取表的基本操作，
 *       需要在子类中重写BindingParameter函数。
 **/

#ifndef REPAST_DBFORM_H_
#define REPAST_DBFORM_H_

#include <WINDOWS.H>
#include <SQLEXT.H>
#include <SQLTYPES.H>
#include <string>

class CDBForm  
{
public:
	bool SQLAllocHandleStmt();
	CDBForm();
	CDBForm(std::string dns, std::string name, std::string password);
	virtual ~CDBForm();
    bool IsEOF();
    bool MoveFirst();
    bool MoveNext();
    bool MovePrior(); 
    bool MoveLast();
    bool GetRecordSet();
    bool ExecuteSQL(const char *sql_statement, std::string &error_info);
    virtual bool BindingParameter();
    bool ReportError(SQLHANDLE &hdbc, int handle_type, std::string &error_info);
	virtual void SetSQLStatement(const std::string statement);
	char* GetDateTime();
	int GetDatePart(char* datepart);
	int GetYear();
	int GetMonth();
	int GetDay();
	int GetHour();
	int GetMinute();
	int GetSecond();

protected:
	inline bool is_connect();
    inline SQLHENV henv() const;
    inline SQLHDBC hdbc() const;
	bool Connect(const char *dsn, const char *id, 
		         const char *password, std::string &information);
    void Disconnect();

protected:
	SQLHENV m_henv_;           /* 环境句柄 */
    SQLHDBC m_hdbc_;           /* 连接句柄 */ 
	SQLHSTMT m_hstmt_;         /* 语句句柄 */
    SQLRETURN m_return_code_;  /* 执行SQL语句返回码 */ 
	bool m_is_connect_;        /* 是否连接数据库，true表示已连上 */
    std::string m_query_sql_;  /* SQL查询语句 */
private:
    char m_datetime_[20];         /* 日期时间 */
	SQLINTEGER m_sql_datetime_;  /**/
	int m_datepart_;
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