#pragma once
#include "IObserver.h"
#include <map>


template <typename T> class Messages {
  public:
    Messages(){};
    ~Messages(){};
    void set_message(IObserver* sender, const T& message);

  private:
    std::multimap<IObserver*, T> msg_{};
};