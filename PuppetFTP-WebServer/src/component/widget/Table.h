#ifndef TABLE_H
#define TABLE_H

#include "AbstractWidget.h"
#include "Container.h"

namespace UI {

class Table : public AbstractWidget {
protected:
    QList< QList<Container*> > _rows;
    QList<Container*>          _header;
    QList<Container*>          _footer;

public:
    Table();
    Table(const Table& obj);
    Table& operator=(const Table& obj);
    virtual ~Table();

    void                       addHeader(Container* head);
    void                       addFooter(Container* foot);
    void                       setHeader(QList<Container*> header);
    void                       setFooter(QList<Container*> footer);
    void                       addRow(QList<Container*> row);
    QList<Container*>          getHeader() const;
    QList<Container*>          getFooter() const;
    QList< QList<Container*> > getRows()   const;
    QString                    render()    const;
};

} // namespace UI

#endif // TABLE_H
