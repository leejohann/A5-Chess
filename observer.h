#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer {
  public:
    virtual void notify(Subject&) = 0;
    virtual ~Observer() = default;
};

#endif