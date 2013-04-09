#ifndef MENU_H
#define MENU_H

#include <QStringList>
#include "AbstractWidget.h"
#include "Widget.h"

namespace UI {

class Menu : public AbstractWidget {
protected:
    Container::TYPE         _containerType;
    QMap<QString, List*>    _widgetMenu;
    QStringList             _sectionOrder;
    QMap<QString, Title*>   _section;

public:
    Menu();
    Menu(const Container::TYPE& type = Container::DIV);
    virtual ~Menu();

    List*                                          getMenu(const QString& section)    const;
    QMap<QString, List*>                           getMenus()                         const;
    Title*                                         getSection(const QString& section) const;
    QMap<QString, Title*>                          getSections()                      const;
    Container::TYPE                                getContainerType()                 const;

    void                                           addMenu(const QString& section, Link* widget);
    void                                           addMenu(const QString& section, Container* widget);
    void                                           addMenu(const QString& section, List* list);
    void                                           addSection(const QString& section, const QString& name);
    void                                           setContainerType(const Container::TYPE& type);

    void                                           removeMenu(const QString& section);
    void                                           removeAllMenus();
    void                                           removeSection(const QString& section);
    void                                           removeAllSections();

    QStringList                                    getSectionOrder() const;
    void                                           setSectionOrder(const QStringList& order);

    QString                                        render() const;
};

} // namespace UI

#endif // MENU_H
