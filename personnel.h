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
 *       hwnd [in] list view父窗口句柄
 *       information [out] 错误信息
 * 返回值: 若成功，返回true，否则返回false。
 **/
bool CreateStaffListView(HWND hwnd, std::string &information);

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
bool CreateGroupBox(HWND hwnd, std::string &error_info);

/*
 * 说明: 创建‘编号’查询条件选项
 * 参数:
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateNumEdit(HWND hwnd, std::string &error_info);

/*
 * 说明: 创建‘姓名’查询条件选项
 * 参数:
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateNameEdit(HWND hwnd, std::string &error_info);

/*
 * 说明: 创建‘性别’查询条件选项
 * 参数:
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateSexBox(HWND hwnd, std::string &error_info);

/*
 * 说明: 创建‘部门’查询条件选项
 * 参数:
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateDeptCombo(HWND hwnd, std::string &error_info);

/*
 * 说明: 创建‘员工人数’查询显示
 * 参数:
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateStaffSum(HWND hwnd, std::string &error_info);

/*
 * 说明: 创建‘部门总数’查询显示
 * 参数:
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateDeptSum(HWND hwnd, std::string &error_info);

/*
 * 说明: 创建‘当前人数’查询显示
 * 参数:
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreateCurrentSum(HWND hwnd, std::string &error_info);

/*
 * 说明: 创建‘开始查询’按钮
 * 参数:
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 */
bool CreatePersonnelQuery(HWND hwnd, std::string &error_info);

/*
 * 说明: 初始化窗口
 * 参数:
 *       hwnd [in] 窗口句柄
 *       error_info [out] 创建失败时的错误信息
 * 返回值: 若执行成功，返回true；否则返回false。
 **/
bool InitWindow(HWND hwnd, std::string &error_info);