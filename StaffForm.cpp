// CStaffForm.cpp: implementation of the CStaffForm class.
//
//////////////////////////////////////////////////////////////////////

#include "StaffForm.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStaffForm::CStaffForm()
: m_age_(0),
  m_salary_(0)
{
    memset(m_id_, '\0', sizeof(m_id_));
    memset(m_name_, '\0', sizeof(m_name_));
    memset(m_sex_, '\0', sizeof(m_sex_));
    memset(m_dept_num_, '\0', sizeof(m_dept_num_));
    memset(m_dept_name_, '\0', sizeof(m_dept_name_));
	memset(m_mailbox_, '\0', sizeof(m_mailbox_));
	memset(m_phone_num_, '\0', sizeof(m_phone_num_));
	memset(m_address_, '\0', sizeof(m_address_));

	m_sql_id_=SQL_NTS;         /* the staff's id in database Staff form */
	m_sql_name_=SQL_NTS;       /* the staff's name in database Staff form */
	m_sql_sex_=SQL_NTS;        /* the staff's sex in database Staff form */
	m_sql_age_=SQL_NTS;        /* the staff's age in database Staff form */
	m_sql_salary_=SQL_NTS;     /* the staff's salary in database Staff form */
	m_sql_dept_num_=SQL_NTS;   /* the staff's department number in database Staff form */
	m_sql_dept_name_=SQL_NTS;  /* the staff's department name in database Dept form */
	m_sql_mailbox_=SQL_NTS;    /* the staff's mailbox in database Dept form */
	m_sql_phone_num_=SQL_NTS;  /* the staff's phone number in database Dept form */
	m_sql_address_=SQL_NTS;    /* the staff's address in database Dept form */
	 m_sql_pro_ret =SQL_NTS;

    m_query_sql_ = "select Sno,Sname,Ssex,Sage,Ssalary,Dname,Smailbox,Sphoneno,Saddress from Staff,Dept where Sdeptno=Dno";
}

CStaffForm::~CStaffForm()
{

}

/*
 * 说明: 绑定记录集参数
 * 返回值: 执行成功返回true, 否则返回false
 */
bool CStaffForm::BindingParameter()
{
    /* 绑定列 *//*TODO:尚未检查返回值 */
    SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_id_, sizeof(m_id_), &m_sql_id_);
    SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
    SQLBindCol(m_hstmt_, 3, SQL_C_CHAR, m_sex_, sizeof(m_sex_), &m_sql_sex_);
    SQLBindCol(m_hstmt_, 4, SQL_C_SSHORT, &m_age_, 0, &m_sql_age_);
    SQLBindCol(m_hstmt_, 5, SQL_C_FLOAT, &m_salary_, 0, &m_sql_salary_);
    SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_dept_name_, sizeof(m_dept_name_), &m_sql_dept_name_);
   // SQLBindCol(m_hstmt_, 6, SQL_C_CHAR, m_dept_num_, sizeof(m_dept_num_), &m_sql_dept_num_);
	SQLBindCol(m_hstmt_, 7, SQL_C_CHAR, m_mailbox_, sizeof(m_mailbox_), &m_sql_mailbox_);
	SQLBindCol(m_hstmt_, 8, SQL_C_CHAR, m_phone_num_, sizeof(m_phone_num_), &m_sql_phone_num_);
	SQLBindCol(m_hstmt_, 9, SQL_C_CHAR, m_address_, sizeof(m_address_), &m_sql_address_);
    return true;
}


/*
 * 说明: 
 *       绑定记录集参数,用于获取存储过程返回值
 * 参数：
 *       is_add       [in]  标志是否是添加员工功能的参数绑定函数：是为true,否则为false
 *       error_info   [out] 获取错误信息
 * 返回值: 
 *       执行成功返回true, 否则返回false
 */
bool CStaffForm::BindingParameter(bool is_add, std::string &error_info)
{
	m_sql_id_=SQL_NTS;         /* the staff's id in database Staff form */
	m_sql_name_=SQL_NTS;       /* the staff's name in database Staff form */
	m_sql_sex_=SQL_NTS;        /* the staff's sex in database Staff form */
	m_sql_age_=SQL_NTS;        /* the staff's age in database Staff form */
	m_sql_salary_=SQL_NTS;     /* the staff's salary in database Staff form */
	m_sql_dept_num_=SQL_NTS;   /* the staff's department number in database Staff form */
	m_sql_dept_name_=SQL_NTS;  /* the staff's department name in database Dept form */
	m_sql_mailbox_=SQL_NTS;    /* the staff's mailbox in database Dept form */
	m_sql_phone_num_=SQL_NTS;  /* the staff's phone number in database Dept form */
	m_sql_address_=SQL_NTS;    /* the staff's address in database Dept form */
	m_sql_pro_ret =SQL_NTS;
	m_sql_old_id_ =SQL_NTS;

	/*绑定存储过程返回值*/
	m_return_code_ = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, \
		                              SQL_INTEGER,0, 0,&m_pro_ret, 0, &m_sql_pro_ret);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定返回值失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
    /* 绑定列参数*/
    m_return_code_ = SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, \
									SQL_CHAR, sizeof(m_id_)-1, 0, m_id_, sizeof(m_id_), &m_sql_id_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定参数2失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, \
		                              SQL_CHAR, sizeof(m_name_)-1, 0, m_name_, sizeof(m_name_), &m_sql_name_);
   	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定参数3失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, \
		                             SQL_CHAR, sizeof(m_sex_)-1, 0, m_sex_, sizeof(m_sex_),  &m_sql_sex_);
   	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定参数4失败!";
			ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 5, SQL_PARAM_INPUT, SQL_C_SSHORT,\
									 SQL_SMALLINT, 0, 0, &m_age_, 0, &m_sql_age_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定参数5失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 6, SQL_PARAM_INPUT, SQL_C_FLOAT, \
		                              SQL_FLOAT, 0, 0, &m_salary_, 0, &m_sql_salary_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定参数6失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 7, SQL_PARAM_INPUT, SQL_C_CHAR,\
		                             SQL_CHAR, sizeof(m_dept_name_)-1, 0, m_dept_name_, 0, &m_sql_dept_name_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定参数7失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 8, SQL_PARAM_INPUT, SQL_C_CHAR,\
		                              SQL_CHAR, sizeof(m_mailbox_)-1, 0, m_mailbox_, 0, &m_sql_mailbox_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定参数8失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 9, SQL_PARAM_INPUT, SQL_C_CHAR, \
		                              SQL_CHAR, sizeof(m_phone_num_)-1, 0, m_phone_num_, 0, &m_sql_phone_num_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定参数9失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	m_return_code_ = SQLBindParameter(m_hstmt_, 10, SQL_PARAM_INPUT, SQL_C_CHAR, \
		                              SQL_CHAR, sizeof(m_address_)-1, 0, m_address_, 0, &m_sql_address_);
	if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        error_info = "绑定参数10失败!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
        return false;
    }
	/*绑定员工的旧ID*/
	if (is_add == false)
	{
		m_return_code_ = SQLBindParameter(m_hstmt_, 11, SQL_PARAM_INPUT, \
			SQL_C_CHAR, SQL_CHAR, sizeof(m_old_id_)-1, 0, m_old_id_, 0, &m_sql_old_id_);
		if ((m_return_code_ != SQL_SUCCESS) &&
			(m_return_code_ != SQL_SUCCESS_WITH_INFO))
		{
			error_info = "绑定参数11失败!";
			ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
			return false;
		}
	}
	return true;
}

/*
 * 说明： 新增员工信息
 * 参数：
 *        staff_info	     [in] 员工信息
 *         error_info		 [out] 错误信息
 * 返回值：
 *        执行成功返回true,否则返回false
 **/
bool CStaffForm::InsertInfo(STAFFINFO * staff_info,   std::string &error_info)
{
	/*检查输入是否正确*/
	if (false == CheckStaff(staff_info, error_info))
	{
		return false;
	}
	/*填充员工数据*/
	if (false == SetStaff(staff_info, error_info))
	{
		return false;
	}
	/*绑定存储过程返回值和传入参数*/
	if(false ==BindingParameter(true, error_info))
	{
		return false;
	}
	/*执行存储过程*/
	m_return_code_ = SQLExecDirect(m_hstmt_, (unsigned char *)"{? = call InsertStaff (?,?,?,?,?,?,?,?,?)}", SQL_NTS);
	if ((m_return_code_ != SQL_SUCCESS) &&
		(m_return_code_ != SQL_SUCCESS_WITH_INFO))
	{
		error_info = "执行修改用户存储过程出错!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
		return false;
    }
	while ( ( m_return_code_ = SQLMoreResults(m_hstmt_) ) != SQL_NO_DATA )
	{
	}
	if (m_pro_ret != 0)
	{
		error_info="员工编号不能重复！";
		return false;
	}
    return true;
}

/*
 * 说明： 删除员工信息
 * 参数：
 *        user_id [in] 员工编号
 *        error_info [out] 错误信息
 * 返回值：
 *        执行成功返回true,否则返回false
 **/
bool CStaffForm::DeleteInfo(const char *user_id, std::string &error_info)
{
	char delete_sql[500];
	sprintf (delete_sql, "execute DeleteStaff '%s'", user_id);/*格式化删除语句*/
	/* 执行语句 */
    if (false == ExecuteSQL(delete_sql, error_info))
    {
		error_info = "删除员工数据失败！";
        return false;
    }
	return true;
}


/*
 * 说明： 更新员工信息
 * 参数：
 *        staff_info	     [in] 员工信息
 *        error_info		 [out] 错误信息
 *返回值：
 *        执行成功返回true,否则返回false
 **/
bool CStaffForm::UpdateInfo(STAFFINFO * staff_info,	 std::string &error_info)
{
	if (false == CheckStaff(staff_info,error_info))
	{
		return false;
	}
	if (false == SetStaff(staff_info, error_info))
	{
		return false;
	}
	if (false == BindingParameter(false, error_info))
	{
		return false;
	}
	m_return_code_ = SQLExecDirect(m_hstmt_, (unsigned char *)"{? = call UpdateStaff (?,?,?,?,?,?,?,?,?,?)}", SQL_NTS);
	if ((m_return_code_ != SQL_SUCCESS) &&
		(m_return_code_ != SQL_SUCCESS_WITH_INFO))
	{
		error_info = "执行修改用户存储过程出错!";
		ReportError(m_hstmt_, SQL_HANDLE_STMT, error_info);
		return false;
    }
	/*TDDO:添加错误处理*/
	while ( ( m_return_code_ = SQLMoreResults(m_hstmt_) ) != SQL_NO_DATA )
	{
	}
	if (m_pro_ret != 0)
	{
		error_info="员工编号不能重复！";
		return false;
	}
	return true;
}


/* 说明：
 *    统计员工数量
 * 返回值
 *       成功返回员工数量，失败返回-1
 */
int CStaffForm::GetStaffSum()
{
	int staff_sum=-1;
	SQLINTEGER sql_sum;
	std::string error;
	char *sql_select_sum="select count(*) from Staff";
	if (false == ExecuteSQL(sql_select_sum, error))
	{
		MessageBox(NULL, error.c_str(), TEXT("统计员工数量出错"), MB_OK);
		return staff_sum;
	}
	SQLBindCol(m_hstmt_, 1, SQL_C_SLONG, &staff_sum, sizeof(staff_sum), &sql_sum);
	MoveFirst();
	return staff_sum;
}

/*
 * 说明：
 *      检查员工数据是否正确
 * 参数：
 *      staff_info    [in]  员工信息
 *      error_info    [out]  错误信息
 * 返回值：
 *       成功返回true,否则返回false
 */
bool CStaffForm::CheckStaff(STAFFINFO * staff_info,std::string &error_info)
{
	if (strlen(staff_info->id.c_str())>sizeof(m_id_)-1)
	{
		error_info ="员工编号太长！  规定员工编号最长为8个英文或数字";
		return false;
	}
	if (strlen(staff_info->name.c_str())>sizeof(m_name_)-1)
	{
		error_info = "员工姓名太长 ！ 规定员工姓名最长为9个英文字符或4个汉字";
		return false;
	}
	if (atoi(staff_info->age.c_str())<16||atoi(staff_info->age.c_str())>150)
	{
		error_info = "员工年龄不正确，请仔细检查！";
		return false;
	}
	if (atof(staff_info->salary.c_str())<0||atof(staff_info->salary.c_str())>12345678)
	{
		error_info = "员工工资不正确，请仔细检查！";
		return false;
	}
	if (NULL == strchr(staff_info->email_address.c_str(), '@'))
	{
		error_info = "员工邮箱格式不正确，请仔细检查！";
		return false;
	}
	if (strlen(staff_info->email_address.c_str())>sizeof(m_mailbox_)-1)
	{
		error_info = "员工邮箱地址太长，正确输入！";
		return false;
	}
	if (staff_info->phone.length() != 11)
	{
		error_info = "员工电话号码为11位，请修正！";
		return false;
	}
	if (strlen(staff_info->address.c_str())>sizeof(m_address_)-1)
	{
		error_info = "员工地址长度太长，请适当减少输入！";
		return false;
	}
	return true;
}



/*
 * 说明：
 *      填充员工信息
 * 参数：
 *      staff_info    [in]  员工信息
 *      error_info    [out]  错误信息  
 * 返回值：
 *       成功返回true,否则返回false
 */
bool CStaffForm::SetStaff(STAFFINFO * staff_info,std::string &error_info)
{
	if (NULL == strcpy(m_old_id_, staff_info->old_id.c_str()))
	{
		return false;
	}
	if (NULL == strcpy(m_id_, staff_info->id.c_str()))
	{
		return false;
	}
	if (NULL == strcpy(m_name_, staff_info->name.c_str()))
	{
		return false;
	}
	if (NULL == strcpy(m_sex_, staff_info->sex.c_str()))
	{
		return false;
	}
	m_age_ = (short)atoi(staff_info->age.c_str());
	m_salary_ = atof(staff_info->salary.c_str());
	char department[41];
	DeleteSpace(staff_info->department.c_str(), department);
	if (NULL == strcpy(m_dept_name_, department))
	{
		return false;
	}
	if (NULL == strcpy(m_mailbox_, staff_info->email_address.c_str()))
	{
		return false;
	}
	if (NULL == strcpy(m_phone_num_, staff_info->phone.c_str()))
	{
		return false;
	}
 	if (NULL ==  strcpy(m_address_, staff_info->address.c_str()))
	{
		return false;
	}
	return true;
}
/*
 * @ brief: 获取员工编号，该编号将拥有登录系统权限的人排除在外
 * @ param: err_info [out] 错误信息
 * @ return: 若成功返回true，否则返回false
 **/
bool CStaffForm::GetStaffNo(std::string &err_info) {
	m_sql_pro_ret = SQL_NTS;
	m_sql_id_ = SQL_NTS;
	if (!BindReturn()) {
		ReportError(m_hstmt_, SQL_HANDLE_STMT, err_info);
		return false;
	}
	if (!ExecSQLProc("{? = call GetStaffNo}", err_info)) {
		return false;
	}
	SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_id_, sizeof(m_id_), &m_sql_id_);
	return MoveFirst();
}

/*
 * @ brief: 获取员工姓名
 * @ param: no [in] 员工编号指针
 * @ param: err_info [out] 出错时的错误信息
 * @ return: 执行成功返回ture，否则返回false
 **/
bool CStaffForm::GetStaffName(const char *no, std::string &err_info) {
	m_sql_name_ = SQL_NTS;
	m_return_code_ = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_INPUT, SQL_CHAR, SQL_C_CHAR,\
		                              sizeof(m_id_) - 1, 0, m_id_, sizeof(m_id_), &m_sql_id_);
	strcpy(m_id_, no);
	if (m_return_code_ == SQL_SUCCESS || m_return_code_ == SQL_SUCCESS_WITH_INFO) {
		if (ExecSQLProc("{call GetStaffName(?)}", err_info)) {
			m_return_code_ = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, m_name_, sizeof(m_name_), &m_sql_name_);
			MoveFirst();
			if (m_return_code_ == SQL_SUCCESS || m_return_code_ == SQL_SUCCESS_WITH_INFO) {
				return true;
			}
		}
	}
	return false;
}