#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace std;
using namespace sql;

sql::Driver *driver;
sql::Connection *con;
sql::PreparedStatement *prep_stmt;
sql::Statement *stmt;
sql::ResultSet *res;


// fungsi untuk create data
void Create(){
  try {
    cout << "connecting to mysql server...." << endl;
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "password");
    cout << "connected!" << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;

    con->setSchema("phone_book");
    prep_stmt = con->prepareStatement("INSERT INTO personal(Nama,Tgl_Lahir,Alamat,Telepon,Email) VALUES(?,?,?,?,?)");

    char nama[100];
    char tgl_lahir[10];
    char alamat[255];
    char telepon[20];
    char email[100];

    cin.ignore();
    cout << "Masukkan Nama: "; cin.getline(nama, sizeof(nama)); cout << endl;
    cout << "Masukkan Tanggal Lahir: "; cin >> tgl_lahir; cout << endl;
    cin.ignore();
    cout << "Masukkan Alamat: "; cin.getline(alamat, sizeof(alamat)); cout << endl;
    cout << "Masukkan Nomor Telepon: "; cin >> telepon; cout << endl;
    cout << "Masukkan Email: "; cin >> email; cout << endl;

    cout << "Menambahkan Data....";

    prep_stmt->setString(1,nama);
    prep_stmt->setString(2,tgl_lahir);
    prep_stmt->setString(3,alamat);
    prep_stmt->setString(4,telepon);
    prep_stmt->setString(5,email);

    prep_stmt->execute();
    cout << "Selesai" << endl;

    delete prep_stmt;
    delete con;

  } catch (sql::SQLException &e) {
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }

  cout << endl;
}

// fungsi untuk read data
int Read(){
  try {
    cout << "connecting to mysql server...." << endl;
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "password");
    cout << "connected!" << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;
    cout << endl;

    con->setSchema("phone_book");
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM personal");

    cout << "List Personal:" << endl;
    while(res->next()) {

      cout << "ID: " << res->getInt(1) << endl;
      cout << "Nama: " << res->getString(2) << endl;
      cout << "Tanggal Lahir: " << res->getString(3) << endl;
      cout << "Alamat: " << res->getString(4) << endl;
      cout << "Telepon: " << res->getString(5) << endl;
      cout << "Email: " << res->getString(6) << endl;

    }

    delete res;
    delete stmt;
    delete con;

  } catch (sql::SQLException &e) {
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }

  cout << endl;
}

// fungsi untuk update data
void Update(){
  try{
    cout << "connecting to mysql server....";
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "password");
    cout << "connected!" << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;

    con->setSchema("phone_book");
    prep_stmt = con->prepareStatement("UPDATE personal SET Nama=?,Tgl_Lahir=?,Alamat=?,Telepon=?,Email=? WHERE ID=?");

    // updated data
    char nama[100];
    char tgl_lahir[10];
    char alamat[255];
    char telepon[20];
    char email[100];
    int id;

    cin.ignore();
    cout << "Masukkan Nama: "; cin.getline(nama, sizeof(nama)); cout << endl;
    cout << "Masukkan Tanggal Lahir: "; cin >> tgl_lahir; cout << endl;
    cin.ignore();
    cout << "Masukkan Alamat: "; cin.getline(alamat, sizeof(alamat)); cout << endl;
    cout << "Masukkan Nomor Telepon: "; cin >> telepon; cout << endl;
    cout << "Masukkan Email: "; cin >> email; cout << endl;
    cout << "Masukkan ID Personal yang ingin diperbarui: "; cin >> id; cout << endl;

    cout << "Perbarui Data....";
    prep_stmt->setString(1,nama);
    prep_stmt->setString(2,tgl_lahir);
    prep_stmt->setString(3,alamat);
    prep_stmt->setString(4,telepon);
    prep_stmt->setString(5,email);
    prep_stmt->setInt(6,id);

    prep_stmt->execute();

    cout << "Selesai" << endl;


    delete prep_stmt;
    delete con;

  } catch (sql::SQLException &e) {
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }

  cout << endl;
}


//fungsi untuk menghapus data
void Delete(){
  try {
    cout << "connecting to mysql server...." << endl;
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "password");
    cout << "connected!" << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;

    con->setSchema("phone_book");
    prep_stmt = con->prepareStatement("DELETE FROM personal WHERE ID=?");

    // deleted data
    int id;

    cout << "Masukkan ID Personal yang data-nya ingin dihapus: " << endl;
    cin >> id;

    cout << "Menghapus data dengan ID Personal " << id << "...." << endl;

    prep_stmt->setInt(1,id);
    prep_stmt->execute();


    cout << "Selesai" << endl;


    delete prep_stmt;
    delete con;

  } catch (sql::SQLException &e) {
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }

  cout << endl;
}


int main(){
  char menu;
  cout << "|" << setw(50) << setfill('=') << "|" << endl;
  cout << "|     Aplikasi CRUD Menggunakan C++ dan MySQL     |" << endl;
  cout << "|" << setw(50) << setfill('=') << "|" << endl;
  cout << "| Menu  | Fungsi" << setw(35) << setfill(' ') << "|" << endl;
  cout << "|" << setw(50) << setfill('-') << "|" << endl;
  cout << "| c     | Create data baru ke database" << setw(13) << setfill(' ') << "|" << endl;
  cout << "| r     | Read data dari database" << setw(18) << setfill(' ') << "|" << endl;
  cout << "| u     | Update data di database" << setw(18) << setfill(' ') << "|" << endl;
  cout << "| d     | Delete data dari database" << setw(16) << setfill(' ') << "|" << endl;
  cout << "|" << setw(50) << setfill('=') << "|" << endl;
  cout << "\nMasukan pilihan anda: ";
  cin >> menu;
  switch (menu) {
    case 'c':
      system("clear");
      Create();
      break;
    case 'r':
      system("clear");
      Read();
      break;
    case 'u':
      system("clear");
      Update();
      break;
    case 'd':
      system("clear");
      Delete();
      break;
    default:
      cout << "pilihan anda salah" << endl;
  }

  cout << "ketik b jika ingin kembali ke menu utama atau x jika ingin keluar dari program: ";
  cin >> menu;
  if(menu == 'b'){
    system("clear");
    main();
  }else if(menu == 'x'){
    system("clear");
    cout << "bye" << endl;
  }else{
    system("clear");
    cout << "bye" << endl;
  }

  return EXIT_SUCCESS;
}
