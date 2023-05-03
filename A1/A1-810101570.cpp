#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int SUMMARY_SIZE = 20;
const char SPACE = ' ';
const char INDENT = '\t';
const char NEW_LINE = '\n';
const vector<char> delimeters = {SPACE, INDENT, NEW_LINE};
const vector<char> date_delimeter = {'/'};

int count_good_words(string &str);
string get_word(string &str, int i);
bool is_good(string &word);
void read_good_words();
string get_date(string &str);
bool contains(vector<char> list, char c);
string get_date(string &str);
bool is_older(string date1, string date2);
vector<int> vec_to_int(vector<string> vec);
vector<string> split(string &str, vector<char> delimeters);
string get_date(string &str);

struct Diary_page {
  string date;
  vector<string> lines;
  int len = 0;
  int good_word_count = 0;
  void add_line(string &line) {
    line += NEW_LINE;
    len += line.size();
    good_word_count += count_good_words(line);
    lines.push_back(line);
  }
  void print() {
    for (string line : lines)
      cout << line;
  }
  void print_summary() {
    cout << date << endl;
    int printed_char_count = 0;
    for (string line : lines) {
      for (char chr : line) {
        printed_char_count++;
        if (printed_char_count > SUMMARY_SIZE)
          break;
        cout << chr;
      }
      if (printed_char_count > SUMMARY_SIZE) {
        cout << "..." << endl;
        break;
      }
    }
  }
};

Diary_page *find_the_longest_page(vector<Diary_page> &diary);
Diary_page *find_the_best_page(vector<Diary_page> &diary);
Diary_page *find_page(string date, vector<Diary_page> &diary);
bool is_better(Diary_page &a, Diary_page &b);

vector<string> good_words;

int main() {
  Diary_page *current_day;
  vector<Diary_page> diary;
  read_good_words();
  while (cin.peek() != EOF) {
    string cur_line;
    getline(cin, cur_line);
    string first_word = get_word(cur_line, 0);
    if (first_word == "start_day")
      current_day = find_page(get_date(cur_line), diary);
    else if (first_word == "show_day")
      find_page(get_date(cur_line), diary)->print();
    else if (first_word == "show_the_longest_day")
      find_the_longest_page(diary)->print_summary();
    else if (first_word == "show_the_best_day")
      find_the_best_page(diary)->print_summary();
    else
      current_day->add_line(cur_line);
  }
  return 0;
}

string get_date(string &str) { return get_word(str, 1); }

vector<int> vec_to_int(vector<string> vec) {
  // takes a vector of strings, converts the strings to ints and returns a
  // vector of corresponding ints
  vector<int> res;
  for (string num : vec)
    res.push_back(stoi(num));
  return res;
}

bool is_older(string date1, string date2) {
  vector<string> splited_date1 = split(date1, date_delimeter);
  vector<string> splited_date2 = split(date2, date_delimeter);
  reverse(splited_date1.begin(), splited_date1.end());
  reverse(splited_date2.begin(), splited_date2.end());
  vector<int> dec_date1 = vec_to_int(splited_date1);
  vector<int> dec_date2 = vec_to_int(splited_date2);
  return dec_date1 > dec_date2;
}

bool is_better(Diary_page &a, Diary_page &b) {
  if (a.good_word_count > b.good_word_count)
    return 1;
  if (a.good_word_count < b.good_word_count)
    return 0;
  return is_older(a.date, b.date);
}

Diary_page *find_page(string date, vector<Diary_page> &diary) {
  // returns a pointer to a page corresponding to the given date, creates a
  // new page if none exits
  for (int i = 0; i < (int)diary.size(); i++)
    if (diary[i].date == date)
      return &diary[i];
  Diary_page new_page;
  new_page.date = date;
  diary.push_back(new_page);
  return &diary.back();
}

bool contains(vector<char> list, char c) {
  for (char x : list)
    if (x == c)
      return true;
  return false;
}

string get_word(string &str, int i) {
  // returns the i'th word in a string
  return split(str, delimeters)[i];
}

Diary_page *find_the_best_page(vector<Diary_page> &diary) {
  int best_page_index = 0;
  for (int i = 0; i < (int)diary.size(); i++)
    if (is_better(diary[i], diary[best_page_index]))
      best_page_index = i;
  return &diary[best_page_index];
}

Diary_page *find_the_longest_page(vector<Diary_page> &diary) {
  int longest_page_index = 0;
  for (int i = 0; i < (int)diary.size(); i++)
    if (diary[i].len > diary[longest_page_index].len or
        (diary[i].len == diary[longest_page_index].len and
         is_older(diary[i].date, diary[longest_page_index].date)))
      longest_page_index = i;
  return &diary[longest_page_index];
}

void read_good_words() {
  FILE *positive_words_file = fopen("positive-words.txt", "r");
  string good_word = "";
  char chr;
  while ((chr = fgetc(positive_words_file)) != EOF) {
    if (contains(delimeters, chr)) {
      if (good_word.size() > 0)
        good_words.push_back(good_word);
      good_word = "";
    } else
      good_word += chr;
  }
  if (good_word.size() > 0)
    good_words.push_back(good_word);
  fclose(positive_words_file);
}

vector<string> split(string &str, vector<char> delimeters) {
  vector<string> res = {""};
  for (char c : str) {
    if (contains(delimeters, c)) {
      if ((int)res.back().size() == 0)
        continue;
      else
        res.push_back("");
    } else {
      res.back() += c;
    }
  }
  return res;
}

bool is_good(string &word) {
  for (string good_word : good_words)
    if (word == good_word)
      return true;
  return false;
}

int count_good_words(string &str) {
  int cnt = 0;
  vector<string> words = split(str, delimeters);
  for (string word : words)
    if (is_good(word))
      cnt++;
  return cnt;
}
