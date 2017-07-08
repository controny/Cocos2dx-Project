#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <vector>
using std::string;
using std::vector;
class Global
{
public:
    Global();
    ~Global();
	const static string remoteServer = "http://paradox5.cn:8080";
    static string gameSessionId;
    static long score;

    static string toString(vector<char> *buffer);

    static string getSessionIdFromHeader(string header);
};

#endif
