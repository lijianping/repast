#ifndef REPAST_MENUFORM_H_
#define REPAST_MENUFORM_H_

#include "DBForm.h"

class CMenuForm : public CDBForm  
{
public:
	bool InsertMenu(char *no, char *name, float price,std::string error);
	CMenuForm();
	virtual ~CMenuForm();
	virtual void SetSQLStatement(const std::string statement);
	inline char* dish_no();
	inline char* dish_name();
	inline float dish_price() const;

protected:
	virtual bool BindingParameter();

private:
	char m_dish_no_[4];              /* 菜名编号 */
	char m_dish_name_[20];           /* 菜名 */
    float m_dish_price_;             /* 单价 */
	SQLINTEGER m_no_len_;               
	SQLINTEGER m_name_len_;
	SQLINTEGER m_price_len_;
};

/*
 * @ 说明: 获取菜名编号
 * @ 返回值:
 *           菜名编号字符串
 **/
char* CMenuForm::dish_no() {
	return m_dish_no_;
}

/*
 * @ 说明: 获取菜名
 * @ 返回值:
 *           菜名字符串
 **/
char* CMenuForm::dish_name() {
	return m_dish_name_;
}

/*
 * @ 说明: 获取菜的单价
 * @ 返回值:
 *           单价
 **/
float CMenuForm::dish_price() const {
	return m_dish_price_;
}

#endif // !defined(AFX_MENUFORM_H__BC3F1D11_8103_4A5B_B9AC_866B8667EE63__INCLUDED_)
