#ifndef REPAST_CDBConnect_H_
#define REPAST_CDBConnect_H_
/* 头文件的包含顺序会影响编译 
 * 应先包含windows.h在包含
 * SQL系列头文件
 */
#include <WINDOWS.H>          
#include <SQLEXT.H>
#include <string>
class CDBConnect  
{
public:
	CDBConnect();
	virtual ~CDBConnect();
    inline bool is_connect();
    inline SQLHENV henv() const;
    inline SQLHDBC hdbc() const;
    bool Connect(CHAR *dsn, CHAR *id, CHAR *password, std::string &information);
    void Disconnect();

private:
    SQLHENV m_henv_;           /* 环境句柄 */
    SQLHDBC m_hdbc_;           /* 连接句柄 */
    SQLRETURN m_return_code_;  /* 执行SQL语句返回码 */
    bool m_is_connect_;        /* 是否连接数据库，true表示已连上 */
};

/*
 * 功能: 获取数据库连接状态
 * 返回值: 返回当前数据库连接状态
 **/
bool CDBConnect::is_connect()
{
    return m_is_connect_;
}

/*
 * 功能: 获取数据源环境句柄
 * 返回值: 返回数据源环境句柄
 **/
SQLHENV CDBConnect::henv() const
{
    return m_henv_;
}

/*
 * 功能: 获取数据源连接句柄
 * 返回值: 返回数据源连接句柄
 **/
SQLHDBC CDBConnect::hdbc() const
{
    return m_hdbc_;
}

#endif /* end #define REPAST_CDBConnect_H_ */
