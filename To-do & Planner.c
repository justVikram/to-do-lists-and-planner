#include <stdio.h>
#include <string.h>

typedef struct Subtask
{
    int SubtaskNumber;
    char SubtaskTitle [40];
    int IsCompleted;
}
SUBTASK;

typedef struct SubtaskNode
{
    SUBTASK SubtaskDetails;
    SUBTASK * next;
}
SUBTASK_NODE;

typedef struct Task
{
    char TaskTitle [40];                        // To store the actual task
    char ScheduledDate [10];
    int IsCompleted;                            // 1 -> Completed, 0 -> Not completed
    SUBTASK_NODE * ListOfSubtasks;
}
TASK;

typedef struct TaskNode
{
    TASK  TaskDetails;
    struct node * next;
}
TASK_NODE;

//MARK:-

static void initListOfTasks (TASK_NODE ** ListOfTasks)
{
    ListOfTasks = NULL;
}

static void initTaskDetails (TASK * ExistingTask)
{
    strcpy (ExistingTask->TaskTitle, "<enter task title here>");
    strcpy (ExistingTask->ScheduledDate, "00-00-00");
    ExistingTask->IsCompleted = 0;
    ExistingTask->ListOfSubtasks = NULL;
    
}

static void initSubtaskDetails (SUBTASK * ExistingSubtask)
{
    ExistingSubtask->SubtaskNumber = 0;
    strcpy (ExistingSubtask->SubtaskTitle, "<enter subtask title here>");
    ExistingSubtask->IsCompleted = 0;
}

//MARK:-

/// Function to read the details of a new task created by the user.
/// @param NewTask Use NewTask->TaskDetails.x to fill up the data elements
static void readNewTask (TASK_NODE * NewTask)
{
    
}


/// Adds the new task created by the user to the list of tasks being maintained.
/// @param ListOfTasks Pointer pointing to the address of the original list of tasks
/// @param NewTask After readNewTask(), pass NewTask to this function.
static void addNewTask (TASK_NODE * ListOfTasks, TASK_NODE * NewTask)
{
    //ADD AT POSITION
}

static void viewTask (const TASK_NODE * ExistingTask)
{
    
}

static void viewListOfTasks (const TASK_NODE * ListOfTasks)
{
    //IN ASCENDING ORDER BY DATE
}

static void viewTasksOnGivenDate (TASK_NODE ** ListOfTasks, char ScheduledDate [])
{
    
}

static void viewCompletedTasks (TASK_NODE ** ListOfTasks)
{
    
}

static TASK_NODE * searchByTaskTitle (const TASK_NODE * ListOfTasks, char TaskTitle [])
{
    TASK_NODE * LocatedTask = NULL;
    
    return LocatedTask;
    
}

static void markTaskAsCompleted (TASK_NODE ** ListOfTasks, int TaskNumber)
{
    
}

static void markAllTasksAsCompleted (TASK_NODE ** ListOfTasks)
{
    
}

static void deleteTaskFromList (TASK_NODE ** ListOfTasks, char TaskTitle [])
{
    
}


//MARK:-

static void readNewSubtask (SUBTASK_NODE * NewSubtask)
{
    
}

static void addNewSubtask (TASK_NODE ** ExistingTask, SUBTASK_NODE * NewSubtask)
{
    
}

static void viewListOfSubtasks (const TASK_NODE * ExistingTask)
{
    
}

static void markSubtaskAsCompleted (SUBTASK_NODE ** ListOfSubtasks, int SubtaskNumber)
{
    
}

static void markAllSubtasksAsCompleted (TASK_NODE ** ExistingTask)
{
    
}

static void deleteSubtask (SUBTASK_NODE ** ListOfSubtasks, char SubtaskTitle [])
{
    
}

static void deleteSubtaskList (TASK_NODE ** ExistingTask)
{
    
}

//MARK:-

int isLeapYear (int y)
{
    return(y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0));
}

int leapYears (int y)
{
    return y/4 - y/100 + y/400;
}

int todayOf (int y, int m, int d)
{
    static int DayOfMonth[] = {-1, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

    return DayOfMonth[m] + d + ((m > 2 && isLeapYear (y))? 1 : 0);
}

long days (int y, int m, int d)
{
    int lastYear;
    lastYear = y - 1;
    
    return 365L * lastYear + leapYears(lastYear) + todayOf(y,m,d);
}

void calendar (int y, int m) /* display calendar at m y */
{
    const char *NameOfMonth[] = {NULL, "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};
    
    char Week[] = "Su Mo Tu We Th Fr Sa";
    
    int DayOfMonth[] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
    int weekOfTopDay;
    int i, day;

    weekOfTopDay = days(y, m, 1) % 7;
    
    if (isLeapYear (y))
        DayOfMonth [2] = 29;
    
    printf ("\n     %s %d\n%s\n", NameOfMonth[m], y, Week);

    for (i = 0; i < weekOfTopDay; i++)
        printf("   ");
    
    for (i = weekOfTopDay, day = 1; day <= DayOfMonth [m]; i++, day++)
    {
        printf ("%2d ", day);
        
        if(i % 7 == 6)
            printf("\n");
    }
    printf("\n");
}

//MARK:-

int main (int argV, const char * argC [])
{
    TASK_NODE * ListOfTasks;
}
