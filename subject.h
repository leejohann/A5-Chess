#ifndef SUBJECT_H
#define SUBJECT_H

#include "state.h"
#include <vector>

class Observer;

class Subject {
  State state;
  std::vector<Observer*> observers;

  public:
    Subject();
    ~Subject();
    void setState(const State&);
    State getState() const;
    virtual Info getInfo() const = 0;
    void attach(Observer*);
    void notifyObservers();
};

#endif