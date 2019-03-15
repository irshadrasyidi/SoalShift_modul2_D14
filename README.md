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


## Soal4
- Pada soal no 4, program yang dibuat adalah sebuah daemon proses yang dapat membuat file `makan_sehat#.txt` jika `makan_enak.txt` diakses.


## Soal5
- Pada soal no 5, program yang dibuat adalah sebuah daemon proses yang dapat membuat folder baru setiap 30 menit di direktori `/home/[user]/log/` dengan format nama `[dd:MM:yyyy-hh:mm]` sesuai waktu dijalankan, dan juga membuat file `log#.log` di dalam folder tadi setiap 1 menit.
