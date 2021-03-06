#include "Err.h"

static const char *errs[] = {
	"绑定返回值失败",
	"绑定输入参数失败",
	"执行存储过程失败",
	"绑定记录集失败",
	"取行记录集失败",
	"分配环境句柄失败",
	"设置ODBC版本的环境属性失败",
	"分配连接句柄失败",
	"连接数据源失败",
	"输入为空",
	"输入长度超出范围",
	"输入的值已存在",
	"分配语句句柄失败",
	"释放语句句柄失败",
	"备份数据库失败",
	"数据库恢复失败",
	"关闭游标失败",
	"房间下有台号正在使用",
	"名称已存在",
	"拒绝操作，该项正在被使用，请稍后再试",
	"楼层不存在",
	"房间不存在"
};


Err::Err(int errcode, const char *file, int line)
{
	this->error_code_ = errcode;
	this->line_ = line;
	this->file_ = file;
}

const char* Err::what() const throw()
{
	static char msg[100];

	if(file_ && line_ !=-1){
		sprintf(msg, "FILE:%s,LINE:%d : %s", file_, line_ ,errs[error_code_]);
		return msg;
	}

	return errs[error_code_];
}

int Err::code() const
{
	return error_code_;
}
