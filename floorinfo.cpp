#include "floorinfo.h"


FloorInfo::FloorInfo(void)
{
}


FloorInfo::~FloorInfo(void)
{
}


/*
 * @ brief: ��ʼ������
 **/
void FloorInfo::Initialize() {
	memset(floor_name_, 0, sizeof(floor_name_));
	memset(floor_no_, 0, sizeof(floor_no_));
	memset(floor_old_no_,0, sizeof(floor_old_no_));
	m_sql_pro_ret = SQL_NTS;
	sql_floor_name_ = SQL_NTS;
	sql_floor_no_ = SQL_NTS;
	sql_floor_old_no_ = SQL_NTS;
}

/*
 * @ brief: ��ȡ¥������
 * @ return: �ɹ�����true�����򷵻�false
 **/
bool FloorInfo::GetFloorName() {
	Initialize();
	SQLRETURN sql_ret;
	// �󶨷���ֵ
	sql_ret = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER,\
		0, 0, &m_pro_ret, 0, &m_sql_pro_ret);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RETURN_ERROR)
	// ִ�д洢����
	sql_ret = SQLExecDirect(m_hstmt_, (SQLCHAR *)"{? = call GetFloorName}", SQL_NTS);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) 
		LTHROW(EXEC_SQL_PROC_ERROR)
	// �󶨼�¼��
	sql_ret = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, floor_name_, sizeof(floor_name_), &sql_floor_name_);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	return true;
}



/*
 * @ brief: ��ȡ����¥����Ϣ
 * @ return: �ɹ�����true�����򷵻�false
 **/
bool FloorInfo::GetFloorSet()
{
	Initialize();
	BindReturn();
	m_pro_ret = SQLExecDirect(m_hstmt_, (SQLCHAR *)"{? = call GetFloorSet}", SQL_NTS);
	if (m_pro_ret != SQL_SUCCESS && m_pro_ret != SQL_SUCCESS_WITH_INFO) 
		LTHROW(EXEC_SQL_PROC_ERROR)
		// �󶨼�¼��
		m_pro_ret = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, floor_no_, sizeof(floor_no_), &sql_floor_no_);
	if (m_pro_ret != SQL_SUCCESS && m_pro_ret != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
		m_pro_ret = SQLBindCol(m_hstmt_, 2, SQL_C_CHAR, floor_name_, sizeof(floor_name_), &sql_floor_name_);
	if (m_pro_ret != SQL_SUCCESS && m_pro_ret != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	return true;
}


/*
 * @ brief:
 *        �󶨲���������ִ�и���¥������ݿ����
 * @ ������
 *       bind_type   [in] �����ͣ�������ADDFLOOR,UPDATEFLOOR,DELETEFLOOR
 * @ return:
 *      �ɹ�����true�����򷵻�false
 **/
bool FloorInfo::Bind(int bind_type)
{
	Initialize();
	BindReturn();
	m_return_code_ =SQLBindParameter(m_hstmt_, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		sizeof(floor_no_)-1, 0, floor_no_, sizeof(floor_no_), &sql_floor_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
	{
		LTHROW(BIND_PARAM_ERROR)
	}
	if (bind_type == DELETEFLOOR)//��Ϊ��ִ�С�ɾ����������ֻ�󶨷���ֵ��¥����
	{
		return true;
	}
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		sizeof(floor_name_)-1, 0, floor_name_, sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
	{
		LTHROW(BIND_PARAM_ERROR)
	}
	if (bind_type == ADDFLOOR)//��Ϊ��ִ�С����ӡ�������ֻ�󶨷���ֵ��¥���š�¥������
	{
		return true;
	}
	//��Ϊ��ִ�С����¡�������Ҫ�󶨷���ֵ��¥���š�¥�����ơ�ԭ��¥��ı��
	m_return_code_ = SQLBindParameter(m_hstmt_, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		sizeof(floor_old_no_)-1, 0, floor_old_no_, sizeof(floor_old_no_), &sql_floor_old_no_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
	{
		LTHROW(BIND_PARAM_ERROR)
	}
	return true;
}
void FloorInfo::SetFloor(FLOORINFO *floor_info)
{
	strcpy(floor_no_,floor_info->no.c_str());
	strcpy(floor_old_no_, floor_info->old_no.c_str());
	strcpy(floor_name_,floor_info->name.c_str());
}

/*
 * ˵����
 *    ��鴫���¥����Ϣ�Ƿ����Ҫ��
 * ������
 *    floor_info   [in]  ָ��¥����Ϣ��ָ��
 * ����ֵ��
 *      �ɹ�����true, ���򷵻�flase
 */
bool FloorInfo::CheckFloor(FLOORINFO *floor_info)
{
	if (floor_info->no.length()==0)
	{
		LTHROW(INPUT_NULL_ERROR)
	}
	if (floor_info->no.length()>sizeof(floor_no_)-1)
	{
		LTHROW(INPUT_TOO_LONG_ERROR)
	}
	if (floor_info->name.length()==0)
	{
		LTHROW(INPUT_NULL_ERROR)
	}
	if (floor_info->name.length()>sizeof(floor_name_)-1)
	{
		LTHROW(INPUT_TOO_LONG_ERROR)
	}
	return true;
}

/*
 * ˵����
 *    ����¥����Ϣ
 * ������
 *    floor_info   [in]  ָ��¥����Ϣ��ָ��
 * ����ֵ��
 *      �ɹ�����true, ���򷵻�flase
 */
bool FloorInfo::AddFloor(FLOORINFO *floor_info)
{
	CheckFloor(floor_info);
	Bind(ADDFLOOR);
	SetFloor(floor_info);
	ExecSQLProc("{?=call AddFloor(?,?)}");
	IsSQLProcRetRight();
	return true;
}

/*
 * ˵����
 *    ����¥����Ϣ
 * ������
 *    floor_info   [in]  ָ��¥����Ϣ��ָ��
 * ����ֵ��
 *      �ɹ�����true, ���򷵻�flase
 */
bool FloorInfo::UpdateFloor(FLOORINFO *floor_info)
{
	CheckFloor(floor_info);
	Bind(UPDATEFLOOR);
	SetFloor(floor_info);
	ExecSQLProc("{?=call UpdateFloor(?,?,?)}");
	IsSQLProcRetRight();
	return true;
}

/*
 * ˵����
 *    ɾ��¥����Ϣ
 * ������
 *    floor_info   [in]  ָ��¥����Ϣ��ָ��
 * ����ֵ��
 *      �ɹ�����true, ���򷵻�flase
 */
bool FloorInfo::DeleteFloor(FLOORINFO *floor_info)
{
//	CheckFloor(floor_info);
	Bind(DELETEFLOOR);
	SetFloor(floor_info);
	ExecSQLProc("{?=call DeleteFloor(?)}");
	IsSQLProcRetRight();
	return true;
}