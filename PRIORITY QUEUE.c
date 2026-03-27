#include <stdio.h>

#define MAX 20

typedef struct {
    int pid, at, bt, pr, rt, ct, wt, tat, completed;
} Process;

void nonPreemptive(Process p[], int n) {
    int time = 0, completed = 0, min_pr, index;

    while (completed < n) {
        min_pr = 9999;
        index = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].completed == 0) {
                if (p[i].pr < min_pr) {
                    min_pr = p[i].pr;
                    index = i;
                }
            }
        }
         if (index != -1) {
            time += p[index].bt;
            p[index].ct = time;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            p[index].completed = 1;
            completed++;
        } else {
            time++;
        }
    }
}

void preemptive(Process p[], int n) {
    int time = 0, completed = 0, min_pr, index;

    while (completed < n) {
        min_pr = 9999;
        index = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (p[i].pr < min_pr) {
                    min_pr = p[i].pr;
                    index = i;
                }
            }
        }

        if (index != -1) {
            p[index].rt--;
            time++;

            if (p[index].rt == 0) {
                p[index].ct = time;
                p[index].tat = p[index].ct - p[index].at;
                p[index].wt = p[index].tat - p[index].bt;
                completed++;
            }
        } else {
            time++;
        }
    }
}

void display(Process p[], int n) {
    float total_wt = 0, total_tat = 0;

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

int main() {
    Process p[MAX], temp[MAX];
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        p[i].pid = i + 1;

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Priority (lower = higher priority): ");
        scanf("%d", &p[i].pr);

        p[i].rt = p[i].bt;
        p[i].completed = 0;
    }

    printf("\n1. Non-Preemptive Priority Scheduling");
    printf("\n2. Preemptive Priority Scheduling");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    for (int i = 0; i < n; i++) {
        temp[i] = p[i];
    }

    switch (choice) {
        case 1:
            nonPreemptive(temp, n);
            printf("\n--- Non-Preemptive Priority Scheduling ---\n");
            display(temp, n);
            break;

        case 2:
            preemptive(temp, n);
            printf("\n--- Preemptive Priority Scheduling ---\n");
            display(temp, n);
            break;

        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
