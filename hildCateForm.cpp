// hildCateForm.cpp: implementation of the ChildCateForm class.
//
//////////////////////////////////////////////////////////////////////

#include "hildCateForm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ChildCateForm::ChildCateForm()
{

}

ChildCateForm::~ChildCateForm()
{

}

/*
 * @ brief: ��ʼ��sql��������
 **/
void ChildCateForm::Initialize()
{
	this->sql_cate_no_ = SQL_NTS;
	this->sql_cate_name_ = SQL_NTS;
	this->sql_main_cate_no_ = SQL_NTS;
	this->sql_main_cate_name_ = SQL_NTS;
	this->sql_old_cate_no_ = SQL_NTS;
}


/*
 * @ brief: ͨ�����������ƻ�ȡ�ӷ�������
 * @ param: main_cate_no [in] ����������
 * @ param: err_info [out] ������Ϣ
 * @ return: ���ɹ�����true�����򷵻�false
 **/
bool ChildCateForm::GetChildCateName(const char *name, std::string &err_info)
{
	this->Initialize(); // ��ʼ��sql����
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR,\
		sizeof(main_cate_name_) - 1, 0, main_cate_name_, sizeof(main_cate_name_), &sql_main_cate_name_);
	strcpy(main_cate_name_, name);

	if (m_return_code_ == SQL_SUCCESS || m_return_code_ == SQL_SUCCESS_WITH_INFO) {
		if (ExecSQLProc("{? = call GetChildCateNameByMainCateName(?)}"/* sql*/, err_info)) {
			m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, cate_name_, sizeof(cate_name_), &sql_cate_name_);
			if (m_return_code_ == SQL_SUCCESS || m_return_code_ == SQL_SUCCESS_WITH_INFO) {
				return true;
			}
		}
	}
	return false;
}


/*
 * ˵��:
 *     �������������ƺ��ӷ������ƻ�ȡ�ӷ���ı��
 * ������
 *     main_name [in] ����������
 *     child_name [in] �ӷ�������
 * ����ֵ��
 *     �ɹ�����true, ʧ�ܷ���false
 */
bool ChildCateForm::GetChildCateByDname(const char *main_name, const char *child_name)
{
	this->Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		sizeof(main_cate_name_) - 1, 0, main_cate_name_, sizeof(main_cate_name_), &sql_main_cate_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) {
		LTHROW(BIND_PARAM_ERROR)
		return false;
	}
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR,SQL_CHAR,\
		sizeof(cate_name_) - 1, 0, cate_name_, sizeof(cate_name_), &sql_cate_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) {
		LTHROW(BIND_PARAM_ERROR)
			return false;
	}
	strcpy(main_cate_name_, main_name);
	strcpy(cate_name_,child_name);
	ExecSQLProc("{?=call GetChildCateByDname(?,?)}");
	m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_SSHORT, &cate_no_, 0, &sql_cate_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) {
		LTHROW(BIND_RECODE_ERROR)
		return false;
	}
	this->IsEOF();
	return true;
}


/*
 * ˵��:
 *     ����ӷ�����Ϣ�Ƿ���ȷ
 * ������
 *     child_cate  [in]ָ���ӷ���ṹ���ָ��
 * ����ֵ��
 *     �ɹ�����true, ʧ�ܷ���false
 */
bool ChildCateForm::CheckChildCate(COMCHILDCATE *child_cate)
{
	unsigned int length;
	length = child_cate->child_no.length();
	if (0 == length)
	{
		LTHROW(INPUT_NULL_ERROR)
	}
	if (length > 17)
	{
		LTHROW(INPUT_TOO_LONG_ERROR)
	}
	length = child_cate->child_name.length();
	if (0==length)
	{
		LTHROW(INPUT_NULL_ERROR)
	}
	if (length > sizeof(cate_name_)-1)
	{
		LTHROW(INPUT_TOO_LONG_ERROR)
	}
	return true;
}


/*
 * ˵��:
 *     �ӷ�����Ϣ��ֵ
 * ������
 *     child_cate  [in]ָ���ӷ���ṹ���ָ��
 * ����ֵ��
 *    ��
 */
void ChildCateForm::SetChildCate(COMCHILDCATE *child_cate)
{
	strcpy(cate_name_,child_cate->child_name.c_str());
	cate_no_ = atoi(child_cate->child_no.c_str());
	strcpy(main_cate_name_,child_cate->main_name.c_str());
	old_cate_no_= atoi(child_cate->old_child_no.c_str());
}

/*
 * ˵��:
 *     ���ӷ����������
 * ������
 *     bind_type  [in]�����ͣ�������ADDCHILDCATE,UPDATECHILDCATE,DELETECHILDCATE
 * ����ֵ��
 *     �ɹ�����true, ʧ�ܷ���false
 */
bool ChildCateForm::Bind(int bind_type)
{
	this->Initialize();
	BindReturn();
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_SMALLINT,\
		0, 0, &cate_no_, 0, &sql_cate_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) {
		LTHROW(BIND_PARAM_ERROR)
	}
	if (bind_type==DELETECHILDCATE)//����"ɾ��"��
	{
		return true;
	}
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		sizeof(main_cate_name_) - 1, 0, main_cate_name_, sizeof(main_cate_name_), &sql_main_cate_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) {
		LTHROW(BIND_PARAM_ERROR)
			return false;
	}
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		sizeof(cate_name_) - 1, 0, cate_name_, sizeof(cate_name_), &sql_cate_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) {
		LTHROW(BIND_PARAM_ERROR)
			return false;
	}
	if (bind_type == ADDCHILDCATE)//����"���"��
	{
		return true;
	}
	//���ǡ����¡���
	m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_SMALLINT,\
		0, 0, &old_cate_no_, 0, &sql_old_cate_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) {
		LTHROW(BIND_PARAM_ERROR)
	}
	return true;
}


/*
 * ˵��:
 *     ����ӷ�����Ϣ
 * ������
 *     child_cate  [in]ָ���ӷ���ṹ���ָ��
 * ����ֵ��
 *     �ɹ�����true, ʧ�ܷ���false
 */
bool ChildCateForm::AddChildCate(COMCHILDCATE *child_cate)
{
	CheckChildCate(child_cate);
	Bind(ADDCHILDCATE);
	SetChildCate(child_cate);
	ExecSQLProc("{?=call AddChildCate(?,?,?)}");
	IsSQLProcRetRight();
	return true;
}


/*
 * ˵��:
 *     �����ӷ�����Ϣ�Ƿ���ȷ
 * ������
 *     child_cate  [in]ָ���ӷ���ṹ���ָ��
 * ����ֵ��
 *     �ɹ�����true, ʧ�ܷ���false
 */
bool ChildCateForm::UpdateChildCate(COMCHILDCATE *child_cate)
{
	CheckChildCate(child_cate);
	Bind(UPDATECHILECATE);
	SetChildCate(child_cate);
	ExecSQLProc("{?=call UpdateChildComCate(?,?,?,?)}");
//	ExecSQLProc("exec UpdateChildComCate 222,'222','222',55");
	IsSQLProcRetRight();
	return true;
}

/*
 * ˵��:
 *     ɾ���ӷ�����Ϣ�Ƿ���ȷ
 * ������
 *     child_cate  [in]ָ���ӷ���ṹ���ָ��
 * ����ֵ��
 *     �ɹ�����true, ʧ�ܷ���false
 */
bool ChildCateForm::DeleteChildCate(const char *child_no)
{
	Bind(DELETECHILDCATE);
    old_cate_no_ = atoi(child_no);
	ExecSQLProc("{?=call DeleteChildCate(?)}");
	IsSQLProcRetRight();
	return true;
}
