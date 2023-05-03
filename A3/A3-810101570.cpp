#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<string> DAY_NAMES = {"Saturday",  "Sunday",   "Monday", "Tuesday",
                                  "Wednesday", "Thursday", "Friday"};
const int WEEK_LEN = 7;
const int CLASS_COUNT = 2;
const string NOT_FOUND = "Not Found";

typedef string Time;

struct TimeRange {
  Time begin;
  Time end;
  bool contains(TimeRange t) { return begin <= t.begin and end >= t.end; }
};

struct Day {
  int position;
  Day(string day_str) {
    for (int i = 0; i < WEEK_LEN; i++)
      if (DAY_NAMES[i] == day_str)
        position = i;
  }
  Day(){};
  friend bool operator>(Day day_1, Day day_2) {
    return day_1.position > day_2.position;
  }
  friend bool operator==(Day day_1, Day day_2) {
    return day_1.position == day_2.position;
  }
  friend bool operator!=(Day day_1, Day day_2) {
    return !(day_1.position == day_2.position);
  }
};

struct Teacher {
  string name;
  int free_days_cnt;
  vector<Day> free_days;
  int course_cnt;
  vector<string> courses;
  void get_input() {
    cin >> name;
    cin >> free_days_cnt;
    for (int i = 0; i < free_days_cnt; i++) {
      string day_name;
      cin >> day_name;
      free_days.push_back(Day(day_name));
    }
    cin >> course_cnt;
    courses.resize(course_cnt);
    for (int i = 0; i < course_cnt; i++)
      cin >> courses[i];
  }
  bool has_course(string course_name) {
    for (string course : courses)
      if (course == course_name)
        return 1;
    return 0;
  }
  bool has_day(Day day) {
    for (Day d : free_days)
      if (d == day)
        return 1;
    return 0;
  }
};

struct Course {
  string name;
  Day first_day, second_day;
  TimeRange lesson_time;
  void get_input() {
    string day_1, day_2;
    cin >> name;
    cin >> day_1 >> day_2;
    first_day = Day(day_1), second_day = Day(day_2);
    cin >> lesson_time.begin >> lesson_time.end;
    if (first_day > second_day)
      swap(first_day, second_day);
  }
};

struct PlanEntry {
  string course_name;
  string teacher_name;
  Day day1, day2;
  TimeRange range;
  int class_id;
  int teacher_free_days_cnt;
  PlanEntry(Course c, Teacher t) {
    course_name = c.name;
    teacher_name = t.name;
    day1 = c.first_day;
    day2 = c.second_day;
    teacher_free_days_cnt = t.free_days_cnt;
  }
  friend bool operator<(PlanEntry a, PlanEntry b) {
    if (a.course_name == b.course_name)
      return a.class_id < b.class_id;
    return a.course_name < b.course_name;
  }
};

const vector<TimeRange> LESSON_TIMES = {
    {"07:30", "09:00"}, {"09:30", "11:00"}, {"11:30", "13:00"}};

typedef vector<Teacher> TeacherList;
typedef vector<Course> CourseList;
typedef pair<Teacher, TimeRange> Lesson;
typedef vector<PlanEntry> Plan;

void get_teacher_data(TeacherList &teachers) {
  int teacher_cnt;
  cin >> teacher_cnt;
  teachers.resize(teacher_cnt);
  for (Teacher &t : teachers)
    t.get_input();
}

void get_course_data(CourseList &courses) {
  int course_cnt;
  cin >> course_cnt;
  courses.resize(course_cnt);
  for (Course &c : courses)
    c.get_input();
}

bool course_time_check(Course course, Day day, TimeRange interval) {
  if (!course.lesson_time.contains(interval))
    return 0;
  if (course.first_day != day and course.second_day != day)
    return 0;
  return 1;
}

bool teacher_time_check(Teacher teacher, Day day) {
  for (Day free_day : teacher.free_days)
    if (free_day == day)
      return 1;
  return 0;
}

CourseList find_ongoing_courses(Day day, TimeRange interval,
                                CourseList &courses) {
  CourseList result;
  for (Course c : courses)
    if (course_time_check(c, day, interval))
      result.push_back(c);
  return result;
}

TeacherList find_ongoing_teachers(Day day, TeacherList &teachers) {
  TeacherList result;
  for (Teacher t : teachers)
    if (teacher_time_check(t, day))
      result.push_back(t);
  return result;
}

bool has_course(Course c, int class_id, Plan &plan) {
  for (PlanEntry pe : plan)
    if (pe.class_id == class_id and pe.course_name == c.name)
      return 1;
  return 0;
}

CourseList find_unpicked_courses(CourseList &courses, Plan &plan,
                                 int class_id) {
  CourseList result;
  for (Course c : courses) {
    if (!has_course(c, class_id, plan))
      result.push_back(c);
  }
  return result;
}

bool is_free(string teacher, Day day, TimeRange interval, Plan &plan) {
  for (PlanEntry p : plan)
    if (p.teacher_name == teacher and (p.day1 == day or p.day2 == day) and
        p.range.contains(interval))
      return 0;
  return 1;
}

bool has_collision(Day day1, Day day2, TimeRange range1, TimeRange range2) {
  return day1 == day2 and range1.contains(range2);
}

bool is_occupied(Course course, int class_id, TimeRange interval, Plan &plan) {
  for (PlanEntry pe : plan) {
    if (pe.class_id == class_id) {
      if (has_collision(course.first_day, pe.day1, interval, pe.range))
        return 1;
      if (has_collision(course.second_day, pe.day1, interval, pe.range))
        return 1;
      if (has_collision(course.first_day, pe.day2, interval, pe.range))
        return 1;
      if (has_collision(course.second_day, pe.day2, interval, pe.range))
        return 1;
    }
  }
  return 0;
}

CourseList find_free_courses(CourseList &courses, Plan &plan, int class_id,
                             TimeRange interval) {
  CourseList result;
  for (Course c : courses) {
    if (!is_occupied(c, class_id, interval, plan))
      result.push_back(c);
  }
  return result;
}

bool are_compatible(Course c, Teacher t, TimeRange interval, Plan &plan) {
  if (!t.has_course(c.name))
    return 0;
  if (!is_free(t.name, c.first_day, interval, plan))
    return 0;
  if (!is_free(t.name, c.second_day, interval, plan))
    return 0;
  return t.has_day(c.first_day) and t.has_day(c.second_day);
}

Plan match_candidates(CourseList &courses, TeacherList &teachers,
                      TimeRange interval, Plan &plan) {
  Plan result;
  for (Course c : courses)
    for (Teacher t : teachers)
      if (are_compatible(c, t, interval, plan))
        result.push_back({c, t});
  return result;
}

Plan fetch_options(Day day, TimeRange interval, TeacherList &teachers,
                   CourseList &courses, Plan &plan, int class_id) {
  CourseList ongoing_courses = find_ongoing_courses(day, interval, courses);
  TeacherList ongoing_teachers = find_ongoing_teachers(day, teachers);
  CourseList unpicked_courses =
      find_unpicked_courses(ongoing_courses, plan, class_id);
  CourseList free_courses =
      find_free_courses(unpicked_courses, plan, class_id, interval);
  Plan matched =
      match_candidates(free_courses, ongoing_teachers, interval, plan);
  for (auto &x : matched)
    x.range = interval, x.class_id = class_id;
  return matched;
}

bool is_better(PlanEntry a, PlanEntry b) {
  if (a.course_name < b.course_name)
    return 1;
  if (a.course_name > b.course_name)
    return 0;
  if (a.teacher_free_days_cnt < b.teacher_free_days_cnt)
    return 1;
  if (a.teacher_free_days_cnt > b.teacher_free_days_cnt)
    return 0;
  if (a.teacher_name < b.teacher_name)
    return 1;
  if (a.teacher_name > b.teacher_name)
    return 0;
  return 0;
}

PlanEntry find_best_option(Plan &options, Plan &plan) {
  PlanEntry best = options[0];
  for (PlanEntry candidate : options) {
    if (is_better(candidate, best))
      best = candidate;
  }
  return best;
}

void construct_day(Day day, TeacherList &teachers, CourseList &courses,
                   Plan &plan, int class_id) {
  for (TimeRange interval : LESSON_TIMES) {
    Plan available_options =
        fetch_options(day, interval, teachers, courses, plan, class_id);
    if (available_options.empty())
      continue;
    plan.push_back(find_best_option(available_options, plan));
  }
}

void construct_class(TeacherList &teachers, CourseList &courses, Plan &plan,
                     int class_id) {
  for (string day : DAY_NAMES)
    construct_day(Day(day), teachers, courses, plan, class_id);
}

Plan assign_lessons(TeacherList &teachers, CourseList &courses) {
  Plan plan;
  for (int id = 1; id <= CLASS_COUNT; id++)
    construct_class(teachers, courses, plan, id);
  return plan;
}

void print(Plan &result, string name, int class_id) {
  if (result.empty()) {
    cout << NOT_FOUND << endl;
    return;
  }
  if (result.back().course_name == name and
      result.back().class_id == class_id) {
    PlanEntry pe = result.back();
    cout << pe.teacher_name << ": " << pe.range.begin << ' ' << pe.range.end
         << endl;
    result.pop_back();
    return;
  }
  cout << NOT_FOUND << endl;
}

void output_result(Plan &result, vector<string> &course_names) {
  sort(result.begin(), result.end());
  reverse(result.begin(), result.end());
  for (string course_name : course_names) {
    cout << course_name << endl;
    for (int id = 1; id <= CLASS_COUNT; id++)
      print(result, course_name, id);
  }
}

int main() {
  TeacherList teachers;
  CourseList courses;
  get_teacher_data(teachers);
  get_course_data(courses);
  vector<string> course_names;
  for (Course c : courses)
    course_names.push_back(c.name);
  sort(course_names.begin(), course_names.end());
  Plan result = assign_lessons(teachers, courses);
  output_result(result, course_names);
  return 0;
}
