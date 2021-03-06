# SoalShift_modul2_D14

*File jawaban adalah file yang namanya ada kata 'soal'-nya*

## Soal 1
- Pada soal no 1, program yang dibuat adalah sebuah daemon proses yang dapat me-rename file ekstensi `.png` menjadi `_grey.png`, dan memindahkan secara otomatis ke direktori `/home/[user]/modul2/gambar`.
- Dalam pengerjaan Soal 1, library yang sangat berperan adalah library <dirent.h> dan struct dirent. ([sumber dirent.h](http://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html))
- Pada library <dirent.h>, ada beberapa fungsi yang akan dipakai, yaitu:
  - opendir(): abc.
  - readdir(): abc.
  - closedir(): abc.
- Lalu, di bawah ini adalah daftar member dari isi struct dirent:
  - ino_t          d_ino;       /* inode number */
  - off_t          d_off;       /* offset to the next dirent */
  - unsigned short d_reclen;    /* length of this record */
  - unsigned char  d_type;      /* type of file; not supported by all file system types */
  - char           d_name[256]; /* filename */
- Selain itu, ada beberapa fungsi penting yang nanti akan digunakan seperti strstr() dan rename().
- Pertama, kita buat 2 variabel dengan tipe `DIR` dan 2 struct dirent.
```
DIR *d, *d2;
struct dirent *dir, *dir2;
```
- Lalu, variabel `DIR` tadi diassignkan posisi direktori file program kami, karena pada kasus ini kami meletakkan file `.png` dalam satu direktori dengan file program kami.
```
d = opendir(".");
d2 = opendir(".");
```
- Lalu, buat 2 string yang akan menyimpan direktori asal file `.png` dan direktori tujuan file akan ditaruh.
```
char dst[250], src[250];
```
- Lalu, masuk ke loop saat program mengecek setiap file yang ada di folder, dengan menggunakan salah satu struct dirent yang sudah dibuat tadi dan fungsi `readdir()` dengan parameter salah satu variabel DIR yang sudah di-opendir().
```
while ((dir = readdir(d)) != NULL)
```
- Pada bagian awal loop, kami gunakan struct dirent dan variabel DIR yang satunya untuk pengecekan juga.
```
dir2 = readdir(d2);
```
- Digunakan 2 struct dirent supaya bisa digunakan untuk komparasi (lebih jelasnya nanti di bagian pengecekan file yang sama)
- Lalu, isi 2 string yang tadi sudah dibuat (`dst` dan `src`) dengan direktori sesuai dengan peran string tersebut:
  - dst : direktori asal file `.png` (/home/irshadrasyidi/Documents/SISOP/MODUL2/SOALSHIFT/soal1/)
  - src : direktori tujuan file akan ditaruh (/home/irshadrasyidi/modul2/gambar/)
- Untuk pengisiannya, digunakan `strcpy` untuk mengosongkan string dulu, dan `strcat` untuk mengisinya
```
strcpy(dst, "");
strcpy(src, "");
strcat(dst, "/home/irshadrasyidi/Documents/SISOP/MODUL2/SOALSHIFT/soal1/");
strcat(src, "/home/irshadrasyidi/modul2/gambar/");
```
- Lalu, buat bagian untuk mengecek nama file yang sama dan ada ekstensi `.png`-nya dengan `if` berikut:
```
if ( strstr( dir->d_name, ".png" ) && strstr( dir2->d_name, ".png" ) && (strcmp(dir->d_name, dir2->d_name) == 0) )
```
- Digunakan fungsi `strstr()` untuk mengecek apakah nama filenya memiliki ekstensi `.png`.
- Fungsi ini mengambil 2 parameter:
  - Parameter 1 : String yang dicek. (`namafile.png`)
  - Parameter 2 : Substring yang dicek jika ada di dalam String utama. (`.png`)
- Fungsi ini akan me-return true/1 jika Substring ditemukan pada string utama
- Fungsi `strstr()` dijalankan dua kali dengan inputan yang kedua menggunakan struct dirent yang kedua, karena akan digunakan di poin berikutnya.
- Di bagian akhir seleksi `if` digunakan fungsi `strcmp()` untuk membandingkan 2 nama file tersebut jika sama
- Jika benar sama, maka langkah selanjutnya adalah menghilangkan ekstensi `.png` pada struct dirent yang akan digunakan sebagai tujuan, dengan menggunakan cara berikut.
  - Buat sebuah variabel tipe pointer of char, untuk diarahkan ke char paling akhir dari string nama file
  ```
  char *end;
  ```
  - Pasangkan variabel tersebut dengan posisi alamat string nama file (`dir2->d_name`) dan dijumlah dengan panjang karakter string tersebut (`strlen(dir2->d_name)`), supaya dapat menunjuk ke karakter paling akhir.
  ```
  end = dir2->d_name + strlen(dir2->d_name);
  ```
  - Loop while berikutnya, untuk memundurkan posisi pointer hingga ketemu dengan karakter titik yang menandakan posisi penamaan ekstensi dimulai.
  ```
  while(end > dir2->d_name && *end != '.'){
					--end;
  }
  ```
  - Jika sudah ketemu, maka pasangkan isi pointer tersebut dengan `\0` supaya dapat memotong bagian ekstensi `.png` lama yang tidak dibutuhkan.
  ```
  if (end > dir2->d_name) {
					*end = '\0';
  }
  ```
- Selanjutnya, gabungkan string yang sudah dihilangkan ekstensinya dengan string sesuai permintaan soal (`_grey.png`)
```
strcat(dir2->d_name, "_grey.png");
```
- Lalu, buat 2 pointer of char yang mengambil alamat string mula-mula (`file.png`) dan satunya mengambil alamat string yang sudah diolah(`file_grey.png`)
```
char *namadst;
char *namasrc;
```
```
namadst = dir->d_name;
namasrc = dir2->d_name;
```
- Lalu gabungkan 2 string nama file tadi dengan string direktori asal dan tujuan yang sebelumnya sudah dibuat
```
strcat(dst, namadst);
strcat(src, namasrc);
```
- Lalu, gunakan fungsi rename untuk mengganti nama file yang lama menjadi yang baru.
```
rename(dst, src);
```
- Fungsi rename() mengambil 2 parameter:
  - Nama lama pada parameter pertama
  - Nama baru pada parameter kedua
- Tetapi karena pada fungsi rename ini stringnya sudah termasuk dengan direktorinya, maka otomatis direktorinya juga berubah dan otomatis langsung terpindah juga.
- Setelah keluar dari while loop, tutup direktori yang tadi sudah dibuka dengan fungsi closedir()
```
closedir(d);
closedir(d2);
```
- Program utama selesai, lalu masukkan potongan kodenya ke program untuk mengubah menjadi daemon proses (kode yang dari modul 2) pada loop `while(1)` pada bagian terakhir, dan pasang sleepnya terserah karena tidak ada ketentuan pada soal (kami gunakan `sleep(3);` dengan harapan prosesnya tidak menunggu terlalu lama)
- Jangan lupa sebelum mencoba programnya untuk membuat terlebih dahulu folder /modul2/gambar di direktori user

### Catatan Pengerjaan:
- 1.c adalah program utama untuk me-rename file-file `.png`-nya
- 1.c berhasil dicompile menjadi 1.out dan berhasil dijalankan dan berhasil me-rename semua file `.png` menjadi `_grey.png` serta memindahkan ke folder gambar
- Kendala Error: Saat sudah dimasukkan ke soal1.c (program untuk daemon proses), dan dijalankan, proses dapat berjalan (sudah dicek di terminal), tetapi tidak bisa menjalankan fungsinya dengan semestinya (tidak bisa me-rename dan memindahkan filenya)

### Catatan Setelah Revisi
- Kegagalan saat demo:
  - File `.png` tidak ter-rename -> karena `chdir` masih pada root, tidak pada direktori tempat file `.png` berada
  - Pengecekan ekstensi `.png` kurang benar -> karena hanya menggunakan `strstr()` yang mengecek pola string secara keseluruhan, tidak mengecek per karakter dari belakang
- Penyebab daemon terlihat tidak jalan karena lupa mengganti `chdir` di awal source code menjadi direktori tempat dimana file2 png berada, sehingga file2 `.png` tidak ter-rename
- Solusinya ganti chdir yang awalnya root menjadi direktori tempat file2 png berada
```
if ((chdir("/home/irshadrasyidi/Documents/SISOP/MODUL2/SOALSHIFT/soal1/")) < 0)
```
- Lalu, pada pengecekan ekstensi `.png` digunakan fungsi strstr() yang mengecek secara keseluruhan dari string, sehingga jika ada pattern `.png.txt` atau `.pngabc`, strstr() akan menganggap benar, sehingga ditambahkan pengecekan lagi di dalamnya
- Proses pengecekan dengan cara mengambil karakter-karakter di belakang titik penunjuk ekstensi dan dimasukkan ke sebuah string `cekpng`
```
end = dir2->d_name + strlen(dir2->d_name);
while(end > dir2->d_name && *end != '.'){
	--end;
}
strcat(cekpng, end);
```
- Lalu di dalam `if` selanjutnya digunakanlah string `cekpng` tersebut
```
if (end > dir2->d_name && (strcmp(cekpng, ".png") == 0))
```
- Di dalam `if` ini, baru dimasukkan proses rename yang sebelumnya 


## Soal2
- Pada soal no 2, program yang dibuat adalah sebuah daemon proses yang dapat menghapus file `elen.ku` pada syarat dan kondisi tertentu.
- Kali ini, library yang berperan penting dalam jalannya program adalah library <pwd.h>, <grp.h>, dan <sys/stat.h>
- Pada library ini terdapat fungsi `getpwuid()` yang dapat mengambil User ID dan me-return pointer of `struct passwd` jika ditemukan entry yang cocok, begitu juga dengan fungsi `getgrgid()` yang dapat mengambil Group ID dan me-return pointer of `struct group` jika ditemukan entry yang cocok. ([sumber grp.h](https://pubs.opengroup.org/onlinepubs/7908799/xsh/grp.h.html), [sumber pwd.h](http://pubs.opengroup.org/onlinepubs/7908799/xsh/pwd.h.html))
- Pertama, masukkan fungsi chmod untuk mengubah mode file dari dalam program supaya bisa dihapus dengan parameter berikut
```
chmod("/home/irshadrasyidi/Documents/SISOP/MODUL2/SOALSHIFT/soal2/hatiku/elen.ku", S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);
```
- Parameter pertama chmod mengambil lokasi file `elen.ku`, dan parameter kedua adalah perubahan/modifikasi mode pada file
- `S_I[p][xxx]`:
  - p : Bisa bernilai R (read), W (write), atau X (execute). Untuk mengeset supaya file bisa dibaca, diedit, atau dijalankan.
  - xxx : Bisa bernilai USR (user), GRP (group), atau OTH (other). Untuk mengeset siapa yang berhak menggunakan mode pada `[p]`
- Lebih lengkapnya bisa dicek di ([man chmod](http://man7.org/linux/man-pages/man2/chmod.2.html))
- Lalu, buat sebuah struct stat dan sebuah string yang menyimpan alamat file `elen.ku`.
```
struct stat info;
char alamat[250] = "/home/irshadrasyidi/Documents/SISOP/MODUL2/SOALSHIFT/soal2/hatiku/elen.ku";
```
- struct stat adalah sebuah struct yang memiliki member yaitu informasi-informasi mengenai sebuah file, berikut adalah isinya:
  - dev_t     st_dev;         /* ID of device containing file */
  - ino_t     st_ino;         /* Inode number */
  - mode_t    st_mode;        /* File type and mode */
  - nlink_t   st_nlink;       /* Number of hard links */
  - uid_t     st_uid;         /* User ID of owner */
  - gid_t     st_gid;         /* Group ID of owner */
  - dev_t     st_rdev;        /* Device ID (if special file) */
  - off_t     st_size;        /* Total size, in bytes */
  - blksize_t st_blksize;     /* Block size for filesystem I/O */
  - blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */
  - struct timespec st_atime;  /* Time of last access */
  - struct timespec st_mtime;  /* Time of last modification */
  - struct timespec st_ctime;  /* Time of last status change */
- Lalu, akan digunakan juga fungsi `stat()`, yang akan menerima 2 parameter:
  - Pertama : Alamat file yang akan dicari tahu informasinya
  - Kedua : Sebuah struct stat
```
stat(alamat, &info);
```
- Jadi, setelah fungsi stat dijalankan, `struct stat info` akan diisi dengan informasi-informasi mengenai file yang ada di `alamat`, yaitu `elen.ku`.
- Dari variabel-variabel di atas, yang akan dipakai adalah `st_uid` untuk mengambil User ID dan `st_gid` untuk mengambil Group ID
- Lebih lengkap mengenai stat ada di ([man stat](http://man7.org/linux/man-pages/man2/fstat.2.html)).
- Selanjutnya, buat sebuah `struct group` dan sebuah `struct passwd`
```
struct group *grp;
struct passwd *pwd;
```
- Struct group adalah struct yang dapat menyimpan dan mengolah informasi lebih spesifik mengenai group, dengan isi variable berikut:
  - char   *gr_name : the name of the group
  - gid_t   gr_gid  : numerical group ID
  - char  **gr_mem  : pointer to a null-terminated array of character
- Struct passwd adalah struct yang dapat menyimpan data mengenai User ID, Username, dan lain-lain sebagai berikut:
  - char    *pw_name   /*user's login name
  - uid_t    pw_uid    /*numerical user ID
  - gid_t    pw_gid    /*numerical group ID
  - char    *pw_dir    /*initial working directory
  - char    *pw_shell  /*program to use as shell
- Dari 2 struct ini, yang akan dipakai adalah `gr_gid` dari struct group untuk mengambil `st_gid` hasil dari fungsi stat, begitu juga dengan `pw_uid` dari struct passwd untuk mengambil `st_uid` hasil dari fungsi stat.
- Mengambilnya dengan fungsi `getpwuid()` untuk yang User ID dan fungsi `getgrgid()` untuk Group ID
```
grp = getgrgid(info.st_gid);
pwd = getpwuid(info.st_uid);
```
- Setelah didapat info-info tadi, kita bisa melihat group name dan username nya dengan mengakses struct group dan struct passwd tadi dengan member yang sesuai (`grp->gr_name` untuk mengakses group name dan `pwd->pw_name` untuk mengakses username)
- Selanjutnya adalah mengecek nama-nama yang didapat tadi dengan `if` berikut
```
if(!strcmp(grp->gr_name, "www-data") && !strcmp(pwd->pw_name, "www-data"))
```
- Pengecekan menggunakan fungsi `strcmp()` dengan parameter nama-namanya dan dibandingkan dengan string `www-data` sesuai dengan permintaan soal.
- Karena `strcmp()` mengembalikan nilai 0 jika sama, maka hasil `strcmp()`-nya dinegasi supaya jadi 1 dan bisa masuk ke dalam `if`-nya.
- Di dalam `if`-nya, cukup gunakan fungsi `remove()` dengan parameter alamat file yang akan dihapus untuk menghapus file `elen.ku`.
- Jika ingin mencoba apakah program berjalan dengan lancar, buat folder `/hatiku` dan buat file `elen.ku` di dalamnya.
- Karena `elen.ku` hanya bisa dihapus jika group name dan username nya `www-data`, maka modif file `elen.ku` dengan cara buka terminal di direktori hatiku, lalu ketikkan command berikut
```
sudo chown www-data:www-data elen.ku
```
- `www-data` di kiri titikdua adalah mengganti owner-user nya, dan yang di kiri mengganti owner-group nya. ([chown](https://linux.die.net/man/1/chown))
- Setelah terganti, jalankan programnya, `elen.ku` akan terhapus.
- Setelah program utama selesai, masukkan snippet code program utama ke template daemon proses dari modul2, di yang bagian `while(1)` paling bawah, untuk menjadikan program tadi daemon proses (sama seperti nomor 1), dan pasang sleep-nya `sleep(3)`, sehingga proses pengecekan dan hapus file `elen.ku` di folder hatiku yang sesuai kriteria terhapus setiap 3 detik.



## Soal3
- Pada soal no 3, program yang dibuat adalah sebuah program yang dapat mengekstrak isi dari `campur2.zip`, lalu menyimpan file-file hasil ekstrak tadi yang ekstensinya `.txt` ke sebuah file `daftar.txt`.
### Catatan Pengerjaan:
  - Tidak dapat mengerjakan karena bingung di `pipe`nya dan kehabisan waktu mencoba menyelesaikan kendala daemon proses di nomor 1

### Catatan Setelah Revisi
- Kegagalan saat demo:
  - Program belum selesai
- Pada program ini, digunakan 3 kali fork untuk menjalan 3 `exec` berikut:
  - exec untuk unzip `campur2.zip`
  - exec untuk `ls` dari isi folder campur2
  - exec untuk `grep` hasil dari ls sebelumnya
- Fork pertama buat exec yang mengunzip `campur2.zip`
```
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
```
- Lalu buka channel pipe
```
//channel pipe dibuka
	if (pipe(pipeArr) < 0) {
		exit(1);
	}
```
- Lalu siapkan file output `daftar.txt` sebagai output dari program
```
outFile = open("daftar.txt", O_CREAT | O_APPEND | O_WRONLY);
dup2(outFile, 1);
```
- Fork kedua, terdapat `exec` untuk mengambil hasil ls pada folder `campur2`
```
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
```
- Pada fork ini, digunakan juga fungsi `dup2()` untuk meng-copy file descriptor, dan menuliskan std output dari program ke pipe
([dup2], (https://www.geeksforgeeks.org/dup-dup2-linux-system-call/))
- Fork ketiga, untuk mengambil hasil dari `ls` sebelumnya dan dimasukkan ke `exec` dari `grep` yang `.txt$` untuk mengambil nama-nama file yang ekstensinya `.txt`
```
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
```
- Pada fork ini, digunakan lagi fungsi `dup2()` untuk meng-copy file descriptor, dan menuliskan std input dari pipe ke program (hasil dari ls jadi input)

## Soal4
- Pada soal no 4, program yang dibuat adalah sebuah daemon proses yang dapat membuat file `makan_sehat#.txt` jika `makan_enak.txt` diakses.
- Pada soal sebelumnya, sempat dijabarkan variabel-variabel yang merupakan member dari `struct stat` salah tiganya adalah variabel yang berhubungan dengan waktu, yaitu:
  - struct timespec st_atime;  /* Time of last access */
  - struct timespec st_mtime;  /* Time of last modification */
  - struct timespec st_ctime;  /* Time of last status change */
- Kita akan menggunakan `st_atime` untuk melihat last access time dari file yang dimaksud.
- Karena berhubungan juga dengan waktu, kita juga menambah library <time.h>, karena ada fungsi yang akan digunakan dari library tersebut, yaitu `difftime()` ([time.h](https://www.tutorialspoint.com/c_standard_library/time_h.htm)).
- Pertama, ambil potongan file daemon proses dari modul 2
- di antara `while(1)` di bagian bawah 3 fungsi close, sisipkan deklarasi sebuah string yang menyimpan direktori dari  file `makan_enak.txt`
```
char pathmakanan[200];
memset(&pathmakanan, 0, sizeof(pathmakanan));
strcat(pathmakanan, "/home/irshadrasyidi/Documents/makanan/makan_enak.txt");
```
- Fungsi `memset()` digunakan untuk mengosongkan string sebelum digunakan untuk memastika string kosong (seperti `strcpy(string, "")` pada soal1).
- Lalu, saat mulai masuk ke while, buat sebuah `struct stat` dan langsung jalankan fungsi `stat()` untuk mengambil informasi-informasi mengenai file `makan_enak.txt` dengan memasukkan argumen alamat direktorinya di parameter pertama fungsi `stat()` dan `struct stat`-nya di parameter pertama.
```
struct stat info;
stat(pathmakanan, &info);
```
- Lalu, buat sebuah variabel bertipe `time_t` dan disimpan dengan waktu sekarang (menggunakan fungsi `time()`)
```
time_t waktu = time(NULL);
```
- Lalu, buat sebuah variabel bertipe `time_t` juga tetapi isinya disimpan last access time dari file `makan_enak.txt`.
```
time_t lastaccess = info.st_atime;
```
- Lalu, buat sebuah pengecekan `if` yang mengecek apakah `makan_enak.txt` diakses kurang dari 30 detik yang lalu
```
if(difftime(waktu, lastaccess) <= 30)
```
- Pengecekan ini dimudahkan dengan fungsi `difftime()` yang dapat menghitung selisih dari 2 argumen waktu yang diberikan.
- Jika `makan_enak.txt` diakses kurang dari 30 detik yang lalu, maka hasil `difftime()` akan bernilai lebih kecil dari 30 dan masuk ke dalam `if`.
- Di dalam `if`, buat sebuah variabel yang menyimpan direktori dan nama file `makan_sehat#.txt`.
```
char sehat[200];
memset(&sehat, 0, sizeof(sehat));
strcat(sehat, "/home/irshadrasyidi/Documents/makanan/makan_sehat");
```
- Untuk mengambil no urutan pembentukan file-nya, dibuat sebuah variabel counter bertipe integer di luar `while(1)` pada program, dipasang nilai 1
```
int no = 1;
```
- Variabel ini akan menjadi sisipan untuk nama file yang akan dibuat, tetapi karena bertipe integer dan nama file bertipe string, maka integer ini harus diubah ke bentuk string menggunakan fungsi `sprintf()` ([sprintf()](https://www.geeksforgeeks.org/sprintf-in-c/)).
- Pengubahan ini dilakukan dengan membuat sebuah string sementara untuk menyimpan hasil konversi fungsi `sprintf()`
```
char temp[200];
memset(&temp, 0, sizeof(temp));
sprintf(temp, "%d", no);
```
- Lalu, variabel string `temp` yang berisi nomor urutan tadi dimasukkan ke variabel string alamat direktori dan nama file yang belum lengkap tadi
```
strcat(sehat, temp);
```
- Lalu, tambahkan ekstensi `.txt` pada akhir nama file
```
strcat(sehat, ".txt");
```
- Nama file sudah siap, lalu buat sebuah file baru menggunakan fungsi `fopen()` dengan argumen terakhir pada fungsi yaitu `"w"` untuk 'Write'
```
FILE *createfile=fopen((char*)sehat,"w");
```
- Jangan lupa untuk meng-increment variabel counter integer-nya di bagian akhir program supaya urutannya bertambah dan tidak meng-overwrite file urutan sebelumnya yang sudah dibuat.
```
no++;
```
- Lalu pasang `sleep()` bernilai sleep(5) supaya pembuatan file dilakukan setiap 5 detik.
- Untuk mengetes program bisa jalan, buat terlebih dahulu folder `/makanan` di Documents dan taruh `makan_enak.txt` di folder tersebut.
- Lalu jalankan program yang sudah dibuat tadi.
- Lalu, buka terminal di folder `/makanan` yang ada file `makan_enak.txt`-nya.
- Lalu, jalankan command berikut
```
touch -a makan_enak.txt`
```
- Command ini akan mengganti hanya last access time dari `file makan_enak.txt` karena menggunakan opsi `-a` ([touch](http://www.linfo.org/touch.html))
- Setelah command dijalankan, akan terbentuk file `makan_sehat#.txt` di folder `/makanan`

### Catatan Setelah Revisi
- Kegagalan saat demo:
  - Saat pengaksesan `makan_enak.txt` pertama kali, daemon berjalan lancar.
  - Saat pengaksesan `makan_enak.txt` pertama kali, file `makan_sehat#.txt` berikutnya tidak terbuat.
- Sebetulnya, saat demo sudah berjalan lancar, tetapi waktu dicoba pengaksesan `makan_enak.txt` yang kedua kali, file `makan_sehat#.txt` tidak terbuat
- Pada saat demo, cara akses hanya dengan membuka file `makan_enak.txt` lalu menutup kembali.
- Lalu pada saat revisi, kami mengikuti petunjuk dari asdos penguji saat demo untuk men-set waktu last access menjadi waktu sekarang
```
lastaccess = time(NULL);
```
- Pada saat dicoba, ternyata file `makan_enak.txt` bisa terganti last accessnya dengan men-save `makan_enak.txt` dan akhirnya membuat file `makan_sehat#.txt` atau menggunakan command pada terminal `touch -a makan_enak.txt`
- Saat dicoba meng-comment baris `lastaccess = time(NULL);`, ternyata file `makan_sehat#.txt` berikutnya tetap terbuat, sehingga kemungkinan gagalnya demo hanya karena cara akses `makan_enak.txt` yang kurang tepat, sehingga dianggap akses time tidak terganti oleh sistem


## Soal5
- Pada soal no 5, program yang dibuat adalah sebuah daemon proses yang dapat membuat folder baru setiap 30 menit di direktori `/home/[user]/log/` dengan format nama `[dd:MM:yyyy-hh:mm]` sesuai waktu dijalankan, dan juga membuat file `log#.log` di dalam folder tadi setiap 1 menit.
- Pada soal nomor 5, program C yang dibuat harus bisa menjalankan 2 proses yaitu proses membuat folder baru setiap 30 menit, dan membuat file baru setiap menit, hal ini bisa dilakukan dengan cara mem-fork lagi proses yang ada, sehingga terbentuk 2 proses, child dan parent
- Proses child akan diisi dengan program yang membuat folder baru setiap 30 menit, dan proses parent akan diisi dengan program yang membuat file `file#.log` setiap menit.
- Karena potongan kode pembuatan formatting nama folder panjang dan digunakan beberapa kali, maka akan dimasukkan ke fungsi sendiri (dibuat di luar int main())
- Karena nama folder yang harus dibuat terdiri dari format-format tanggal dan waktu, maka tambahkan dulu library <time.h>([time.h](https://www.tutorialspoint.com/c_standard_library/time_h.htm))
- Di library ini, ada suatu tipe variabel struct yaitu `struct tm` yang akan digunakan dalam penyusunan nama folder, berikut isi dari struct tersebut:
  - int tm_sec;         /* seconds,  range 0 to 59          */
  - int tm_min;         /* minutes, range 0 to 59           */
  - int tm_hour;        /* hours, range 0 to 23             */
  - int tm_mday;        /* day of the month, range 1 to 31  */
  - int tm_mon;         /* month, range 0 to 11             */
  - int tm_year;        /* The number of years since 1900   */
  - int tm_wday;        /* day of the week, range 0 to 6    */
  - int tm_yday;        /* day in the year, range 0 to 365  */
  - int tm_isdst;       /* daylight saving time             */
- Member dari struct yang akan digunakan adalah `int tm_min` (menit), `int tm_hour` (jam), `int tm_mday` (tanggal), `int tm_mon` (bulan), dan `int tm_year` (tahun).
- Fungsi formatting nama ini dapat menghasilkan 2 macam format nama, sehingga fungsi harus menerima argumen untuk membedakan.
  - Format nama dengan waktu sekarang.
  - Format nama dengan waktu sekarang + 30 menit.
- Pada awal fungsi, ambil waktu sekarang dengan fungsi `time()` dan disimpan ke sebuah variabel bertipe time_t
```
time_t wkt = time(NULL);
```
- Lalu, buat variabel `struct tm` yang isinya diisi dengan fungsi `*localtime()`.
- Fungsi dari fungsi `*localtime()` adalah menyusun kondisi waktu yang didapat menjadi waktu lokal dan memasangkan ke masing-masing member dari struct tersebut (mis. menit ke `tm_min`, jam ke `tm_hour`, bulan ke `tm_mon`, dst).
- Lalu siapkan variabel string untuk menyimpan nama yang akan dipakai untuk penamaan folder.
```
static char nama[200];
```
- Karena potongan-potongan waktu dari `struct tm` bertipe integer, supaya bisa dimasukkan ke string maka integer-integer tersebut harus dikonversi ke bentuk string dengan fungsi `sprintf` seperti yang telah digunakan pada nomor 4 sebelumnya, sehingga diperlukan variabel string sementara untuk menyimpan hasil konversi tersebut.
```
static char temp[200];
```
- Berikut adalah contoh pemasangan format-format waktu ke string nama
```
sprintf(temp, "%d", waktu.tm_mday);
strcat(nama, temp);
```
- Namun, pada tanggal, bulan, jam, dan menit, terdapat kemungkinan string hanya terdiri dari 1 digit angka (), padahal format dari soal meminta 2 digit semua kecuali tahun yang 4 digit.
- Untuk mengatasinya, dibuat `if` di masing-masing format waktu untuk mengecek apakah format waktu tersebut lebih kecil dari 10.
```
if(waktu.tm_mday < 10)
```
- Jika kurang dari 10, maka sebelum pemasangan biasanya, harus diisi angka 0 terlebih dahulu
```
sprintf(temp, "%d", 0);
strcat(nama, temp);
```
- Cara diatas sebetulnya bisa dipercepat dengan langsung di`strcat()` dengan "0"
```
strcat(nama, "0");
```
- Jika tidak kurang dari 10, maka bisa langsung dipasangkan.
- Perhatikan penjelasan sebelumnya pada member bulan dan tahun, disebutkan bahwa range bulan adalah 0-11 dan range tahun adalah nomor tahun sejak/dimulai dari 1900.
- Untuk mengatasi ini, maka saat pemasangan pada bulan, `tm_mon`-nya dijumlah dengan 1 dan `tm_year`-nya dijumlah dengan 1900.
```
sprintf(temp, "%d", waktu.tm_mon + 1);
sprintf(temp, "%d", waktu.tm_year + 1900);
```
- Jangan lupa `strcat()` untuk yang simbol-simbol pemisah.
```
strcat(nama, ":");
strcat(nama, "-");
```
- Lalu untuk format penamaan yang ditambah 30 menit, sama semua seperti sebelumnya, tetapi cukup pada bagian awal `else`, `tm_min`-nya ditambah 30, lalu panggil fungsi `mktime()` dengan argumennya alamat dari `struct tm`. Fungsi ini untuk mengatasi case jika menit di atas 30, saat ditambah 30 akan menjadi lebih besar dari 60. ([mktime()](https://www.tutorialspoint.com/c_standard_library/c_function_mktime.htm))
```
waktu.tm_min += 30;
mktime(&waktu);
```
- Lalu pada bagian akhir fungsi, fungsi me-return string nama folder dengan format sudah lengkap.
- Setelah fungsi pembuatan nama folder selesai, waktunya membuat 2 proses dengan memanggil fungsi `fork()`.
- Mula-mula panggil fungsi fork setelah 3 baris kode fungsi `close()` di kode daemon proses dari modul 2.
```
pid = fork();
```
- Buat juga variabel string yang menyimpan direktori ke folder `/log` pada `/user`, sebagai tempat pembuatan folder akan dilangsungkan.
```
char pathdir[200];
strcat(pathdir, "/home/irshadrasyidi/log/");
```
- Pada child proses, buat sebuah variabel string dan diisi dengan hasil fungsi pembuatan nama yang merupakan waktu sekarang (bukan yang ditambah 30 menit)
```
strcat(nama, buatnama(1));
```
- Gabungkan string barusan dengan string sebelumnya yang berisi lokasi direktori `/log`.
```
strcat(pathdir, nama);
```
- Lalu, panggil fungsi `mkdir()` untuk membuat folder baru dengan argumen pertama adalah string nama folder yang sudah lengkap, dan argumen kedua berisi settingan mode-mode supaya bisa digunakan oleh semua entitas (sama seperti soal nomor 2)
```
mkdir(pathdir, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);
```
- Jangan lupa untuk mereset ulang kembali string yang tadi digunakan, supaya bisa digunakan di pembuatan-pembuatan folder selanjutnya (stringnya tidak menumpuk).
```
memset(&pathdir, 0, sizeof(pathdir));
strcat(pathdir, "/home/irshadrasyidi/log/");
```
- Pada akhir proses child tersebut buat fungsi `sleep()` dengan nilai 1800 untuk dijalankan lagi 30 menit kemudian (30 x 60).
- Pada proses yang kedua (yang parent), buat 3 variabel berikut sebelum masuk ke `while(1)`:
  - Sebuah integer counter dengan nilai awal 1 : Untuk nomor urutan nama file `log#.log`.
  - Sebuah integer pengecekan bernilai awal 1 : Untuk pengecekan jika sudah waktunya pindah folder (pindah ke yang 30 menit selanjutnya).
  - Sebuah variabel string : Untuk menyimpan nama folder yang 30 menit kemudian.
  ```
  int counter = 0;
  int start = 1;
  char scndryname[200];
  ```
- Selanjutnya buat sebuat `while(1)` dan pertama, buat 2 variabel string lagi
  - Pertama : Untuk menyimpan nama folder yang akan dipakai sebagai tempat disimpannya file `log#.log`
  - Kedua : Untuk menyimpan nama folder dengan waktu sekarang.
```
char primryname[200];
char currentname[200];
strcat(currentname, buatnama(1));
```
- Lalu, buat 1 variabel string sementara yang berisi nama folder 30 menit kemudian beserta direktorinya dari `/home`, dan akan digunakan dalam fungsi `stat()`
```
char tmp[200];
strcat(tmp, pathdir);
strcat(tmp, scndryname);
```
- Buat juga sebuah variabel dengan tipe `struct stat` lagi, fungsinya adalah untuk pengecekan di dalam `if` jika suatu folder sudah ada di folder `/log` atau belum.
- Selanjutnya, buat sebuah `if` untuk mengecek apakah proses tersebut dijalankan pertama kali atau tidak.
```
if (start == 1)
```
- Jika benar, maka string yang berfungsi menyimpan nama folder tujuan dibuatnya file diisi dengan nama folder dengan waktu sekarang, dan string yang berfungsi menyimpan nama folder 30 menit selanjutnya diisi dengan nama folder dengan waktu 30 menit kemudian.
```
strcat(primryname, buatnama(1));
strcat(scndryname, buatnama(0));
```
- **Reminder : Untuk pengisian (assignment) string pada program C tidak bisa langsung menghilangkan isi sebelumnya, jadi harus dikosongkan terlebih dahulu dengan strcpy() atau memset().
- Jika kondisi if salah, maka masuk ke `else if` berikutnya, yang mengecek jika proses sudah pernah dijalankan `(start < 1)`, dan nama folder dengan waktu 30 menit kemudian sudah sama dengan nama folder dengan waktu sekarang `(strcmp(currentname, scndryname) == 0)`, dan folder dengan nama yang waktunya 30 menit kemudian sudah terbuat `(stat(tmp, &info) == 0)`, maka string yang berfungsi menyimpan nama folder tujuan dibuatnya file diisi dengan nama folder dengan waktu 30 menit kemudian, dan string yang berfungsi menyimpan nama folder 30 menit selanjutnya diisi dengan nama folder dengan waktu 30 menit selanjutnya lagi.
- Secara singkat, kondisi `if` dan `if else` yang dijabarkan di atas berfungsi menyiapkan nama folder 30 menit kedepan dan menukar nama folder tujuan sekarang dengan nama folder 30 menit kedepan.
- Selanjutnya ganti isi variabel sementara yang sebelumnya berisi nama folder 30 menit kemudian dengan nama folder waktu sekarang. Karena `if` selanjutnya akan mengecek apakah folder waktu sekarang sudah dibuat atau belum.
```
strcat(tmp, pathdir);
strcat(tmp, primryname);
```
- Buat `if` yang dimaksud di poin atas yang mengecek apakah folder tujuan letak file ditaruh sudah dibuat `(stat(tmp, &info) == 0)` dan string untuk menyimpan nama folder tujuan memang sudah ada isinya`(strcmp(primryname, "") != 0)`
- Jika `if` memenuhi, maka buat `while(1)` utama di dalamnya yang isinya adalah proses mengambil isi syslog dan disimpan ke file `log#.log` setiap menitnya.
- Pertama ubah nilai variabel integer yang sebelumnya dibuat dengan fungsi pengecekan pembuatan folder menjadi lebih kecil supaya tidak masuk ke `if` di sebelumn-sebelumnya (`if` yang `(start == 1)`).
- Lalu, buat sebuah string yang mengambil alamat direktori file `syslog`.
```
char pathsys[200];
strcat(pathsys, "/var/log/syslog");
```
- Lalu, buat string lagi yang digunakan untuk menyimpan nama file yang akan dibuat beserta alamat dan direktori lengkap dari root hingga nama folder dengan format waktu yang sebelumnya sudah dibuat.
```
char filelog[200];
strcat(filelog, pathdir);
strcat(filelog, primryname);
strcat(filelog, "/log");
```
- Jangan lupa untuk mensisipkan integer counter yang jauh-jauh hari sudah dibuat untuk nomor urut nama file (konversi integer ke string-nya gunakan `sprintf()` lagi).
```
sprintf(temp, "%d", counter + 1);
strcat(filelog, temp);
strcat(filelog, ".log");
```
- Lalu, gunakan u=fungsi `fopen()` untuk membaca isi syslog dan membuat file baru dengan nama lengkap beserta direktorinya yang sudah dibuat tadi.
```
FILE *sys=fopen((char*)pathsys, "r");
FILE *log=fopen((char*)filelog, "w");
```
- Lalu, gunakan while loop selama tidak End-Of-File (EOF) untuk meng-copy isi syslog ke file tujuan (proses copy men-scan per karakter)
```
char ch;
	while((ch = fgetc(sys)) != EOF ){
		fputc(ch, log);
}
```
- Selanjutnya tutup 2 file tadi dengan `fclose()`.
```
fclose(sys);
fclose(log);
```
- Variabel integer counter di-increment supaya nomor urutan file tetap urut dan yang baru tidak meng-overwrite yang lama.
```
counter++;
```
- Lalu berikan satu `if` terakhir yang mengecek jika counter sudah menyentuh 30, maka di-break dari `while(1)` utama dan bersiap untuk proses pemindahan folder tujuan (proses yang ada `if` dan `else if` nya di luar loop `while(1)` utama)
```
if(counter % 30 == 0){
	//printf("BREAK\n");
	break;
}
```
- Jangan lupa untuk memasang `sleep(60)` pada `while(1)` utama (while pembentukan file log), supaya pembentukan file log dijalankan setiap menit.

### Catatan Saat Revisi
- Kegagalan saat demo:
  - Folder dengan format waktu terbuat, tetapi file `log#.log` tidak.
- Sebetulnya, program sudah benar sesuai soal, namun, pada saat demo, range waktu pembuatan folder dan file log diubah, dan kami lupa mengganti waktu pada fungsi yang membuat string dengan format waktu untuk nama folder.
- Penjelasan lengkapnya ada pada dokumentasi/comment pada source code
- *CATATAN PENTING* : Kondisi source code sekarang tidak sesuai dengan permintaan soal (tiap 30 menit buat folder baru, tiap 1 menit buat file log baru), tetapi diganti dengan waktu yang lebih singkat supaya mudah saat pengecekan/koreksi (tiap 1 menit buat folder baru, tiap 4 detik buat file log baru)
