#ifndef REPAST_FLOORINFO_H_
#define REPAST_FLOORINFO_H_

#include "Err.h"
#include "dbform.h"


#define ADDFLOOR 0
#define UPDATEFLOOR 1
#define DELETEFLOOR 2

struct FLOORINFO
{
	std::string no;
	std::string old_no;
	std::string name;
};

class FloorInfo : public CDBForm
{
public:
	FloorInfo(void);
	~FloorInfo(void);
	void Initialize();
	bool GetFloorName();
	inline char* floor_name();
	inline char* floor_no();
	bool GetFloorSet();
	bool Bind(int bind_type);
	void SetFloor(FLOORINFO *floor_info);
	bool CheckFloor(FLOORINFO *floor_info);
	bool AddFloor(FLOORINFO *floor_info);
	bool UpdateFloor(FLOORINFO *floor_info);
	bool DeleteFloor(FLOORINFO *floor_info);

private:
	char floor_no_[3];           // Â¥²ã±àºÅ
	char floor_old_no_[3];        // Â¥²ãÔ­À´µÄ±àºÅ
	char floor_name_[17];        // Â¥²ãÃû³Æ
	SQLINTEGER sql_floor_no_;    // ¶ÔÓ¦Â¥²ã±àºÅ
	SQLINTEGER sql_floor_old_no_;      // 
	SQLINTEGER sql_floor_name_;  // ¶ÔÓ¦Â¥²ãÃû³Æ
};

/*
 * @ brief; »ñÈ¡Â¥²ãÃû³Æ
 * @ return: Â¥²ãÃû³Æ×Ö·û´®Ö¸Õë
 **/
char* FloorInfo::floor_name() {
	DeleteSpace(floor_name_, floor_name_);
	return floor_name_;
}

/*
 * @brief; »ñÈ¡Â¥²ã±àºÅ
 * @ return: Â¥²ã±àºÅ×Ö·û´®Ö¸Õë
 **/
char* FloorInfo::floor_no()
{
	DeleteSpace(floor_no_,floor_no_);
	return floor_no_;
}
#endif