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
 * @ breif: ������Ʒ�������η������ƻ�ȡ��Ʒ��Ϣ
 * @ param: main_name [in] ��������
 * @ param: child_name [in] �η�����
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool CCommodity::GetCommodityNameSet(const char* main_name) {
	Initialize();
	BindReturn();// �󶨷���ֵ
	// ���������
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
 * ˵����
 *     ͨ�������������ӷ�������ȡ��������Ʒ��Ϣ
 * ������
 *    main_name  [in] ��������
 *    child_name [in] �ӷ�����
 * ����ֵ��
 *    �ɹ�����true, ���򷵻�false
 */
bool CCommodity::GetCommodityNameSet(const char* main_name, const char *child_name) {
	Initialize();
	BindReturn(); // �󶨷���ֵ
	// ���������
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
 * @ brief: ��ʼ������
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
 * @ brief: �󶨷��ؼ�¼��
 * @ return: �ɹ�����true
 **/
bool CCommodity::BindingParameter() {
	// ����Ʒ���
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_no_, sizeof(m_no_), &m_sql_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ����
		m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ����
	m_return_code_ = SQLBindCol(m_hstmt_, 3, SQL_C_FLOAT, &m_purchase_price_, 0, &m_sql_purchase_price_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ����
	m_return_code_ = SQLBindCol(m_hstmt_, 4, SQL_C_LONG, &m_quantity_, 0, &m_sql_quantity_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ�ӷ�����
	short child_no;   // ����
	m_return_code_ = SQLBindCol(m_hstmt_, 5, SQL_C_SHORT, &child_no, 0, &m_sql_child_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ��λ
	m_return_code_ = SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_unit_, sizeof(m_unit_), &m_sql_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ�ۼ�
	m_return_code_ = SQLBindCol(m_hstmt_, 7, SQL_C_FLOAT, &m_sale_price_, 0, &m_sql_sale_price_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒע��ʱ��
	m_return_code_ = SQLBindCol(m_hstmt_, 8, SQL_C_CHAR, m_register_date_, sizeof(m_register_date_), &m_sql_register_date_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
		return true;
}


/*
 * ˵����
 *     ͨ����Ʒ��Ż�ȡ�����������ӷ�����
 * ������
 *    com_no [in] ��Ʒ���
 * ����ֵ��
 *    �ɹ�����true, ���򷵻�false
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
	// ����������
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_main_name_, sizeof(m_main_name_), &m_sql_main_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
		// ����Ʒ�ӷ�����
		m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_child_name_, sizeof(m_child_name_), &m_sql_child_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	IsEOF();
	return true;
}


/*
 * ˵����
 *     ����������Ʒ��Ϣ�Ƿ���Ϲ淶����Ҫ������ֶεĳ����Ƿ���ȷ 
 * ������
 *    com_info [in] ָ����Ʒ��Ϣ��ָ��
 * ����ֵ��
 *    �ɹ�����true, ���򷵻�false
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
 * ˵����
 *     ��Ʒ��Ϣ��ֵ�������������
 * ������
 *    com_info [in] ָ����Ʒ��Ϣ��ָ��
 * ����ֵ��
 *    ��
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
 * ˵����
 *     ����Ʒ��Ϣ������ִ����Ʒ����ӣ��޸ģ�ɾ��ʱ�����İ�
 * ������
 *    bind_type [in] �����󶨵����ͣ���Ϊ��ADDCOM,UPDATECOM,DELETECOM
 * ����ֵ��
 *    �ɹ�����true, ���򷵻�false
 */
bool CCommodity::Bind(int bind_type)
{
	Initialize();
	BindReturn();
	//����Ʒ���
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT,SQL_C_CHAR, SQL_CHAR,  sizeof(m_no_) - 1,\
		0, m_no_, sizeof(m_no_), &m_sql_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	if (bind_type==DELETECOM)//��Ϊ��ɾ���������İ�
	{
		return true;
	}
		//����Ʒ����
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR ,SQL_CHAR, sizeof(m_name_) - 1,\
		0, m_name_, sizeof(m_name_), &m_sql_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//����Ʒ����
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_FLOAT,SQL_REAL , 0,\
		0, &m_purchase_price_, 0, &m_sql_purchase_price_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//����Ʒ����
	m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_SLONG,SQL_INTEGER , 0,\
		0, &m_quantity_, 0, &m_sql_quantity_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//����Ʒ��������
	m_return_code_ = SQLBindParameter(m_hstmt_, 6, SQL_PARAM_INPUT, SQL_C_CHAR ,SQL_CHAR, sizeof(m_main_name_) - 1,\
		0, m_main_name_, sizeof(m_main_name_), &m_sql_main_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//����Ʒ�ӷ�����
	m_return_code_ = SQLBindParameter(m_hstmt_, 7, SQL_PARAM_INPUT, SQL_C_CHAR ,SQL_CHAR, sizeof(m_child_name_) - 1,\
		0, m_child_name_, sizeof(m_child_name_), &m_sql_child_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//����Ʒ��λ
	m_return_code_ = SQLBindParameter(m_hstmt_, 8, SQL_PARAM_INPUT, SQL_C_CHAR ,SQL_CHAR, sizeof(m_unit_) - 1,\
		0, m_unit_, sizeof(m_unit_), &m_sql_child_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//����Ʒ����
	m_return_code_ = SQLBindParameter(m_hstmt_, 9, SQL_PARAM_INPUT, SQL_C_FLOAT,SQL_REAL , 0,\
		0, &m_sale_price_, 0, &m_sql_sale_price_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
		//����Ʒ�Ǽ�����
	m_return_code_ = SQLBindParameter(m_hstmt_, 10, SQL_PARAM_INPUT, SQL_C_CHAR ,SQL_CHAR, sizeof(m_register_date_) - 1,\
		0, m_register_date_, sizeof(m_register_date_), &m_sql_register_date_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	if (bind_type==DELETECOM)//��Ϊ����Ӳ������İ�
	{
		return true;
	}
	//����Ʒԭ���ı��
	m_return_code_ = SQLBindParameter(m_hstmt_, 11, SQL_PARAM_INPUT,SQL_C_CHAR, SQL_CHAR,  sizeof(m_old_no_) - 1,\
		0, m_old_no_, sizeof(m_old_no_), &m_sql_old_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	return true;
}

/*
 * ˵����
 *     �����Ʒ��Ϣ
 * ������
 *    com_info [in] ָ����Ʒ��Ϣ��ָ��
 * ����ֵ��
 *    �ɹ�����true, ���򷵻�false
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
 * ˵����
 *     �޸���Ʒ��Ϣ
 * ������
 *    com_info [in] ָ����Ʒ��Ϣ��ָ��
 * ����ֵ��
 *    �ɹ�����true, ���򷵻�false
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
 * ˵����
 *     ɾ����Ʒ��Ϣ
 * ������
 *    com_info [in] ָ����Ʒ��Ϣ��ָ��
 * ����ֵ��
 *    �ɹ�����true, ���򷵻�false
 */
bool CCommodity::DeleteCom(const std::string com_no)
{
	Bind(DELETECOM);
	strcpy(m_no_,com_no.c_str());
	ExecSQLProc("{?=call DeleteCommodity(?)}");
	IsSQLProcRetRight();
	return true;
}