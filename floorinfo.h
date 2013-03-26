#ifndef REPAST_FLOORINFO_H_
#define REPAST_FLOORINFO_H_

#include "Err.h"
#include "dbform.h"
class FloorInfo : public CDBForm
{
public:
	FloorInfo(void);
	~FloorInfo(void);
	void Initialize();
	bool GetFloorName();
	inline char* floor_name();

private:
	char floor_no_[3];           // ¥����
	char floor_name_[33];        // ¥������
	SQLINTEGER sql_floor_no_;    // ��Ӧ¥����
	SQLINTEGER sql_floor_name_;  // ��Ӧ¥������
};

/*
 * @ brief; ��ȡ¥������
 * @ return: ¥�������ַ���ָ��
 **/
char* FloorInfo::floor_name() {
	DeleteSpace(floor_name_, floor_name_);
	return floor_name_;
}
#endif