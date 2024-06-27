#include <stdio.h>
#include <stdlib.h>

#define RR_QUANTUM 4
#define QUANTUM 20

struct Process {
    int p_id;
    int start_burst_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

int time = 0;
int flag0 = 0;

int rr_scheduling(struct Process *queue, int n) {
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (queue[i].burst_time != 0) {
                done = 0;
                if (queue[i].burst_time + time <= QUANTUM && queue[i].burst_time <= RR_QUANTUM) {
                    time += queue[i].burst_time;
                    queue[i].burst_time = 0;
                    queue[i].turnaround_time = time;
                    queue[i].waiting_time = queue[i].turnaround_time - queue[i].start_burst_time;
                } else if (queue[i].burst_time + time <= QUANTUM && queue[i].burst_time > RR_QUANTUM){
                    queue[i].burst_time -= RR_QUANTUM;
                    time += RR_QUANTUM;
                } else if (queue[i].burst_time + time > QUANTUM && queue[i].burst_time <= RR_QUANTUM) {
                    int temp_time = QUANTUM - time;
                    queue[i].burst_time -= temp_time;
                    time += temp_time;
                    break;
                }
            }
        }
        if (done || time > QUANTUM) {
            if (done){
                flag0 = 1;
            }
            break;
        }
    }
    return time;
}

int sjf_scheduling(struct Process *queue, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (queue[j].burst_time > queue[j + 1].burst_time) {
                struct Process temp = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp;
            }
        }
    }
    int time1 = 0, flag = 0;
    for (int i = 0; i < n; i++) {
        if (queue[i].burst_time + time1 <= QUANTUM) {
            if (i > 0) {
                queue[i].turnaround_time = queue[i - 1].turnaround_time + queue[i].burst_time;
                queue[i].burst_time = 0;
            } else {
                queue[i].turnaround_time = queue[i].burst_time;
                queue[i].burst_time = 0;
            }
            queue[i].waiting_time = queue[i].turnaround_time - queue[i].start_burst_time;
            time1 += queue[i].burst_time;
        } else if (queue[i].burst_time + time1 > QUANTUM) {
            int temp_time = QUANTUM - time1;
            queue[i].burst_time -= temp_time;
            time1 += queue[i].burst_time;
        }
        if (time1 == QUANTUM) {
            return flag;
        }
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + queue[i].burst_time;
    }
    if (sum == 0) {
        flag = 1;
    }
    return flag;
}

int fifo_scheduling(struct Process *queue, int n) {
    int time2 = 0, flag = 0;
    for (int i = 0; i < n; i++) {
        if (queue[i].burst_time + time2 <= QUANTUM) {
            if (i > 0) {
                queue[i].turnaround_time = queue[i - 1].turnaround_time + queue[i].burst_time;
            } else {
                queue[i].turnaround_time = queue[i].burst_time;
            }
            queue[i].waiting_time = queue[i].turnaround_time - queue[i].start_burst_time;
            time2 += queue[i].burst_time;
        } else if (queue[i].burst_time + time2 > QUANTUM){
            int temp_time = QUANTUM - time2;
            queue[i].burst_time -= temp_time;
            time2 += queue[i].burst_time;
        }
        if (time2 == QUANTUM){
            return flag;
        }
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + queue[i].burst_time;
    }
    if (sum == 0){
        flag = 1;
    }
    return flag;
}

void multilevel_scheduling(struct Process *processes, int n) {
    struct Process q0[n], q1[n], q2[n], q3[n];
    int q0_size = 0, q1_size = 0, q2_size = 0, q3_size = 0;

    for (int i = 0; i < n; i++) {
        switch (processes[i].priority) {
            case 1:
                q0[q0_size++] = processes[i];
                break;
            case 2:
                q1[q1_size++] = processes[i];
                break;
            case 3:
                q2[q2_size++] = processes[i];
                break;
            case 4:
                q3[q3_size++] = processes[i];
                break;
            default:
                printf("Invalid priority\n");
                exit(1);
        }
    }

    while (1) {
        time = rr_scheduling(q0, q0_size);
        int flag1 = sjf_scheduling(q1, q1_size);
        int flag2 = sjf_scheduling(q2, q2_size);
        int flag3 = fifo_scheduling(q3, q3_size);
        if (flag0 == 1 && flag1 == 1 && flag2 == 1 && flag3 == 1) {
            break;
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter process ID for process %d: ", i + 1);
        scanf("%d", &processes[i].p_id);

        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].start_burst_time = processes[i].burst_time;

        printf("Enter priority for process %d (use between 1-4): ", i + 1);
        scanf("%d", &processes[i].priority);
        printf("\n");
    }

    multilevel_scheduling(processes,n);

    printf("Process ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].p_id, processes[i].burst_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
    }
    return 0;
}