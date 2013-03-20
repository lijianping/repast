// Commodity.cpp: implementation of the CCommodity class.
//
//////////////////////////////////////////////////////////////////////

#include "Commodity.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommodity::CCommodity()
{  
	 m_sql_no_ = SQL_NTS;
	 m_sql_name_ = SQL_NTS;
	 m_sql_purchase_price_ = SQL_NTS;
	 m_sql_sum_ = SQL_NTS;
	 m_sql_category_ = SQL_NTS;
	 m_sql_unit_ = SQL_NTS;
	 m_sql_sale_price_ = SQL_NTS;
	 m_sql_register_date_ = SQL_NTS;
//	m_query_sql_ =  "select Commodity.Cno,Cname,Cprice,Cregisterdate,Csum from Commodity,	CommoditySum where Commodity.Cno=CommoditySum.Cno";
    m_query_sql_ = "select Cno,Cname,Cpurchase_price,Cquantity,CCname,Cunit,Csale_price,Cregister_date from Commodity,CommodityCategory where Ccategory = CCno";
}

CCommodity::~CCommodity()
{

}

bool CCommodity::BindingParameter()
{
	/* 绑定列 */
    SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_no_, sizeof(m_no_), &m_sql_no_);
	SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
//	SQLBindCol(m_hstmt_, 3, SQL_C_DOUBLE, &m_price_,        sizeof(m_price_),        &m_sql_price_);/*TODO: 将不在使用了*/
	SQLBindCol(m_hstmt_, 3, SQL_C_DOUBLE, &m_purchase_price_, sizeof(m_purchase_price_), &m_sql_purchase_price_);
	SQLBindCol(m_hstmt_, 4, SQL_C_LONG, &m_sum_, sizeof(m_sum_), &m_sql_sum_);
	SQLBindCol(m_hstmt_, 5, SQL_C_CHAR, m_category_, sizeof(m_category_), &m_sql_category_);
	SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_unit_, sizeof(m_unit_), &m_sql_unit_);
	SQLBindCol(m_hstmt_, 7, SQL_C_DOUBLE, &m_sale_price_, sizeof(m_sale_price_),  &m_sql_sale_price_);
	SQLBindCol(m_hstmt_, 8, SQL_C_CHAR, m_register_date_, sizeof(m_register_date_), &m_sql_register_date_);

	return true;
}

bool CCommodity::InsertInfo(char no[9], char name[256], double price, char register_date[21], int sum)
{
//	char insert_sql[1024];
	/*TODO: ADD INSERT*/
	return true;
}

/*
 *说明：
 *     通过商品的分类名，查找对应的商品的记录集
 *参数：
 *    category_name    [in]  商品分类名称
 *返回值：
 *     成功返回对应商品的记录集
 *
 **/
bool CCommodity::SelectByName(char* name, std::string error)
{
	char query[256];
	sprintf(query, "select Cno,Cname,Cpurchase_price,Cquantity,CCname,Cunit,Csale_price,Cregister_date \
		from Commodity,CommodityCategory where Ccategory = CCno and (CCname ='%s' or Cname = '%s')", name, name);
	if (false == ExecuteSQL(query, error))
	{
		return false;
	}
	BindingParameter();
	MoveFirst();
	return true;
}