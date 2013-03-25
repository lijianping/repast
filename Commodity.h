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
	void Initialize();
	inline char* name();

private:
	char main_name_[33];    // 主分类名称
	char child_name_[33];   // 此分类名称
	char name_[257];        // 商品名称
	SQLINTEGER sql_main_name_;   // 对应主分类名称
	SQLINTEGER sql_child_name_;  // 对应此分类名称
	SQLINTEGER sql_name_;        // 对应商品名称

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
