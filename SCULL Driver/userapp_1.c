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

#define CDRV_IOC_MAGIC 'Z'
#define E2_IOCMODE1 _IOWR(CDRV_IOC_MAGIC, 1, int)
#define E2_IOCMODE2 _IOWR(CDRV_IOC_MAGIC, 2, int)

#define MODE1 1 
#define MODE2 2

/* Parent and child proces enter Mode2 and try to enter Mode1 */

void main(int argc, char* argv[]){
int fd = open("/dev/a5",O_RDWR);
pid_t pid;
int count;
int ret;

/* Changing to mode2 */
ioctl(fd,E2_IOCMODE2,0);
/*	*/

pid = fork();
close(fd);

switch(pid){

case -1:
	printf("Error while creating child process\n");
	break;

case 0:
	sleep(2);
	printf("Child Process opening the device\n");
	fd = open("/dev/a5",O_RDWR);
	printf("Child Process successfully opened the device in Mode2\n");
	printf("Child Process sleeping for 5 seconds\n");
	sleep(5);
	printf("Child process trying to change to Mode1\n");
	ioctl(fd,E2_IOCMODE1,0);
	printf("Child process successfully changed to Mode1\n");
	close(fd);
	break;

default:
	printf("Parent Process opening the device\n");
	fd = open("/dev/a5",O_RDWR);
	printf("Parent Process successfully opened the device in Mode2\n");
	printf("Parent Process sleeping for 5 seconds\n");
	sleep(5);
	printf("Parent process trying to change to Mode1\n");
	ioctl(fd,E2_IOCMODE1,0);
	printf("Parent process successfully changed to Mode1\n");
	wait(NULL);
	close(fd);
	break;
}


close(fd);
return;


}


