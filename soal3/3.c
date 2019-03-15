#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	pid_t child_id;
	int status;

	int pipe1[2];
	int pipe2[2];

	child_id = fork();

	pipe(pipe1);
	if (child_id == 0) {

	char *argv[3] = {"unzip", "campur2.zip", NULL};
	execv("/usr/bin/unzip", argv);
	} else {

	while ((wait(&status)) > 0);

	chdir("/home/irshadrasyidi/Documents/SISOP/MODUL2/SOALSHIFT/soal3/campur2");

	dup2(pipe1[1], 1);
	close(pipe1[0]);
	close(pipe1[1]);

	char *argv[2] = {"ls", NULL};
	execv("/bin/ls", argv);

	}

	pipe(pipe2);
	child_id = fork();
	if (child_id == 0) {

	} else {

	while ((wait(&status)) > 0);

	//dup2(pipe1[0], 0);
	//dup2(pipe2[1], 1);
	//close(pipe1[0]);
	//close(pipe1[1]);
	//close(pipe2[0]);
	//close(pipe2[1]);

	char *argv[3] = {"egrep", ".txt$", NULL};
	execv("/bin/egrep", argv);

	}
}

//command biasa
//ls | egrep '.txt$'
