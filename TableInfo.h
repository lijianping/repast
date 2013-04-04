#ifndef REPAST_TABLEINFO_H_
#define REPAST_TABLEINFO_H_
#include "DBForm.h"

static const char *TableStatus[] = {
	"δ��̨",
	"�ѿ�̨",
	"��Ԥ��"
};

struct TABLEINFO
{
	std::string new_floor_name;
	std::string new_room_name;
	std::string new_table_no;
	std::string new_table_payable;
	std::string old_floor_name;
	std::string old_room_name;
	std::string old_table_no;
};

class CTableInfo : public CDBForm
{
public:
	CTableInfo();
	virtual ~CTableInfo();
	
	bool UpdateForm(std::string sql, std::string &error);
	bool GetTableInfoSet(const char *floor_name);
	bool GetTableInfoSet(const char *floor_name, const char *room_name);
	bool GetStartTableSet(const char *floor_name, short status);
	bool AddTable(const char *floor_name, const char *room_name,
		          const char *table_no, short payable);
	bool DeleteTable(const char *floor_name, const char *room_name, const char *table_no);
	bool CheckTable(const TABLEINFO *table_info);
	void SetTable(const TABLEINFO *table_info);
	bool UpdateTable(const TABLEINFO *table_info);

	inline char* table_no();
	inline short status();
	inline short payable();
	inline char* room_name();

protected:
	void Initialize();
	virtual bool BindingParameter();

private:
	char table_no_[5];             // ̨��
	char room_name_[33];              // ������
	char floor_name_[33];             // ¥����
	short payable_;                // ̨�ſ���������
	short status_;                 // ̨��״̬
    char old_table_no_[5];
	char old_room_name_[33];
	char old_floor_name_[33];
	SQLINTEGER sql_table_no_;      // ��Ӧ̨��
	SQLINTEGER sql_room_name_;       // ��Ӧ������
	SQLINTEGER sql_floor_name_;      // ��Ӧ¥���� 
	SQLINTEGER sql_payable_;       // ��Ӧ̨�ſ���������
	SQLINTEGER sql_status_;        // ��Ӧ̨��״̬
	SQLINTEGER sql_old_floor_name_;
	SQLINTEGER sql_old_room_name_;
	SQLINTEGER sql_old_table_no_;
};

/*
 * @ brief: ��ȡ̨��
 * @ return: ̨���ַ���ָ��
 **/
char* CTableInfo::table_no() {
	DeleteSpace(table_no_, table_no_);
	return table_no_;
}

/*
 * @ brief: ��ȡ̨��״̬
 * @ return: ̨�ŵ�״̬��Ϣ 0 -- δ��̨ 1 -- ��̨ 2 -- Ԥ��
 **/
short CTableInfo::status() {
	return status_;
}

/*
 * @ brief: ��ȡ̨�ſ����ɵ�����
 * @ return: �����ɵ�����
 **/
short CTableInfo::payable() {
	return payable_;
}

/*
 * @ brief: ��ȡ��������
 * @ return: ���������ַ�ָ��
 **/
char* CTableInfo::room_name() {
	DeleteSpace(room_name_, room_name_);
	return room_name_;
}
#endif 
