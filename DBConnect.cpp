// DBConnect.cpp: implementation of the CDBConnect class.
//
//////////////////////////////////////////////////////////////////////

#include "DBConnect.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBConnect::CDBConnect()
{

}

CDBConnect::~CDBConnect()
{

}

/*
 * 功能: 连接数据源
 * 参数:
 *            dsn [in] 数据源名称
 *             id [in] 数据用户登录名
 *       password [in] 数据库用户密码
 *        string  [out] 连接失败错误原因
 * 返回值: 返回数据库连接状态，已连接返回true，否则返回false。
 **/
bool CDBConnect::Connect(CHAR *dsn, CHAR *id, CHAR *password, std::string &information)
{
    /* 分配环境句柄 */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &m_henv_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "分配环境句柄失败!";
        return false;
    }
    /* 设置ODBC版本的环境属性 */
    m_return_code_ = SQLSetEnvAttr(m_henv_, SQL_ATTR_ODBC_VERSION,
        (void *)SQL_OV_ODBC3, 0);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "设置ODBC版本的环境属性失败!";
        return false;
    }
    /* 分配连接句柄 */
    m_return_code_ = SQLAllocHandle(SQL_HANDLE_DBC, m_henv_, &m_hdbc_);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
       information = "分配连接句柄失败!";
        return false;
    }
    /* 连接数据源 */
    /* 调试：若连接失败，请重启数据库服务 */
    m_return_code_ = SQLConnect(m_hdbc_, (SQLCHAR *)dsn, 
        SQL_NTS,(SQLCHAR *)id, SQL_NTS,
        (SQLCHAR *)password, SQL_NTS);
    if ((m_return_code_ != SQL_SUCCESS) &&
        (m_return_code_ != SQL_SUCCESS_WITH_INFO))
    {
        information = "连接数据源失败!";
        return false;
    }
    m_is_connect_ = true;
    return m_is_connect_;
}

/*
 * 功能: 断开与数据源的连接，释放资源
 **/
void CDBConnect::Disconnect()
{
    /*
     * HIT: There has something that we are not 
     *      clear. When you disconnect database,
     *      if has something wrong, you can check
     *      here.
     **/
    if (true == m_is_connect_)
    {
        m_is_connect_ = false;
    }
    if (NULL != m_hdbc_)
    {
        SQLDisconnect(m_hdbc_);
        SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc_);
    }
    if (NULL != m_henv_)
    {
        SQLFreeHandle(SQL_HANDLE_ENV, m_henv_);
    }
}