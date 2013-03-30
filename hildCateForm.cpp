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
	this->sql_main_cate_no_ = SQL_NTS;
	this->sql_cate_name_ = SQL_NTS;
	this->sql_main_cate_name_ = SQL_NTS;
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
	m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR,\
		sizeof(main_cate_name_) - 1, 0, main_cate_name_, sizeof(main_cate_name_), &sql_main_cate_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) {
		LTHROW(BIND_PARAM_ERROR)
		return false;
	}
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR,\
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
	return true;
}
