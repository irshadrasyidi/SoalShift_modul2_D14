#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
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
	return(0);
}
