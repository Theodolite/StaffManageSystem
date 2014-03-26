

#include "stdafx.h"
#include "stdio.h"
#include "header.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int CreateUser(StaffInfo* Staff)
{
	system("cls");
	fflush(stdin);
	printf("*********Adding new items**********\n");
	printf("Name:");
	gets(Staff->cName);
	printf("%s",Staff->cName);
	printf("\nAge:");
	scanf("%d",&Staff->iAge);
	printf("%d",Staff->iAge);
	printf("\nID:");
	scanf("%d",&Staff->lID);
	printf("%d",Staff->lID);
	printf("\nSalary:");
	scanf("%d",&Staff->iSalary);
	printf("%d\n",Staff->iSalary);
	Staff->stNext=NULL;
	return(0);
}

int ShowList(StaffInfo* Head)
{
	StaffInfo* stCurrent=NULL;
	stCurrent=Head;
	printf("Now\n*******************************************************\n");
	printf("Name			Age		Salary		ID\n");
	while(stCurrent!=NULL)
	{
		printf("%s		",stCurrent->cName);
		printf("%d		",stCurrent->iAge);
		printf("%d		",stCurrent->iSalary);
		printf("%d\n",stCurrent->lID);
		stCurrent=stCurrent->stNext;	
	}
	printf("******************************************************\n");
	printf("(Q)uit/(E)dit:");
	return(0);
}

StaffInfo *SearchItem(StaffInfo* stHead)
{
	char cKeyRecv;
	char cName[20];
	long lID;
	StaffInfo* stSearch=NULL;
	stSearch=stHead;
	fflush(stdin);
	printf("********Searching********\n");
	printf("Search by?\n1.Name\n2.ID\n");
	if((cKeyRecv=getchar())=='1')
	{
		fflush(stdin);
		printf("Name:");
		gets(cName);
		while(stSearch!=NULL)
		{
			if(!(stricmp(cName,stSearch->cName)))
			{
				return(stSearch);
			}
			stSearch=stSearch->stNext;
			
		}
		return(NULL);
	}
	else if(cKeyRecv=='2')
	{
		fflush(stdin);
		printf("ID:");
		scanf("%d",&lID);
		while(stSearch!=NULL)
		{
			if(stSearch->lID==lID)
			{
				return(stSearch);
			}
			stSearch=stSearch->stNext;
			
		}
		return(NULL);
	}
}

StaffInfo *AddDelEditNode(StaffInfo* stHead)
{
	int ret;
	StaffInfo* stCurrent=NULL;
	StaffInfo* stNew=NULL;
	char KeyRecv;

	printf("1.Add\n2.Delete\n3.Edit ");
	fflush(stdin);
	switch(getchar())
	{
		case('1'):
			system("cls");
			stCurrent=stHead;
			while(stCurrent->stNext!=NULL)
				stCurrent=stCurrent->stNext;
			stNew = (StaffInfo*)malloc(sizeof(StaffInfo));
			ret = CreateUser(stNew);
			stCurrent->stNext=stNew;
			
			break;
			
		case('2'):
			printf("Who you want to delete:\n");
			if((stCurrent=SearchItem(stHead))!=NULL)
			{
				stHead=DeleteItem(stHead,stCurrent);
			}
			break;
		case('3'):
			printf("Insert the member you wanna edit:\n");
			if((stCurrent=SearchItem(stHead))!=NULL)
			{
				system("cls");
				printf("Change item\n");
				printf("*******************************************************\n");
				printf("Name			Age		Salary		ID\n");
				printf("%s		",stCurrent->cName);
				printf("%d		",stCurrent->iAge);
				printf("%d		",stCurrent->iSalary);
				printf("%d\n",stCurrent->lID);
				printf("******************************************************\n");
				printf("Name:");
				scanf("%s",&stCurrent->cName);
				printf("\nAge:");
				scanf("%d",&stCurrent->iAge);
				printf("\nSalary:");
				scanf("%d",&stCurrent->iSalary);
				printf("\nID:");
				scanf("%d",&stCurrent->lID);
			}
			break;
	}
	printf("Changed successfully!\nSave to file now?(Y/N):");
	fflush(stdin);
	scanf("%c",&KeyRecv);
	while((KeyRecv!='Y')&(KeyRecv!='y')&(KeyRecv!='	N')&(KeyRecv!='n'))
	{
		scanf("%c",&KeyRecv);
	}
	if((KeyRecv=='Y')||(KeyRecv=='y'))
	{
		SaveLinkList(stHead);
	}


return(stHead);

}
int SaveLinkList(StaffInfo* stHead)
{
	FILE* fp;
	char filename[20]="d:\\Output";
	StaffInfo* stCurrent;
	stCurrent=stHead;
	
	fp=fopen(filename,"w+");
	if(fp!=NULL)
		printf("Output document created");
	while(stCurrent!=NULL)
	{
		fprintf(fp,"%s %d %d %d \n",stCurrent->cName,stCurrent->iAge,stCurrent->iSalary,stCurrent->lID);
		stCurrent=stCurrent->stNext;
	}
	fclose(fp);
	return(0);
}

StaffInfo *DeleteItem(StaffInfo* stHead,StaffInfo* stDelete)
{
	StaffInfo* stNew=NULL;
	if(stDelete==stHead)
	{
		stHead=stHead->stNext;
		free(stDelete);
	}
	else if(stDelete->stNext==NULL)
	{
		stDelete=stHead;
		while(stDelete->stNext!=NULL)
		{
			stNew=stDelete;
			stDelete=stDelete->stNext;
		}
		stNew->stNext=stDelete->stNext;
		free(stDelete);
	}
	else
	{
		stNew=stHead;
		while(stNew->stNext!=stDelete)
		{
			stNew=stNew->stNext;
		}
		stNew->stNext=stDelete->stNext;
		free(stDelete);
	}	
	return(stHead);
}



StaffInfo *ReorderList(StaffInfo* stHead)
{
	StaffInfo* stMax=NULL;
	StaffInfo* stNewHead=NULL;
	StaffInfo* stCurrent=NULL;
	StaffInfo* stNewCurrent=NULL;

	if(stHead!=NULL)
	{
		stMax=stHead;
		stNewHead=(StaffInfo*)malloc(sizeof(StaffInfo));
		stNewHead->stNext=NULL;
	}
	
	while(stHead!=NULL)
	{
		stCurrent=stHead;
		while(stCurrent!=NULL)
		{

			if(stMax->iSalary < stCurrent->iSalary)
			{
				stMax=stCurrent;
			}	
			stCurrent=stCurrent->stNext;
			
		}
		if(stMax->iSalary==0)
			break;
		if(stNewCurrent==NULL)
		{

			stNewCurrent=(StaffInfo*)malloc(sizeof(StaffInfo));
			stNewCurrent=stNewHead;
		}
		else
		{
			stNewCurrent->stNext=(StaffInfo*)malloc(sizeof(StaffInfo));
			stNewCurrent=stNewCurrent->stNext;
			stNewCurrent->stNext=NULL;
		}
		strcpy(stNewCurrent->cName,stMax->cName);
		stNewCurrent->iAge=stMax->iAge;
		stNewCurrent->iSalary=stMax->iSalary;
		stNewCurrent->lID=stMax->lID;
		
		stMax->iSalary=0;

		//	stHead=DeleteItem(stHead,stMax);

	}

return(stNewHead);
}

int ReleaseList(StaffInfo* stHead)
{
	StaffInfo* stCurrent=stHead;
	while(stCurrent!=NULL)
	{
		
		stHead=stHead->stNext;
		free(stCurrent);
		stCurrent=stHead;
	}
return(0);
}


StaffInfo *ReorderList2(StaffInfo* stHead)
{
	StaffInfo* stMax=NULL;
	StaffInfo* stNewHead=NULL;
	StaffInfo* stCurrent=NULL;
	StaffInfo* stNewCurrent=NULL;
	
	while(stHead!=NULL)
	{
		stMax=stHead;
		stCurrent=stHead;
		while(stCurrent!=NULL)
		{

			if(stMax->iSalary < stCurrent->iSalary)
			{
				stMax=stCurrent;
			}	
			stCurrent=stCurrent->stNext;
			
		}
		if(stNewHead==NULL)
		{
			stNewHead=(StaffInfo*)malloc(sizeof(StaffInfo));
			stNewHead=stMax;
			stNewHead->stNext=NULL;
		}
		else
		{
			stNewCurrent=stNewHead;
			while(stNewCurrent->stNext!=NULL)
				stNewCurrent=stNewCurrent->stNext;
			stNewCurrent->stNext=(StaffInfo*)malloc(sizeof(StaffInfo));
			stNewCurrent=stNewCurrent->stNext;
			stNewCurrent->stNext=NULL;
			stNewCurrent=stMax;
		}
		if(stMax==stHead)
		{
			stHead=stHead->stNext;
			continue;
		}
		else if(stMax->stNext==NULL)
		{
			stNewCurrent=stHead;
			while(stNewCurrent->stNext!=stMax)
			{
				stNewCurrent=stNewCurrent->stNext;
			}
			stNewCurrent->stNext=NULL;	
			continue;
		}
		else
		{
			stNewCurrent=stHead;
			while(stNewCurrent->stNext!=stMax)
			{
				stNewCurrent=stNewCurrent->stNext;
			}
			stNewCurrent->stNext=stMax->stNext;
			continue;
		}

	}
return(stNewHead);
}