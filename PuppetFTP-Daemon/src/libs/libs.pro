TEMPLATE = subdirs
CONFIG += ordered

QT += core
QT -= gui

#abstactplugin is the last because dependencies of serverconfig
SUBDIRS =  communication serverconfig abstractplugin
