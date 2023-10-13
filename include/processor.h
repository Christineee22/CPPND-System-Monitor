#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:

int pre_user = 0;
int pre_nice = 0;
int pre_system = 0;
int pre_idle = 0;
int pre_iowait = 0;
int pre_irq = 0;
int pre_softirq = 0;
int pre_steal = 0;
};

#endif