#include "ProcessParser.h"

string ProcessParser::getCmd(string pid){
    
}

string ProcessParser::getVmSize(string pid){
    string name = "VmData";
    string result;
    // Opening input file stream for status file
    std::ifstream stream = Util::getStream(Path::basePath() + pid + Path::statusPath());

    string line;
    while(std::getline(stream, line)){
        if(line.compare(0, name.size(), name) == 0){
            // remove whitespaces from line
            std::istringstream buff(line);
            std::istream_iterator<string> beg(buff), end;
            std::vector<string> values(beg, end);

            // convert KB ---> GB
            result = (std::stof(values[1])/float(1024*1024));
            break;
        }
    }
}

string ProcessParser::getCpuPercent(string pid)
{
    string value;
    float result;
    ifstream stream = Util::getStream((Path::basePath()+ pid + "/" + Path::statpath()));
    string line;
    getline(stream, line);
    string str = line;
    std::istringstream buf(str);
    std::istream_iterator<string> beg(buf), end;
    std::vector<string> values(beg, end); // done!
    // acquiring relevant times for calculation of active occupation of CPU for selected process
    float utime = stof(ProcessParser::getProcUpTime(pid));
    float stime = stof(values[14]);
    float cutime = stof(values[15]);
    float cstime = stof(values[16]);
    float starttime = stof(values[21]);
    float uptime = ProcessParser::getSysUpTime();
    float freq = sysconf(_SC_CLK_TCK);
    float total_time = utime + stime + cutime + cstime;
    float seconds = uptime - (starttime/freq);
    result = 100.0*((total_time/freq)/seconds);
    return std::to_string(result);
}


string ProcessParser::getProcUpTime(string pid){
    ifstream stream = Util::getStream(Path::basePath() + pid + "/" + Path::statpath());
    string line;
    getline(stream, line);
    string str = line;
    std::istringstream buff(str);
    std::istream_iterator<string> beg(buff), end;
    std::vector<string> values(beg, end);
    return std::to_string(float(stof(values[13])/sysconf(_SC_CLK_TCK)));
}

string ProcessParser::getProcUser(string pid){
    string name = "Uid:";
    string result{};
    ifstream stream = Util::getStream(Path::basePath() + pid + "/" + Path::statusPath());
    
    string line;
    while(getline(stream, line)){
        if(line.compare(0, name.size(), name) == 0){
            std::istringstream buff(line);
            std::istream_iterator<string> beg(buff), end;
            std::vector<string> values(beg, end);
            result = values[1];
            break;
        }
    }
    stream = Util::getStream("/etc/passwd");
    name = ("x:" + result);
    // Search for the User with selected UID
    while(std::getline(stream, line)){
        if(line.find(name) != std::string::npos){
            result = line.substr(0, line.find(":"));
            return result;
        }
    }
    return "";
}

std::vector<string> ProcessParser::getPidList(){
    DIR* dir;
    std::vector<string> container;
    if(!(dir = opendir("/proc")))
        throw std::runtime_error(std::strerror(errno));
    while (dirent* dirp = readdir(dir)) {
        // is this a directory?
        if(dirp->d_type != DT_DIR)
            continue;
        // Is every character of the name a digit?
        if (std::all_of(dirp->d_name, dirp->d_name + std::strlen(dirp->d_name), 
        [](char c){ return std::isdigit(c); })) {
            container.push_back(dirp->d_name);
        }
    }
    //Validating process of directory closing
    if(closedir(dir))
        throw std::runtime_error(std::strerror(errno));
    return container;
}

string ProcessParser::getCmd(string pid)
{
    string line;
    ifstream stream = Util::getStream((Path::basePath() + pid + Path::cmdPath()));
    std::getline(stream, line);
    return line;
}

int ProcessParser::getTotalNumberOfProcesses()
{
    // Get the number of host cpu cores
    string line;
    string name = "cpu cores";
    ifstream stream = Util::getStream((Path::basePath() + "cpuinfo"));
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(),name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<string> beg(buf), end;
            std::vector<string> values(beg, end);
            return std::stoi(values[3]);
        }
    }
    return 0;
}

std::vector<string> ProcessParser::getSysCpuPercent(string corNumber){
    string name = "cpu" + corNumber;
    string line;
     ifstream stream = Util::getStream((Path::basePath() + Path::statPath()));
    while (std::getline(stream, line)) {
        if (line.compare(0, name.size(),name) == 0) {
            std::istringstream buf(line);
            std::istream_iterator<string> beg(buf), end;
            std::vector<string> values(beg, end);
            return values;
        }
    }
    return (std::vector<string>());
}