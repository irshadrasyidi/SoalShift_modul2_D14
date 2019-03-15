#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

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
  //close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    // main program here
	DIR *d, *d2;
	struct dirent *dir, *dir2;
	d = opendir(".");
	d2 = opendir(".");

	char *end;

	char dst[250], src[250];
	strcat(dst, "/home/irshadrasyidi/Documents/SISOP/MODUL2/SOALSHIFT/soal1/");
	strcat(src, "/home/irshadrasyidi/modul2/gambar/");
	char *namadst;
	char *namasrc;

	if (d){
		//printf("bisa masuk if\n");
		while ((dir = readdir(d)) != NULL){
			//printf("bisa masuk while\n");
			dir2 = readdir(d2);
			strcpy(dst, "");
			strcpy(src, "");
			strcat(dst, "/home/irshadrasyidi/Documents/SISOP/MODUL2/SOALSHIFT/soal1/");
			strcat(src, "/home/irshadrasyidi/modul2/gambar/");
			if ( strstr( dir->d_name, ".png" ) && strstr( dir2->d_name, ".png" ) && (strcmp(dir->d_name, dir2->d_name) == 0) ){
				//printf("bisa masuk if2\n");
				end = dir2->d_name + strlen(dir2->d_name);
				while(end > dir2->d_name && *end != '.'){
					--end;
				}
				if (end > dir2->d_name) {
					*end = '\0';
				}
				strcat(dir2->d_name, "_grey.png");
				
				namadst = dir->d_name;
				namasrc = dir2->d_name;

				strcat(dst, namadst);
				strcat(src, namasrc);

				rename(dst, src);
			}
		}
	closedir(d);
	closedir(d2);
	}
    sleep(3);
  }
  
  exit(EXIT_SUCCESS);
}
