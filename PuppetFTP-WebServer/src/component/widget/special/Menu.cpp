#include "Menu.h"
#include <QDebug>

namespace UI {

Menu::Menu() {
    _containerType = Container::DIV;
}

Menu::Menu(const Container::TYPE& type) {
    _containerType = type;
}

Menu::~Menu() {
    removeAllMenus();
    removeAllSections();
}

List*                                          Menu::getMenu(const QString& name) const {
    if (_widgetMenu.contains(name))
        return _widgetMenu[name];
    return NULL;
}

QMap<QString, List*>                           Menu::getMenus()                              const { return _widgetMenu;       }
Title*                                         Menu::getSection(const QString& section)      const { return _section[section]; }
QMap<QString, Title*>                          Menu::getSections()                           const { return _section;          }
Container::TYPE                                Menu::getContainerType()                      const { return _containerType;    }

void                                           Menu::addMenu(const QString& section, Link* widget) {
    Container* div = new Container(Container::NONE);
    div->addWidget(widget);
    addMenu(section, div);
}

void                                           Menu::addMenu(const QString& section, Container* widget) {
    if (!_sectionOrder.contains(section)) {
        addSection(section, "");
    }
    if (!_widgetMenu.contains(section)) {
        _widgetMenu[section] = new List();
    }

    _widgetMenu[section]->addWidget(widget);
}

void                                           Menu::addMenu(const QString& section, List* list) {
    if (_widgetMenu.contains(section))
        delete _widgetMenu[section];
    _widgetMenu[section] = list;
}

void                                           Menu::addSection(const QString& section, const QString& name) {
    _section[section] = new Title(name);
    if (_sectionOrder.contains(section))
        _sectionOrder.removeAll(section);
    _sectionOrder << section;
}

void                                           Menu::setContainerType(const Container::TYPE& type) {
    _containerType = type;
}

void                                           Menu::removeMenu(const QString& name) {
    if (_widgetMenu.contains(name)) {
        delete _widgetMenu[name];
        _widgetMenu.remove(name);
    }
}

void                                           Menu::removeAllMenus() {
    for (QMap<QString, List*>::iterator it = _widgetMenu.begin(); it != _widgetMenu.end(); it++) {
        delete it.value();
    }
    _widgetMenu.clear();
}

void                                           Menu::removeSection(const QString& section) {
    if (_section.contains(section)) {
        delete _section[section];
        _section.remove(section);
        _sectionOrder.removeAll(section);
    }
}

void                                           Menu::removeAllSections() {
    for (QMap<QString, Title*>::iterator it = _section.begin(); it != _section.end(); it++) {
        delete it.value();
        _sectionOrder.removeAll(it.key());
    }
    _section.clear();
}

QStringList                                    Menu::getSectionOrder()                      const { return _sectionOrder;         }

void                                           Menu::setSectionOrder(const QStringList& order) {
    _sectionOrder.clear();
    _sectionOrder.append(order);
}

QString                                        Menu::render() const {
    QString res;
    QMap<Container::TYPE, QString> block;
    block[Container::DIV]        = "div";
    block[Container::SECTION]    = "section";
    block[Container::ASIDE]      = "aside";
    block[Container::HEADER]     = "header";
    block[Container::FOOTER]     = "footer";
    block[Container::NAV]        = "nav";
    block[Container::PARAGRAPH]  = "p";
    block[Container::NONE]       = "div";

    for (QStringList::const_iterator sectionName = _sectionOrder.begin(); sectionName != _sectionOrder.end(); sectionName++) {

        if (_widgetMenu.contains(*sectionName)) {
            res.append(_section[(*sectionName)]->render());
            if (_containerType != Container::NONE || (_containerType == Container::NONE && !_attributes.empty())) {
                res.append("<" + block[_containerType] + renderAttribute() + ">\n");
            }

            res.append(_widgetMenu[(*sectionName)]->render());

            if (_containerType != Container::NONE || (_containerType == Container::NONE && !_attributes.empty())) {
                res.append("</" + block[_containerType] + ">\n");
            }
        }
    }

    return res;
}

} // namespace UI
