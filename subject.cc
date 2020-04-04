#include "subject.h"
#include "observer.h"

Subject::Subject() : state{State{Posn{0,0},StateType::Negative}} {
  
}

Subject::~Subject() {}

void Subject::setState(const State& newState) {
  this->state = newState;
}

State Subject::getState() const {
  return this->state;
}

void Subject::attach(Observer* newObsv) {
  this->observers.emplace_back(newObsv);
}

void Subject::notifyObservers() {
  for (unsigned int i = 0; i < this->observers.size(); i++) {
    this->observers[i]->notify(*this);
  }
}