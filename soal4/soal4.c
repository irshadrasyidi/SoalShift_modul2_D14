#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

	char pathmakanan[200];
	memset(&pathmakanan, 0, sizeof(pathmakanan));
	strcat(pathmakanan, "/home/irshadrasyidi/Documents/makanan/makan_enak.txt");
	int no = 1;
  while(1) {
    // main program here
	struct stat info;
	stat(pathmakanan, &info);
	time_t waktu = time(NULL);
	time_t lastaccess = info.st_atime;

	//cek supaya makan sehat keluar cmn 30 dtk pertama setelah lastaccess
	if(difftime(waktu, lastaccess) <= 30){
		//printf("tes\n");
		char sehat[200];
		memset(&sehat, 0, sizeof(sehat));
		strcat(sehat, "/home/irshadrasyidi/Documents/makanan/makan_sehat");
		char temp[200];
		memset(&temp, 0, sizeof(temp));
		
		//printf("%s\n", sehat);

		sprintf(temp, "%d", no);
		strcat(sehat, temp);
		strcat(sehat, ".txt");

		FILE *createfile=fopen((char*)sehat,"w");

		no++;
		//printf("%d\n", no);

	}

    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}
