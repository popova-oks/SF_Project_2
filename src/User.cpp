#include "../headers/User.h"
#include "../headers/Chat.h"
#include <iostream>


User::User(Chat* chat) : chat_(chat) { chat_->set_User(this); }

User* User::log_in(Chat* chat) {
    std::cin.clear();
    std::cin.ignore(32767, '\n');

    std::string login;
    std::cout << "\nEnter your login: ";
    std::cin >> login;

    std::string password;
    std::cout << "Enter your password: ";
    std::cin >> password;

    User* user = dynamic_cast<User*>(chat->find_user(login));
    if(user == nullptr) {
        std::cout << "\nSuch user wasn't found! You'll need to register in the chat!\n";
        return nullptr;
    } else {
        if(chat->is_check_Observer(user, login, password)) {
            if(user->is_autorization_) {
                std::cout << "\nYou are login!\n";
            } else {
                chat->attach(user);
            }
            return user;
        } else {
            std::cout << "\nTry again!\n ";
            return nullptr;
        }
    }
}

void User::create_message() {
    char event;
    while(true) {
        std::cout << "\nEnter an action: s - send to all users, c - chose some user, q - quit: ";
        std::cin >> event;

        if(event == 'q') {
            return;
        } else if(event == 's' || event == 'c') {
            chat_->notify(this, event);
        } else {
            std::cout << "\nTry agan!\n";
        }
    }
}

void User::update(IObserver* sender, const std::string& message) {
    messages_.insert({sender, message});
}

void User::display_Messages() {
    if(messages_.empty()) {
        std::cout << "No messages!\n";
    }
    for(std::pair<const IObserver*, const std::string&> msg : messages_) {
        std::cout << "The message received from user: " << msg.first->get_login() << "\n";
        std::cout << "The message: " << msg.second << "\n\n";
    }
}

void User::leave_chat(Chat* chat) {
    chat->detach(this);
    set_notAutorization();
    std::cout << "\nYou are detached from the chat!\n";
}

int User::static_counter = 0;