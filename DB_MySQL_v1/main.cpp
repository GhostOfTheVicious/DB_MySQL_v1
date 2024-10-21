#include <string>
#include <iostream>
#include <cppconn/prepared_statement.h>
#include "Database.cpp"

class User {
public:
    int id;
    std::string login;
    std::string password;

    User(std::string login, std::string password) : login(login), password(password) {}

    void saveToDB(sql::Connection* con) {
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO User (login, password) VALUES (?, ?)");
        pstmt->setString(1, login);
        pstmt->setString(2, password);
        pstmt->executeUpdate();
        delete pstmt;

        // Получаем ID пользователя
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT LAST_INSERT_ID()");
        if (res->next()) {
            id = res->getInt(1);
        }
        delete res;
        delete stmt;
    }
};

class License {
public:
    int id;
    std::string license_key;
    std::string name;
    int user_id;

    License(std::string license_key, std::string name, int user_id)
        : license_key(license_key), name(name), user_id(user_id) {}

    void saveToDB(sql::Connection* con) {
        sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO License (license_key, user_id, name) VALUES (?, ?, ?)");
        pstmt->setString(1, license_key);
        pstmt->setInt(2, user_id);
        pstmt->setString(3, name);
        pstmt->executeUpdate();
        delete pstmt;
    }
};

int main() {
    try {
        Database db;

        // Создаем нового пользователя
        User newUser("zzz", "zzzzz");
        newUser.saveToDB(db.con);

        // Создаем лицензию для пользователя
        License newLicense("ABC123-XYZ", "My Software", newUser.id);
        newLicense.saveToDB(db.con);

        std::cout << "User and License have been saved successfully!" << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
