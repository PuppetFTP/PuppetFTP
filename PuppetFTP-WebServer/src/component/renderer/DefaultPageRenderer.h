/*
 * DefaultPageRenderer.h
 *
 *  Created on: 06 nov. 2012
 *      Author: mtonnelier
 */

#ifndef DEFAULTPAGERENDERER_H
#define DEFAULTPAGERENDERER_H

#include "IOutputRenderer.h"
#include "PageRenderer.h"


namespace UI {

/**
 * Class Definition
 */
class DefaultPageRenderer: public PageRenderer {
protected:
    bool _disabledMenu;

public:
    DefaultPageRenderer(const bool disabled = false);
    ~DefaultPageRenderer();
};

} // namespace UI

#endif // DEFAULTPAGERENDERER_H
