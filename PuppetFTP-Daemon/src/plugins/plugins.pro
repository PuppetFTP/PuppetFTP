TEMPLATE = subdirs

FTP-DRIVERS += proftpd
FTP-DRIVERS += vsftpd

for(driver, FTP-DRIVERS) {
    exists($$driver) {
        SUBDIRS += $$driver
    } else {
        message(Ftp driver folder ($$driver) not found.)
    }
}
