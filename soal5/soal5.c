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

//PENTING
//Settingan Kode Sekarang:
//Pembuatan folder setiap 1 menit, dan pembuatan file log tiap 4 detik


//Revisi:
//Penyebab demo gagal -> fungsi 'buatnama' lupa tidak diganti waktu menit-nya:
//Pada soal, diminta pembuatan folder setiap 30 menit, sedangkan waktu demo, durasinya diganti jadi sekian menit


//Pada fungsi buatnama, ia bekerja untuk membuat sebuah string dengan format waktu seperti pada soal
//Fungsi ini menerima 1 parameter integer:
//jika bernilai 1, maka dibuat sebuah format waktu sesuai waktu sekarang
//jika bernilai 0, maka dibuat sebuah format waktu sesuai dengan waktu 30 menit dari sekarang
//Karena pada saat demo waktunya diganti, fungsi ini lupa diganti dan tetap membuat string dengan format 30 menitan, mengakibatkan folder berikutnya tidak bisa diisi dengan file log#.log selanjutnya

char *buatnama(int x){
	//func formatiing nama folder
	time_t wkt = time(NULL);
	struct tm waktu = *localtime(&wkt);
	static char temp[200];
	static char nama[200];
	memset(&temp, 0, sizeof(temp));
	memset(&nama, 0, sizeof(nama));
	//if utk format sesuai current time
	//pembuatan format waktu sesuai waktu sekarang
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
	//pembuatan format waktu 30 menit ATAU 1 menit kemudian (pilih salah satu, dan komen baris yang tidak dipilih)
	else{
		waktu.tm_min += 1; 		//ini yang 1 menit
		//waktu.tm_min += 30; 		//ini yang 30 menit

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

			//sleep(60) untuk pembuatan file setiap 60 detik atau 1 menit
			sleep(60);
		}
  	} else if (pid > 0){
		//pada proses parent, tidak digunakan wait karena 2 proses ini berjalan secara paralel/bersamaan

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
			

			//Mulai bagian ini, fungsi 'buatnama' mulai sering dipanggil
			//Karena fungsi ini berperan penting dalam pemilihan folder tempat diletakkannya file log, maka pada saat demo, proses tidak berjalan karena string nama yang dihasilkan merupakan string 30 menit selanjutnya, tetapi folder wadah yang dibuat tidak dengan nama 30 menit selanjutnya, sehingga tidak cocok

			if (start == 1){
				//printf("masuk if start1");
				memset(&primryname, 0, sizeof(primryname));
				strcat(primryname, buatnama(1));
				memset(&scndryname, 0, sizeof(scndryname));
				strcat(scndryname, buatnama(0));
			}
			//cek jika sdh waktunya pindah folder
			else if (start != 1 && (strcmp(currentname, scndryname) == 0) && (stat(tmp, &info) == 0)){
				//printf("masuk if start0");
				memset(&primryname, 0, sizeof(primryname));
				strcat(primryname, scndryname);
				memset(&scndryname, 0, sizeof(scndryname));
				strcat(scndryname, buatnama(0));
			}
			
			memset(&tmp, 0, sizeof(tmp));
			strcat(tmp, pathdir);
			strcat(tmp, primryname);

			//cek apakah folder sdh siap
			if ((stat(tmp, &info) == 0) && (strcmp(primryname, "") != 0)){
				while(1){
					//printf("tes\n");
					start = 0;
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
					if(counter % 15 == 0){
						//printf("BREAK\n");
						break;
					}
					//sleep(4) untuk pembuatan file log setiap 4 detik
					sleep(4);
				}
			}
		}
	}
  
  exit(EXIT_SUCCESS);
}
