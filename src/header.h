


typedef struct  stStaffInfo_Tag
{
	char cName[20];
	int iAge;
	int iSalary;
	long lID;
	//int iLevel;
	//bool bGender;
	//int iAttribute;
	struct stStaffInfo_Tag* stNext;
}StaffInfo;

int CreateUser(StaffInfo* Staff);
int ShowList(StaffInfo* Head);
StaffInfo *SearchItem(StaffInfo* stHead);
StaffInfo *AddDelEditNode(StaffInfo* stHead);
int SaveLinkList(StaffInfo* stHead);
StaffInfo *DeleteItem(StaffInfo* stHead,StaffInfo* stDelete);
StaffInfo *ReorderList(StaffInfo* stHead);
int ReleaseList(StaffInfo* stHead);
StaffInfo *ReorderList2(StaffInfo* stHead);
