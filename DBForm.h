/*
 * file: DBForm.h
 * ˵��: ���ඨ���˳��������ݿ��л�ȡ��Ļ���������
 *       ��Ҫ����������дBindingParameter������
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
    std::string m_query_sql_;  /* SQL��ѯ��� */
    SQLHSTMT m_hstmt_;         /* ����� */
    SQLHDBC m_hdbc_;           /* ���Ӿ�� */
    SQLRETURN m_return_code_;  /* ִ��SQL��䷵���� */
};

#endif /* end #define REPAST_DBFORM_H_ */