FILESEXTRAPATHS := "${THISDIR}/files"

PRINC := "${@int(PRINC) + 4}"

SRC_URI_append = " \
                  file://devinit \
"

do_install_append() {
        install -d ${D}/bin
        install -m 755 ${WORKDIR}/devinit ${D}/bin
        find  ${D}${sysconfdir}/rc* -name "*bootlogd" -exec rm {} \; || true
}

FILES_${PN} += " \
                /bin \
"
