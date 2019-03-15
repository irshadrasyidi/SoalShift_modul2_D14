#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(){
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

	return 0;
}
