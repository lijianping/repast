/* 
 * ˵��: ��ʾԱ����Ϣ��list view������̺���
 * */
LRESULT CALLBACK PersonnelList(HWND hwnd, UINT message,
                               WPARAM wParam, LPARAM lParam);

/*
 * ˵��: Ա����ӡ�ɾ�����޸ı༭�Ի�������̺���
 **/
BOOL CALLBACK EditStaff(HWND hwnd, UINT message,
                             WPARAM wParam, LPARAM lParam);
/*
 * ˵��: ��ʼ��Ա����Ϣ�б�
 * ����:
 *       hinstance [in] ����ʵ�����
 *       hwnd [in] list view�����ھ��
 *       information [out] ������Ϣ
 * ����ֵ: ���ɹ�������true�����򷵻�false��
 **/
bool CreateStaffListView(HINSTANCE hinstance, HWND hwnd,
                         std::string &information);

/*
 * ˵��: ��ȡ�ַ������߶�
 * ����:
 *       hwnd [in] ���ھ��
 *       width [out] �ַ����
 *       height [out] �ַ��߶�
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */

bool GetTextInfo(HWND hwnd, int &width, int &height);

/*
 * ˵��: ��������ѯ��������Ͽ�
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateGroupBox(HINSTANCE hinstance, HWND hwnd,
                    std::string &error_info);

/*
 * ˵��: ��������š���ѯ����ѡ��
 * ����:
 *       hinstance [in] ����ʵ�����
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateNumEdit(HINSTANCE hinstance, HWND hwnd,
                   std::string &error_info);

/*
 * ˵��: ��������������ѯ����ѡ��
 * ����:
 *       hinstance [in] ����ʵ�����
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateNameEdit(HINSTANCE hinstance, HWND hwnd,
                    std::string &error_info);

/*
 * ˵��: �������Ա𡯲�ѯ����ѡ��
 * ����:
 *       hinstance [in] ����ʵ�����
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateSexBox(HINSTANCE hinstance, HWND hwnd,
                  std::string &error_info);

/*
 * ˵��: ���������š���ѯ����ѡ��
 * ����:
 *       hinstance [in] ����ʵ�����
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateDeptCombo(HINSTANCE hinstance, HWND hwnd,
                     std::string &error_info);

/*
 * ˵��: ������Ա����������ѯ��ʾ
 * ����:
 *       hinstance [in] ����ʵ�����
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateStaffSum(HINSTANCE hinstance, HWND hwnd,
                    std::string &error_info);

/*
 * ˵��: ������������������ѯ��ʾ
 * ����:
 *       hinstance [in] ����ʵ�����
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateDeptSum(HINSTANCE hinstance, HWND hwnd,
                   std::string &error_info);

/*
 * ˵��: ��������ǰ��������ѯ��ʾ
 * ����:
 *       hinstance [in] ����ʵ�����
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateCurrentSum(HINSTANCE hinstance, HWND hwnd,
                      std::string &error_info);

/*
 * ˵��: ��������ʼ��ѯ����ť
 * ����:
 *       hinstance [in] ����ʵ�����
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreatePersonnelQuery(HINSTANCE hinstance, HWND hwnd,
                          std::string &error_info);

/*
 * ˵��: ��ʼ������
 * ����:
 *       hinstance [in] ����ʵ�����
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 **/
bool InitWindow(HINSTANCE hinstance, HWND hwnd,
                std::string &error_info);

/*
 * ˵��: ��ʼ��������Ϣ
 * ����:
 *       hinstance [in] ����ʵ�����
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 **/
bool ShowInfo(HINSTANCE hinstance, HWND hwnd,
              std::string &error_info);
/*
 * ˵��: ��ʼ��������Ͽ�
 * ����:
 *       hwnd [in] ������Ͽ򸸴��ھ��
 *       id [in] ��Ͽ�id
 * ����ֵ: ���ɹ�����true�����򷵻�false��
 **/
bool InitComboBox(HWND hwnd, int id);

/*
 *˵����   �������ѯ����ť����������������ִ�в�ѯ
 *������  
 *         hwnd        [in]  �����ھ��
 *         error_info  [out] ������Ϣ
 *����ֵ����ִ�гɹ�������true�����򷵻�false��
 */
bool OnStartQuery(HWND hwnd, std::string &error_info);

/*
 *˵����   ִ�в�ѯ���
 *������  
 *         sql_query   [in]  ��ѯ���
 *         error_info  [out] ������Ϣ
 *����ֵ����ִ�гɹ�������true�����򷵻�false��
 */
bool ExecQuery(const char * sql_query, std::string &error_info);

/*
 *˵����   ��ȡ�û��ڱ༭���������id��
 *������  
 *         hwnd   [in]  �����ھ��  
 *����ֵ����ִ�гɹ�������ID�ַ��������򷵻ؿմ�
 */
std::string GetID(HWND hwnd);

/*
 *˵����   ��ȡ�û��ڱ༭�������������
 *������  
 *         hwnd   [in]  �����ھ��  
 *����ֵ����ִ�гɹ������������ַ��������򷵻ؿմ�
 */
std::string GetName(HWND hwnd);

/*
 *˵����   ��ȡ�û�ѡ����Ա�
 *������  
 *         hwnd   [in]  �����ھ��  
 *����ֵ����ִ�гɹ��������Ա��ַ��������򷵻ؿմ�
 */
std::string GetSex(HWND hwnd);

/*
 *˵����   ��ȡ�û�ѡ��Ĳ���
 *������  
 *         hwnd   [in]  �����ھ��  
 *����ֵ����ִ�гɹ������ز����ַ��������򷵻ؿմ�
 */
std::string GetDept(HWND hwnd);

/*
 *˵����   �ж��û��Ƿ�ѡ��������ѡ���
 *������  
 *         hwnd   [in]  �����ھ��  
 *����ֵ������ѡ�������ѡ�з���ture,���򷵻�false
 */
bool IsCheckName(HWND hwnd);

/*
 *˵����   �ж��û��Ƿ�ѡ���Ա�ѡ���
 *������  
 *         hwnd   [in]  �����ھ��  
 *����ֵ������ѡ�������ѡ�з���ture,���򷵻�false
 */
bool IsCheckSex(HWND hwnd);

/*
 *˵����   �ж��û��Ƿ�ѡ�񡰲��š�ѡ���
 *������  
 *         hwnd   [in]  �����ھ��  
 *����ֵ������ѡ�������ѡ�з���ture,���򷵻�false
 */
bool IsCheckDept(HWND hwnd);

/*
 *˵����   ��ʼ���Ӵ��ڣ�Ĭ��ѡ���С��Ա�ť�����������༭��
 *                       �����Ա�ѡ��ť�����ò��������б�            
 *������  
 *         hwnd   [in]  �����ھ��  
 *����ֵ����ִ�гɹ�������ture, ���򷵻�false;
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


