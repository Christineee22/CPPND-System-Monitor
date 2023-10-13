#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"
#include <unistd.h>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  float value_tot;
  float value_free;
  float value_memo;
  float value;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename); 
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal"){
          value_tot = value;
          //std::cout<< "total value is" << value_tot << "\n";
        } else if (key == "MemFree"){
          value_free = value;
          //std::cout<< "free value is" << value_free << "\n";
        }
      }      
    }
  }
  value_memo = (value_tot - value_free)/value_tot ;
  return value_memo; }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long value_time1, value_time2;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> value_time1 >> value_time2;
  }
  return value_time1; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  std::string pid_str = '/' + std::to_string(pid);
  std::string pid_string = std::to_string(pid);
  vector<long> value_set;
  //long total_active;
  std::string key,word1,word2;
  std::string line;
  long value;
  std::ifstream filestream(kProcDirectory + pid_str + kStatFilename); 
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> word1 >> word2;
      if (key == pid_string){
        while(linestream >> value){
          value_set.push_back(value);
        }
      }
    }      
  }

  if (value_set.size()> 14){
    long utime = value_set[10];  //#14
    long stime = value_set[11];  //#15
    long cutime = value_set[12];  //#16
    long cstime = value_set[13];  //#17

    long total_active = utime + stime + cutime + cstime;
 
    return total_active;
  }
  else{
    return 0;
  }
}
   

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpu_data_set;
  std::string line;
  std::string key;
  std::string value;
  std::ifstream filestream(kProcDirectory + kStatFilename); 
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key) {
        if (key == "cpu"){
          for(int i=0; i<10; i++){
            linestream >> value;
            cpu_data_set.push_back(value);
          }
        } 
      }      
    }
  }
  return cpu_data_set; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  int process_tot;
  std::string line;
  std::string key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename); 
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes"){
          process_tot = value;
        } 
      }      
    }
  }
  return process_tot; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  int process_run;
  std::string line;
  std::string key;
  int value;
  std::ifstream filestream(kProcDirectory + kStatFilename); 
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running"){
          process_run = value;
        } 
      }      
    }
  }
  return process_run;
   }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::string pid_str = '/' + std::to_string(pid);
  std::string cmd;
  std::string line;
  std::ifstream filestream(kProcDirectory + pid_str + kCmdlineFilename); 
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::istringstream linestream(line);
      linestream >> cmd;
      std::replace(cmd.begin(), cmd.end(), '_', ' ');
    }      
  }
  
  return cmd; }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  std::string pid_str = '/' + std::to_string(pid);
  int ram, ram_mb;
  std::string ram_MB;
  std::string line;
  std::string key;
  int value;
  std::ifstream filestream(kProcDirectory + pid_str + kStatusFilename); 
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:"){
          ram = value;
        } 
      }      
    }
  }

  ram_mb = ram/1000;
  ram_MB = std::to_string(ram_mb);
  return ram_MB; }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  std::string pid_str = '/' + std::to_string(pid);
  std::string uid;
  std::string line;
  std::string key;
  std::string value;
  std::ifstream filestream(kProcDirectory + pid_str + kStatusFilename); 
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:"){
          uid = value;
        } 
      }      
    }
  }
  return uid;
 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  //Find Uid 
  std::string uid;
  uid = LinuxParser::Uid(pid);
  // find User
  std::string line;
  std::string x,key;
  std::string value,user_name;
  std::ifstream filestream(kPasswordPath); 
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> value >> x >> key ) {
        if (key == uid){
          user_name = value;
        } 
      }      
    }
  }
  
  return user_name; }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  std::string pid_str = '/' + std::to_string(pid);
  std::string pid_string = std::to_string(pid);
  std::vector <long> value_list;
  std::string key,word1,word2;
  std::string line;
  long value;
  std::ifstream filestream(kProcDirectory + pid_str + kStatFilename); 
  if (filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> word1 >> word2;
      if (key == pid_string){
        while(linestream >> value){
          value_list.push_back(value);
        }
      }
    }      
  }

  if (value_list.size()> 19){
    long start_time = value_list[18];
    long time = start_time/sysconf(_SC_CLK_TCK);

    return time;
  }
  else {
    return 0;
  }

}

