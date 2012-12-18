/* 
 * 说明: 显示员工信息的list view处理过程函数
 * */
LRESULT CALLBACK PersonnelList(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam);

/*
 * 说明: 员工添加、删除、修改编辑对话框处理过程函数
 **/
BOOL CALLBACK EditStaff(HWND hwnd, UINT message,
                             WPARAM wParam, LPARAM lParam);
/*
 * 说明: 初始化员工信息列表
 * 参数:
 *       hinstance [in] 程序实例句柄
 *       hwnd [in] list view父窗口句柄
 *       information [out] 错误信息
 * 返回值: 若成功，返回true，否则返回false。
 **/
bool CreateStaffListView(HINSTANCE hinstance, HWND hwnd,
                         std::string &information);

/*
 * 说明: 获取字符宽度与高度
 * 参数:
 *       hwnd [in] 窗口句柄
 *       width [out] 字符宽度
 *       height [out] 字符高度
 * 返回值: 若执行成功，返回true；否则返回false。
 */

bool GetTextInfo(HWND hwnd, int &width, int &height);

/*
 * 说明: 创建‘查询条件’组合框
 * 参数:
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateGroupBox(HINSTANCE hinstance, HWND hwnd,
                    std::string &error_info);

/*
 * 说明: 创建‘编号’查询条件选项
 * 参数:
 *       hinstance [in] 程序实例句柄
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateNumEdit(HINSTANCE hinstance, HWND hwnd,
                   std::string &error_info);

/*
 * 说明: 创建‘姓名’查询条件选项
 * 参数:
 *       hinstance [in] 程序实例句柄
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateNameEdit(HINSTANCE hinstance, HWND hwnd,
                    std::string &error_info);

/*
 * 说明: 创建‘性别’查询条件选项
 * 参数:
 *       hinstance [in] 程序实例句柄
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateSexBox(HINSTANCE hinstance, HWND hwnd,
                  std::string &error_info);

/*
 * 说明: 创建‘部门’查询条件选项
 * 参数:
 *       hinstance [in] 程序实例句柄
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateDeptCombo(HINSTANCE hinstance, HWND hwnd,
                     std::string &error_info);

/*
 * 说明: 创建‘员工人数’查询显示
 * 参数:
 *       hinstance [in] 程序实例句柄
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateStaffSum(HINSTANCE hinstance, HWND hwnd,
                    std::string &error_info);

/*
 * 说明: 创建‘部门总数’查询显示
 * 参数:
 *       hinstance [in] 程序实例句柄
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateDeptSum(HINSTANCE hinstance, HWND hwnd,
                   std::string &error_info);

/*
 * 说明: 创建‘当前人数’查询显示
 * 参数:
 *       hinstance [in] 程序实例句柄
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateCurrentSum(HINSTANCE hinstance, HWND hwnd,
                      std::string &error_info);

/*
 * 说明: 创建‘开始查询’按钮
 * 参数:
 *       hinstance [in] 程序实例句柄
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreatePersonnelQuery(HINSTANCE hinstance, HWND hwnd,
                          std::string &error_info);

/*
 * 说明: 初始化窗口
 * 参数:
 *       hinstance [in] 程序实例句柄
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 **/
bool InitWindow(HINSTANCE hinstance, HWND hwnd,
                std::string &error_info);

/*
 * 说明: 初始化窗口信息
 * 参数:
 *       hinstance [in] 程序实例句柄
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 **/
bool ShowInfo(HINSTANCE hinstance, HWND hwnd,
              std::string &error_info);
/*
 * 说明: 初始化下拉组合框
 * 参数:
 *       hwnd [in] 下拉组合框父窗口句柄
 *       id [in] 组合框id
 * 返回值: 若成功返回true，否则返回false。
 **/
bool InitComboBox(HWND hwnd, int id);

/*
 *说明：   点击“查询”按钮，根据输入条件，执行查询
 *参数：  
 *         hwnd        [in]  主窗口句柄
 *         error_info  [out] 错误信息
 *返回值：若执行成功，返回true；否则返回false。
 */
bool OnStartQuery(HWND hwnd, std::string &error_info);

/*
 *说明：   执行查询语句
 *参数：  
 *         sql_query   [in]  查询语句
 *         error_info  [out] 错误信息
 *返回值：若执行成功，返回true；否则返回false。
 */
bool ExecQuery(const char * sql_query, std::string &error_info);

/*
 *说明：   获取用户在编辑框中输入的id号
 *参数：  
 *         hwnd   [in]  主窗口句柄  
 *返回值：若执行成功，返回ID字符串；否则返回空串
 */
std::string GetID(HWND hwnd);

/*
 *说明：   获取用户在编辑框中输入的姓名
 *参数：  
 *         hwnd   [in]  主窗口句柄  
 *返回值：若执行成功，返回姓名字符串；否则返回空串
 */
std::string GetName(HWND hwnd);

/*
 *说明：   获取用户选择的性别
 *参数：  
 *         hwnd   [in]  主窗口句柄  
 *返回值：若执行成功，返回性别字符串；否则返回空串
 */
std::string GetSex(HWND hwnd);

/*
 *说明：   获取用户选择的部门
 *参数：  
 *         hwnd   [in]  主窗口句柄  
 *返回值：若执行成功，返回部门字符串；否则返回空串
 */
std::string GetDept(HWND hwnd);

/*
 *说明：   判断用户是否选择“姓名”选择框
 *参数：  
 *         hwnd   [in]  主窗口句柄  
 *返回值：返回选择情况，选中返回ture,否则返回false
 */
bool IsCheckName(HWND hwnd);

/*
 *说明：   判断用户是否选择“性别”选择框
 *参数：  
 *         hwnd   [in]  主窗口句柄  
 *返回值：返回选择情况，选中返回ture,否则返回false
 */
bool IsCheckSex(HWND hwnd);

/*
 *说明：   判断用户是否选择“部门”选择框
 *参数：  
 *         hwnd   [in]  主窗口句柄  
 *返回值：返回选择情况，选中返回ture,否则返回false
 */
bool IsCheckDept(HWND hwnd);

/*
 *说明：   初始化子窗口：默认选择“男”性别按钮，禁用姓名编辑框，
 *                       禁用性别选择按钮，禁用部门下来列表            
 *参数：  
 *         hwnd   [in]  主窗口句柄  
 *返回值：若执行成功，返回ture, 否则返回false;
 */
bool InitChildWind(HWND hwnd);


/* struct define */
typedef struct StaffInfo
{
    std::string id;
    std::string name;
    std::string sex;
    std::string age;
    std::string salary;
}STAFFINFO;


