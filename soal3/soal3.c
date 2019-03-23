#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


void main() {

	pid_t pid;
	int pipeArr[2];
	int outFile;
	int status;
	
	//fork pertama
	//untuk unzip
	pid = fork();
	if (pid < 0) {
		exit(1);
	}
	else if (pid == 0) {
		//exec untuk unzip campur2.zip
		char* arr1[3]={"unzip", "/home/irshadrasyidi/Documents/SISOP/MODUL2/SOALSHIFT/soal3/campur2.zip", NULL};
		execv("/usr/bin/unzip", arr1);
	}
	while((wait(&status)) > 0);

	//channel pipe dibuka
	if (pipe(pipeArr) < 0) {
		exit(1);
	}

	outFile = open("daftar.txt", O_CREAT | O_APPEND | O_WRONLY);
	dup2(outFile, 1);
	//meng-copy file descriptor untuk FileDesc, dan menulis std output dari hasil program di bawah ke file yang sudah dibuka

	//fork kedua
	//untuk ls
	pid = fork();
	if (pid < 0) {
		exit(1);
	}
	else if (pid == 0) {
		//meng-copy file descriptor, dan menuliskan std output dari program ke pipe
		dup2(pipeArr[1], 1);
		close(pipeArr[0]);
		close(pipeArr[1]);

		//exec untuk menampilkan file2 yang ada di folder campur2
		char* arr2[3]={"ls", "/home/irshadrasyidi/Documents/SISOP/MODUL2/SOALSHIFT/soal3/campur2/", NULL};
		execv("/bin/ls", arr2);
	}

	//fork ketiga
	//untuk grep hasil dari ls
	pid = fork();
	if (pid < 0) {
		exit(1);
	}
	else if (pid == 0) {
		//meng-copy file descriptor, dan menuliskan std input dari pipe ke program (hasil dari ls jadi input)
		dup2(pipeArr[0], 0);
		close(pipeArr[0]);
		close(pipeArr[1]);
		
		//exec untuk menampilkan hasil ls yang berakhiran '.txt'
		char* arr3[3]={"grep", ".txt$", NULL};
		execv("/bin/grep", arr3);
	}
	close(pipeArr[0]);
	close(pipeArr[1]);
}

