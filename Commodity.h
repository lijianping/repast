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
	bool GetCommodityNameSet(const char* main_name, const char *child_name);
	bool GetCommodityNameSet(const char* main_name);
	
	
	inline char* no();
	inline char* name();
	inline float purchase_price() const;
	inline int quantity() const;
	inline char* unit();
	inline float sale_price() const;
	inline char* register_date();

protected:
	void Initialize();
	virtual bool BindingParameter();

private:
	char m_no_[9];            // 商品编号
	char m_name_[257];        // 商品名称
	float m_purchase_price_;  // 商品进价
	int m_quantity_;          // 商品数量
	char m_child_name_[33];   // 此分类名称
	char m_main_name_[33];    // 主分类名称
	char m_unit_[9];          // 商品单位
	float m_sale_price_;      // 商品卖价
	char m_register_date_[20];// 商品注册日期
	
	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_name_;        // 对应商品名称
	SQLINTEGER m_sql_purchase_price_;
	SQLINTEGER m_sql_quantity_;
	SQLINTEGER m_sql_child_name_;  // 对应此分类名称	
	SQLINTEGER m_sql_main_name_;   // 对应主分类名称
	SQLINTEGER m_sql_unit_;
	SQLINTEGER m_sql_sale_price_;
	SQLINTEGER m_sql_register_date_;

};

/*
 * @ brief: 获取商品编号
 * @ return: 商品编号字符指针
 **/
char *CCommodity::no() {
	DeleteSpace(m_no_, m_no_);
	return m_no_;
}

/*
 * @ brief: 获取商品名称
 * @ return: 指向商品名称的字符串指针
 **/
char* CCommodity::name() {
	DeleteSpace(m_name_, m_name_);
	return m_name_;
}

/*
 * @ brief: 获取商品进价
 * @ return: 商品进价
 **/
float CCommodity::purchase_price() const {
	return m_purchase_price_;
}

/*
 * @ brief: 获取商品数量
 * @ return: 商品数量
 **/
int CCommodity::quantity() const {
	return m_quantity_;
}

/*
 * @ brief: 获取商品单位信息
 * @ return: 商品单位字符指针
 **/
char* CCommodity::unit() {
	DeleteSpace(m_unit_, m_unit_);
	return m_unit_;
}

/*
 * @ brief: 获取商品卖价
 * @ return: 商品卖价
 **/
float CCommodity::sale_price() const {
	return m_sale_price_;
}

/*
 * @ brief: 获取注册日期
 * @ return: 注册日期字符指针
 **/
char* CCommodity::register_date() {
	return m_register_date_;   // 不能删除空格
}

#endif 
