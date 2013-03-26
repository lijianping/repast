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
	char m_no_[9];            // 商品编号
	char m_name_[257];        // 商品名称
	float m_purchase_price_;  // 商品进价
	int m_quantity_;          // 商品数量
	char m_child_name_[33];   // 此分类名称
	char m_main_name_[33];    // 主分类名称
	char m_unit_;             // 商品单位
	float m_sale_price_;      // 商品卖价
	char m_register_date_;    // 商品注册日期
	
	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_name_;        // 对应商品名称
	SQLINTEGER m_sql_purchase_price;
	SQLINTEGER m_sql_quantity_;
	SQLINTEGER m_sql_child_name_;  // 对应此分类名称	
	SQLINTEGER m_sql_main_name_;   // 对应主分类名称
	SQLINTEGER m_sql_unit_;
	SQLINTEGER m_sql_sale_price_;
	SQLINTEGER m_sql_register_date_;

};


/*
 * @ brief: 获取商品名称
 * @ return: 指向商品名称的字符串指针
 **/
char* CCommodity::name() {
	DeleteSpace(name_, name_);
	return name_;
}
#endif 
