/*
 * IOutputRender.h
 *
 *  Created on: 06 nov. 2012
 *      Author: mtonnelier
 */


#ifndef IOUTPUTRENDERER_H
#define IOUTPUTRENDERER_H

#include <QString>

namespace UI {

class IOutputRenderer {
public:
    virtual ~IOutputRenderer() {}

    virtual QByteArray render() const = 0;
};

} // namespace UI

#endif // IOUTPUTRENDERER_H
