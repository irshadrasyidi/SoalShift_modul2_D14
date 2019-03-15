# SoalShift_modul2_D14

*File jawaban adalah file yang namanya ada kata 'soal'-nya*

## Soal 1
- Pada soal no 1, program yang dibuat adalah sebuah daemon proses yang dapat me-rename file ekstensi `.png` menjadi `_grey.png`, dan memindahkan secara otomatis ke direktori `/home/[user]/modul2/gambar`.
- Dalam pengerjaan Soal 1, library yang sangat berperan adalah library <dirent.h> dan struct dirent.
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
Catatan Pengerjaan:
- 1.c adalah program utama untuk me-rename file-file `.png`-nya
- 1.c berhasil dicompile menjadi 1.out dan berhasil dijalankan dan berhasil me-rename semua file `.png` menjadi `_grey.png` serta memindahkan ke folder gambar
- Kendala Error: Saat sudah dimasukkan ke soal1.c (program untuk daemon proses), dan dijalankan, proses dapat berjalan (sudah dicek di terminal), tetapi tidak bisa menjalankan fungsinya dengan semestinya (tidak bisa me-rename dan memindahkan filenya)
## Soal2
- Pada soal no 2, program yang dibuat adalah sebuah daemon proses yang dapat menghapus file `elen.ku` pada syarat dan kondisi tertentu.

## Soal3
- Pada soal no 3, program yang dibuat adalah sebuah program yang dapat mengekstrak isi dari `campur2.zip`, lalu menyimpan file-file hasil ekstrak tadi yang ekstensinya `.txt` ke sebuah file `daftar.txt`.


## Soal4
- Pada soal no 4, program yang dibuat adalah sebuah daemon proses yang dapat membuat file `makan_sehat#.txt` jika `makan_enak.txt` diakses.


## Soal5
- Pada soal no 5, program yang dibuat adalah sebuah daemon proses yang dapat membuat folder baru setiap 30 menit di direktori `/home/[user]/log/` dengan format nama `[dd:MM:yyyy-hh:mm]` sesuai waktu dijalankan, dan juga membuat file `log#.log` di dalam folder tadi setiap 1 menit.
