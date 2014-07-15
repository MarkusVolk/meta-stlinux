require conf/machine/include/tune-sh4.inc
TARGET_ARCH = "sh4"
STLINUX_SH_UPD_SRPMS = "http://ftp.stlinux.com/pub/stlinux/2.4/updates/SRPMS"
STLINUX_SH_UPD_RPMS = "http://ftp.stlinux.com/pub/stlinux/2.4/updates/RPMS/sh4/"
STM_PATCH_STR ??= "0214"
LINUX_VERSION ??= "2.6.32.61"

PREFERRED_VERSION_stlinux24-${MACHINE} = "${LINUX_VERSION}-stm24-${STM_PATCH_STR}"
PREFERRED_VERSION_linux-libc-headers = "2.6.32"
PREFERRED_PROVIDER_virtual/kernel = "stlinux24-${MACHINE}"
PREFERRED_PROVIDER_openssl = "openssl"
PREFERRED_PROVIDER_libcrypto = "openssl"
PREFERRED_PROVIDER_libssl = "openssl"
PREFERRED_PROVIDER_udev ?= "${@base_contains('DISTRO_FEATURES','systemd','systemd','udev',d)}"
PREFERRED_PROVIDER_curl ?= "curl"

PREFERRED_VERSION_glibc = "2.10"
PREFERRED_VERSION_glibc ?= "${GLIBCVERSION}"
PREFERRED_VERSION_glibc-locale ?= "${GLIBCVERSION}"
PREFERRED_VERSION_glibc-nativesdk ?= "2.10"
PREFERRED_VERSION_glibc-initial ?= "${GLIBCVERSION}"
PREFERRED_VERSION_glibc-initial-nativesdk ?= "2.10"

USE_VT = "0"
MACHINE_FEATURES = "kernel26 ext2 alsa usbhost serial legacykernel wifi wifiusblegacy"

SERIAL_CONSOLE = "115200 ttyAS0"

KERNEL_IMAGETYPE = "uImage"

# save some extra space, kernel has its own mtd partion
RDEPENDS_kernel-base = ""

UBI_VOLNAME = "rootfs"
MKUBIFS_ARGS = "-m 2048 -e 126976 -c 4096 -F"
UBINIZE_ARGS = "-m 2048 -p 128KiB"

JFFS2_ERASEBLOCK = "0x20000"
JFFS2_SUM_EXTRA_ARGS = "-p -e 0x20000"
EXTRA_IMAGECMD_jffs2 = "-p -U --no-cleanmarkers"

INHERIT += "usb_image-spark71xx"
IMAGE_FSTYPES ?= "tar.gz ubi ext2 jffs2.sum spark71xx-usbimg"

IMAGE_CLASSES += "usb_image-spark71xx"
INITRAMFS_FSTYPES = "ext2.gz spark-updt"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += " \
                                     stlinux24-sh4-stx7111-fdma-firmware \
                                     stlinux24-sh4-stmfb-firmware-stx7111 \
                                     stslave-fw \
                                     fp-control \
                                     stfbcontrol \
                                     ustslave \
                                     libmmeimage \
                                     lirc \
                                     lrzsz \
                                     mtd-utils \
                                     mtd-utils-jffs2 \
                                     mtd-utils-ubifs \
                                     mtd-utils-misc \
                                     tdt-driver \
"

MACHINE_EXTRA_RRECOMMENDS = " \
        gst-plugin-dvbmediasink \
        tdt-driver \
        kernel-modules \
        "
GCCVERSION ?= "4.8%"

#####
##### With eglibc-2.18 / OLDEST_KERNEL=2.6.12 (default), I had strange
##### problems with user name resolution, apparently libnss_files-2.18.so
##### was incompatible and could not be used (????!!!)
#####
##### I'm actually not sure if it is a eglibc-2.18 problem, solved by
##### downgrading to 2.17 or if the "OLDEST_KERNEL=2.6.32" solves the
##### issue, as I have changed both at once, but now my box works fine.
#####
##
## eglibc-2.18 gives me strange results wrt. user name resolution etc.
##
EGLIBCVERSION ?= "2.19"
##
## stlinux is configured like that:
OLDEST_KERNEL = "2.6.32"



##
## This would not work unless the kernel supports open by handle syscall
## http://lwn.net/Articles/390863/ 
##
#DISTRO_FEATURES_append = " systemd"
#VIRTUAL-RUNTIME_init_manager = "systemd"
#DISTRO_FEATURES_BACKFILL_CONSIDERED = "sysvinit"

##
## gcc-4.8 as in dora or newer (yocto-1.5+) will fail compiling the kernel
## with "error: 'asm' operand requires impossible reload"
## seems to be http://gcc.gnu.org/bugzilla/show_bug.cgi?id=58314
## which is not fixed in any released 4.8.x, so just use 4.7 for now:
##
## we workaround this issue by patching the kernel source
GCCVERSION ?= "4.8%"

