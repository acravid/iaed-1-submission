/*
 *
 *File:        kanban.c
 *Author:      Allan Donizette Cravid Fernades 97281
 *Description: a schedulling system for tasks management
 *  
 */


/*  Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/*  Macros*/               
#define START 1                 /* true value for the command line parsing*/
#define TASKSMAX  10000         /* maximum number of tasks*/ 
#define TASKINFO 50             /* maximum number of characters of a task description*/
#define ACTIVITYMAX 10          /* maximum number of activities in the system*/
#define ACTIVITYINFO 20         /* maximum number of characters of an activity description*/
#define USERMAX 50              /* maximum number of users in the system*/
#define USERNAME 20             /* maximum number of characters of an user description*/
#define ONE 1                   /* comparison/computation value*/
#define ZERO 0                  /* comparison/computation value*/
#define STAGE1 "TO DO"          /* first stage of an activity*/
#define STAGE2 "IN PROGRESS"    /*second stage of an activity*/
#define STAGE3 "DONE"           /*last stage of an activity*/


/*booleans definiton*/

typedef enum {false = 0,true = !false}boolean;

/*  Definition of Structures type*/

/*
 * Structure Name: Activity_t
 * ----------------------
 * Description: Activity structure definition
 * A task is characterized by the following:
 * 
 *         * a name,       what is it with want to accomplish 
 * 
 */

typedef struct{

    char name[ACTIVITYINFO];
    

}Activity_t;


/*
 * Structure Name: User_t
 * ----------------------
 * Description: User structure definition
 * A task is characterized by the following:
 * 
 *         * a name
 * 
 */

typedef struct{

    char name[USERNAME];

}User_t;

/*
 * Structure Name: Task_t
 * ----------------------
 * Description: Task structure definition
 * A task is characterized by the following:
 * 
 *          * an identifier,    id
 *          * a description,    info
 *          * an user
 *          * an activity 
 *          * a duration
 *          * a starting time   instant
 * 
 */

typedef struct{ 

    short int id;
    char info[TASKINFO];
    User_t user;
    Activity_t activity;
    short int duration;
    short int instant;

}Tasks_t;

/*  (Global)*/

/* array variables*/

                        /*  an array of Users in which the index indentifies the current user,
                        the system supports a
                        maximum of 50 users*/
User_t users[USERMAX];

                        /*  an array of Activities in which the index indentifies the current
                        activity,the system allows a
                         maximum of 10 activities */
Activity_t activities[ACTIVITYMAX];

                         /*  an array of Tasks, the index + 1 indentifies the current task 
                         externally,the system supports
                         a maximum of 1000 tasks*/
Tasks_t tasks[TASKSMAX];



/*  variables*/
int tsk_counter;        /*  counts the number of tasks in the system*/
int usr_counter;        /*  counts the number of users in the system*/
int act_counter;        /*  counts the number of activities in the system*/
int clock;              /*  current time in the system, associated with the command n*/

int task_id_tracker;    /*  tracks  think about */

/*  Function Prototypes*/

void addTaskToSystem();  /*  adds a new task to the system, command: t*/
void listTask();         /*  lists tasks in the system, command l*/
void advanceTimeSystem();/*  advances time of the system, command n*/
void addUserListUser();  /*  adds an user or lists all the users in the system, command u */
void moveTask();         /*  moves a Task from an activity to another, command m */
void listTaskActvity();  /*  lists all tasks in a given activity, command d*/
void addOrListActivity();/*  adds an activity or lists all activities in the system, command a*/

/* Auxiliary Functions*/


int isTaskinSystem(int id); /* done  */
int nonNegativeIntChecker(int time); 
int isUserinSystem(char name[]); /*done*/
int taskAlreadyStarted(int id,char activity[]);
int taskDone(int id);
int isActivityinSystem(char name[]); /* not */

/*int taskStage(Tasks_t task); // not  
int activityNameChecker(Activity_t activity); // not 
*/
int isTaskInfoDuplicated(char s[]);  /*done */ 
int isActivityInfoDuplicated(char s[]); /**/


int  main(){

    char cmd;

    while(START){
        
        cmd = getchar();
        switch(cmd){
            case    'q':
                return EXIT_SUCCESS;

            case    't':
                addTaskToSystem();
                break;

            case    'l':
                listTask();
                break;

            case    'n':
                advanceTimeSystem();
                break;

            case    'u':
                addUserListUser(); 
                break;

            case    'm':
                moveTask();
                break;

            case    'd':
                listTaskActvity();
                break;

            case    'a':
                addOrListActivity();
                break; 
        }
        
    }
    return EXIT_FAILURE;
}

/*-----------------------------------------------------------------------------------------------*/

/* Auxiliary Functions */

/*checks for non negative integers*/
int  nonNegativeIntChecker(int num){
    
    int res;
    res = (num >= false) ? true:false;
    return res;
}

/* checks if the given task is already in the system*/
int isTaskInfoDuplicated(char s[]){

    int i;
    
    for(i = 0; i < tsk_counter;i++){
        if(strcmp(users[i].name,s) == false){
            return true;
        }
    }
    return false;
}

/*  checks if the given activity is already in the system*/
int isActivityInfoDuplicated(char s[]){

    int i;
    
    for(i = 0; i < act_counter;i++){
        if(strcmp(activities[i].name,s) == false){
            return true;
        }
    }
    return false;

}

/* verifies if an user name is already in the system*/
int isUserinSystem(char name[]){

    int i;

    for(i = 0; i < usr_counter; i++){
        if(strcmp(users[i].name,name) == false){
            return true;
        }
    }
    return false;
}

/* verifies if the task with the given id is in the system*/
int isTaskinSystem(int id){

    int i;

    for(i = 0; i <= tsk_counter; i++){
        if(tasks[tsk_counter].id == id-ONE){ /*id starts at one, the - ONE removes the offset*/
            return true;
        }
    }
    return false;
}

int isActivityinSystem(char activity[]){

    int i;

    for(i = 0; i < act_counter; i++){
        if(strcmp(activities[i].name,activity) == false){
            return true;
        }
    }
    return false;
}
/*  verifies if a task already started*/
int taskAlreadyStarted(int id,char activity[]){

    return  (tasks[id - ONE].instant > ZERO && (strcmp(activity,STAGE1) == false)); 
}

/*  verifies if a task has reached its last stage, DONE*/
int taskDone(int id){

    return  ((strcmp(tasks[id - ONE].activity.name,STAGE3) == false));
}


/*-----------------------------------------------------------------------------------------------*/
 /*  main functions */


void addTaskToSystem(){ /*Command t*/

    int duration;
    char info[TASKINFO];
    scanf("%d",&duration);
    getchar();           /*removes the first character after the duration -- integer*/
    scanf("%[^\n]s",info);/*the description cannot start with a whitespace*/
  
    if(!(info[0] == '\0') && nonNegativeIntChecker(duration)){
        
        if(tsk_counter > TASKSMAX){
            printf("too many tasks");
        }
        else if(isTaskInfoDuplicated(info)){
            printf("duplicate description");
        }
        else{
            tasks[tsk_counter].duration = duration;
            tasks[tsk_counter].id = tsk_counter + ONE;
            tasks[tsk_counter].instant = ZERO;
            strcpy(tasks[tsk_counter].info,info);
            strcpy(tasks[tsk_counter].activity.name,STAGE1);
            printf("task %d\n",tasks[tsk_counter].id);
            tsk_counter++;
        }       
    }

}

void  listTask(){
    /*int c,status = false,i;*/

    getchar(); /*removes the first white space*/

} 

void  advanceTimeSystem(){

    int duration;
    scanf("%d",&duration);

    if(!nonNegativeIntChecker(duration)){
        printf("invalid time");

    }
    else{
        clock += duration;
        printf("%d\n",clock);
        
    }


}

void  addUserListUser(){       /*Command u*/

    char user[USERNAME];
    int i = ONE,j,savechar,c;     
               
    getchar();              /*removes the first white space immediately after the u command */
    savechar = getchar();   /*saves the character after the whitespace to check later*/  

                            /*checks whether or not the saved character is a  whitespace */
    if(!(isspace(savechar))){/*verifies if we're dealing with a list users or a
                             create user command*/
        user[0] = savechar; /*saves the first non whitespace character to an auxiliary array*/
        while ((c=getchar())!='\n' && c!=EOF && c!=' '&& i < USERNAME){
            user[i++] = c;
        }
        user[i] = '\0';
        if(isUserinSystem(user)){ /*tests for errors*/
            printf("user already exists");
        }
        else if(usr_counter > USERMAX){
            printf("too many users");
        }
        else{               /* creates a new user */
      
        strcpy(users[usr_counter].name,user); 
        usr_counter++;      /*increases the number of users in the system*/
        }
    }
    else{                   /*lists all users in the system by insertion order*/


            for(j = 0; j < usr_counter; j++){
                printf("%s\n",users[j].name);
        }
    } 
}

void moveTask(){

    int id,duration,slack;
    char user[USERNAME], activity[ACTIVITYINFO];
    
    scanf("%d %s %[^\n]s",&id,user,activity);

    tasks[id- ONE].instant = ONE; /*Testing*/

    if(isTaskinSystem(id) == false){ /*tests for errors*/
        printf("no such task");
    }
    else if(taskAlreadyStarted(id,activity)){
        printf("task already started");
    }
    else if(isUserinSystem(user) == false){
        printf("no such user");
    }
    else if((isUserinSystem(user) == false)){
        printf("no such activity");
    }
    else if(taskDone(id)){

        duration = tasks[id - ONE].instant - clock;
        slack = duration -  tasks[id - ONE].duration;
        printf("duration=%d slack=%d",duration,slack);

        strcpy(tasks[id-ONE].user.name,user);   /* more conditions ??*/
        strcpy(tasks[id-ONE].activity.name,activity);
        tasks[id - ONE].instant = clock;  /*update the starting time*/
    }
}

void listTaskActvity(){ /*later,, sorting stuff*/
    

}
void addOrListActivity(){ /*check if the given string does not have lowercase letters*/

    int savechar,c,i=ONE,j;
    char activity[ACTIVITYINFO];

    getchar();              /*removes the first white space immediately after the u command */
    savechar = getchar();   /*saves the character after the whitespace to check later*/  

    
                            /*checks whether or not the saved character is a whitespace */
    if(!(isspace(savechar))){/*verifies if we're dealing with a list activities or a*/
                             /*tests for errors*/

        activity[0] = savechar;/*saves the first non whitespace character to an auxiliary array*/
	while ((c=getchar())!='\n' && c!=EOF && i < ACTIVITYINFO){

            if(islower(c)){    /*checks for nonvalid characters*/
                printf("invalid description");
                break;
            }
            activity[i++] = c; 
        }
        activity[i] = '\0';
        if(isActivityInfoDuplicated(activity)){
            printf("duplicate activity");
        }
        else if(act_counter > ACTIVITYMAX ){
            printf("too many activities");
        }
        else{                   /*creates a new activity*/
            strcpy(activities[act_counter].name,activity);
            act_counter++;      /*increases the number of activities in the system*/
        }
    }
    else{                       /*lists all activities in the system by insertion order*/
            for(j = 0; j < act_counter; j++){
                printf("%s\n",activities[j].name);
            }
    }

}



/* merge sort is it ??*/
