# SPDX-License-Identifier: GPL-2.0
# Copyright (c)  2018 Intel Corporation

#
# Intel(R) I225-LM/I225-V 2.5G Ethernet Controller
#

obj-m += igc-ethercat.o

igc-ethercat-objs := igc_main.o igc_mac.o igc_i225.o igc_base.o igc_nvm.o igc_phy.o \
igc_diag.o igc_ethtool.o igc_ptp.o igc_dump.o igc_tsn.o igc_xdp.o

EXTRA_CFLAGS=-I$(src)/../../../../../../
KBUILD_EXTRA_SYMBOLS=$(src)/../../../../../../Module.symvers
