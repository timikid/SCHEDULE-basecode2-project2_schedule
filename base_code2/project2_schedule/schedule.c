#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"

#define MAX_TYPE		7

//strings for printing the name of each enum element
//enum type's name
char type_string[MAX_TYPE][20] = 
{
	"drama",
	"movie",
	"advertisement",
	"entertainment",
	"meeting",
	"fitness",
	"privacy"
};

//month's name
char month_string[13][4] = 
{
	"", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

//enum definitions
typedef enum scheduleType {
	drama=0, 		//드라마 
	movie, 			//영화 
	advertisement, 	//광고 
	entertainment, 	//예능 
	meeting,		//회의 
	fitness,		//운동 
	privacy			//개인사 
} scheduleType_e;



//structure definition for a schedule info.
typedef struct schedInfo
{
	char name[200];			//schedule name
	scheduleType_e type;	//schedule type
	int month;				//when : month
	int day;				//when : day
	char place[100];		//where
} schedInfo_t;


void sched_printTypes(void) 
{
	int i;
	for (i=0;i<MAX_TYPE;i++) 
	{
		printf("%i- %s\n", i, type_string[i]);
	}
}

void sched_print(void* obj) 
{
	schedInfo_t* schedPtr = (schedInfo_t*)obj; 
	if (schedPtr == NULL) {
		printf("[ERROR] failed to print the schedule Info! (object is NULL)\n");
	}
	
	printf("Schedule Name : %s (%s)\n",schedPtr->name, type_string[schedPtr->type]);
	printf("When : %s. %i\n", month_string[schedPtr->month], schedPtr->day);
	printf("Where : %s\n", schedPtr->place);

	return;
}









//generating a structure of scheduling information
void* sched_genSchedInfo(char* name, char* place, int type, int month, int day)
{
	schedInfo_t* schedPtr;
	//error handler
	//allocate memory and set the member variables
	schedPtr = (schedInfo_t*)malloc(sizeof(schedInfo_t));
	strcpy(schedPtr->name,(char *)name);         //구조체 멤버 name에 입력받은 name 문자열 복사  
	//printf("%s",schedPtr->name);
    strcpy(schedPtr->place,(char *)place);
	//printf("%s",schedPtr->place);
	schedPtr->type = type;
	schedPtr->month = month;
	schedPtr->day = day;	
	
	return (void*)schedPtr;
}



//get month information from the scheduler info structure
float sched_getMonth(void* obj)
{
   schedInfo_t* schedPtr = obj;
   float getmonth;
   getmonth = schedPtr->month;
   return getmonth;
}


//get type information from the scheduler info structure
int sched_getType(void* obj)
{
	schedInfo_t* schedPtr = obj;
	int getType;
	getType = schedPtr->type;
	return getType;
}



//get place string information from the scheduler info structure

char* sched_getPlace(void* obj, char* getPlace)       //문자 입력받고 리턴할 문자배열 getPlace 추가  
{
    
	schedInfo_t* schedPtr = obj;
    strcpy(getPlace,schedPtr->place);
    return getPlace;
}

//convert the name of the type into the enum(integer) value
int sched_convertType(char* typeName)
{
	int getType;
	char type[30];
	int i;
	int j=0;
	
	strcpy(type,typeName);
    
	for (i=0;i<MAX_TYPE;i++)   
	{
		if(strncmp(typeName,type_string[i],strlen(type_string[i]))==0)    
		{
		getType=i;
		j++;
	    }
	}
	
	if(j==0)
	return -1;              //Type 종류에 입력받은 Type 존재하지 않으면 -1 리턴   
	
	else
	return getType;
}

