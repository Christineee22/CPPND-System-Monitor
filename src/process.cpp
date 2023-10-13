#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid()const { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
    int pid = this->Pid();
    long total_time = LinuxParser::ActiveJiffies(pid);
    long seconds = this->UpTime();
    float sys_time = sysconf(_SC_CLK_TCK);
    float sys_tot = total_time/sys_time;

    float cpu_usage = sys_tot/seconds;
    return cpu_usage;}
    
     //return 0.0;}

// TODO: Return the command that generated this process
string Process::Command() { 
    int pid = this->Pid();
    std::string cmd = LinuxParser::Command(pid);
    return cmd; }

// TODO: Return this process's memory utilization
string Process::Ram() { 
    int pid = this->Pid();
    std::string ram = LinuxParser::Ram(pid);
    return ram; }

// TODO: Return the user (name) that generated this process
string Process::User() { 
    // Get pid
    int pid = this->Pid();
    // Get User 
    string user_name = LinuxParser::User(pid);
    return user_name; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() const { 
    int pid = this->Pid();   
    long int start_time;
    start_time = LinuxParser::UpTime(pid);
    long uptime = LinuxParser::UpTime(); 
    long int sec = uptime - start_time;
    
    return sec; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 

    float cpu_uti = this->CpuUtilization();
    float cpu_uti_a = a.CpuUtilization();
    bool value = cpu_uti > cpu_uti_a;

    
    return value;}
     //return true;}