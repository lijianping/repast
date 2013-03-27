#ifndef REPAST_ERR_H_
#define REPAST_ERR_H_

#include <exception>
#include <cstdio>
enum RepastErr {
	BIND_RETURN_ERROR = 0,           // 绑定返回值失败

	BIND_PARAM_ERROR,                // 绑定输入参数失败

	EXEC_SQL_PROC_ERROR,             // 执行存储过程失败

	BIND_RECODE_ERROR,               // 绑定记录集失败

	FETCH_ROWSET_ERROR,              // 取行记录集失败

	ALLOCATE_HANDLE_ERROR,           // 分配环境句柄失败

	SET_ODBC_VERSION_ERROR,          // 设置ODBC版本的环境属性失败

	ALLOCATE_CONNECT_HANDLE_ERROR,   // 分配连接句柄失败

	CONNECT_ERROR,                   // 连接数据源失败

	ALLOCATE_STATEMENT_HANDLE_ERROR, // 分配语句句柄失败

	FREE_STATEMENT_HANDLE_ERROR,     // 释放语句句柄失败

	BACKUP_DATABASE_ERROR,           // 备份数据库失败

	RESTORE_DATABASE_ERROR          // 数据库恢复失败
};
class Err : public std::exception {
public:
	Err(int errcode, const char *file = 0, int line = -1);
	virtual const char* what() const throw();
	int code() const;

private:
	int error_code_;
	int line_;
	const char* file_;
};

#ifdef DEBUG

#define LTHROW(err) throw Err(err, (const char*)__LINE__, (int)__FILE__);
#else

#define LTHROW(err) throw Err(err);
#endif

#endif