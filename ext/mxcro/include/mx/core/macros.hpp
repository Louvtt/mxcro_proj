#ifndef _MX_MACROS_HPP_
#define _MX_MACROS_HPP_

#include <iostream>

namespace mx
{

#define MX_LOG(msg) std::iostream << __FILE__ << ": " << msg << '\n';
#define MX_ERR(msg) std::iostream << "[ERROR]" << __FILE__ << ":" << msg << '\n';

} // namespace mx


#endif //_MX_MACROS_HPP_