#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    //clear vector to fill up with new values
    processes_.clear();
    for (int pid:LinuxParser::Pids()){
        Process process(pid);
        processes_.push_back(process);
    }

    // sort
    std::sort(processes_.begin(),processes_.end());  
    return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    std::string kernel_version;
    kernel_version = LinuxParser::Kernel();
    return kernel_version; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    float value_mem;
    value_mem = LinuxParser::MemoryUtilization();
    return value_mem; }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    std::string os_name;
    os_name = LinuxParser::OperatingSystem();
    return os_name; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    int value_proc_run;
    value_proc_run = LinuxParser::RunningProcesses();
    return value_proc_run; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    int value_process;
    value_process = LinuxParser::TotalProcesses();
    return value_process; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    long up_time;
    up_time = LinuxParser::UpTime();
    return up_time; }