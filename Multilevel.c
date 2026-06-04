#include<stdio.h>

struct process
{
    int p_id;
    int atime;
    int btime;
    int ctime;
    int tat;
    int wtime;
    int type;
};

void FCFS(struct process p[], int n, int start)
{
    int time=start;

    for(int i=0; i<n; i++)
    {
        if(time <p[i].atime)
            time = p[i].atime;

        time += p[i].btime;
        p[i].ctime = time;
        p[i].tat = p[i].ctime - p[i].atime;
        p[i].wtime = p[i].tat - p[i].btime;
    }
}

int main()
{
    int n, sys_n, user_n;
     printf("Enter total number of processes:");
     scanf("%d", &n);

     struct process sys[20], user[20], all[50];

     sys_n=0, user_n=0;

     for(int i=0; i<n; i++)
     {
         struct process p;

         printf("\nProcess %d\n", i+1);
         printf("Enter Arrival Time: ");
         scanf("%d", &p.atime);
         printf("Enter Burst Time: ");
         scanf("%d", &p.btime);
         printf("Enter Type(1-System, 2-User): ");
         scanf("%d", &p.type);

         p.p_id = i+1;

         if(p.type == 1)
            sys[sys_n++]=p;
         else
            user[user_n++]=p;
     }

     FCFS(sys, sys_n, 0);

     int last_time = 0;
     if(sys_n > 0)
        last_time = sys[sys_n - 1].ctime;

     for(int i=0; i<user_n; i++)
     {
         if(i==0 && user[i].atime < last_time)
            user[i].atime = last_time;
     }

     FCFS(user, user_n, last_time);

     int k = 0;
    for(int i = 0; i < sys_n; i++)
        all[k++] = sys[i];

    for(int i = 0; i < user_n; i++)
        all[k++] = user[i];

    float total_wtime = 0, total_tat = 0;

    printf("\nFinal Scheduling Table:\n");
    printf("PID\tType\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < k; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n", all[i].p_id, (all[i].type == 1) ? "SYS" : "USR", all[i].atime, all[i].btime, all[i].ctime, all[i].tat, all[i].wtime);

        total_wtime += all[i].wtime;
        total_tat += all[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", total_wtime / k);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / k);

     return 0;
}
