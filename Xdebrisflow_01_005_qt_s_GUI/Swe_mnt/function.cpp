#include <iostream>
#include <sstream>
#include "function.h"
namespace FO{
void stringSplit(std::string s,char splitchar,std::vector<std::string>& vec)
{
    if(vec.size()!=0){vec.clear();}
    int length= s.length();
    int flag_begin= 0;
    for (int i=0;i<length;i++)
    {
        if(s[0]=='#')
        {
            if(s[i]==splitchar){
                if(flag_begin==0){vec.push_back(s.substr(flag_begin+1,i-1-flag_begin));}
                else if(s[i-1]==splitchar){}
                else{vec.push_back(s.substr(flag_begin,i-flag_begin));}
                flag_begin=i+1;
                }
            else if (i==length-1){vec.push_back(s.substr(flag_begin,i+1-flag_begin));break;}
        }
        else{break;}
    }
}
int stringToInt (std::string input_string)
{
    int output;
    std::stringstream sstream;
    sstream<<input_string;
    sstream>>output;
    return output;
}
double stringToDouble (std::string input_string)
{
    double output;
    std::stringstream sstream;
    sstream<<input_string;
    sstream>>output;
    return output;
}
bool stringToBool (std::string input_string)
{
    int output=stringToInt(input_string);
    return (output>0?true:false);
}
}
