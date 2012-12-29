#ifndef REPAST_TABLEINFO_H_
#define REPAST_TABLEINFO_H_
#include "DBForm.h"

class CTableInfo : public CDBForm
{
public:
	CTableInfo();
	virtual ~CTableInfo();
	enum TableStatu {
		kFounding = 0,       /* 已开台 */
		kNotFounding = 1,    /* 未开台 */
		kBooked = 2          /* 已预定 */
	};
private:
	char m_table_no_[7];     /* 编号 */
	short m_payable_num_;    /* 应纳人数 */
	short m_real_num_;       /* 实纳人数 */
	short m_table_status_;   /* 状态 */

};

#endif // !defined(AFX_TABLEINFO_H__F25E8D17_8722_4F1C_97B8_A3C37606CE23__INCLUDED_)
