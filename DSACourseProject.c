#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct date
{
    int month;
    int day;
    int year;
}
DATE;

typedef struct Subtask
{
    char SubtaskTitle [40];
    int IsCompleted;
}
SUBTASK;

typedef struct SubtaskNode
{
    SUBTASK SubtaskDetails;
    struct SubtaskNode * next;
}
SUBTASK_NODE;

typedef struct Task
{
    char TaskTitle [40];                        // To store the actual task
    DATE ScheduledDate;
    int IsCompleted;                            // 1 -> Completed, 0 -> Not completed
    SUBTASK_NODE * ListOfSubtasks;
}
TASK;

typedef struct TaskNode
{
    TASK  TaskDetails;
    struct TaskNode * next;
}
TASK_NODE;

int compareDates (DATE d1, DATE d2)
{
    if (d1.year < d2.year)
        return -1;
    
    else if (d1.year > d2.year)
        return 1;
    
    else
    {
        if (d1.month<d2.month)
            return -1;
        
        else if (d1.month>d2.month)
            return 1;
        
        else if (d1.day<d2.day)
            return -1;
        
        else if(d1.day>d2.day)
            return 1;
        
        else
            return 0;
    }
}

static void getDate (DATE * GivenDate)
{
    scanf ("%d %*c %d %*c %d", &GivenDate->day, &GivenDate->month, &GivenDate->year);
}

//MARK:-

static void initListOfTasks (TASK_NODE ** ListOfTasks)
{
    ListOfTasks = NULL;
}

static void initTaskDetails (TASK_NODE ** ExistingTask)
{
    strcpy ((*ExistingTask)->TaskDetails.TaskTitle, "<enter task title here>");
    
    (*ExistingTask)->TaskDetails.ScheduledDate.day = 00;
    (*ExistingTask)->TaskDetails.ScheduledDate.month = 00;
    (*ExistingTask)->TaskDetails.ScheduledDate.year = 0000;
    
    (*ExistingTask)->TaskDetails.IsCompleted = 0;
    (*ExistingTask)->TaskDetails.ListOfSubtasks = NULL;
    
}

static void initSubtaskDetails (SUBTASK_NODE ** ExistingSubtask)
{
    strcpy ((*ExistingSubtask)->SubtaskDetails.SubtaskTitle, "<enter subtask title here>");
    (*ExistingSubtask)->SubtaskDetails.IsCompleted = 0;
    (*ExistingSubtask)->next = NULL;
}

//MARK:-

static void readNewSubtask (SUBTASK_NODE ** NewSubtask)
{
    printf ("Enter subtask title:");
    scanf ("%s", (*NewSubtask)->SubtaskDetails.SubtaskTitle);
}

static void viewSubtask (const SUBTASK_NODE * ExistingSubtask)
{
    if (ExistingSubtask->SubtaskDetails.IsCompleted == 0)
        printf ("%s\n", ExistingSubtask->SubtaskDetails.SubtaskTitle);
}

static void addNewSubtask (TASK_NODE ** ExistingTask, SUBTASK_NODE * NewSubtask)
{
    if (! (*ExistingTask)->TaskDetails.ListOfSubtasks)
        (*ExistingTask)->TaskDetails.ListOfSubtasks = NewSubtask;
    
    else
    {
        SUBTASK_NODE * cur = (*ExistingTask)->TaskDetails.ListOfSubtasks;
        
        while (cur->next)
            cur = cur->next;
        
        cur->next = NewSubtask;
    }
}

static void viewListOfSubtasks (const TASK_NODE * ExistingTask)
{
    int i = 1;
    SUBTASK_NODE * cur = ExistingTask->TaskDetails.ListOfSubtasks;
    
    while (cur)
    {
        printf ("Subtask %d:\n", i++);
        viewSubtask (cur);
        cur = cur->next;
    }
}

static void markSubtaskAsCompleted (TASK_NODE ** ExistingTask, char SubtaskTitle [])
{
    SUBTASK_NODE * cur = (*ExistingTask)->TaskDetails.ListOfSubtasks;
    
    while (cur && (strcmp (cur->SubtaskDetails.SubtaskTitle, SubtaskTitle) != 0))
        cur = cur->next;
    
    if (! cur)
        printf ("ERROR -- Check the title and try again.\n");
    
    else
        cur->SubtaskDetails.IsCompleted = 1;
}

static void markAllSubtasksAsCompleted (TASK_NODE ** ExistingTask)
{
    SUBTASK_NODE *cur = (*ExistingTask)->TaskDetails.ListOfSubtasks;
    while (cur)
    {
        cur->SubtaskDetails.IsCompleted = 1;
        cur = cur->next;
    }
}

static void deleteSubtask (SUBTASK_NODE ** ListOfSubtasks, char SubtaskTitle [])
{
    SUBTASK_NODE *cur = *ListOfSubtasks;
    SUBTASK_NODE *prev = NULL;
    while (cur)
    {
        if (strcmp(cur->SubtaskDetails.SubtaskTitle, SubtaskTitle) == 0)
        {
            if (cur == *ListOfSubtasks)
            {
                *ListOfSubtasks = cur->next;
                free(cur);
                return;
            }
            else
            {
                if (prev)
                    prev->next = cur->next;
                return;
            }
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}

static void deleteSubtaskList (TASK_NODE ** ExistingTask)
{
    SUBTASK_NODE *cur = (*ExistingTask)->TaskDetails.ListOfSubtasks;
    while (cur)
    {
        (*ExistingTask)->TaskDetails.ListOfSubtasks = cur->next;
        cur = (*ExistingTask)->TaskDetails.ListOfSubtasks;
    }
}

//MARK:-

static void readNewTask (TASK_NODE ** NewTask)
{
    printf ("Enter task title:");
    scanf("%s",(*NewTask)->TaskDetails.TaskTitle);
    printf ("Enter scheduled date in the form of DD/MM/YYYY\n");
    getDate (&(*NewTask)->TaskDetails.ScheduledDate);
    (*NewTask)->next=NULL;
}


static void addNewTask (TASK_NODE ** ListOfTasks, TASK_NODE * NewTask)
{
    TASK_NODE *cur=(*ListOfTasks);
    TASK_NODE *prev=NULL;
    int res;
    
    if (*ListOfTasks==NULL)
    {
        NewTask->next=(*ListOfTasks);
        (*ListOfTasks)=NewTask;
    }
    
    else
    {
        cur=(*ListOfTasks);
        
        while(cur)
        {
            DATE date2 = cur->TaskDetails.ScheduledDate;
            DATE date1 = NewTask->TaskDetails.ScheduledDate;
            res = compareDates(date1,date2);
            if(res <= 0)
            {
                if (! prev)
                {
                    NewTask->next = cur;
                    *ListOfTasks = NewTask;
                    break;
                }
                
                if(prev)
                    prev->next=NewTask;
                
                NewTask->next=cur;
                break;
                
            }
            
            prev=cur;
            cur=cur->next;
        }
        if (prev)
            prev->next=NewTask;
    
        NewTask->next=cur;
    }
}

static void viewTask (const TASK_NODE * ExistingTask)
{
    if (ExistingTask == NULL)
        printf("No task scheduled.\n");
    
    else
    {
        if (ExistingTask->TaskDetails.IsCompleted == 0)
        {
        
        printf("%s\n",ExistingTask->TaskDetails.TaskTitle);
        printf ("Scheduled for: ");
        printf ("%d/%d/%d\n", ExistingTask->TaskDetails.ScheduledDate.day, ExistingTask->TaskDetails.ScheduledDate.month, ExistingTask->TaskDetails.ScheduledDate.year);
        
        if (ExistingTask->TaskDetails.ListOfSubtasks)
            viewListOfSubtasks(ExistingTask);
        }
    }
}

static void viewListOfTasks (const TASK_NODE * ListOfTasks)
{
    //IN ASCENDING ORDER BY DATE
    const TASK_NODE * cur = ListOfTasks;
    while(cur)
    {
        viewTask (cur);
        ListOfTasks=ListOfTasks->next;
        
        printf ("\n");
        cur = cur->next;
    }
}

static int viewTasksOnGivenDate (const TASK_NODE * ListOfTasks, DATE GivenDate)
{
    const TASK_NODE *cur = ListOfTasks;
    int flag = 0;
    
    if(ListOfTasks == NULL)
        printf("Task list empty.\n");
    
    else
    {
        while(cur)
        {
            if (! compareDates(cur->TaskDetails.ScheduledDate, GivenDate))
            {
                viewTask(cur);
                flag = 1;
            }
            cur=cur->next;
        }
    }
    return flag;
}

static void viewCompletedTasks (const TASK_NODE * ListOfTasks)
{
    const TASK_NODE *cur = ListOfTasks;
    SUBTASK_NODE *cur1;
    
    if (! ListOfTasks)
        printf ("Task list empty.\n");
    
    while (cur)
    {
        if (cur->TaskDetails.IsCompleted == 1)
        {
            printf ("Task:\n");
            printf("%s\n\n", cur->TaskDetails.TaskTitle);
            cur1 = cur->TaskDetails.ListOfSubtasks;
            
            printf ("Subtask(s):\n");
            
            while (cur1)
            {
                printf("%s\n", cur1->SubtaskDetails.SubtaskTitle);
                
                cur1 = cur1->next;
            }
        }
        cur = cur->next;
        printf ("\n");
    }
}

static TASK_NODE * searchByTaskTitle(TASK_NODE *ListOfTasks, char TaskTitle[])
{
    TASK_NODE *cur = ListOfTasks;
    while (cur)
    {
        if (strcmp (cur->TaskDetails.TaskTitle, TaskTitle) == 0)
            return cur;
        
        cur = cur->next;
    }
    return NULL;
}

static void markTaskAsCompleted (TASK_NODE ** ListOfTasks, char TaskTitle [])
{
    TASK_NODE *cur = (*ListOfTasks);
    
    while (cur && (strcmp(cur->TaskDetails.TaskTitle, TaskTitle)) != 0)
    {
        
        cur = cur->next;
    }
    if (cur)
    {
        cur->TaskDetails.IsCompleted = 1;
        SUBTASK_NODE *ListOfSubtasks = cur->TaskDetails.ListOfSubtasks;
        
        while (ListOfSubtasks)
        {
            ListOfSubtasks->SubtaskDetails.IsCompleted = 1;
            ListOfSubtasks = ListOfSubtasks->next;
        }
    }
}

static void markAllTasksAsCompleted (TASK_NODE ** ListOfTasks)
{
    TASK_NODE *cur = (*ListOfTasks);
    SUBTASK_NODE *cur1;
    while (cur)
    {
        cur->TaskDetails.IsCompleted = 1;
        cur1 = cur->TaskDetails.ListOfSubtasks;
        while (cur1)
        {
            cur1->SubtaskDetails.IsCompleted = 1;
            cur1 = cur1->next;
        }
        cur = cur->next;
    }
}

static void deleteTaskFromList (TASK_NODE ** ListOfTasks, char TaskTitle [])
{
    TASK_NODE *cur = *ListOfTasks;
    TASK_NODE *prev = NULL;
    while (cur)
    {
        if (strcmp(cur->TaskDetails.TaskTitle, TaskTitle) == 0)
        {
            if (cur == *ListOfTasks)
            {
                *ListOfTasks = cur->next;
                return;
            }
            else
            {
                if (prev)
                    prev->next = cur->next;
                return;
            }
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}

//MARK:-

static int isLeapYear (int y)
{
    return (y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0));
}

static int leapYears (int y)
{
    return y/4 - y/100 + y/400;
}

static int todayOf (int y, int m, int d)
{
    static int DayOfMonth[] = {-1, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    
    return DayOfMonth[m] + d + ((m > 2 && isLeapYear (y))? 1 : 0);
}

static long days (int y, int m, int d)
{
    int lastYear;
    lastYear = y - 1;
    
    return 365L * lastYear + leapYears(lastYear) + todayOf(y,m,d);
}

static void calendar (int y, int m) /* display calendar at m y */
{
    const char *NameOfMonth[] = {NULL, "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};
    
    char Week[] = "Su Mo Tu We Th Fr Sa";
    
    int DayOfMonth[] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
    int weekOfTopDay;
    int i, day;
    
    weekOfTopDay = days (y, m, 1) % 7;
    
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
    TASK_NODE *ListOfTasks;
    initListOfTasks(&ListOfTasks);
    
    char subtaskTitle [100];
    char taskTitle[100];
    
    while (1)
    {
        int ch;
        printf("Enter choice:");
        scanf("%d", &ch);
        
        switch (ch)
        {
            case 0:
                printf ("Welcome. Please enter the date in the form of MM/YY to view the calender for the required date.\n");
                
                int year,month;
                scanf("%d %*c %d", &month, &year);
                calendar(year, month);
                
                break;
                
                
            case 1:
                printf("Add a new task.\n");
                
                TASK_NODE  *NewTask = (TASK_NODE *)malloc(sizeof(TASK_NODE));
                initTaskDetails (&NewTask);
                
                printf ("Enter the task details mentioned below.\n");
                readNewTask (&NewTask);
                
                addNewTask (&ListOfTasks, NewTask);
                printf ("Task added successfully.\n");
                
                break;
                
            case 2:
                printf ("Add subtask to a task.\n");
                
                printf ("Enter title of task for which you'd like to add a subtask:");
                char TaskTitle [20];
                scanf ("%s", TaskTitle);
                
                TASK_NODE * ExistingTask = searchByTaskTitle(ListOfTasks, TaskTitle);
                
                if (ExistingTask)
                {
                    SUBTASK_NODE * NewSubtask = (SUBTASK_NODE *)malloc(sizeof(SUBTASK_NODE));
                    initSubtaskDetails (&NewSubtask);
                    
                    printf ("Enter subtask details below.\n");
                    readNewSubtask (&NewSubtask);
                    
                    addNewSubtask(&ExistingTask, NewSubtask);
                }
                
                else
                    printf ("The title did not match to any existing task. Try again.\n");
                
                break;
                
            case 3:
                printf ("View a task.\n");
                
                printf ("Enter title of task you want to view:");
                scanf ("%s", TaskTitle);
                
                ExistingTask = searchByTaskTitle(ListOfTasks, TaskTitle);
                
                if (ExistingTask)
                    viewTask (ExistingTask);
                
                else
                    printf ("The title did not match to any existing task. Try again.\n");
                
                break;
                
            case 4:
                printf ("View all tasks.\n\n");
                
                viewListOfTasks (ListOfTasks);
                
                break;
                
            case 5:
                printf ("View tasks on a given date.\n");
                
                DATE GivenDate;
                printf ("Enter date:");
                getDate (&GivenDate);
                
                if (! viewTasksOnGivenDate(ListOfTasks, GivenDate))
                    printf ("ERROR - No tasks found scheduled on the given date.\n");
                    
                break;
                
            case 6:
                printf ("View completed tasks.\n\n");
                
                viewCompletedTasks(ListOfTasks);
                
                break;
                
            case 7:
                printf ("Search for a task.\n");
                
                printf ("Enter title of task you want to search for:");
                scanf ("%s", TaskTitle);
                
                ExistingTask = searchByTaskTitle(ListOfTasks, TaskTitle);
                
                if (ExistingTask)
                    printf ("Task was found.\n");
                
                else
                    printf ("The title did not match to any existing task. Try again.\n");
                
                break;
                
            case 8:
                printf ("Mark a task as completed.\n");
                
                printf ("Enter title of task you want to mark as completed:");
                scanf ("%s", TaskTitle);
                
                ExistingTask = searchByTaskTitle(ListOfTasks, TaskTitle);
                
                if (ExistingTask)
                    markTaskAsCompleted(&ListOfTasks, TaskTitle);
                
                else
                    printf ("The title did not match to any existing task. Try again.\n");
                
                break;
                
            case 9:
                printf ("Mark all tasks as completed.\n");
                
                int IsSure;
                printf ("Are you sure?\n");
                scanf ("%d", &IsSure);
                
                if (IsSure)
                    markAllTasksAsCompleted (&ListOfTasks);
                
                break;
                
            case 10:
                printf ("Delete a task from the list.\n");
                
                printf ("Enter title of task you want to delete:");
                scanf ("%s", TaskTitle);
                
                ExistingTask = searchByTaskTitle(ListOfTasks, TaskTitle);
                
                if (ExistingTask)
                    deleteTaskFromList (&ListOfTasks, TaskTitle);
                
                else
                    printf ("The title did not match to any existing task. Try again.\n");
                
                break;
                
            case 11:
                printf("Enter Title of Task whose subtask is to be marked as complet:e\n");
                scanf("%s", taskTitle);
                ExistingTask = searchByTaskTitle(ListOfTasks, TaskTitle);
                
                if (ExistingTask)
                {
                    printf("Enter Title of Subtask to be marked as completed\n");
                    scanf("%s", subtaskTitle);
                    markSubtaskAsCompleted(&ExistingTask,subtaskTitle);
                }
                
                else
                    printf("The title did not match to any existing task. Try again.\n");
                
                break;
                
            case 12:
                printf("Enter Title of the task for which you want to mark all subtasks as completed:");
                scanf("%s", taskTitle);
                ExistingTask = searchByTaskTitle(ListOfTasks, TaskTitle);
                
                if (ExistingTask)
                    markAllSubtasksAsCompleted(&ExistingTask);
                else
                    printf("The title did not match to any existing task. Try again.\n");
                
                break;
                
            case 13:
                printf("Enter title of the task whose subtask is to be deleted:");
                scanf("%s", TaskTitle);
                ExistingTask = searchByTaskTitle(ListOfTasks, TaskTitle);
                
                if (ExistingTask)
                {
                    printf("Enter Title of the subtask to be deleted\n");
                    scanf("%s", subtaskTitle);
                    deleteSubtask (&(ExistingTask)->TaskDetails.ListOfSubtasks, subtaskTitle);
                    break;
                }
                else
                    printf("The title did not match to any existing task. Try again.\n");
                
                break;
                
            case 14:
                printf("Enter Title of Task whose every subtask is to be deleted.\n");
                scanf("%s", TaskTitle);
                ExistingTask = searchByTaskTitle(ListOfTasks, TaskTitle);
                
                if (ExistingTask)
                    deleteSubtaskList(&ExistingTask);
                else
                    printf("The title did not match to any existing task. Try again.\n");
                
                break;
                
        }
    }
}