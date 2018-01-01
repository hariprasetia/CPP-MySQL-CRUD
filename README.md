# CPP-MySQL-CRUD

### System Requirments
Kode CRUD sederhana menggunakan C++ dan MySQL ini dibuat menggunakan platform linux yang sudah terinstall g++ dan MySQL untuk database testing.
untuk yang menggunakan Debian/Ubuntu bisa menginstall mysql-server dan mysql-client.

    $ sudo apt-get install mysql-server mysql-client

kalian juga butuh MySQL library, libmysqlcppconn-dev.

    $ sudo apt-get install libmysqlcppconn-dev
    
### Database
Untuk database testing kalian bisa execute crud.sql script untuk membuat database

### Compiling & Linking
sebelum compile, silahkan rubah MySQL konfigurasi sesuai dengan konfigurasi MySQL anda

untuk compile anda bisa menggunakan make.

    $ make
