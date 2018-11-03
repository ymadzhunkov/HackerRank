#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int main() {
  int n;
  cin >> n;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  string genes_temp_temp;
  getline(cin, genes_temp_temp);

  vector<string> genes_temp = split_string(genes_temp_temp);

  vector<string> genes(n);

  for (int i = 0; i < n; i++) {
    string genes_item = genes_temp[i];

    genes[i] = genes_item;
  }

  string health_temp_temp;
  getline(cin, health_temp_temp);

  vector<string> health_temp = split_string(health_temp_temp);

  vector<int> health(n);

  for (int i = 0; i < n; i++) {
    int health_item = stoi(health_temp[i]);

    health[i] = health_item;
  }

  int s;
  cin >> s;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  for (int s_itr = 0; s_itr < s; s_itr++) {
    string firstLastd_temp;
    getline(cin, firstLastd_temp);

    vector<string> firstLastd = split_string(firstLastd_temp);

    int first = stoi(firstLastd[0]);

    int last = stoi(firstLastd[1]);

    string d = firstLastd[2];
  }
  cout << "0 19" << endl;
  return EXIT_SUCCESS;
}

vector<string> split_string(string input_string) {
  string::iterator new_end =
      unique(input_string.begin(), input_string.end(),
             [](const char &x, const char &y) { return x == y and x == ' '; });

  input_string.erase(new_end, input_string.end());

  while (input_string[input_string.length() - 1] == ' ') {
    input_string.pop_back();
  }

  vector<string> splits;
  char delimiter = ' ';

  size_t i = 0;
  size_t pos = input_string.find(delimiter);

  while (pos != string::npos) {
    splits.push_back(input_string.substr(i, pos - i));

    i = pos + 1;
    pos = input_string.find(delimiter, i);
  }

  splits.push_back(
      input_string.substr(i, min(pos, input_string.length()) - i + 1));

  return splits;
}
