#include "Notify.h"
#include "Text.h"
#include "Container.h"

namespace UI {

Notify::Notify() {
}

Notify::~Notify() {
}

void                                 Notify::addNotice(IInlinable* notice, SEVERITY severity)  { _notify[severity] << notice;            }
void                                 Notify::addNotice(QPair<QString, SEVERITY> notice)        { addNotice(notice.first, notice.second); }
void                                 Notify::addNotice(const QString& text, SEVERITY severity) { _notify[severity] << new Text(text);    }
QList<IInlinable*>                   Notify::getNotice(SEVERITY severity)                const { return _notify[severity];               }
QMap< Notify::SEVERITY, QList<IInlinable*> > Notify::getNotice()                         const { return _notify;                         }

QString                              Notify::render() const {
    Container* notice = new Container();
    notice->setId("notice");
    QMap<Notify::SEVERITY, QString> classes;
    classes[INFO]    = "info";
    classes[WARNING] = "warning";
    classes[ERROR]   = "error";
    classes[NONE]    = "";

    for ( int severityInt = INFO; severityInt <= NONE; ++severityInt ) {
       SEVERITY severity = static_cast<SEVERITY>(severityInt);

       if (_notify.contains(severity) && !_notify[severity].empty()) {
           for (QList<IInlinable*>::const_iterator it = (_notify[severity]).begin(); it != (_notify[severity]).end(); it++) {
               dynamic_cast<IWidget*>(*it)->addClass(classes[severity]);
               notice->addWidget(dynamic_cast<IWidget*>(*it));
           }
       }
    }
    return notice->render();
}

} // namespace UI
