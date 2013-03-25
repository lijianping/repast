#include "Err.h"

static const char *errs[] = {
	"绑定返回值失败",
	"绑定输入参数失败",
	"执行存储过程失败",
	"绑定记录集失败",
	"取行记录集失败"
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
