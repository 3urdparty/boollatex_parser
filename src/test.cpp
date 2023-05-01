#include <cmath>
#include <iomanip>
#include <iostream>
#include <regex>
#include <strfmt/strfmt.hpp>
#include <string>
#include <vector>
using namespace std;

string barRegexQuery = "(\\\\bar\\{)(.*)(\\})";

string expression = "\\bar{A+BC\\bar{D}} \\oplus C";

enum Operation { unknown = 0, bar = 1 };

Operation categorizeOperation(string token) {
  if (regex_match(token, regex(barRegexQuery))) {
    return Operation::bar;
  }
  return Operation::unknown;
}

string extractInner(string expression) {
  unsigned int firstIndex = expression.find('{') + 1;
  unsigned int lastIndex = expression.find('}') - 5;
  return expression.substr(firstIndex, lastIndex);
}

// void generateTruthTable(string expression) {
//   regex variableRegexQuery("[A-Z]");
//   smatch sm;
//   if (regex_search(expression, sm, variableRegexQuery,
//   regex_constants::match_any)) {
//     for (int i = 0; i < sm.size(); i++) {
//       cout << sm[i] << endl;
//     }
//   }
// //   cout << sm.size();
// }

using namespace std;
vector<string> getAllMatches(string str, regex regexQuery) {
  string subject = str;
  smatch match;
  vector<string> matches;
  int i = 1;
  while (regex_search(subject, match, regexQuery)) {
    matches.push_back(match.str(0));
    i++;
    subject = match.suffix().str();
  }
  return matches;
}

vector<string> getAllVariables(string expression) {
  regex r("([A-Z][0-9]+|[A-Z]_\\{[A-z0-9]+\\}|[A-Z]_([A-z]+|[0-9]+)|[A-Z])");
  vector<string> variables = getAllMatches(expression, r);
  return variables;
}

vector<vector<string>> generateTruthTable(string expression) {
  vector<string> variables = getAllVariables(expression);

  vector<vector<string>> table;

  for (int x = 0; x < variables.size(); x++) {
    vector<string> column;
    column.push_back(variables[x]);
    for (int y = 0; y < pow(2, variables.size()); y++) {
      column.push_back("1");
    }
    table.push_back(column);
  }
  return table;
}

void addRow(vector<string> row) {
  for (int x = 0; x < row.size(); x++) {
    cout <<  '|' << left << setw(3) << row[x];
  }
      cout << '|' << endl;

}
void displayTable(vector<vector<string>> table) {
  int columns = table.size();
  int rows = table[0].size();

  for (int row = 0; row < columns; row++) {
    addRow(table[row]);
  }
};

int main() {
  //   generateTruthTable(" A+B");
  //   //   vector<string> tokens = splitString(expression, ' ');
  //   //   for (auto token : tokens) cout << token << endl;

  //   //   string testToken = "\\bar{A+B}";
  //   //   Operation op = categorizeOperation(testToken);

  //   //   string inner = extractInner(testToken);
  //   //   cout << inner << endl;

  //   //   vector<string> tokens = splitString(inner, '+');
  string expression = "A+B";
  vector<vector<string>> table = generateTruthTable(expression);
  displayTable(table);
  //   for (string match :) cout << match << endl;
};