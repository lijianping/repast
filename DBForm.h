/*
 * file: DBForm.h
 * ˵��: ���ඨ���˳��������ݿ��л�ȡ��Ļ���������
 *       ��Ҫ����������дBindingParameter������
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
	bool SQLAllocHandleStmt(std::string &error_info);
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
	virtual bool BindingParameter(bool is_out, std::string error);
    bool ReportError(SQLHANDLE &hdbc, int handle_type, std::string &error_info);
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
	bool ExecuteProc(const char * sql_proc, std::string error);

protected:
	inline bool is_connect();
    inline SQLHENV henv() const;
    inline SQLHDBC hdbc() const;
	int GetDatePart(char* datepart);
	char *GetDatePartString(const char *datepart);

protected:
	ULONG m_auto_commit_;      /* �����Զ��ύָ��*/
	SQLHENV m_henv_;           /* ������� */
    SQLHDBC m_hdbc_;           /* ���Ӿ�� */ 
	SQLHSTMT m_hstmt_;         /* ����� */
    SQLRETURN m_return_code_;  /* ִ��SQL��䷵���� */ 
	bool m_is_connect_;        /* �Ƿ��������ݿ⣬true��ʾ������ */
    std::string m_query_sql_;  /* SQL��ѯ��� */
	SQLINTEGER m_sql_pro_ret;     /* the return of procedure in database*/
	int m_pro_ret;              /* the return of procedure*/
private:
    char m_datetime_[20];         /* ����ʱ�� */
	SQLINTEGER m_sql_datetime_;  /**/
	int m_datepart_;
	char m_server_datatime[32];
	SQLINTEGER m_server_datetime_len_;
};

/*
 * ����: ��ȡ���ݿ�����״̬
 * ����ֵ: ���ص�ǰ���ݿ�����״̬
 **/
bool CDBForm::is_connect()
{
    return m_is_connect_;
}

/*
 * ����: ��ȡ����Դ�������
 * ����ֵ: ��������Դ�������
 **/
SQLHENV CDBForm::henv() const
{
    return m_henv_;
}

/*
 * ����: ��ȡ����Դ���Ӿ��
 * ����ֵ: ��������Դ���Ӿ��
 **/
SQLHDBC CDBForm::hdbc() const
{
    return m_hdbc_;
}
#endif /* end #define REPAST_DBFORM_H_ */