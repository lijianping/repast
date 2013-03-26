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
	char floor_no_[3];           // 楼层编号
	char floor_name_[33];        // 楼层名称
	SQLINTEGER sql_floor_no_;    // 对应楼层编号
	SQLINTEGER sql_floor_name_;  // 对应楼层名称
};

/*
 * @ brief; 获取楼层名称
 * @ return: 楼层名称字符串指针
 **/
char* FloorInfo::floor_name() {
	DeleteSpace(floor_name_, floor_name_);
	return floor_name_;
}
#endif