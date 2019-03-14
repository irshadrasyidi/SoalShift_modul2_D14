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
#include <sys/wait.h>

char *buatnama(int x){
	//func formatiing nama folder
	time_t wkt = time(NULL);
	struct tm waktu = *localtime(&wkt);
	static char temp[200];
	static char nama[200];
	memset(&temp, 0, sizeof(temp));
	memset(&nama, 0, sizeof(nama));
	//if utk format sesuai current time
	if(x == 1){
		if(waktu.tm_mday < 10){
			sprintf(temp, "%d", 0);
			strcat(nama, temp);
			sprintf(temp, "%d", waktu.tm_mday);
			strcat(nama, temp);
		}else{
			sprintf(temp, "%d", waktu.tm_mday);
			strcat(nama, temp);
		}
		strcat(nama, ":");
		if(waktu.tm_mon < 10){
			sprintf(temp, "%d", 0);
			strcat(nama, temp);
			sprintf(temp, "%d", waktu.tm_mon + 1);
			strcat(nama, temp);
		}else{
			sprintf(temp, "%d", waktu.tm_mon + 1);
			strcat(nama, temp);
		}
		strcat(nama, ":");
		//sprintf(temp, "%d", waktu.tm_year);
		sprintf(temp, "%d", waktu.tm_year + 1900);
		strcat(nama, temp);
		strcat(nama, "-");
		if(waktu.tm_hour < 10){
			sprintf(temp, "%d", 0);
			strcat(nama, temp);
			sprintf(temp, "%d", waktu.tm_hour);
			strcat(nama, temp);
		}else{
			sprintf(temp, "%d", waktu.tm_hour);
			strcat(nama, temp);
		}
		strcat(nama, ":");
		if(waktu.tm_min < 10){
			sprintf(temp, "%d", 0);
			strcat(nama, temp);
			sprintf(temp, "%d", waktu.tm_min);
			strcat(nama, temp);
		}else{
			sprintf(temp, "%d", waktu.tm_min);
			strcat(nama, temp);
		}
		//printf("%s\n", nama);
		
	}
	//else utk format current time + 30 mnt
	else{
		waktu.tm_min += 30;
		mktime(&waktu);
		//printf("%s\n", nama);

		if(waktu.tm_mday < 10){
			sprintf(temp, "%d", 0);
			strcat(nama, temp);
			sprintf(temp, "%d", waktu.tm_mday);
			strcat(nama, temp);
		}else{
			sprintf(temp, "%d", waktu.tm_mday);
			strcat(nama, temp);
		}
		strcat(nama, ":");
		if(waktu.tm_mon < 10){
			sprintf(temp, "%d", 0);
			strcat(nama, temp);
			sprintf(temp, "%d", waktu.tm_mon + 1);
			strcat(nama, temp);
		}else{
			sprintf(temp, "%d", waktu.tm_mon + 1);
			strcat(nama, temp);
		}
		strcat(nama, ":");
		sprintf(temp, "%d", waktu.tm_year + 1900);
		strcat(nama, temp);
		strcat(nama, "-");
		if(waktu.tm_hour < 10){
			sprintf(temp, "%d", 0);
			strcat(nama, temp);
			sprintf(temp, "%d", waktu.tm_hour);
			strcat(nama, temp);
		}else{
			sprintf(temp, "%d", waktu.tm_hour);
			strcat(nama, temp);
		}
		strcat(nama, ":");
		if(waktu.tm_min < 10){
			sprintf(temp, "%d", 0);
			strcat(nama, temp);
			sprintf(temp, "%d", waktu.tm_min);
			strcat(nama, temp);
		}else{
			sprintf(temp, "%d", waktu.tm_min);
			strcat(nama, temp);
		}
		//printf("%s\n", nama);
	}
	return nama;
}

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

	char pathdir[200];
	memset(&pathdir, 0, sizeof(pathdir));
	strcat(pathdir, "/home/irshadrasyidi/log/");

	int status;

  	pid = fork();

  	if (pid == 0) {
	    	while(1){
			char nama[200];
			memset(&nama, 0, sizeof(nama));
			strcat(nama, buatnama(1));

			strcat(pathdir, nama);
			//printf("%s\n", pathdir);
			mkdir(pathdir, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);

			memset(&pathdir, 0, sizeof(pathdir));
			strcat(pathdir, "/home/irshadrasyidi/log/");

			sleep(1800);
		}
  	} else if (pid > 0){
		//while ((wait(&status)) > 0);

		int counter = 0;
		int start = 1;
		char scndryname[200];
		memset(&scndryname, 0, sizeof(scndryname));
		while(1){
			//printf("pls masuk\n");
			char primryname[200];
			char currentname[200];
			memset(&primryname, 0, sizeof(primryname));
			memset(&currentname, 0, sizeof(currentname));

			strcat(currentname, buatnama(1));
			
			char tmp[200];
			memset(&tmp, 0, sizeof(tmp));
			strcat(tmp, pathdir);
			strcat(tmp, scndryname);

			struct stat info;

			//printf("%s\n", currentname);

			if (start == 1){
				//printf("masuk if start1");
				memset(&primryname, 0, sizeof(primryname));
				strcat(primryname, buatnama(1));
				memset(&scndryname, 0, sizeof(scndryname));
				strcat(scndryname, buatnama(0));
			}
			//cek jika sdh waktunya pindah folder
			else if ((start < 1) && (strcmp(currentname, scndryname) == 0) && (stat(tmp, &info) == 0)){
				//printf("masuk if start0");
				memset(&primryname, 0, sizeof(primryname));
				strcat(primryname, scndryname);
				memset(&scndryname, 0, sizeof(scndryname));
				strcat(scndryname, buatnama(0));
			}
			
			memset(&tmp, 0, sizeof(tmp));
			strcat(tmp, pathdir);
			strcat(tmp, primryname);

			//printf("%s\n", tmp);
			//cek apakah folder sdh siap
			if ((stat(tmp, &info) == 0) && (strcmp(primryname, "") != 0)){
				while(1){
					printf("tes\n");
					start--;
					char pathsys[200];
					memset(&pathsys, 0, sizeof(pathsys));
					strcat(pathsys, "/var/log/syslog");

					//proses formatting path + nama file
					char filelog[200];
					memset(&filelog, 0, sizeof(filelog));
					strcat(filelog, pathdir);
					strcat(filelog, primryname);
					strcat(filelog, "/log");
					char temp[50];
					memset(&temp, 0, sizeof(temp));
					sprintf(temp, "%d", counter + 1);
					strcat(filelog, temp);
					strcat(filelog, ".log");

					FILE *sys=fopen((char*)pathsys, "r");
					FILE *log=fopen((char*)filelog, "w");

					//loop copy syslog
					char ch;
					while((ch = fgetc(sys)) != EOF ){
						fputc(ch, log);
					}
					fclose(sys);
					fclose(log);

					counter++;
					if(counter % 30 == 0){
						//printf("BREAK\n");
						break;
					}
					sleep(60);
				}
			}
		}
	}
  
  exit(EXIT_SUCCESS);
}
