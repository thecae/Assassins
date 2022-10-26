#ifndef ASSASSINS_V2_LOG_H
#define ASSASSINS_V2_LOG_H

#include <fstream>
#include <sstream>

class Log {
private:
  std::stringstream pLog;
  std::stringstream aLog;

public:
  explicit Log();

  ~Log();

  void playerLog(const std::string &info);

  void activityLog(const std::string &category, const std::string &info);
};

#endif // ASSASSINS_V2_LOG_H
