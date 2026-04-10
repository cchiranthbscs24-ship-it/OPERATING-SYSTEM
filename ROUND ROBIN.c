#include <stdio.h>

struct process {
    int process_id;
    int arrivaltime;
    int bursttime;
    int remainingtime;
    int compt;
    int tat;
    int waitt;
};

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, Burst Time for process %d:\n", i+1);
        scanf("%d", &p[i].process_id);
        scanf("%d", &p[i].arrivaltime);
        scanf("%d", &p[i].bursttime);
        p[i].remainingtime = p[i].bursttime;
        p[i].compt = 0;
        p[i].tat = 0;
        p[i].waitt = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int current_time = 0;
    int completed = 0;


    while (completed < n) {
        int done_in_cycle = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].remainingtime > 0 && p[i].arrivaltime <= current_time) {
                done_in_cycle = 1;
                if (p[i].remainingtime > tq) {
                    current_time += tq;
                    p[i].remainingtime -= tq;
                } else {
                    current_time += p[i].remainingtime;
                    p[i].remainingtime = 0;
                    p[i].compt = current_time;
                    p[i].tat = p[i].compt - p[i].arrivaltime;
                    p[i].waitt = p[i].tat - p[i].bursttime;
                    completed++;
                }
            }
        }
        if (!done_in_cycle) {
            current_time++; //
        }
    }

    float avg_wait = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wait += p[i].waitt;
        avg_tat += p[i].tat;
    }
    avg_wait /= n;
    avg_tat /= n;

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].process_id,
               p[i].arrivaltime,
               p[i].bursttime,
               p[i].compt,
               p[i].tat,
               p[i].waitt);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_wait);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
