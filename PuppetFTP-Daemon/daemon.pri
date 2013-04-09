!isEmpty(DAEMON_PRI_INCLUDED):error("daemon.pri already included")
DAEMON_PRI_INCLUDED = 1

defineReplace(cleanPath) {
    win32:1 ~= s|\\\\|/|g
    contains(1, ^/.*):pfx = /
    else:pfx =
    segs = $$split(1, /)
    out =
    for(seg, segs) {
        equals(seg, ..):out = $$member(out, 0, -2)
        else:!equals(seg, .):out += $$seg
    }
    return($$join(out, /, $$pfx))
}

isEmpty(DAEMON_LIBRARY_BASENAME) {
    DAEMON_LIBRARY_BASENAME = library
}

DAEMON_SRC_TREE = $$PWD
PLUGIN_SRC_TREE = $$PWD/src/plugins
LIBRARY_SRC_TREE = $$PWD/src/libs
NETWORK_SRC_TREE = $$PWD/../PuppetFTP-Common/Network/src

isEmpty(DAEMON_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    DAEMON_BUILD_TREE = $$cleanPath($$OUT_PWD)
    DAEMON_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

DAEMON_SERVICE_PATH = $$DAEMON_BUILD_TREE/bin
DAEMON_SERVICE_TARGET = puppetFtpd
DAEMON_LIBRARY_PATH = $$DAEMON_SERVICE_PATH/$$DAEMON_LIBRARY_BASENAME
DAEMON_PLUGIN_PATH = $$DAEMON_SERVICE_PATH/plugins

LIBS += -L$$DAEMON_LIBRARY_PATH

CONFIG(debug, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/debug-shared
CONFIG(release, debug|release):OBJECTS_DIR = $${OUT_PWD}/.obj/release-shared

CONFIG(debug, debug|release):MOC_DIR = $${OUT_PWD}/.moc/debug-shared
CONFIG(release, debug|release):MOC_DIR = $${OUT_PWD}/.moc/release-shared

RCC_DIR = $${OUT_PWD}/.rcc
UI_DIR = $${OUT_PWD}/.uic
