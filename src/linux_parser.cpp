#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

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

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {   
  string type, tot, free, line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> type >> tot;
    std::getline(stream, line);
    linestream.str(line);
    linestream >> type >> free;
  }
  stream.close();
  return (std::stof(tot) - std::stof(free))/std::stof(tot);
}

// Read and return the system uptime
long LinuxParser::UpTime() {   
  string val("0"), line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> val;
  }
  stream.close();
  return std::stol(val);
}

// Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return sysconf(_SC_CLK_TCK); }

// Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) { 
  int counter(1);
  long aj(0);
  string val("0"), line;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while(linestream >> val) {
      if(counter == (int)LinuxParser::ProcessStat::utime) {
        aj += stol(val);
      }
      else if(counter == (int)LinuxParser::ProcessStat::stime) {
        aj += stol(val);
      }
      else if(counter == (int)LinuxParser::ProcessStat::cutime) {
        aj += stol(val);
      }
      else if(counter == (int)LinuxParser::ProcessStat::cstime) {
        aj += stol(val);
        break;
      }
      counter++;
    }
  }
  stream.close();
  return aj;
}

// Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {   
  string val, line;
  std::vector<string> raw;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> val;
    while(linestream >> val)
      raw.push_back(val);
  }
  stream.close();
  return raw;
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() { return LinuxParser::Pids().size(); }

// Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  auto proc_list = LinuxParser::Pids();
  string type, val, line;
  int count(0);
  for(const auto& proc : proc_list) {
    std::ifstream stream(kProcDirectory+std::to_string(proc)+kStatusFilename);
    if (stream.is_open()) {
      while (std::getline(stream, line)) {
        std::istringstream linestream(line);
        linestream >> type >> val;
        if(type == "State:") {
          if(val == "R") {
            count++;
          }
          break;
        }
      }
    }
    stream.close();
  }
  return count;
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  string val, line;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    stream.close();
  }
  return line;
}

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  string type, val("0"), line;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> type >> val;
      if(type == "VmSize:") {
        break;
      }
    }
  }
  stream.close();
  return to_string(stoi(val)/1024);
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  string type, val("0"), line;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> type >> val;
      if(type == "Uid:") {
        break;
      }
    }
  }
  stream.close();
  return val;
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  string key = LinuxParser::Uid(pid);
  string usrname, tmp, usrid, line;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> usrname >> tmp >> usrid;
      if(usrid == key) {
        break;
      }
    }
  }
  stream.close();
  return usrname;
}

long LinuxParser::UpTime(int pid) { 
  int counter(1);
  string val("0"), line;
  std::ifstream stream(kProcDirectory+std::to_string(pid)+kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while(linestream >> val) {
      if(counter == (int)LinuxParser::ProcessStat::starttime) {
        break;
      }
      else {counter++;}
    }
  }
  stream.close();
  return std::stol(val);
}