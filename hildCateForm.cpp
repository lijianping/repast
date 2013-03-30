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
 * @ brief: 初始化sql类型数据
 **/
void ChildCateForm::Initialize()
{
	this->sql_cate_no_ = SQL_NTS;
	this->sql_main_cate_no_ = SQL_NTS;
	this->sql_cate_name_ = SQL_NTS;
	this->sql_main_cate_name_ = SQL_NTS;
}


/*
 * @ brief: 通过主分类名称获取子分类名称
 * @ param: main_cate_no [in] 主分类名称
 * @ param: err_info [out] 错误信息
 * @ return: 若成功返回true，否则返回false
 **/
bool ChildCateForm::GetChildCateName(const char *name, std::string &err_info)
{
	this->Initialize(); // 初始化sql类型
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
 * 说明:
 *     根据主分类名称和子分类名称获取子分类的编号
 * 参数：
 *     main_name [in] 主分类名称
 *     child_name [in] 子分类名称
 * 返回值：
 *     成功返回true, 失败返回false
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
 * 说明:
 *     检查子分类信息是否正确
 * 参数：
 *     child_cate  [in]指向子分类结构体的指针
 * 返回值：
 *     成功返回true, 失败返回false
 */
bool ChildCateForm::CheckChildCate(COMCHILDCATE *child_cate)
{
	return true;
}


/*
 * 说明:
 *     子分类信息赋值
 * 参数：
 *     child_cate  [in]指向子分类结构体的指针
 * 返回值：
 *    无
 */
void ChildCateForm::SetChildCate(COMCHILDCATE *child_cate)
{

}

/*
 * 说明:
 *     绑定子分类输入参数
 * 参数：
 *     bind_type  [in]绑定类型，可以是ADDCHILDCATE,UPDATECHILDCATE,DELETECHILDCATE
 * 返回值：
 *     成功返回true, 失败返回false
 */
bool ChildCateForm::Bind(int bind_type)
{
	return true;
}


/*
 * 说明:
 *     添加子分类信息
 * 参数：
 *     child_cate  [in]指向子分类结构体的指针
 * 返回值：
 *     成功返回true, 失败返回false
 */
bool ChildCateForm::AddChildCate(COMCHILDCATE *child_cate)
{
	return true;
}


/*
 * 说明:
 *     更新子分类信息是否正确
 * 参数：
 *     child_cate  [in]指向子分类结构体的指针
 * 返回值：
 *     成功返回true, 失败返回false
 */
bool ChildCateForm::UpdateChildCate(COMCHILDCATE *child_cate)
{
	return true;
}

/*
 * 说明:
 *     删除子分类信息是否正确
 * 参数：
 *     child_cate  [in]指向子分类结构体的指针
 * 返回值：
 *     成功返回true, 失败返回false
 */
bool ChildCateForm::DeleteChildCate(const char *child_no)
{
	return true;
}
