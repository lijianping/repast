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
	sql_floor_name_ = SQL_NTS;
	sql_floor_no_ = SQL_NTS;
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