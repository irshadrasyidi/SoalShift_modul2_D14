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

char *buatnama(){
	time_t wkt = time(NULL);
	struct tm waktu = *localtime(&wkt);
	static char temp[200];
	static char nama[200];
	memset(&temp, 0, sizeof(temp));
	memset(&nama, 0, sizeof(nama));
	//if(x == 0){
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
		
	/*}else{
		waktu.tm_min += 30;
		mktime(&waktu);
		sprintf(temp, "%d", waktu.tm_mday);
		strcat(nama, temp);
		strcat(nama, ":");
		sprintf(temp, "%d", waktu.tm_mon + 1);
		strcat(nama, temp);
		strcat(nama, ":");
		sprintf(temp, "%d", waktu.tm_year + 1900);
		strcat(nama, temp);
		strcat(nama, "-");
		sprintf(temp, "%d", waktu.tm_hour);
		strcat(nama, temp);
		strcat(nama, ":");
		sprintf(temp, "%d", waktu.tm_min);
		strcat(nama, temp);
	}*/
	return nama;
}

int main(){
	//int x;
	//scanf("%d", &x);
	//printf("%s\n", buatnama(x));
	char pathdir[200];
	char nama[200];
	memset(&pathdir, 0, sizeof(pathdir));
	memset(&nama, 0, sizeof(nama));
	strcat(pathdir, "/home/irshadrasyidi/log/");
	strcat(nama, buatnama());
	strcat(pathdir, nama);
	printf("%s\n", pathdir);
	//mkdir(pathdir, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);
	FILE *bacafel=fopen("sourcecoba.txt", "r");
	FILE *buatfel=fopen("destcoba.txt", "w");

	char ch;
	while((ch = fgetc(bacafel)) != EOF ){
		fputc(ch, buatfel);
	}

	return 0;
}
