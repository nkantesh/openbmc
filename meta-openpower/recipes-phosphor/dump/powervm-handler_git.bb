SUMMARY = "OpenPOWER VM handlers"

DESCRIPTION = \
    "This is a common repository for virtual machine handling"

HOMEPAGE = "https://github.com/ibm-openbmc/powervm-handler"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

PR = "r1"
PV = "0.1+git${SRCPV}"

SRC_URI = "git://github.com/ibm-openbmc/powervm-handler;branch=main"
SRCREV = "47d718de1b205d63a17f4c3d242dab9a687bc926"

S = "${WORKDIR}/git"

inherit meson
inherit systemd

DEPENDS += " \ 
        phosphor-dbus-interfaces \
        phosphor-logging \
        fmt \
        pldm \
        sdbusplus \
        systemd \
        "
SYSTEMD_SERVICE:${PN} = "pvm_dump_offload@.service"
FILES:${PN}:append = " ${systemd_system_unitdir}/* "
