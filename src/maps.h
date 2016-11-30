#ifndef maps
#define maps

#include "libcec.h"
#include <cstdint>
#include <cstdlib>
#include <string>
#include <boost/bimap.hpp>
#include <asm/types.h>
#include <linux/input.h>

typedef boost::bimap<CEC::cec_user_control_code, std::string> cec_code_map;
typedef std::map<const __u16, std::list<__u16>> uinput_cec_map;
typedef std::map<const std::string, int> uinput_code_map;

class Maps {
public:
  Maps() {};
  ~Maps() {};
  
  static const std::map<const std::string, int> uinputKeyMap;
  static std::map<const __u16, std::list<__u16>> uinputCecMap;
  const static cec_code_map cecUserControlCodeName;
  
private:
  static const std::map<const std::string, int> setupKeyMap();
  static std::map<const __u16, std::list<__u16>> setupUinputMap();
  static const cec_code_map & setupUserControlCodeName();
  

  
};

#endif //maps
