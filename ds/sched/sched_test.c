/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Daniel Jenudi
Reviewer: Osher
Date: 30/03/2022
File: Data struct - Schedular
Description: Source file
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <stdio.h> /*printf*/
#include <unistd.h> /*sleep*/

#include "uid.h"
#include "sched.h"

#define RUNTEST(test) {\
            if (!test)\
            {\
                printf("\x1b[0;34m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;35m");\
                printf("\nTest Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }


enum return_status
{
	BOOL_FALSE = 0,
	BOOL_TRUE = 1,
	SUCCESS = 0,
	FAILURE = 1,
	ERROR = -1
};

struct task_info
{
	sched_t *sched;
	sc_action_func_t action_func;
	void *action_param;
	sc_clean_up_func_t clean_up_func;
	void *clean_up_param;
	time_t time;
};
typedef struct task_info taskinfo_t;

struct remove_info
{
	sched_t *sched;
	ilrd_uid_t uid;
};
typedef struct remove_info rmvinfo_t;

int ValCheck(int recieved_val, int expected_val, int line);
int action_add(void *action_param);
void cleanup_zero(void *cleanup_param);
int CreateDestroyTest();
int AddRemoveTest();
int SizeIsEmptyClearTest();
int RunTest();
int ActionRun(void *action_param);
void CleanupDummy(void *cleanup_param);
int ActionStop(void *action_param);
void CleanStop(void *action_param);
int StopTest();
int ActionAddTask(void *action_param);
int ActionRemoveTask(void *action_param);
int AddRemoveTaskByTaskTest();


int total_fails = 0;
    
int main()
{
	RUNTEST(CreateDestroyTest());
	RUNTEST(AddRemoveTest());
	RUNTEST(SizeIsEmptyClearTest());
	RUNTEST(RunTest());
	RUNTEST(StopTest());
	RUNTEST(AddRemoveTaskByTaskTest());
	
	
	if (0 < total_fails)
	{
		printf("\n\n****** TOTAL FAILS = %d ******\n\n", total_fails);
	}
	return 0;
}


int ValCheck(int recieved_val, int expected_val, int line)
{
	if (recieved_val != expected_val)
	{
		printf("----------------FAIL line %d----------------\n", line);
		printf("got %d, when wanted %d\n",recieved_val, expected_val);
		++total_fails;
		return 1;
	}
	return 0;
}

int action_add(void *action_param)
{
	*(int *)action_param += 10;
	
	return SUCCESS;
}

void cleanup_zero(void *cleanup_param)
{
	*(int *)cleanup_param = 0;
}

int CreateDestroyTest()
{
	int status = 0;
	int a = 1;
	sched_t *sched1 = SchedCreate();
	time_t time1 = time(NULL);
	ilrd_uid_t uid1 = UIDBadUID;
	sc_action_func_t action_func = action_add;
	sc_clean_up_func_t cleanup_func = cleanup_zero;
	
	printf("\n~~~~~CreateDestroyTest~~~~~\n");
	
	SchedDestroy(sched1);
	
	sched1 = SchedCreate();
	uid1 = SchedAddTask(sched1, action_func, &a, cleanup_func, &a, time1);
	status += ValCheck(UIDIsSame(uid1, UIDBadUID), BOOL_FALSE, __LINE__);
	SchedDestroy(sched1);
	
	return status;
}

int AddRemoveTest()
{
	int status = 0;
	int a = 1;
	int b = 2;
	sched_t *sched1 = SchedCreate();
	time_t time1 = time(NULL);
	time_t time2 = 0;
	ilrd_uid_t uid1 = UIDBadUID;
	ilrd_uid_t uid2 = UIDBadUID;
	sc_action_func_t action_func = action_add;
	sc_clean_up_func_t cleanup_func = cleanup_zero;
	
	printf("\n~~~~~AddRemoveTest~~~~~\n");
	
	uid1 = SchedAddTask(sched1, action_func, &a, cleanup_func, &a, time1);
	status += ValCheck(UIDIsSame(uid1, UIDBadUID), BOOL_FALSE, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 1, __LINE__);
	
	sleep(1);
	time2 = time(NULL);
	uid2 = SchedAddTask(sched1, action_func, &b, cleanup_func, &b, time2);
	status += ValCheck(UIDIsSame(uid2, UIDBadUID), BOOL_FALSE, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 2, __LINE__);
	
	SchedRemoveTask(sched1, uid1);
	status += ValCheck((int)SchedSize(sched1), 1, __LINE__);
	
	SchedRemoveTask(sched1, uid1);
	status += ValCheck((int)SchedSize(sched1), 1, __LINE__);
	
	SchedRemoveTask(sched1, uid2);
	status += ValCheck((int)SchedSize(sched1), 0, __LINE__);
	status += ValCheck(SchedIsEmpty(sched1), BOOL_TRUE, __LINE__);
	
	SchedDestroy(sched1);
	
	return status;
}

int SizeIsEmptyClearTest()
{
	int status = 0;
	int a = 1;
	int b = 2;
	int c = 3;
	sched_t *sched1 = SchedCreate();
	time_t time1 = time(NULL);
	time_t time2 = 0;
	time_t time3 = 0;
	ilrd_uid_t uid1 = UIDBadUID;
	ilrd_uid_t uid2 = UIDBadUID;
	ilrd_uid_t uid3 = UIDBadUID;
	sc_action_func_t action_func = action_add;
	sc_clean_up_func_t cleanup_func = cleanup_zero;
	
	printf("\n~~~~~SizeIsEmptyClearTest~~~~~\n");
	status += ValCheck(SchedIsEmpty(sched1), BOOL_TRUE, __LINE__);
	
	uid1 = SchedAddTask(sched1, action_func, &a, cleanup_func, &a, time1);
	status += ValCheck(UIDIsSame(uid1, UIDBadUID), BOOL_FALSE, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 1, __LINE__);
	status += ValCheck(SchedIsEmpty(sched1), BOOL_FALSE, __LINE__);
	
	sleep(1);
	time2 = time(NULL);
	uid2 = SchedAddTask(sched1, action_func, &b, cleanup_func, &b, time2);
	status += ValCheck(UIDIsSame(uid2, UIDBadUID), BOOL_FALSE, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 2, __LINE__);
	status += ValCheck(SchedIsEmpty(sched1), BOOL_FALSE, __LINE__);
	
	sleep(1);
	time3 = time(NULL);
	uid3 = SchedAddTask(sched1, action_func, &c, cleanup_func, &c, time3);
	status += ValCheck(UIDIsSame(uid3, UIDBadUID), BOOL_FALSE, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 3, __LINE__);
	status += ValCheck(SchedIsEmpty(sched1), BOOL_FALSE, __LINE__);
	
	SchedRemoveTask(sched1, uid1);
	status += ValCheck((int)SchedSize(sched1), 2, __LINE__);
	status += ValCheck(SchedIsEmpty(sched1), BOOL_FALSE, __LINE__);
	
	SchedClear(sched1);
	status += ValCheck((int)SchedSize(sched1), 0, __LINE__);
	status += ValCheck(SchedIsEmpty(sched1), BOOL_TRUE, __LINE__);
	
	time1 = time(NULL);
	uid1 = SchedAddTask(sched1, action_func, &a, cleanup_func, &a, time1);
	status += ValCheck(UIDIsSame(uid1, UIDBadUID), BOOL_FALSE, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 1, __LINE__);
	status += ValCheck(SchedIsEmpty(sched1), BOOL_FALSE, __LINE__);
	
	SchedClear(sched1);
	status += ValCheck((int)SchedSize(sched1), 0, __LINE__);
	status += ValCheck(SchedIsEmpty(sched1), BOOL_TRUE, __LINE__);
	
	SchedDestroy(sched1);
	
	return status;
}

int ActionRun(void *action_param)
{
	--*(int *)action_param;
	if (*(int *)action_param > 10)
	{
		printf("	%d |reschedule|\n",*(int *)action_param);
		return 5;
	}
	if (*(int *)action_param < 0)
	{
		printf("	%d |error|\n",*(int *)action_param);
		return ERROR;
	}
	printf("	%d\n",*(int *)action_param);
	return SUCCESS;
}

void CleanupDummy(void *cleanup_param)
{
	(void)cleanup_param;
}

int RunTest()
{
	int status = 0;
	int a = 12;
	int b = 0;
	int c = 3;
	int d = 4;
	int run_res = 0;
	sched_t *sched1 = SchedCreate();
	sched_t *sched2 = SchedCreate();
	time_t time1 = 0;
	ilrd_uid_t uid1 = UIDBadUID;
	ilrd_uid_t uid2 = UIDBadUID;
	ilrd_uid_t uid3 = UIDBadUID;
	sc_action_func_t action_func = ActionRun;
	sc_clean_up_func_t cleanup_func = CleanupDummy;
	
	printf("\n~~~~~RunTest~~~~~\n");
	
	time1 = time(NULL);
	uid1 = SchedAddTask(sched1, action_func, &a, cleanup_func, &a, time1+2);
	status += ValCheck(UIDIsSame(uid1, UIDBadUID), BOOL_FALSE, __LINE__);
	uid2 = SchedAddTask(sched1, action_func, &b, cleanup_func, &b, time1);
	status += ValCheck(UIDIsSame(uid2, UIDBadUID), BOOL_FALSE, __LINE__);
	uid3 = SchedAddTask(sched1, action_func, &c, cleanup_func, &c, time1+3);
	status += ValCheck(UIDIsSame(uid3, UIDBadUID), BOOL_FALSE, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 3, __LINE__);
	
	uid1 = SchedAddTask(sched2, action_func, &d, cleanup_func, &d, time1);
	status += ValCheck(UIDIsSame(uid1, UIDBadUID), BOOL_FALSE, __LINE__);
	uid2 = SchedAddTask(sched2, action_func, &d, cleanup_func, &d, time1);
	status += ValCheck(UIDIsSame(uid1, UIDBadUID), BOOL_FALSE, __LINE__);
	
	run_res = SchedRun(sched1);
	status += ValCheck(run_res, 1, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 0, __LINE__);
	status += ValCheck(a, 10, __LINE__);
	status += ValCheck(b, -1, __LINE__);
	status += ValCheck(c, 2, __LINE__);
	
	run_res = SchedRun(sched2);
	status += ValCheck(run_res, 0, __LINE__);
	status += ValCheck((int)SchedSize(sched2), 0, __LINE__);
	status += ValCheck(d, 2, __LINE__);
	
	printf("!! compare manually :\n");
	printf("\t-1\n\t11\n\t2\n\t10\n\t3\n\t2\n \n");
	
	SchedDestroy(sched1);
	SchedDestroy(sched2);
	
	return status;
}

int ActionStop(void *action_param)
{
	SchedStop((sched_t *)action_param);
	
	return SUCCESS;
}

void CleanStop(void *action_param)
{
	SchedStop((sched_t *)action_param);
}

int StopTest()
{
	int status = 0;
	int a = 12;
	int b = 0;
	int c = 3;
	int d = 4;
	int run_res = 0;
	sched_t *sched1 = SchedCreate();
	sched_t *sched2 = SchedCreate();
	time_t time1 = 0;
	ilrd_uid_t uid1 = UIDBadUID;
	ilrd_uid_t uid2 = UIDBadUID;
	ilrd_uid_t uid3 = UIDBadUID;
	sc_action_func_t action_func = ActionRun;
	sc_clean_up_func_t cleanup_func = CleanupDummy;
	
	printf("\n~~~~~StopTest~~~~~\n");
	
	time1 = time(NULL);
	uid1 = SchedAddTask(sched1, action_func, &a, cleanup_func, &a, time1+2);
	status += ValCheck(UIDIsSame(uid1, UIDBadUID), BOOL_FALSE, __LINE__);
	uid2 = SchedAddTask(sched1, action_func, &b, cleanup_func, &b, time1);
	status += ValCheck(UIDIsSame(uid2, UIDBadUID), BOOL_FALSE, __LINE__);
	action_func = ActionStop;
	uid2 = SchedAddTask(sched1, action_func, sched1, cleanup_func, sched1, \
	time1);
	status += ValCheck(UIDIsSame(uid2, UIDBadUID), BOOL_FALSE, __LINE__);
	action_func = ActionRun;
	uid3 = SchedAddTask(sched1, action_func, &c, cleanup_func, &c, time1+3);
	status += ValCheck(UIDIsSame(uid3, UIDBadUID), BOOL_FALSE, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 4, __LINE__);
	
	
	cleanup_func = CleanStop;
	uid1 = SchedAddTask(sched2, action_func, &d, cleanup_func, sched2, time1);
	status += ValCheck(UIDIsSame(uid1, UIDBadUID), BOOL_FALSE, __LINE__);
	cleanup_func = CleanupDummy;
	uid2 = SchedAddTask(sched2, action_func, &d, cleanup_func, &d, time1);
	status += ValCheck(UIDIsSame(uid1, UIDBadUID), BOOL_FALSE, __LINE__);
	
	
	run_res = SchedRun(sched1);
	status += ValCheck(run_res, 1, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 2, __LINE__);
	run_res = SchedRun(sched1);
	status += ValCheck(run_res, 0, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 0, __LINE__);
	

	run_res = SchedRun(sched2);
	status += ValCheck(run_res, 0, __LINE__);
	status += ValCheck((int)SchedSize(sched2), 1, __LINE__);
	SchedClear(sched2);
	status += ValCheck((int)SchedSize(sched2), 0, __LINE__);
	
	printf("!! compare manually :\n");
	printf("\t-1\n\t11\n\t2\n\t10\n\t3\n");
	
	SchedDestroy(sched1);
	SchedDestroy(sched2);
	
	return status;
}

int ActionAddTask(void *action_param)
{
	ilrd_uid_t uid = SchedAddTask(((taskinfo_t *)action_param)->sched, \
	((taskinfo_t *)action_param)->action_func, \
	((taskinfo_t *)action_param)->action_param, \
	((taskinfo_t *)action_param)->clean_up_func, \
	((taskinfo_t *)action_param)->clean_up_param, \
	((taskinfo_t *)action_param)->time);
	
	return UIDIsSame(uid, UIDBadUID);
}

int ActionRemoveTask(void *action_param)
{
	SchedRemoveTask(((rmvinfo_t *)action_param)->sched, \
	((rmvinfo_t *)action_param)->uid);
	
	return SUCCESS;
}

int AddRemoveTaskByTaskTest()
{
	int status = 0;
	int run_res = 0;
	int a = -1;
	int b = -2;
	sched_t *sched1 = SchedCreate();
	time_t time1 = time(NULL);
	ilrd_uid_t uid1 = UIDBadUID;
	ilrd_uid_t uid2 = UIDBadUID;
	sc_action_func_t action_func = ActionRun;
	sc_action_func_t action_func_add = ActionAddTask;
	sc_action_func_t action_func_remove = ActionRemoveTask;
	sc_clean_up_func_t cleanup_func = CleanupDummy;
	taskinfo_t info;
	rmvinfo_t rm_info;
	
	printf("\n~~~~~AddRemoveTaskByTaskTest~~~~~\n");
	info.sched = sched1;
	info.action_func = action_func;
	info.action_param = &b;
	info.clean_up_func = cleanup_func;
	info.clean_up_param = &b;
	info.time = time1;
	
	uid1 = SchedAddTask(sched1, action_func, &a, cleanup_func, &a, time1);
	status += ValCheck(UIDIsSame(uid1, UIDBadUID), BOOL_FALSE, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 1, __LINE__);

	uid2 = SchedAddTask(sched1, action_func, &a, cleanup_func, &a, time1 + 5);
	status += ValCheck(UIDIsSame(uid2, UIDBadUID), BOOL_FALSE, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 2, __LINE__);

	uid1 = SchedAddTask(sched1, action_func_add, &info, cleanup_func, &info, \
	time1);
	status += ValCheck(UIDIsSame(uid1, UIDBadUID), BOOL_FALSE, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 3, __LINE__);

	rm_info.sched = sched1;
	rm_info.uid = uid2;

	uid1 = SchedAddTask(sched1, action_func_remove, &rm_info, cleanup_func, \
	&rm_info, time1);
	status += ValCheck(UIDIsSame(uid1, UIDBadUID), BOOL_FALSE, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 4, __LINE__);
	
	run_res = SchedRun(sched1);
	status += ValCheck(run_res, 1, __LINE__);
	status += ValCheck((int)SchedSize(sched1), 0, __LINE__);
	
	printf("!! compare manually :\n");
	printf("\t-2\n\t-3\n");
	
	SchedDestroy(sched1);
	
	return status;
}

