#include "processor.h"
#include "linux_parser.h"
#include <string>
#include <vector>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    float totald, idled;
    float CPU_Precentage;

    int user;
    int nice;
    int system;
    int idle;
    int iowait;
    int irq;
    int softirq;
    int steal;
    std::vector<std::string> data = LinuxParser::CpuUtilization();

    user = std::stoi(data[0]);
    nice = std::stoi(data[1]);
    system = std::stoi(data[2]);
    idle = std::stoi(data[3]);
    iowait = std::stoi(data[4]);
    irq = std::stoi(data[5]);
    softirq = std::stoi(data[6]);
    steal = std::stoi(data[7]);

    // Idle
    int PrevIdle = pre_idle + pre_iowait;
    int Idle = idle + iowait;
    // Non-Idle
    int PrevNonIdle = pre_user + pre_nice + pre_system + pre_irq + pre_softirq + pre_steal;
    int NonIdle = user + nice + system + irq + softirq + steal;
    // Total
    int PrevTotal = PrevIdle + PrevNonIdle;
    int Total = Idle + NonIdle;
    // Differentiate
    totald = Total - PrevTotal;
    idled = Idle - PrevIdle;
    CPU_Precentage = (totald - idled)/totald;

    pre_user = user;
    pre_nice = nice;
    pre_system = system;
    pre_irq = irq;
    pre_softirq = softirq;
    pre_steal = steal;
    pre_idle = idle;
    pre_iowait = iowait;
 
    return CPU_Precentage; }