#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>
#include <pthread.h>

#define CDRV_IOC_MAGIC 'Z'
#define E2_IOCMODE1 _IOWR(CDRV_IOC_MAGIC, 1, int)
#define E2_IOCMODE2 _IOWR(CDRV_IOC_MAGIC, 2, int)

#define MODE1 1 
#define MODE2 2


/* Same process tries to open the device file when it is in Mode1*/

static void* open_device(){
int fd;
fd = open("/dev/a5",O_RDWR);
close(fd);
return 0;
}

void main(int argc, char* argv[]){
int fd;
int fd_1,fd_2;
pthread_t t1;
pid_t pid_1,pid_2;
int count;


/* Changing mode to Mode1 if it is already not in Mode 1 */
fd = open("/dev/a5",O_RDWR);
ioctl(fd,E2_IOCMODE1,0);
close(fd);
/*	*/

fd = open("/dev/a5",O_RDWR);
/* Calling the thread */
printf("Calling thread\n");
pthread_create(&t1,NULL,open_device,NULL);
pthread_join(t1,NULL);
close(fd);
printf("Thread returned\n");
return;


}


