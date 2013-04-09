/*
 * IServerForm.h
 *
 *  Created on: 15 nov. 2012
 *      Author: laplace
 */

#ifndef ISERVERFORM_H_
#define ISERVERFORM_H_

#include "IServerConfigurationProvider.h"

namespace Widget {
namespace ServerConfig {

class IServerForm {
public:
    virtual ~IServerForm();
    virtual void bind(IServerConfigurationProvider* server) = 0;
};

} // namespace ServerConfig
} // namespace Widget

#endif /* ISERVERFORM_H_ */
