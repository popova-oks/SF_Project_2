#include "../headers/ClientCode.h"
#include <algorithm>
#include <exception>


void ClientCode::start() {
    std::cin.exceptions(std::istream::failbit);

    Chat* chat = nullptr;
    try {
        chat = new Chat();
    } catch(const std::bad_alloc& ex) {

        std::cout << "Allocation failed: " << ex.what() << '\n';
    }
    User* user = nullptr;
    bool flag = true;

    while(flag) {
        if(user == nullptr) {
            std::cout << "\nNo current User";
        } else {
            std::cout << "\nThe current user:"
                      << "\nname - " << user->get_name() << "\nlogin - " << user->get_login()
                      << "\nuser_ID - " << user->get_userID();
        }
        std::cout << "\n\nSelect an action:" << std::endl;
        std::cout << "1 - registration, 2 - log in the chat, 3 - send a message, ";
        std::cout << "\n4 - exit the chat,  5 - quit from the program: ";
        char ch;
        std::cin >> ch;

        switch(ch) {
        case '1': {
            user = make_user(chat);
            break;
        }
        case '2': {
            chat->display_listObservers();
            if(chat->is_Users()) {
                user = user->log_in(chat);
                if(user != nullptr) {
                    user->display_Messages();
                }
            } else {
                std::cout << "\nUsers were not found!\nYou'll need to register in the chat!\n";
            }
            break;
        }
        case '3': {
            chat->display_listObservers();
            if(user == nullptr) {
                std::cout << "\nYou need to log in!";
            } else {
                if(chat->is_Observes()) {
                    user->create_message();
                } else {
                    std::cout << "\nNo authorized users!\n";
                }
            }
            break;
        }
        case '4': {
            if(user == nullptr) {
                std::cout << "\nYou need to log in!";
            } else {
                user->leave_chat(chat);
                user = nullptr;
            }
            break;
        }
        case '5': {
            flag = false;
            break;
        }
        default: {
            std::cout << "\nTry agan.";
            break;
        }
        }
        //ñáðîñèòü âñå ñèìâîëû èç ïîòîêà
        std::cin.clear();
        std::cin.ignore(32767, '\n');
    }
    std::cout << "\nSee you soon agan! " << std::endl;

    delete chat;
}

User* ClientCode::make_user(Chat* chat) {
    try {
        std::string name;
        std::string login;
        std::string password;
        bool OnlyLettersNum = false;
        while(!OnlyLettersNum) {
            std::cout << "\nEnter only letters or numbers without using spaces or other symbols!\n";

            std::cout << "Enter your name: ";
            std::cin >> name;
            OnlyLettersNum = containsOnlyLettersNum(name);
            if(!OnlyLettersNum) {
                continue;
            }

            std::cout << "Enter your username: ";
            std::cin >> login;
            OnlyLettersNum = containsOnlyLettersNum(login);
            if(!OnlyLettersNum) {
                continue;
            }

            std::cout << "Enter your password: ";
            std::cin >> password;
            OnlyLettersNum = containsOnlyLettersNum(password);
            if(!OnlyLettersNum) {
                continue;
            }
        }

        User* user = dynamic_cast<User*>(chat->find_user(login));

        if(user != nullptr) {
            std::cout << "\nThis user was registrated!\n";
        } else {
            try {
                user = new User(chat);
            } catch(const std::bad_alloc& ex) {

                std::cout << "Allocation failed: " << ex.what() << '\n';
            }
            user->set_name(name);
            user->set_login(login);
            user->set_password(password);
            user->set_userID();
            user->set_isAutorization();
            std::cout << "\nHi, You are new User! name - " << user->get_name() << " : "
                      << "ID - " << user->get_userID();
            chat->attach(user);
        }
        return user;
    } catch(const std::istream::failure& ex) {
        std::cerr << "Failed to input: " << ex.what() << "\n";
    } catch(...) {
        std::cerr << "Some other exception\n";
    }
}

bool ClientCode::containsOnlyLettersNum(std::string const& str) {
    return std::all_of(str.begin(), str.end(), [](char const& c) { return std::isalnum(c); });
}
