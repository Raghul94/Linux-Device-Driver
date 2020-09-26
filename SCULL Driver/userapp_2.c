#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <time.h>

#define CDRV_IOC_MAGIC 'Z'
#define E2_IOCMODE1 _IOWR(CDRV_IOC_MAGIC, 1, int)
#define E2_IOCMODE2 _IOWR(CDRV_IOC_MAGIC, 2, int)

#define MODE1 1 
#define MODE2 2


/* Parent process opens in Mode1 and tries to go to Mode2 while Child process is waiting to open device */

void main(int argc, char* argv[]){
int fd;
int fd_p,fd_c,ret;
pid_t pid;
int count;


fd = open("/dev/a5",O_RDWR);

/* Changing mode to Mode1 */
ioctl(fd,E2_IOCMODE1,0);
/**/

close(fd);
pid = fork();

switch(pid){

case -1:
	printf("Error while creating child process\n");
	break;

case 0:
	sleep(5);
	printf("Child Process trying to open device\n");
	fd_c = open("/dev/a5",O_RDWR);
	printf("Child Process successfully opened device\n");
	close(fd_c);


default:
	printf("Parent Process trying to open device in Mode1\n");
	fd_p = open("/dev/a5",O_RDWR);
	printf("Parent Process successfully openend device in Mode1\n");
	printf("Parent process Sleeping for 10s\n");
	sleep(10);
	printf("Parent process trying to change to Mode2\n");
	ret = ioctl(fd_p,E2_IOCMODE2,0);
	printf("Parent Process successfully changed to Mode2\n");
	close(fd_p);
	break;
}


return;


}


