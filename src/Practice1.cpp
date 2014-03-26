// Practice1.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <stdio.h>
#include "header.h"
#include <stdlib.h>
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	int j;
	int i,ret;
	FILE *fp;
	char filename[40]="c:\\test";
	char mode[4]="r";
	char cSearchName[20];
	char KeyRecv;
	StaffInfo* stHead = NULL;
	StaffInfo* stCurrent = NULL;
	StaffInfo* stNew = NULL;
	StaffInfo* stSearchResult=NULL;
	//stHead = (StaffInfo*)malloc(sizeof(StaffInfo));

	while(1)
	{
		fflush(stdin);
		system("cls");
		printf("********Main Menu********\n");
		printf("1.Load Data\n2.Show&Edit List\n3.Search Items\n4.Reorder Items\n5.Exit\n");
		switch(getchar())
		{
			case('1'):
				fflush(stdin);
				fp=fopen(filename,mode);
				if(fp!=NULL)
				{
					printf("File is successfully opened!\n");
					//Sleep(1000);
				}
				
				stNew =(StaffInfo*)malloc(sizeof(StaffInfo));
				stHead = (StaffInfo*)malloc(sizeof(StaffInfo));
				stHead->stNext=NULL;
				//stCurrent = stHead;
				//stCurrent->stNext=NULL;
				
				
				while((i=fscanf(fp,"%s %d %d %d",&stNew->cName,&stNew->iAge,&stNew->iSalary,&stNew->lID))>0)
				{
					if(stCurrent==NULL)
					{
						stCurrent=(StaffInfo*)malloc(sizeof(StaffInfo));
						stCurrent=stHead;
					}
					else
					{
						stCurrent->stNext=(StaffInfo*)malloc(sizeof(StaffInfo));
						stCurrent=stCurrent->stNext;
						stCurrent->stNext=NULL;	
					}
					strcpy(stCurrent->cName,stNew->cName);
					stCurrent->iAge=stNew->iAge;
					stCurrent->iSalary=stNew->iSalary;
					stCurrent->lID=stNew->lID;
				}
				
				//stCurrent=NULL;	
				//stNew->stNext = NULL;
				fclose(fp);
				printf("Successfully Loaded!");
				//Sleep(1000);
				
				




				/*if(stHead==NULL)
				{
					stHead = (StaffInfo*)malloc(sizeof(StaffInfo));
					ret = CreateUser(stHead);
				}
				else
				{
					stCurrent=stHead;
					while(stCurrent->stNext!=NULL)
						stCurrent=stCurrent->stNext;
					stNew = (StaffInfo*)malloc(sizeof(StaffInfo));
					ret = CreateUser(stNew);
					stCurrent->stNext=stNew;
				}*/
				break;
			case('2'):
				ret=ShowList(stHead);
				fflush(stdin);
				scanf("%c",&KeyRecv);
				while((KeyRecv!='q')&(KeyRecv!='Q')&(KeyRecv!='e')&(KeyRecv!='E'))
				{
					scanf("%c",&KeyRecv);
				}
				if((KeyRecv=='e')||(KeyRecv=='E'))
				{
					if(stHead==NULL)
					{
						printf("Nothing to edit");
						Sleep(1000);
					}
					else
						stHead=AddDelEditNode(stHead);

				}
				break;
			case('3'):
				stSearchResult=SearchItem(stHead);
				if(stSearchResult!=NULL)
				{
					printf("SearchResult\n*****************************************************\n");
					printf("Name		Age		Salary		ID\n");
					printf("%s		",stSearchResult->cName);
					printf("%d		",stSearchResult->iAge);
					printf("%d		",stSearchResult->iSalary);
					printf("%d\n",stSearchResult->lID);
					printf("******************************************************\n");
					printf("(Q)uit:");
					fflush(stdin);
					scanf("%c",&KeyRecv);
					while((KeyRecv!='q')&(KeyRecv!='Q'))
					{
						scanf("%c",&KeyRecv);
					}
				}
				else
				{
					printf("\nNo item matches!\n");
					Sleep(1000);
				}
			case('4'):
				stHead=ReorderList(stHead);
				break;
			
			case('5'):
				ReleaseList(stHead);
				exit(1);
				break;
			default:
				break;
					

		}
	}
	return 0;
}
