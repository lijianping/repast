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
	char m_no_[9];            // ��Ʒ���
	char m_name_[257];        // ��Ʒ����
	float m_purchase_price_;  // ��Ʒ����
	int m_quantity_;          // ��Ʒ����
	char m_child_name_[33];   // �˷�������
	char m_main_name_[33];    // ����������
	char m_unit_;             // ��Ʒ��λ
	float m_sale_price_;      // ��Ʒ����
	char m_register_date_;    // ��Ʒע������
	
	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_name_;        // ��Ӧ��Ʒ����
	SQLINTEGER m_sql_purchase_price;
	SQLINTEGER m_sql_quantity_;
	SQLINTEGER m_sql_child_name_;  // ��Ӧ�˷�������	
	SQLINTEGER m_sql_main_name_;   // ��Ӧ����������
	SQLINTEGER m_sql_unit_;
	SQLINTEGER m_sql_sale_price_;
	SQLINTEGER m_sql_register_date_;

};


/*
 * @ brief: ��ȡ��Ʒ����
 * @ return: ָ����Ʒ���Ƶ��ַ���ָ��
 **/
char* CCommodity::name() {
	DeleteSpace(m_name_, m_name_);
	return m_name_;
}
#endif 
