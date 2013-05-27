TEMPLATE = subdirs
CONFIG += ordered

QT += core
QT -= gui

#pluginsystem is the last because dependencies of serverconfig
SUBDIRS += serverconfig
SUBDIRS += pluginsystem
SUBDIRS += metabridge
SUBDIRS += communication
