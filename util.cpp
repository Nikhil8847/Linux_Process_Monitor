#include "util.h"

string Util::convertToTime(long int input_seconds){
    long totalMinutes = input_seconds/60;
    long hoursPassed = totalMinutes/60;
    long minutesPassed = (long)(totalMinutes%60);   
    long secondsPassed = (long)(input_seconds%60);

    string time = std::to_string(hoursPassed) + std::to_string(minutesPassed) + std::to_string(secondsPassed);
    return time;
}

string Util::getProgressBar(string percent){
    string progressBar = "0% ";
    int _size = 50;
    int boudaries = (std::stof(percent)/100)*_size;

    for(int i = 0; i < _size; i++){
        if(i <= boudaries){
            progressBar += "|";
        }
        else{
            progressBar += " ";
        }
    }

    progressBar += " " + percent.substr(0,5), " /100%";
    return progressBar;
}

ifstream Util::getStream(string path){
    ifstream stream(path);
    if(!stream){
        throw std::runtime_error("Non - existing PID");
    }
    return stream;
}