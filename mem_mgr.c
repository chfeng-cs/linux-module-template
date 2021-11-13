#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <sched.h>


int count = 0;
void *memory_list[100];

void free_memory() {
    while (count) {
        free(memory_list[--count]);
    }
    
}

int main(int argc, char** argv) {
    fd_set rfds;
    pid_t pid, ppid;
    pid = getpid();
    ppid = getppid();

    printf("pid: %d\tppid: %d\n", pid, ppid);
    while (1) {
        int op;
        scanf("%d", &op);
        switch (op) {
            void *p;
            int s;
        case 1:
            printf("1\n");
            break;
        case 2:
            printf("malloc memory(KB): ");
            scanf("%d", &s);
            p = malloc(s * 1024);
            if (p == NULL) {
                printf("malloc failed!\n");
            } else {
                memory_list[count++] = p;
            }
            break;
        case 3:
            free_memory();
            break;
        case 9:
            free_memory();
            exit(0);
            break;
        default:
            break;
        }
    }
    

    return 0;
}
