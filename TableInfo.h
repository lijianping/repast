#ifndef REPAST_TABLEINFO_H_
#define REPAST_TABLEINFO_H_
#include "DBForm.h"

class CTableInfo : public CDBForm
{
public:
	CTableInfo();
	virtual ~CTableInfo();
	enum TableStatus {
		kFounding = 0,       // δ��̨ 
		kNotFounding = 1,    // �ѿ�̨ 
		kBooked = 2          // ��Ԥ�� 
	};
	inline char* table_no();
	inline short payable_num();
	inline short real_num();
	inline short table_status();
	inline char* datetime();
	bool UpdateForm(std::string sql, std::string &error);
	virtual bool BindingParameter();

	bool GetTableInfoSet(const char *floor_name);
	bool GetTableInfoSet(const char *floor_name, const char *room_name);
	void Initialize();

private:
	char m_table_no_[7];			 // ��� 
	short m_table_status_;			 // ״̬ 
	short m_payable_num_;			 // Ӧ������ 
	SQLINTEGER m_sql_table_no_;    
	SQLINTEGER m_sql_table_status_;
	SQLINTEGER m_sql_payable_num_;

	// �½�,����ȡ��
	char table_no_[5];             // ̨��
	char room_name_[33];              // ������
	char floor_name_[33];             // ¥����
	short payable_;                // ̨�ſ���������
	short status_;                 // ̨��״̬
	SQLINTEGER sql_table_no_;      // ��Ӧ̨��
	SQLINTEGER sql_room_name_;       // ��Ӧ������
	SQLINTEGER sql_floor_name_;      // ��Ӧ¥���� 
	SQLINTEGER sql_payable_;       // ��Ӧ̨�ſ���������
	SQLINTEGER sql_status_;        // ��Ӧ̨��״̬
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
 * ˵��: ��ȡ̨��״̬
 * ����ֵ: 	0, �ѿ�̨ 
 *          1, δ��̨ 
 *          2, ��Ԥ�� 
 **/
short CTableInfo::table_status()
{
	return m_table_status_;
}

/*
 * ˵��: ��ȡӦ������
 * ����ֵ: Ӧ������
**/
short CTableInfo::payable_num()
{
	return m_payable_num_;
}


#endif 
