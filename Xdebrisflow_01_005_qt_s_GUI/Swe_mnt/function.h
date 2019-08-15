#ifndef FUNCTION_H
#define FUNCTION_H
#include <string>
#include <vector>
namespace FO {
void stringSplit(std::string s,char splitchar,std::vector<std::string>& vec);
int stringToInt (std::string input_string);
double stringToDouble (std::string input_string);
bool stringToBool (std::string input_string);
}
#endif // FUNCTION_H
