#include <stdio.h>
#include <string.h>

typedef struct Subtask
{
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

static void displayCalendar ()
{
    //USE ZELLER'S ALGORITHM
}

//MARK:-

int main (int argC, const char * argV [])
{
    TASK_NODE * ListOfTasks;
}
