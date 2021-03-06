#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"
#include "linkedList.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int exit_flag = 0;
	FILE *fp;
    
	char word[300];
	char name[200];
	char place[100], typeName[100];	
	char cmonth[5];   
	char ctype[5];
	char cday[5];    // 문자로 입력받을 정수들 위해 우선 배열선언 
	char getPlace[30];   //배열 입력받을 배열 선언  
	size_t size;
	int month;
	int day;
	int type;
	void *list;
	void *ndPtr;
	void *schedInfo;
	int option;
	int cnt;
	
	//1. FILE pointer open & error handling
	//fill code here ----
	fp = fopen("schedule.dat","r");
	if(fp==NULL){
		return -1;
	}
	
	//initializing the list
	printf("Reading the data files... \n");
	list = (void*)list_genList();
	
	
	
	
	//2. read from the file
	int line=0;
	while (fgets(word,50,fp)!=NULL)    //페이지 끝날 때 까지 한줄씩 입력 반복  
	{   
	    
	    // 공백때문에 스케줄 11개 생기는 오류 발견 
	    if(0){
	    	printf("%d(%d) : %s",line++,strlen(word),word);
		}
		
	    // 공백 스킵  
		if(strlen(word)==1){
		   	continue;
		}
		
	    int i=0;
	    int j=0;
	    
	    while(word[i]!=' ')    //띄어쓰기를 만나면 name입력받기 중지  
        {
       	    name[j]=word[i];
	        i++;
	        j++;
        }
        name[j]='\0';         //이번 턴에 입력된 문자만 인식되게 단어 끝에 \0 
	    i++;
	    j=0;
	    
	    
  	    while(word[i]!=' ')   
  	    {
  	        place[j]=word[i];
	        i++;
	        j++;
	   	}
	   	place[j]='\0';   
        i++;
	    j=0;

        while(word[i]!=' ')
	    {
            ctype[j]=word[i];
	        i++;
	        j++;

	    }
	    type= atoi(ctype);         //배열로 입력받은 수(문자)  atoi함수로 정수로 변환  
	    ctype[j]='\0';
	    i++;
	    j=0;
	
    	while(word[i]!=' ')
    	{
            cmonth[j]=word[i];
	        i++;
	        j++;
	    }
	    month= atoi(cmonth);
	    cmonth[j]='\0';
	    i++;
	    j=0;
	
    	while(word[i]!=' ')
    	{
            cday[j]=word[i];
	        i++;
	        j++;
	    }
	    day= atoi(cday);
        cday[j]='\0';
        /*printf("%s %s %i %i %i ", name, place, type, month, day);*/

		// list_addTail의 *object역할인  schedInfo에 생성된 구조체 포인터 넘겨줌  
        schedInfo = sched_genSchedInfo(name, place, type, month, day);    
		
		//put the scheduling info instance generated by genSchedInfo function
		list_addTail(schedInfo, list);  
		
	}
	
	
	
	//fclose the file pointer
	fclose(fp);
	
	printf("Read done! %i schedules are read\n\n", list_len(list));
	

    //program starts
	while(exit_flag == 0) 
	{
		//3. menu printing
		printf("1.print all the schedules\n");
		printf("2.search for schedules in the month\n");
		printf("3.search for schedules in the place\n");
		printf("4.search for specific type schedule\n");
		printf("5.exit\n");
		
		//4. get option from keyboard
		printf("select an option :");
		scanf("%i",&option);
		
		
		switch(option)
		{
			case 1: //print all the schedules
				printf("printing all the schedules in the scheduler.....\n\n\n");
				list_getIndexNd(0, list);
				ndPtr = list;
				while (list_isEndNode(ndPtr) == 0)    
				{
					// print count and each scheduling info element
					printf("___________________________\n");
					sched_print(schedInfo);
					
				
					ndPtr = list_getNextNd(ndPtr); //get the next node from the list
					schedInfo = list_getNdObj(ndPtr); //get the object (scheduling info)
					
					//end
				}
				printf("___________________________\n");
				break;



			case 2:
				printf("which month ? : ");
				scanf("%i", &month);
				
				ndPtr = list;
				while (list_isEndNode(ndPtr) == 0)
				{
					//입력받은month와 구조체의month같으면 스케줄 프린트
					if(sched_getMonth(schedInfo)==month)             
					{
					printf("___________________________\n");
					sched_print(schedInfo);
					
				    }
				    
					ndPtr = list_getNextNd(ndPtr); //get the next node from the list
					schedInfo = list_getNdObj(ndPtr); //get the object (scheduling info)
					
					//end
					
				}
				    printf("___________________________\n");
				
				break;



			case 3:
				printf("which place ? : ");
				scanf("%s", place);
				
				ndPtr = list;
				while (list_isEndNode(ndPtr) == 0)
				{   
				    //스케줄의 장소와 입력받은 place가 같다면 스케줄 print 
					if(strncmp(sched_getPlace(schedInfo,getPlace),place,strlen(place))==0)    
					{
						printf("___________________________\n");
					    sched_print(schedInfo);
					}
					
					//print scheduling info elements matching to the place
					ndPtr = list_getNextNd(ndPtr); //get the next node from the list
					schedInfo = list_getNdObj(ndPtr); //get the object (scheduling info)
					
					//end
				}
				printf("___________________________\n");
				
				break;
			
	
			
			case 4:
				printf("which type ?\n");
				sched_printTypes();
				printf("your choice : ");
				scanf("%s", typeName);

		    //해당함수에서, 입력받은 Type이 유효하지 않은 Type이면 -1 값 리턴
			if (sched_convertType(typeName)!=-1)        
				{
					ndPtr = list;
					while (list_isEndNode(ndPtr) == 0)
					{
						//입력받은 타입네임과 스케줄 구조체안의 타입네임이 같다면 (정수형태로 비교) 
						if(sched_convertType(typeName)==sched_getType(schedInfo))
						{
						printf("___________________________\n");
					    sched_print(schedInfo);
					    }
						
						ndPtr = list_getNextNd(ndPtr); //get the next node from the list
						schedInfo = list_getNdObj(ndPtr); //get the object (scheduling info)
						
						//fill code this part - end
					}
				    printf("___________________________\n");
			    }
				
				else
				{
					printf("wrong type name!\n");
				}
				break;
			
			
			
			case 5:
				printf("Bye!\n\n");
				exit_flag = 1;
				break;
				
			default:
				printf("wrong command! input again\n");
				break;
		}
		
		
	}
  
  return 0;
}
