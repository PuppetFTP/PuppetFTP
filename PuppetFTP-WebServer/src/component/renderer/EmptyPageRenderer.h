#ifndef EMPTYPAGERENDERER_H
#define EMPTYPAGERENDERER_H

#include "IOutputRenderer.h"
#include "PageRenderer.h"


namespace UI {

/**
 * Class Definition
 */
class EmptyPageRenderer: public PageRenderer {
public:
    EmptyPageRenderer();
    virtual ~EmptyPageRenderer();
};

} // namespace UI

#endif // EMPTYPAGERENDERER_H
