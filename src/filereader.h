#ifndef FILEREADER_H
#define FILEREADER_H

#include <QString>
void saveSetting(const std::string &key, const QString &value);
std::string readVal(const std::string& key);
#endif // FILEREADER_H
