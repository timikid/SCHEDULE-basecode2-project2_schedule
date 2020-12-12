void* sched_genSchedInfo(char* name, char* place, int type, int month, int day);
void sched_print(void* obj);
float sched_getMonth(void* obj);
int sched_getType(void* obj);
char* sched_getPlace(void* obj);
void sched_printTypes(void);
int sched_convertType(char* typeName);
