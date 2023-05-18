#include "driver.hpp"

Driver::Driver(int id_) { id = id_; }

Driver::~Driver() {
  for (auto x : errands)
    delete x.second;
}

void Driver::add_mission(Mission *m) {
  if (errands.count(m->get_id()))
    throw runtime_error(DUP_D_MS);
  errands[m->get_id()] = new Errand(m);
}

int Driver::get_mission_count() { return errands.size(); }

void Driver::show_status() {
  if (get_mission_count() == 0)
    throw runtime_error(NO_D_MISSION);
  cout << "missions status for driver " << id << DELIM << endl;
  vector<Errand *> err_vec;
  for (pair<int, Errand *> x : errands) {
    err_vec.push_back(x.second);
  }
  sort(err_vec.begin(), err_vec.end(),
       [](Errand *x, Errand *y) { return *x < *y; });
  for (auto x : err_vec)
    x->show();
}

void Driver::add_ride(Ride ride) {
  cout << "completed missions for driver " << id << DELIM << endl;
  vector<Errand *> err_vec;
  for (pair<int, Errand *> x : errands) {
    err_vec.push_back(x.second);
  }
  sort(err_vec.begin(), err_vec.end(),
       [](Errand *x, Errand *y) { return *x < *y; });
  for (auto x : err_vec)
    x->add_ride(ride);
}