#include "metaplugin.h"

/*!
    \class MetaPlugin
    \brief The MetaPlugin abstract class is a Plugin which can provide a MetaConfig object instance

    The implementation class must provide MetaConfigObject instance througt the virtual MetaConfig * getMetaConfigInstance()
 */

MetaPlugin::MetaPlugin()
{
    setType(QLatin1String(META_PLUGIN));
}
