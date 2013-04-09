#include "Table.h"

namespace UI {

Table::Table() {
}

Table::Table(const Table& obj) {
    _rows       = obj.getRows();
    _header     = obj.getHeader();
    _footer     = obj.getFooter();
    _attributes = obj.getAttributes();
}

Table& Table::operator=(const Table& obj) {
    _rows       = obj.getRows();
    _header     = obj.getHeader();
    _footer     = obj.getFooter();
    _attributes = obj.getAttributes();
    return *this;
}

Table::~Table() {
    for (QList<Container*>::iterator it = _header.begin(); it != _header.end(); ++it) {
        delete (*it);
    }
    _header.clear();
    for (QList<Container*>::iterator it = _footer.begin(); it != _footer.end(); ++it) {
        delete (*it);
    }
    _footer.clear();
    for (QList< QList<Container*> >::iterator tr = _rows.begin(); tr != _rows.end(); ++tr) {
        for (QList<Container*>::iterator td = (*tr).begin(); td != (*tr).end(); ++td) {
            delete (*td);
        }
        (*tr).clear();
    }
    _rows.clear();
}

void                       Table::addHeader(Container* head)            {
    head->setNodeType(Container::NONE);
    _header.push_back(head);
}

void                       Table::addFooter(Container* foot)            {
    foot->setNodeType(Container::NONE);
    _footer.push_back(foot);
}

void                       Table::setHeader(QList<Container*> header)  {
    for (QList<Container*>::iterator it = header.begin(); it != header.end(); ++it) {
        (*it)->setNodeType(Container::NONE);
    }
    _header = header;
}

void                       Table::setFooter(QList<Container*> footer)  {
    for (QList<Container*>::iterator it = footer.begin(); it != footer.end(); ++it) {
        (*it)->setNodeType(Container::NONE);
    }
    _footer = footer;
}

void                       Table::addRow(QList<Container*> row)              {
    for (QList<Container*>::iterator it = row.begin(); it != row.end(); ++it) {
        (*it)->setNodeType(Container::NONE);
    }
    _rows.push_back(row);
}

QList<Container*>          Table::getHeader()                           const { return _header;          }
QList<Container*>          Table::getFooter()                           const { return _footer;          }
QList< QList<Container*> > Table::getRows()                             const { return _rows;            }

QString Table::render() const {
    QString res;

    res.append("<table"+renderAttribute()+">");

    if (!_header.empty()) {
        res.append("    <thead>\n");
        res.append("        <tr>\n");
        for (QList<Container*>::const_iterator td = _header.begin(); td != _header.end(); ++td) {
            res.append("            <th>" + (*td)->render() + "</th>\n");
        }
        res.append("        </tr>\n");
        res.append("    </thead>\n");
    }

    if (!_footer.empty()) {
        res.append("    <tfoot>\n");
        res.append("        <tr>\n");
        for (QList<Container*>::const_iterator td = _footer.begin(); td != _footer.end(); ++td) {
            res.append("            <td>" + (*td)->render() + "</td>\n");
        }
        res.append("        </tr>\n");
        res.append("    </tfoot>\n");
    }

    res.append("    <tbody>\n");
    for (QList< QList<Container*> >::const_iterator tr = _rows.begin(); tr != _rows.end(); ++tr) {
        res.append("        <tr>\n");
        for (QList<Container*>::const_iterator td = (*tr).begin(); td != (*tr).end(); ++td) {
            res.append("            <td>" + (*td)->render() + "</td>\n");
        }
        res.append("        </tr>\n");
    }
    res.append("    </tbody>\n");

    res.append("</table>\n");
    return res;
}


} // namespace UI
