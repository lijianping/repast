#include "Err.h"

static const char *errs[] = {
	"�󶨷���ֵʧ��",
	"���������ʧ��",
	"ִ�д洢����ʧ��",
	"�󶨼�¼��ʧ��",
	"ȡ�м�¼��ʧ��",
	"���价�����ʧ��",
	"����ODBC�汾�Ļ�������ʧ��",
	"�������Ӿ��ʧ��",
	"��������Դʧ��",
	"����Ϊ��",
	"���볤�ȳ�����Χ",
	"�����ֵ�Ѵ���",
	"���������ʧ��",
	"�ͷ������ʧ��",
	"�������ݿ�ʧ��",
	"���ݿ�ָ�ʧ��",
	"�ر��α�ʧ��",
	"��������̨������ʹ��",
	"�����Ѵ���",
	"¥�㲻����",
	"���䲻����"
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
