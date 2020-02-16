#include "filereader.h"
#include <QString>
#include <fstream>
#include <iostream>
#include <regex>
using namespace std;
static string path = "res\\setting.conf";
void saveSetting(const string &key, const QString &value)
{
    ifstream ifs(path);
    string text
    {
        istreambuf_iterator<char>{ifs}, {}
    };
    ifs.close();
    regex rgx{key + ".+(?=\\n)"};
    regex_replace(text, rgx, key + "=" + value.toStdString()).swap(text);
    ofstream ofs(path, ios::trunc | ios::out);
    ofs << text;
}
string readVal(const string& key)
{
    ifstream ifs(path);
    string text{istreambuf_iterator<char>{ifs}, {} };

    regex rgx{ key + "\\s*=\\s*(.+(?=\\n|$))" };
    smatch sub;
    if (regex_search(text, sub, rgx))
        return sub[1];
}
