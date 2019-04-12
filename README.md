# SoalShift_modul3_C05
Laporan Soal Shift Modul 3<br>
Anggota Kelompok C5 :
1. (05111740000117) Bella Septina Ika Hartanti
2. (05111740000144) Miranda Manarung

## Soal 1
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
<br>Contoh:<br>
    ./faktorial 5 3 4<br>
    3! = 6<br>
    4! = 24<br>
    5! = 120<br>

## Penjelasan
Langkah-langkah :
1. Konversi argumen ke tipe data integer dan simpan hasilnya dalam array. Untuk konversi, gunakan fungsi atoi yang mengubah karakter menjadi integer.
2. Sorting array (misalnya menggunakan merge sort), sehingga array argumen (tipe data integer) berurutan secara increasing.
3. Buat thread untuk menjalankan fungsi faktorial.
4. Simpan hasil thread ke dalam array.
5. Lakukan iterasi untuk menampilkan hasil faktorial secara increasing sesuai dengan format output yang telah ditentukan.

Berikut adalah solusi soal 1 dalam bentuk source code :<br>
[Source Code Soal 1](https://github.com/bellasih/SoalShift_modul3_C05/blob/master/soal1/soal1.c)

## Soal 2
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:
- Terdapat 2 server: server penjual dan server pembeli
- 1 server hanya bisa terkoneksi dengan 1 client
- Server penjual dan server pembeli memiliki stok barang yang selalu sama
- Client yang terkoneksi ke server penjual hanya bisa menambah stok
   * Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
- Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
   * Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
- Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
   * Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
   * Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
- Server penjual akan mencetak stok saat ini setiap 5 detik sekali
- Menggunakan thread, socket, shared memory

## Penjelasan
Langkah-langkah :

a. Untuk Server Jual :
   1. Buat fungsi *display_stock* untuk menampilkan banyaknya stok yang masih tersedia
   2. Buat fungsi *selling* untuk melakukan restock (stock bertambah satu)
   3. Buat thread untuk menjalankan fungsi *display_stock*
   4. Untuk memberikan akses pertukaran data dengan client, maka gunakan shared memory.
   5. Selain itu menerapkan socket programming untuk komunikasi antara server penjual dan client.
   6. Buat thread untuk menjalankan fungsi *selling* ketika client memberikan input berupa "tambah"
   
b. Untuk Server Beli :
   1. Buat fungsi *buying* untuk melakukan pembelian, dimana :
      - Transaksi berhasil apabila saat client memberikan input "beli", stock masih bernilai >= 1
      - Transaksi gagal apabila saat client memberikan input "beli", stock bernilai 0
   2. Gunakan shared memory untuk memberikan akses pertukaran data antara server pembeli dan client
   3. Menerapkan socket programming untuk komunikasi antara server pembeli dan client, sehingga output *transaksi berhasil* atau *transaksi gagal* akan ditampilkan pada client

c. Untuk Client:
   1. Agar dapat berkomunikasi dengan server penjual maupun pembeli, gunakan socket programming.
   2. Agar server penjual maupun server pembeli dapat menjalankan thread, maka client akan memberikan input dan mengirimkannya ke server sesuai dengan portnya.<br>
Keterangan : *port antara server penjual dan server pembeli harus berbeda*

Berikut adalah solusi soal 2 dalam bentuk source code :<br>
[Source Code Soal 2 Server Jual](https://github.com/bellasih/SoalShift_modul3_C05/blob/master/soal2/soal2jual.c) <br>
[Source Code Soal 2 Server Beli](https://github.com/bellasih/SoalShift_modul3_C05/blob/master/soal2/soal2beli.c) <br>
[Source Code Soal 2 Client Jual](https://github.com/bellasih/SoalShift_modul3_C05/blob/master/soal2/soal2clientj.c) <br>
[Source Code Soal 2 Client Beli](https://github.com/bellasih/SoalShift_modul3_C05/blob/master/soal2/soal2clientb.c)

## Soal 3
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut: <br> 
- Terdapat 2 karakter Agmal dan Iraj
- Kedua karakter memiliki status yang unik
  * Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
  * Iraj memiliki Spirit_Status, di awal program memiliki status 100
  * Terdapat 3 Fitur utama
    1. All Status, yaitu menampilkan status kedua sahabat
       Ex: Agmal WakeUp_Status = 75 
       Iraj Spirit_Status = 30
    2. “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
    3. “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
- Terdapat Kasus yang unik dimana:
  * Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
  * Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
- Program akan berhenti jika Salah Satu :
  * WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
  * Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)
- *Syarat Menggunakan Lebih dari 1 Thread*

## Penjelasan
Langkah-langkah :
1. Buat fungsi *sleep_iraj* untuk melakukan pengurangan terhadap nilai dari Spirit_Iraj sebanyak 20 apabila pemanggilan fungsi dilakukan sebanyak n%3 != 0. Namun, apabila fungsi telah dipanggil sebanyak n%3 kali, maka fungsi akan memberikan pesan output bahwa fitur Agmal Ayo Bangun tidak dapat dijalankan selama 10 detik. Untuk penerapannya, kami menggunakan parameter dua parameter yaitu apabila n < 3 maka status running masing-masing dari agmal atau iraj akan bernilai 1. Namun, jika sebaliknya maka status running masing-masing dari agmal atau iraj akan bernilai 1 dan nilai n akan direset menjadi 0
2. Buat fungsi *wakeup_agmal* untuk melakukan penambahan terhadap nilai dari WakeUp_Agmal sebanyak 15 apabila pemanggilan fungsi dilakukan sebanyak n%3 != 0. Namun, apabila fungsi telah dipanggil sebanyak n%3 kali, maka fungsi akan memberikan pesan output bahwa fitur Iraj Ayo tidut tidak dapat dijalankan selama 10 detik. Untuk penerapannya, kami menggunakan parameter dua parameter yaitu apabila n < 3 maka status running masing-masing dari agmal atau iraj akan bernilai 1. Namun, jika sebaliknya maka status running masing-masing dari agmal atau iraj akan bernilai 1 dan nilai n akan direset menjadi 0.
3. Pada main, buat thread yang akan menjalankan fungsi *sleep_iraj* dan fungsi *wakeup_agmal*
4. Lakukan looping dengan terminal kondisi bahwa nilai dari Spirit_Iraj bernilai maksimum 0 atau WakeUp_Agmal bernilai minimal 100. 
5. Apabila telah mencapai terminal, maka program akan berhenti dengan memberikan output: 
   - Agmal Terbangun, mereka bangun pagi dan berolahraga jika WakeUp_Agmal bernilai > 99
   - Iraj ikut tidur, dan bangun kesiangan bersama Agmal jika Spirit_Status bernilai < 1

Berikut adalah solusi soal 2 dalam bentuk source code :<br>
[Source Code Soal 3](https://github.com/bellasih/SoalShift_modul3_C05/blob/master/soal3/soal3.c) <br>

## Soal 4
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip<br>
Dengan Syarat : 
* Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
* Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
* Ketika Mengekstrak file .zip juga harus secara bersama-sama
* Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
* Wajib Menggunakan Multithreading
* Boleh menggunakan system

## Penjelasan
Langkah-langkah :
1. Buat fungsi *get_list* untuk melakukan penyimpanan list proses maksimal sebanyak 10 dalam file .txt (SimpanProses1.txt dan SimpanProses2.txt di folder /Documents/FolderProses1/ dan /Documents/FolderProses2/ 
2. Buat fungsi *zip_rm* untuk melakukan kompres file SimpanProses1.txt dan SimpanProses2.txt menjadi zip dengan nama masing-masing KompresProses1.zip dan KompresProses2.zip
3. Buat fungsi *unzip* untuk melakukan ekstrak file .zip dari KompresProses1.zip dan KompresProses2.zip setelah 15 detik menunggu 
4. Jalankan iterasi sebanyak 2 kali untuk menjalankan thread *get_list*, thread *zip_rm*, dan thread *unzip*. Untuk masing-masing iterasi thread, harus menunggu dulu 2 tread sebelumnya terselesaikan.

Berikut adalah solusi soal 2 dalam bentuk source code :<br>
[Source Code Soal 4](https://github.com/bellasih/SoalShift_modul3_C05/blob/master/soal4/soal4.c) <br>

## Soal 5
Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. <br>
1. Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.
2. Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.
3. Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).
4. Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.
5. Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 
6. Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
   * Pembeli (terintegrasi dengan game)
     - Dapat mengecek stok makanan yang ada di toko.
     - Jika stok ada, pembeli dapat membeli makanan.
   * Penjual (terpisah)
     - Bisa mengecek stok makanan yang ada di toko
     - Penjual dapat menambah stok makanan.

<b>Spesifikasi program :</b><br>
1. Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)
2. Program terdiri dari 3 scene yaitu standby, battle, dan shop.
3. Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :
```
Standby Mode
Health : [health status]
Hunger : [hunger status]
Hygiene : [hygiene status]
Food left : [your food stock]
Bath will be ready in [cooldown]s
Choices
Eat
Bath
Battle
Shop
Exit
```
4. Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :
```
Battle Mode
Monster’s Health : [health status]
Enemy’s Health : [enemy health status]
Choices
Attack
Run
```
5. Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :
```
Shop Mode
Shop food stock : [shop food stock]
Your food stock : [your food stock]
Choices
Buy
Back
```
6. Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :
```
Shop
Food stock : [shop food stock]
Choices
Restock
Exit
```
7. Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))


## Penjelasan
Langkah-langkah :
1. Game<br>
   Program mampu mendeteksi input berupa key press : menggunakan getch()
   ```
   int getch(void){
    struct termios oldt,
    newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
    }
   ```
   Thread : ada 4 thread
   ```
   void *lapar(void *arg){
	    while(1){// -5 per 10 detik
		    hunger -= 20;
            sleep(1);}
    }
    void *kotor(void *arg){
	    while(1){// -10 per 30 detik
		    hygiene -= 10;
            sleep(30);}
    }
    void *sehat(void *arg){
	    while(1){ // +5 per 10 detik
		    health += 5;
		    sleep(10);}
    }
    void *waktu(void *arg){
	    while(1){// timer ready or not
		    if(turn > 0){
			    turn--;
                sleep(1);}
	    }
    }
   ```
   Standby mode
   ```
   void xplay(){
        while(1){
		    printf("MONSTER DALAM KEADAAN STANDBY\n");
		    printf("HEALTH STATUS: %d\n", health);
		    printf("HUNGER STATUS: %d\n", hunger);
		    printf("STOK MAKANAN MONSTER: %d\n", stok);
		    printf("MANDI?? \n");
		    if(turn == 0){printf("BATH IS READY\n");}
            else{printf("BATH WILL BE READY IN %d\n", turn);}
		    printf("OPSI: 1. KASIH MAKAN\t2. MANDI\t3. BATTLE\t4. SHOP\t5. EXIT\n");
            opsi = getch();
		    if(opsi == '1'){
                if(stok > 15){//liat stok masih sisa
    			    if(stok-15 >= 0 && hunger+15 <= 200){//batas max 200
	    			    hunger += 15;
		    		    stok -= 15;
		    	    }else{printf("SUDAH MAKSIMUM.\n");}
		        }else{printf("STOK MAKANAN HABIS.\n");}
            }if(opsi == '2'){
                if(hygiene < 100){
                    if(turn == 0){
                        hygiene += 30;
                        if(hygiene > 100){hygiene = 100;}
                        turn = 20; //mandi ready dlm 20 dtk
                    }   
                }else{ //timer blm selesai
                    system("clear");
                    printf("NOT READY\n");
                    sleep(1);
                    system("clear");
                }
		    }if(opsi == '3'){
                system("clear");
			    battle();
		    }if(opsi == '4'){
                system("clear");
			    shop_buyer();
		    }if(opsi == '5'){break;}
		    if(hunger <= 0 || hygiene <= 0){
			    printf("\nGame telah selesai!\n");
			    printf("Skor Akhir: \n");
			    printf("%s hunger status: %d | hygiene status: %d\n", xplayer, hunger, hygiene);
			    sleep(5);
                break;
            }system("clear");
	    }
    }
   ```
   Battle
   ```
   void battle(){
	while(1){
	    printf("MONSTER %s VS. MONSTER NPC \n", xplayer);
	    printf("HEALTH STATUS: %d\n", health);
	    printf("HUNGER STATUS: %d\n", hunger);
	    printf("STOK MAKANAN MONSTER: %d\n", stok);
	    printf("OPSI: 1. SERANG\t2. LARI\n");
        opsi = getch();
	    if(opsi == '1'){
		    health -= 20;
		    zblood -= 20;
    	    if(zblood <= 0){
		        printf("\nGame telah selesai!\n");
			    printf("Skor Akhir: \n");
			    printf("%s hunger status: %d | hygiene status: %d\n", xplayer, hunger, hygiene);
				sleep(5);
		        break;
	        }
        }if(opsi == '2'){break;}
        system("clear");
        }
    }
   ```
2. Shop (Shared Memory)<br>
   Shop_buyer (Ada dalam program game)
   ```
   void shop_buyer(){
        key_t key = 1234;
        int *stok_toko;

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        stok_toko = shmat(shmid, NULL, 0);

        while(1){
            printf("SHOP\n");
            printf("STOK MAKANAN TOKO: %d\n", *stok_toko);
	        printf("STOK MAKANAN MONSTER: %d\n", stok);
	        printf("OPSI: 1. BUY\t2. BACK\n");    
            opsi = getch();
	        if(opsi == '1'){
                if(*stok_toko > 0){//toko masih punya stok
    		        stok += 15;
		            *stok_toko -= 15;
                    printf("STOK MAKANAN MONSTER: %d\n", stok);
                }else{
                    system("clear");
                    printf("MAKANAN TOKO HABIS\n");
                }
            }if(opsi == '2'){break;}
	        system("clear");
        }
        shmdt(stok_toko);
        shmctl(shmid, IPC_RMID, NULL);
    }
   ```
   Shop_seller (Buat program c baru)
   ```
   void main(){
        key_t key = 1234;
        int *stok_toko;

        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        stok_toko = shmat(shmid, NULL, 0);

        *stok_toko = 45;
        while(1){
            printf("TOKO MAKANAN\n");
	        printf("STOK MAKANAN TOKO: %d\n", *stok_toko);
	        printf("OPSI: 1. RESTOCK\t2. EXIT\n");
            char opsi = getch();            
            if(opsi == '1'){
                *stok_toko += 15;
            }if(opsi == '2'){break;}
            system("clear");
        }
        shmdt(stok_toko);
        shmctl(shmid, IPC_RMID, NULL);
    }
   ```

