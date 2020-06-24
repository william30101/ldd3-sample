
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include "scull_ioctl.h"
 
#define SCULL_DEVICE "/dev/scull0"
 
int main(int argc, char *argv[])
{
    int fd = 0;
    int quantum = 8000;
    int quantum_old = 0;
    int qset = 2000;
    int qset_old = 0;

    char* testArg = "William test";
    char receivedArr[30] = "";
    
    fd = open(SCULL_DEVICE, O_RDWR);
    if(fd < 0)
    {
        printf("open scull device error!\n");
        return 0;
    }
 
    printf("SCULL_IOCSQUANTUM: quantum = %s\n", testArg);
    ioctl(fd, SCULL_IOCSQUANTUM, testArg);
    // quantum -= 500;
    // printf("SCULL_IOCTQUANTUM: quantum = %d\n", quantum);    
    // ioctl(fd, SCULL_IOCTQUANTUM, quantum);
    
    ioctl(fd, SCULL_IOCGQUANTUM, &receivedArr);
    printf("SCULL_IOCGQUANTUM: quantum = %s\n", receivedArr);    
    quantum = ioctl(fd, SCULL_IOCQQUANTUM);
    printf("SCULL_IOCQQUANTUM: quantum = %s\n", receivedArr);    
 
    quantum -= 500;
    quantum_old = ioctl(fd, SCULL_IOCHQUANTUM, quantum);
    printf("SCULL_IOCHQUANTUM: quantum = %d, quantum_old = %d\n", quantum, quantum_old);    
    quantum -= 500;
    printf("SCULL_IOCXQUANTUM: quantum = %d\n", quantum);
    ioctl(fd, SCULL_IOCXQUANTUM, &quantum);
    printf("SCULL_IOCXQUANTUM: old quantum = %d\n", quantum);
 
    printf("SCULL_IOCSQSET: qset = %d\n", qset);
    ioctl(fd, SCULL_IOCSQSET, &qset);
    qset += 500;
    printf("SCULL_IOCTQSET: qset = %d\n", qset);
    ioctl(fd, SCULL_IOCTQSET, qset);
 
    ioctl(fd, SCULL_IOCGQSET, &qset);
    printf("SCULL_IOCGQSET: qset = %d\n", qset);
    qset = ioctl(fd, SCULL_IOCQQSET);
    printf("SCULL_IOCQQSET: qset = %d\n", qset);
 
    qset += 500;
    qset_old = ioctl(fd, SCULL_IOCHQSET, qset);
    printf("SCULL_IOCHQSET: qset = %d, qset_old = %d\n", qset, qset_old);    
    qset += 500;
    printf("SCULL_IOCXQSET: qset = %d\n", qset);        
    ioctl(fd, SCULL_IOCXQSET, &qset);
    printf("SCULL_IOCHQSET: old qset = %d\n", qset);
 
    return 0;
}