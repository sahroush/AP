#include <iostream>
#include <vector>

using namespace std;

void traverse(vector<int> &arr, int cur_indx = 0, int prv_val = 0,
              bool get_max = 1) {
  if (cur_indx < 0 or cur_indx >= (int)arr.size())
    return;
  cout << arr[cur_indx] << ' ';
  if (!arr[cur_indx] and !prv_val)
    return;
  if (get_max)
    traverse(arr, cur_indx + max(arr[cur_indx], prv_val), arr[cur_indx],
             !get_max);
  else
    traverse(arr, cur_indx + min(arr[cur_indx], prv_val), arr[cur_indx],
             !get_max);
}

int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++)
    cin >> arr[i];
  traverse(arr);
  return 0;
}
