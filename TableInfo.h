#ifndef REPAST_TABLEINFO_H_
#define REPAST_TABLEINFO_H_
#include "DBForm.h"

class CTableInfo : public CDBForm
{
public:
	CTableInfo();
	virtual ~CTableInfo();
	enum TableStatus {
		kFounding = 0,       /* δ��̨ */
		kNotFounding = 1,    /* �ѿ�̨ */
		kBooked = 2          /* ��Ԥ�� */
	};
	inline char* table_no();
	inline short payable_num();
	inline short real_num();
	inline short table_status();
	bool UpdateForm(std::string sql, std::string &error);
	virtual bool BindingParameter();
private:
	char m_table_no_[7];     /* ��� */
	short m_payable_num_;    /* Ӧ������ */
	short m_real_num_;       /* ʵ������ */
	short m_table_status_;   /* ״̬ */
    SQLINTEGER m_sql_table_no_;
	SQLINTEGER m_sql_payable_num_;
	SQLINTEGER m_sql_real_num_;
	SQLINTEGER m_sql_table_status_;
};

/*
 * ˵��: ��ȡ̨��
 * ����ֵ: ̨���ַ���
 **/
char* CTableInfo::table_no()
{
	return m_table_no_;
}

/*
 * ˵��: ��ȡӦ������
 * ����ֵ: Ӧ������
 **/
short CTableInfo::payable_num()
{
	return m_payable_num_;
}

/*
 * ˵��: ��ȡʵ������
 * ����ֵ: ʵ������
 **/
short CTableInfo::real_num()
{
	return m_real_num_;
}

/*
 * ˵��: ��ȡ̨��״̬
 * ����ֵ: 	0, �ѿ�̨ 
 *          1, δ��̨ 
 *          2, ��Ԥ�� 
 **/
short CTableInfo::table_status()
{
	return m_table_status_;
}

#endif 
