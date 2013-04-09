/*
 * NetworkForm.h
 *
 *  Created on: 15 nov. 2012
 *      Author: laplace
 */

#ifndef NETWORKFORM_H_
#define NETWORKFORM_H_

#include "BaseForm.h"

namespace Widget {
namespace ServerConfig {

class NetworkForm: public Widget::Form::BaseForm {
public:
    virtual ~NetworkForm();
    NetworkForm();

    virtual void bind(IServerConfigurationProvider* server);
};

} // namespace ServerConfig
} // namespace Widget

#endif /* NETWORKFORM_H_ */
