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
 *       hwnd [in] list view�����ھ��
 *       information [out] ������Ϣ
 * ����ֵ: ���ɹ�������true�����򷵻�false��
 **/
bool CreateStaffListView(HWND hwnd, std::string &information);

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
bool CreateGroupBox(HWND hwnd, std::string &error_info);

/*
 * ˵��: ��������š���ѯ����ѡ��
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateNumEdit(HWND hwnd, std::string &error_info);

/*
 * ˵��: ��������������ѯ����ѡ��
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateNameEdit(HWND hwnd, std::string &error_info);

/*
 * ˵��: �������Ա𡯲�ѯ����ѡ��
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateSexBox(HWND hwnd, std::string &error_info);

/*
 * ˵��: ���������š���ѯ����ѡ��
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateDeptCombo(HWND hwnd, std::string &error_info);

/*
 * ˵��: ������Ա����������ѯ��ʾ
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateStaffSum(HWND hwnd, std::string &error_info);

/*
 * ˵��: ������������������ѯ��ʾ
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateDeptSum(HWND hwnd, std::string &error_info);

/*
 * ˵��: ��������ǰ��������ѯ��ʾ
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreateCurrentSum(HWND hwnd, std::string &error_info);

/*
 * ˵��: ��������ʼ��ѯ����ť
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 */
bool CreatePersonnelQuery(HWND hwnd, std::string &error_info);

/*
 * ˵��: ��ʼ������
 * ����:
 *       hwnd [in] ���ھ��
 *       error_info [out] ����ʧ��ʱ�Ĵ�����Ϣ
 * ����ֵ: ��ִ�гɹ�������true�����򷵻�false��
 **/
bool InitWindow(HWND hwnd, std::string &error_info);