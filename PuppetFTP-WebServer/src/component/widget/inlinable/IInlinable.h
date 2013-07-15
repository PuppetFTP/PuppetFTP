#ifndef IINLINABLE_H
#define IINLINABLE_H

#include "IWidget.h"

namespace UI {

class IInlinable {
public:
    virtual ~IInlinable() {}
    virtual QString  render() const = 0;
};

} // namespace UI

#endif // IINLINABLE_H
