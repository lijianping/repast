// Commodity.cpp: implementation of the CCommodity class.
//
//////////////////////////////////////////////////////////////////////

#include "Commodity.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommodity::CCommodity()
{  
	
}

CCommodity::~CCommodity()
{

}

/*
 * @ breif: 根据商品的主，次分类名称获取商品信息
 * @ param: main_name [in] 主分类名
 * @ param: child_name [in] 次分类名
 * @ return: 若成功返回true，否则返回false
 **/
bool CCommodity::GetCommodityNameSet(const char* main_name) {
	Initialize();
	BindReturn();// 绑定返回值
	// 绑定输入参数
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR,\
		                              sizeof(m_main_name_) - 1, 0, m_main_name_, \
									  sizeof(m_main_name_), &m_sql_main_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(m_main_name_, main_name);
	std::string err_info;
	ExecSQLProc("{? = call GetCommodityByMainName(?)}", err_info);
	BindingParameter();
	return true;
}

/*
 * 说明：
 *     通过主分类名和子分类名获取所属的商品信息
 * 参数：
 *    main_name  [in] 主分类名
 *    child_name [in] 子分类名
 * 返回值：
 *    成功返回true, 否则返回false
 */
bool CCommodity::GetCommodityNameSet(const char* main_name, const char *child_name) {
	Initialize();
	BindReturn(); // 绑定返回值
	// 绑定输入参数
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR, sizeof(m_main_name_) - 1,\
		                             0, m_main_name_, sizeof(m_main_name_), &m_sql_main_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR, sizeof(m_child_name_) - 1,\
		                              0, m_child_name_, sizeof(m_child_name_), &m_sql_child_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(m_main_name_, main_name);
	strcpy(m_child_name_, child_name);
	std::string err_info;
	ExecSQLProc("{? = call GetCommodityByDBName(?,?)}", err_info);
	BindingParameter();
	return true;
}

/*
 * @ brief: 初始化数据
 **/
void CCommodity::Initialize() {
	m_sql_no_ = SQL_NTS;
	m_sql_old_no_ = SQL_NTS;
	m_sql_name_ = SQL_NTS;
	m_sql_purchase_price_ = SQL_NTS;
	m_sql_quantity_ = SQL_NTS;
	m_sql_child_name_ = SQL_NTS;
	m_sql_main_name_ = SQL_NTS;
	m_sql_unit_ = SQL_NTS;
	m_sql_sale_price_ = SQL_NTS;
	m_sql_register_date_ = SQL_NTS;
	m_sql_pro_ret = SQL_NTS;
	memset(m_no_, 0, sizeof(m_no_));
	memset(m_name_, 0, sizeof(m_name_));
	memset(m_main_name_, 0, sizeof(m_main_name_));
	memset(m_child_name_, 0, sizeof(m_child_name_));
	memset(m_unit_, 0, sizeof(m_unit_));
	memset(m_register_date_, 0, sizeof(m_register_date_));
}

/*
 * @ brief: 绑定返回记录集
 * @ return: 成功返回true
 **/
bool CCommodity::BindingParameter() {
	// 绑定商品编号
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_no_, sizeof(m_no_), &m_sql_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品名称
		m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品进价
	m_return_code_ = SQLBindCol(m_hstmt_, 3, SQL_C_FLOAT, &m_purchase_price_, 0, &m_sql_purchase_price_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品数量
	m_return_code_ = SQLBindCol(m_hstmt_, 4, SQL_C_LONG, &m_quantity_, 0, &m_sql_quantity_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品子分类编号
	short child_no;   // 不用
	m_return_code_ = SQLBindCol(m_hstmt_, 5, SQL_C_SHORT, &child_no, 0, &m_sql_child_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品单位
	m_return_code_ = SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_unit_, sizeof(m_unit_), &m_sql_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品售价
	m_return_code_ = SQLBindCol(m_hstmt_, 7, SQL_C_FLOAT, &m_sale_price_, 0, &m_sql_sale_price_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// 绑定商品注册时间
	m_return_code_ = SQLBindCol(m_hstmt_, 8, SQL_C_CHAR, m_register_date_, sizeof(m_register_date_), &m_sql_register_date_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
		return true;
}


/*
 * 说明：
 *     通过商品编号获取主分类名和子分类名
 * 参数：
 *    com_no [in] 商品编号
 * 返回值：
 *    成功返回true, 否则返回false
 */
bool CCommodity::GetCategoryByComNO(const char* com_no)
{
	Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR, sizeof(m_no_) - 1,\
		0, m_no_, sizeof(m_no_), &m_sql_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		strcpy(m_no_, com_no);
	ExecSQLProc("{?=call GetCategoryByComNO(?)}");
	// 绑定主分类名
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_main_name_, sizeof(m_main_name_), &m_sql_main_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
		// 绑定商品子分类名
		m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_child_name_, sizeof(m_child_name_), &m_sql_child_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	IsEOF();
	return true;
}


/*
 * 说明：
 *     检查输入的商品信息是否符合规范，主要检查其字段的长度是否正确 
 * 参数：
 *    com_info [in] 指向商品信息的指针
 * 返回值：
 *    成功返回true, 否则返回false
 */
bool CCommodity::CheckCommodity(const CommodityInfo *com_info)
{
	if (com_info->commodity_no.length()==0||
		com_info->commodity_name.length()==0||
		com_info->commodity_unit.length()==0||
		com_info->commodity_main_category.length()==0||
		com_info->commodity_child_category.length()==0)
	{
		LTHROW(INPUT_NULL_ERROR)
	}
	if (com_info->commodity_no.length()>(sizeof(m_no_)-1)||
		com_info->commodity_name.length()>(sizeof(m_name_)-1)||
		com_info->commodity_unit.length()>(sizeof(m_unit_)-1)||
		com_info->commodity_purchase.length()>8||
		com_info->commodity_sum.length()>8||
		com_info->commodity_sale.length()>8)
	{
		LTHROW(INPUT_TOO_LONG_ERROR)
	}
	return true;
}


/*
 * 说明：
 *     商品信息赋值，用于输入参数
 * 参数：
 *    com_info [in] 指向商品信息的指针
 * 返回值：
 *    无
 */
void CCommodity::SetCommodity(const CommodityInfo *com_info)
{
	strcpy(m_no_,com_info->commodity_no.c_str());
	strcpy(m_old_no_,com_info->com_old_no.c_str());
	strcpy(m_name_,com_info->commodity_name.c_str());
	m_purchase_price_=atof(com_info->commodity_purchase.c_str());
	m_quantity_ = atoi(com_info->commodity_sum.c_str());
    strcpy(m_unit_,com_info->commodity_unit.c_str());
	m_sale_price_= atof(com_info->commodity_sale.c_str());
	strcpy(m_main_name_,com_info->commodity_main_category.c_str());
	strcpy(m_child_name_,com_info->commodity_child_category.c_str());
	strcpy(m_register_date_,com_info->commodity_register_date.c_str());
}


/*
 * 说明：
 *     绑定商品信息，用于执行商品的添加，修改，删除时参数的绑定
 * 参数：
 *    bind_type [in] 标明绑定的类型，可为：ADDCOM,UPDATECOM,DELETECOM
 * 返回值：
 *    成功返回true, 否则返回false
 */
bool CCommodity::Bind(int bind_type)
{
	Initialize();
	BindReturn();
	//绑定商品编号
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT,SQL_C_CHAR, SQL_CHAR,  sizeof(m_no_) - 1,\
		0, m_no_, sizeof(m_no_), &m_sql_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	if (bind_type==DELETECOM)//若为“删除操作”的绑定
	{
		return true;
	}
		//绑定商品名称
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR ,SQL_CHAR, sizeof(m_name_) - 1,\
		0, m_name_, sizeof(m_name_), &m_sql_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//绑定商品进价
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_FLOAT,SQL_REAL , 0,\
		0, &m_purchase_price_, 0, &m_sql_purchase_price_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//绑定商品数量
	m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_SLONG,SQL_INTEGER , 0,\
		0, &m_quantity_, 0, &m_sql_quantity_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//绑定商品主分类名
	m_return_code_ = SQLBindParameter(m_hstmt_, 6, SQL_PARAM_INPUT, SQL_C_CHAR ,SQL_CHAR, sizeof(m_main_name_) - 1,\
		0, m_main_name_, sizeof(m_main_name_), &m_sql_main_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//绑定商品子分类名
	m_return_code_ = SQLBindParameter(m_hstmt_, 7, SQL_PARAM_INPUT, SQL_C_CHAR ,SQL_CHAR, sizeof(m_child_name_) - 1,\
		0, m_child_name_, sizeof(m_child_name_), &m_sql_child_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//绑定商品单位
	m_return_code_ = SQLBindParameter(m_hstmt_, 8, SQL_PARAM_INPUT, SQL_C_CHAR ,SQL_CHAR, sizeof(m_unit_) - 1,\
		0, m_unit_, sizeof(m_unit_), &m_sql_child_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//绑定商品卖价
	m_return_code_ = SQLBindParameter(m_hstmt_, 9, SQL_PARAM_INPUT, SQL_C_FLOAT,SQL_REAL , 0,\
		0, &m_sale_price_, 0, &m_sql_sale_price_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//绑定商品登记日期
	m_return_code_ = SQLBindParameter(m_hstmt_, 10, SQL_PARAM_INPUT, SQL_C_CHAR ,SQL_CHAR, sizeof(m_register_date_) - 1,\
		0, m_register_date_, sizeof(m_register_date_), &m_sql_register_date_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	if (bind_type==DELETECOM)//若为“添加操作”的绑定
	{
		return true;
	}
	//绑定商品原来的编号
	m_return_code_ = SQLBindParameter(m_hstmt_, 11, SQL_PARAM_INPUT,SQL_C_CHAR, SQL_CHAR,  sizeof(m_old_no_) - 1,\
		0, m_old_no_, sizeof(m_old_no_), &m_sql_old_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	return true;
}

/*
 * 说明：
 *     添加商品信息
 * 参数：
 *    com_info [in] 指向商品信息的指针
 * 返回值：
 *    成功返回true, 否则返回false
 */
bool CCommodity::AddCom(const CommodityInfo *com_info)
{
	CheckCommodity(com_info);
	Bind(ADDCOM);
	SetCommodity(com_info);
	ExecSQLProc("{?=call AddCommodity(?,?,?,?,?,?,?,?,?)}");
	IsSQLProcRetRight();
	return true;
}

/*
 * 说明：
 *     修改商品信息
 * 参数：
 *    com_info [in] 指向商品信息的指针
 * 返回值：
 *    成功返回true, 否则返回false
 */
bool CCommodity::UpdateCom(const CommodityInfo *com_info)
{
	CheckCommodity(com_info);
	Bind(UPDATECOM);
	SetCommodity(com_info);
	ExecSQLProc("{?=call UpdateCommodity(?,?,?,?,?,?,?,?,?,?)}");
	IsSQLProcRetRight();
	return true;
}

/*
 * 说明：
 *     删除商品信息
 * 参数：
 *    com_info [in] 指向商品信息的指针
 * 返回值：
 *    成功返回true, 否则返回false
 */
bool CCommodity::DeleteCom(const std::string com_no)
{
	Bind(DELETECOM);
	strcpy(m_no_,com_no.c_str());
	ExecSQLProc("{?=call DeleteCommodity(?)}");
	IsSQLProcRetRight();
	return true;
}