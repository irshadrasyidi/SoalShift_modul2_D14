#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

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

  while(1) {
    // main program here
	chmod("/home/irshadrasyidi/Documents/SISOP/MODUL2/SOALSHIFT/soal2/hatiku/elen.ku", S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);
	struct stat info;
	char alamat[250] = "/home/irshadrasyidi/Documents/SISOP/MODUL2/SOALSHIFT/soal2/hatiku/elen.ku";
	struct group *grp;
	struct passwd *pwd;
	stat(alamat, &info);

	//ambil grupname
	grp = getgrgid(info.st_gid);
	//printf("group: %s\n", grp->gr_name);

	//ambil username
	pwd = getpwuid(info.st_uid);
	//printf("username: %s\n", pwd->pw_name);
	
	//cek klo grupname & username == www-data
	if(!strcmp(grp->gr_name, "www-data") && !strcmp(pwd->pw_name, "www-data")){
		//printf("username: %s\n", pwd->pw_name);
		remove("/home/irshadrasyidi/Documents/SISOP/MODUL2/SOALSHIFT/soal2/hatiku/elen.ku");
	}
    sleep(3);
  }
  
  exit(EXIT_SUCCESS);
}
