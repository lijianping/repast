// Commodity.h: interface for the CCommodity class.
//
//////////////////////////////////////////////////////////////////////

#ifndef REPAST_COMMODITY_H_
#define REPAST_COMMODITY_H_

#include "Err.h"
#include "DBForm.h"

class CCommodity: public CDBForm
{
public:
	CCommodity();
	virtual ~CCommodity();
	bool GetCommodityNameSet(const char* main_name, 
		                     const char *child_name,
						     std::string &err_info);
	bool GetCommodityByMainName(const char* main_name,std::string &err_info);
	void Initialize();
	inline char* name();

private:
	char main_name_[33];    // ����������
	char child_name_[33];   // �˷�������
	char name_[257];        // ��Ʒ����
	
	SQLINTEGER sql_main_name_;   // ��Ӧ����������
	SQLINTEGER sql_child_name_;  // ��Ӧ�˷�������
	SQLINTEGER sql_name_;        // ��Ӧ��Ʒ����
};


/*
 * @ brief: ��ȡ��Ʒ����
 * @ return: ָ����Ʒ���Ƶ��ַ���ָ��
 **/
char* CCommodity::name() {
	DeleteSpace(name_, name_);
	return name_;
}
#endif 
