// CustomerMenuForm.cpp: implementation of the CCustomerMenuForm class.
//
//////////////////////////////////////////////////////////////////////

#include "CustomerMenuForm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomerMenuForm::CCustomerMenuForm()
{

}

CCustomerMenuForm::~CCustomerMenuForm()
{

}



/*
 * @ brief: ���ݹ˿ͱ�Ż�ȡ�˿͵����Ϣ
 * @ param: customer_no [in] �˿ͱ��
 **/
bool CCustomerMenuForm::GetCustomerMenuSet(const char *customer_no) {
	Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(customer_no_) - 1, 0, customer_no_,\
		                              sizeof(customer_no_), &sql_customer_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(customer_no_, customer_no);
	std::string err_info;	
	// ִ�д洢����
	// TODO: ��ӻ�ȡ�û��˵��洢����
	ExecSQLProc("{? = call GetConsumerMenuSet(?)}", err_info);
	BindingParameter();   // �󶨷��ؼ�¼��
	return true;
}


/*
 * @ brief: ɾ���˿�������Ʒ��Ϣ
 * @ param: customer_no [in] �˿ͱ��
 * @ return: ���ɹ�����true
 **/
bool CCustomerMenuForm::DeleteCustomerMenu(const char *customer_no) {
	Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		sizeof(customer_no_) - 1, 0, customer_no_,\
		sizeof(customer_no_), &sql_customer_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(customer_no_, customer_no);
	std::string err_info;	
	// ִ�д洢����
	// TODO: ��ӻ�ȡ�û��˵��洢����
	ExecSQLProc("{? = call DeleteCustomerMenuAll(?)}", err_info);
	return true;
}

/*
 * @ brief: ���ӹ˿���Ʒ��Ϣ
 * @ param: consumer_no [in] �˿ͱ��
 * @ param: commodity_name [in] ��Ʒ����
 * @ param: quantity [in] ��Ʒ����
 * @ return: �ɹ�����true
 **/
bool CCustomerMenuForm::AddCustomerMenu(const char *customer_no,
	                                    const char *commodity_name,
										int quantity) {
    Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(customer_no_) - 1, 0, customer_no_,\
		                              sizeof(customer_no_), &sql_customer_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
    m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		                              sizeof(commodity_name_) - 1, 0, commodity_name_,\
		                              sizeof(commodity_name_), &sql_commodity_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_SMALLINT,\
		                              0, 0, &quantity_, 0, &sql_quantity_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_PARAM_ERROR)
	strcpy(customer_no_, customer_no);
	strcpy(commodity_name_, commodity_name);
	quantity_ = quantity;
	std::string err_info;	
	// ִ�д洢����
	// TODO: ��ӻ�ȡ�û��˵��洢����
	ExecSQLProc("{? = call AddConsumerMenu(?,?,?)}", err_info);
	return true;
}

/*
 * @ brief: ������ʱ��
 * @ return: �ɹ�����true
 */
bool CCustomerMenuForm::CreateTempTable() {
	ExecSQLProc("{exec CreateTempTable}");
	return true;
}

/*
 * @ brief: ɾ����ʱ��
 * @ return: �ɹ�����true
 */
bool CCustomerMenuForm::DropTempTable() {
	ExecSQLProc("{exec DropTempTable}");
	return true;
}
/*
 * @ brief: ��ʼ���������
 **/
void CCustomerMenuForm::Initialize() {
	memset(customer_no_, 0, sizeof(customer_no_));
	memset(commodity_name_, 0, sizeof(commodity_name_));
	quantity_ = 0;
	commodity_price_ = 0;
	sql_customer_no_ = SQL_NTS;
	sql_commodity_name_ = SQL_NTS;
	sql_quantity_ = SQL_NTS;
	sql_commodity_price_ = SQL_NTS;
}

bool CCustomerMenuForm::BindingParameter()
{
	/* ����--����--���� */
	// ����Ʒ����
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, commodity_name_, sizeof(commodity_name_), &sql_commodity_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ�ۼ�
	m_return_code_ = SQLBindCol(m_hstmt_, 2, SQL_C_FLOAT, &commodity_price_, 0, &sql_commodity_price_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	// ����Ʒ����
	m_return_code_ = SQLBindCol(m_hstmt_, 3, SQL_C_LONG, &quantity_, 0, &sql_quantity_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	return true;
}
