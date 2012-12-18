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
	bool Connect(CHAR *dsn, CHAR *id, CHAR *password, std::string &information);
	inline bool is_connect();
    inline SQLHENV henv() const;
    inline SQLHDBC hdbc() const;
    void Disconnect();
	CDBForm();
	virtual ~CDBForm();
    bool Initialize(SQLHDBC hdbc, std::string &information);
    bool IsEOF();
    bool MoveFirst();
    bool MoveNext();
    bool MovePrior(); 
    bool MoveLast();
    bool GetRecordSet();
    bool ExecuteSQL(const char *sql_statement, std::string &error_info);
    virtual bool BindingParameter();
    bool ReportError(SQLHANDLE &hdbc, int handle_type, std::string &error_info);

protected:
	SQLHENV m_henv_;           /* ������� */
    SQLHDBC m_hdbc_;           /* ���Ӿ�� */ 
	SQLHSTMT m_hstmt_;         /* ����� */
    SQLRETURN m_return_code_;  /* ִ��SQL��䷵���� */ 
	bool m_is_connect_;        /* �Ƿ��������ݿ⣬true��ʾ������ */
    std::string m_query_sql_;  /* SQL��ѯ��� */
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