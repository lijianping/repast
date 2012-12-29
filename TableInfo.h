#ifndef REPAST_TABLEINFO_H_
#define REPAST_TABLEINFO_H_
#include "DBForm.h"

class CTableInfo : public CDBForm
{
public:
	CTableInfo();
	virtual ~CTableInfo();
	enum TableStatu {
		kFounding = 0,       /* �ѿ�̨ */
		kNotFounding = 1,    /* δ��̨ */
		kBooked = 2          /* ��Ԥ�� */
	};
private:
	char m_table_no_[7];     /* ��� */
	short m_payable_num_;    /* Ӧ������ */
	short m_real_num_;       /* ʵ������ */
	short m_table_status_;   /* ״̬ */

};

#endif // !defined(AFX_TABLEINFO_H__F25E8D17_8722_4F1C_97B8_A3C37606CE23__INCLUDED_)
