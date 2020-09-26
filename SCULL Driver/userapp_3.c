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


/* Same process tries to open the device file when it is in Mode1*/

void main(int argc, char* argv[]){
int fd;
int fd_1,fd_2;
int fd_p,fd_c,ret;
pid_t pid;
int count;


/* Changing mode to Mode1 if it is already not in Mode 1 */
fd = open("/dev/a5",O_RDWR);
ioctl(fd,E2_IOCMODE1,0);
close(fd);
/*	*/


/* Opening for the first time */
printf("Opening the device for the first time\n");
fd_1 = open("/dev/a5",O_RDWR);
printf("Opened the device for the first time\n");
/* Opening for the second time */
printf("Opening the device for the second time\n");
fd_2 = open("/dev/a5",O_RDWR);
printf("Opened the device for the second time\n"); /* This statement should not get printed if there is deadlock*/
/* Closing the file. Deadlock happens here.*/

close(fd_1);
close(fd_2);

return;


}


