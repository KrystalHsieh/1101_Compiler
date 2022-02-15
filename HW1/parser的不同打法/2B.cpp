#include <iostream>
#include <iterator>
#include <regex>
#include <vector>
#include <sstream>

using namespace std;

void SyntaxCheck(const vector<string> &);
vector<string> SplitLine(const string &);
bool IsID(const string &);
bool IsAString(string);

int main(void)
{
    vector<string> lines;
    string line;
    int i = 0;
    while (i < 2 && getline(cin, line))
    {
        i++;
        lines.push_back(line);
    }

    SyntaxCheck(lines);

    return 0;
}

void SyntaxCheck(const vector<string> &codes)
{
    bool invalid = false;
    for (const auto &line : codes)
    {
        vector<string> tokens = SplitLine(line);

        if (!((tokens[0] == "s" && IsID(tokens[1]) && IsAString(tokens[2])) || (tokens[0] == "p" && IsID(tokens[1]))))
        {
            cout << "valid input" << endl;
            return;
        }
    }
    for (const auto &line : codes)
    {
        vector<string> tokens = SplitLine(line);
        if (tokens[0] == "s")
        {
            if (IsID(tokens[1]) && IsAString(tokens[2]))
            {
                cout << "strdcl " << tokens[0] << endl;
                cout << "id " << tokens[1] << endl;
                cout << "quote \"" << endl;
                tokens[2].erase(0, 1);
                tokens[2].erase(tokens[2].size() - 1);
                cout << "string " << tokens[2] << endl;
                cout << "quote \"" << endl;
            }
        }
        else if (tokens[0] == "p")
        {
            if (IsID(tokens[1]))
            {
                cout << "print " << tokens[0] << endl;
                cout << "id " << tokens[1] << endl;
            }
        }
    }
}

vector<string> SplitLine(const string &line)
{
    vector<string> tokens;
    stringstream ss(line);
    copy(istream_iterator<string>(ss),
         istream_iterator<string>(),
         back_inserter(tokens));
    return tokens;
}

bool IsID(const string &token)
{
    //const static
    regex reg("[a-o|q|r|t-z]");
    return regex_match(token, reg);
}

bool IsAString(string token)
{
    //const static
    regex reg("\"[a-zA-Z0-9]*\"");
    return regex_match(token, reg);
}
