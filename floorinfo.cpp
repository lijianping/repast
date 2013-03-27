#include "floorinfo.h"


FloorInfo::FloorInfo(void)
{
}


FloorInfo::~FloorInfo(void)
{
}


/*
 * @ brief: 初始化数据
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
 * @ brief: 获取楼层名称
 * @ return: 成功返回true，否则返回false
 **/
bool FloorInfo::GetFloorName() {
	Initialize();
	SQLRETURN sql_ret;
	// 绑定返回值
	sql_ret = SQLBindParameter(m_hstmt_, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER,\
		0, 0, &m_pro_ret, 0, &m_sql_pro_ret);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) 
		LTHROW(BIND_RETURN_ERROR)
	// 执行存储过程
	sql_ret = SQLExecDirect(m_hstmt_, (SQLCHAR *)"{? = call GetFloorName}", SQL_NTS);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO) 
		LTHROW(EXEC_SQL_PROC_ERROR)
	// 绑定记录集
	sql_ret = SQLBindCol(m_hstmt_, 1, SQL_C_CHAR, floor_name_, sizeof(floor_name_), &sql_floor_name_);
	if (sql_ret != SQL_SUCCESS && sql_ret != SQL_SUCCESS_WITH_INFO)
		LTHROW(BIND_RECODE_ERROR)
	return true;
}



/*
 * @ brief: 获取所有楼层信息
 * @ return: 成功返回true，否则返回false
 **/
bool FloorInfo::GetFloorSet()
{
	Initialize();
	BindReturn();
	m_pro_ret = SQLExecDirect(m_hstmt_, (SQLCHAR *)"{? = call GetFloorSet}", SQL_NTS);
	if (m_pro_ret != SQL_SUCCESS && m_pro_ret != SQL_SUCCESS_WITH_INFO) 
		LTHROW(EXEC_SQL_PROC_ERROR)
		// 绑定记录集
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
 *        绑定参数，用于执行更新楼层的数据库操作
 * @ 参数；
 *       bind_type   [in] 绑定类型，可以是ADDFLOOR,UPDATEFLOOR,DELETEFLOOR
 * @ return:
 *      成功返回true，否则返回false
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
	if (bind_type == DELETEFLOOR)//若为绑定执行“删除”操作，只绑定返回值和楼层编号
	{
		return true;
	}
	m_return_code_ = SQLBindParameter(m_hstmt_, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,\
		sizeof(floor_name_)-1, 0, floor_name_, sizeof(floor_name_), &sql_floor_name_);
	if (m_return_code_ != SQL_SUCCESS && m_return_code_ != SQL_SUCCESS_WITH_INFO) 
	{
		LTHROW(BIND_PARAM_ERROR)
	}
	if (bind_type == ADDFLOOR)//若为绑定执行“增加”操作，只绑定返回值、楼层编号、楼层名称
	{
		return true;
	}
	//若为绑定执行“更新”操作，要绑定返回值、楼层编号、楼层名称、原来楼层的编号
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
 * 说明：
 *    检查传入的楼层信息是否符合要求
 * 参数：
 *    floor_info   [in]  指向楼层信息的指针
 * 返回值：
 *      成功返回true, 否则返回flase
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
 * 说明：
 *    新增楼层信息
 * 参数：
 *    floor_info   [in]  指向楼层信息的指针
 * 返回值：
 *      成功返回true, 否则返回flase
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
 * 说明：
 *    更新楼层信息
 * 参数：
 *    floor_info   [in]  指向楼层信息的指针
 * 返回值：
 *      成功返回true, 否则返回flase
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
 * 说明：
 *    删除楼层信息
 * 参数：
 *    floor_info   [in]  指向楼层信息的指针
 * 返回值：
 *      成功返回true, 否则返回flase
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