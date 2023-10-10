#include "../headers/Messages.h"

template <typename T> void Messages<T>::set_message(IObserver* sender, const T& message) {
    msg_.insert({sender, message});
}

template class Messages<std::string>;