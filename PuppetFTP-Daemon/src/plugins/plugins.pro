TEMPLATE = subdirs

FTP-DRIVERS += proftpd vsftpd

for(driver, FTP-DRIVERS) {
    exists($$driver) {
        SUBDIRS += $$driver
    } else {
        message(Ftp driver folder ($$driver) not found.)
    }
}

