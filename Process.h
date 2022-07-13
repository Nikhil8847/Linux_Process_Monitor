#include<string>

class Process {
    int pId;
    std::string user;
    std::string cmd;
    float CPU_Percentage;
    long long Memory;
    std::string time;
    Process(){

    }
    int PID() {return pId;}
    std::string User() {return user;}
    std::string CMD() {return cmd;}
};