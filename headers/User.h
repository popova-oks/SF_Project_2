#pragma once
#include "Chat.h"
#include <map>
#include <string>

class User : public IObserver {
  public:
    User(Chat* chat);
    virtual ~User() {}

    void update(IObserver* sender, const std::string& message) override;

    const std::string& get_name() const override { return name_; }
    const std::string& get_login() const override { return login_; }
    const std::string& get_password() const override { return password_; }
    const int get_userID() const override { return user_ID_; }

    User* log_in(Chat* chat);
    void create_message();
    void leave_chat(Chat* chat);
    void display_Messages();

    void set_name(const std::string &name) { name_ = name; }
    void set_login(const std::string &login) { login_ = login; }
    void set_password(const std::string &password) { password_ = password; }	// FIX ME!! Вызов хэш функции!!!!
    void set_userID() { user_ID_ = ++static_counter; }
    void set_isAutorization() { is_autorization_ = true; }
    void set_notAutorization() { is_autorization_ = false; }

  private:
    Chat* chat_ = nullptr;
    std::string name_{};
    std::string login_{};
    std::string password_{};
    int user_ID_{0};
    bool is_autorization_{false};
    std::multimap<IObserver*, const std::string> messages_{};

    static int static_counter;
};
