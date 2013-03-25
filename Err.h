#ifndef REPAST_ERR_H_
#define REPAST_ERR_H_

#include <exception>
#include <cstdio>
enum RepastErr {
	BIND_RETURN_ERROR = 0,           // �󶨷���ֵʧ��
	BIND_PARAM_ERROR,                // ���������ʧ��
	EXEC_SQL_PROC_ERROR,             // ִ�д洢����ʧ��
	BIND_RECODE_ERROR,               // �󶨼�¼��ʧ��
	FETCH_ROWSET_ERROR              // ȡ�м�¼��ʧ��
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