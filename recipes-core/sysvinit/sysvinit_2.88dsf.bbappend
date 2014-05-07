FILESEXTRAPATHS := "${THISDIR}/files"

SRC_URI_append = " \
                  file://devinit \
"

# we do not need this, because this cost boottime 
do_install_append() {
        install -d ${D}/bin
        install -m 755 ${WORKDIR}/devinit ${D}/bin
        find  ${D}${sysconfdir}/rc* -name "*bootlogd" -exec rm {} \;
}

FILES_${PN} += " \
                /bin \
"
