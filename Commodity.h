// Commodity.h: interface for the CCommodity class.
//
//////////////////////////////////////////////////////////////////////

#ifndef REPAST_COMMODITY_H_
#define REPAST_COMMODITY_H_

#include "Err.h"
#include "DBForm.h"


#define ADDCOM 1
#define UPDATECOM 2
#define DELETECOM 3

/* ��Ʒ��Ϣ */
struct CommodityInfo {
	UINT menu_id;                            // ��ťid
	std::string commodity_no;                // ��Ʒ���
	std::string com_old_no;                  // ��Ʒԭ���ı�ţ��޸���Ʒ��Ϣʱʹ��
	std::string commodity_name;              // ��Ʒ����
	std::string commodity_purchase;          // ��Ʒ����
	std::string commodity_sum;               // ��Ʒ����
	std::string commodity_main_category;     // ��Ʒ�����
	std::string commodity_child_category;    // ��Ʒ�����
	std::string commodity_unit;              // ��Ʒ��λ
	std::string commodity_sale;              // ��Ʒ����
	std::string commodity_register_date;     // ��Ʒע��ʱ��
};

class CCommodity: public CDBForm
{
public:
	CCommodity();
	virtual ~CCommodity();
	bool GetCommodityNameSet(const char* main_name, const char *child_name);
	bool GetCommodityNameSet(const char* main_name);
	bool GetCategoryByComNO(const char* com_no);
	bool CheckCommodity(const CommodityInfo *com_info);
	void SetCommodity(const CommodityInfo *com_info);
	bool Bind(int bind_type);
	bool AddCom(const CommodityInfo *com_info);
	bool UpdateCom(const CommodityInfo *com_info);
	bool DeleteCom(const std::string com_no);
	
	inline char* no();
	inline char* name();
	inline float purchase_price() const;
	inline int quantity() const;
	inline char* child_name();	
	inline char* unit();
	inline char* main_name();
	inline float sale_price() const;
	inline char* register_date();

protected:
	void Initialize();
	virtual bool BindingParameter();

private:
	char m_no_[9];            // ��Ʒ���
	char m_old_no_[9];        // ��Ʒԭ���ı��
	char m_name_[257];        // ��Ʒ����
	float m_purchase_price_;  // ��Ʒ����
	int m_quantity_;          // ��Ʒ����
	char m_child_name_[33];   // �˷�������
	char m_main_name_[33];    // ����������
	char m_unit_[9];          // ��Ʒ��λ
	float m_sale_price_;      // ��Ʒ����
	char m_register_date_[20];// ��Ʒע������
	
	SQLINTEGER m_sql_no_;
	SQLINTEGER m_sql_old_no_;
	SQLINTEGER m_sql_name_;        // ��Ӧ��Ʒ����
	SQLINTEGER m_sql_purchase_price_;
	SQLINTEGER m_sql_quantity_;
	SQLINTEGER m_sql_child_name_;  // ��Ӧ�˷�������	
	SQLINTEGER m_sql_main_name_;   // ��Ӧ����������
	SQLINTEGER m_sql_unit_;
	SQLINTEGER m_sql_sale_price_;
	SQLINTEGER m_sql_register_date_;

};

/*
 * @ brief: ��ȡ��Ʒ���
 * @ return: ��Ʒ����ַ�ָ��
 **/
char *CCommodity::no() {
	DeleteSpace(m_no_, m_no_);
	return m_no_;
}

/*
 * @ brief: ��ȡ��Ʒ����
 * @ return: ָ����Ʒ���Ƶ��ַ���ָ��
 **/
char* CCommodity::name() {
	DeleteSpace(m_name_, m_name_);
	return m_name_;
}

/*
 * @ brief: ��ȡ��Ʒ����
 * @ return: ��Ʒ����
 **/
float CCommodity::purchase_price() const {
	return m_purchase_price_;
}

/*
 * @ brief: ��ȡ��Ʒ����
 * @ return: ��Ʒ����
 **/
int CCommodity::quantity() const {
	return m_quantity_;
}

/*
 * ˵����
 *    ��ȡ����Ʒ�������ӷ���
 * ����ֵ��
 *    ����Ʒ�������ӷ�����ַ���ָ��
 */
char* CCommodity::child_name()
{
	DeleteSpace(m_child_name_,m_child_name_);
	return m_child_name_;
}

/*
 * ˵����
 *    ��ȡ����Ʒ������������
 * ����ֵ��
 *    ����Ʒ��������������ַ���ָ��
 */
char* CCommodity::main_name()
{
	DeleteSpace(m_main_name_,m_main_name_);
	return m_main_name_;
}
/*
 * @ brief: ��ȡ��Ʒ��λ��Ϣ
 * @ return: ��Ʒ��λ�ַ�ָ��
 **/
char* CCommodity::unit() {
	DeleteSpace(m_unit_, m_unit_);
	return m_unit_;
}

/*
 * @ brief: ��ȡ��Ʒ����
 * @ return: ��Ʒ����
 **/
float CCommodity::sale_price() const {
	return m_sale_price_;
}

/*
 * @ brief: ��ȡע������
 * @ return: ע�������ַ�ָ��
 **/
char* CCommodity::register_date() {
	return m_register_date_;   // ����ɾ���ո�
}

#endif 
