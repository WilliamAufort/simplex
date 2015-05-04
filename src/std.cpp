#include "../include/std.h"

#include <sstream>

using namespace std;

string intToString(int a)
{
    stringstream ss;
    ss << a;
    return ss.str();
}
