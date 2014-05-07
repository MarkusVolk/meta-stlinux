FILESEXTRAPATHS := "${THISDIR}/udev"

PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI += " \
    file://udev-builtin-input_id.patch \
"

