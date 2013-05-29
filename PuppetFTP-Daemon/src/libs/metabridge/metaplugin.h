#ifndef METAPLUGIN_H
#define METAPLUGIN_H

#include "metaconfig.h"
#include "plugin.h"

#define META_PLUGIN "MetaPlugin"

class MetaPlugin : public Plugin
{
    Q_OBJECT

public:
    MetaPlugin();

    virtual MetaConfig * getMetaConfigInstance() = 0;
};

#endif // METAPLUGIN_H
