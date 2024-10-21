#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>

class Database {
public:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    Database() {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "dante");
        con->setSchema("my_database");
    }

    ~Database() {
        delete con;
    }
};
