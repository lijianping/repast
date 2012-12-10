/*
 * file: DBForm.h
 * 说明: 该类定义了程序在数据库中获取表的基本操作，
 *       需要在子类中重写BindingParameter函数。
 **/

#ifndef REPAST_DBFORM_H_
#define REPAST_DBFORM_H_

#include <WINDOWS.H>
#include <SQLEXT.H>
#include <string>

class CDBForm  
{
public:
	CDBForm();
	virtual ~CDBForm();
    bool Initialize(SQLHDBC hdbc);
    bool IsEOF();
    bool MoveFirst();
    bool MoveNext();
    bool MovePrior(); 
    bool MoveLast();
    bool GetRecordSet();
    bool ExecuteSQL(char *sql_statement);
    virtual bool BindingParameter();
    bool ReportError(SQLHSTMT &hstmt, int handle_type, char *alert);

protected:
    std::string m_query_sql_;  /* SQL查询语句 */
    SQLHSTMT m_hstmt_;         /* 语句句柄 */
    SQLHDBC m_hdbc_;           /* 连接句柄 */
    SQLRETURN m_return_code_;  /* 执行SQL语句返回码 */
};

#endif /* end #define REPAST_DBFORM_H_ */