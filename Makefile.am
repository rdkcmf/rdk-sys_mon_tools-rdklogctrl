##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################

SUBDIRS =
DIST_SUBDIRS =

# the list of header files that belong to the library (to be installed later)

IARM        = /usr/include/rdk/iarmbus
IARM_MGR    = /usr/include/rdk/iarmmgrs

AM_CFLAGS = -I=$(IARM) -I=$(IARM_MGR)/../iarmmgrs-hal

bin_PROGRAMS = rdklogctrl

rdklogctrl_SOURCES=iARM_RDKLogControl.c
rdklogctrl_LDADD = -ldbus-1 -lstdc++ -lIARMBus -lpthread

## IPK generation Support
rdklogctrl_IPK_OUTDIR = $(abs_top_builddir)/ipk
rdklogctrl_IPK_STAGING_DIR=$(abs_top_builddir)/staging_dir
rdklogctrl_IPK_TMP_DIR=$(rdklogctrl_IPK_STAGING_DIR)/ipk

rdklogctrl_CONTROL_FILES = control
rdklogctrl_IPK_FILES  = debian-binary control.tar.gz data.tar.gz
rdklogctrl_IPK_OUTPUT = rdklogctrl.ipk

WRKDIR          =       .
SYS_USR_DIR     =       /usr

package_ipk:
	echo "Generating IPK Package"
	install -d $(rdklogctrl_IPK_STAGING_DIR)$(SYS_USR_DIR)/bin
	install -m 0755 $(WRKDIR)/rdklogctrl $(rdklogctrl_IPK_STAGING_DIR)$(SYS_USR_DIR)/bin
	cd $(rdklogctrl_IPK_STAGING_DIR)$(SYS_USR_DIR) && ln -sf /usr/bin/rdklogctrl $(rdklogctrl_IPK_STAGING_DIR) && cd -
	tar -czvf $(rdklogctrl_IPK_OUTDIR)/data.tar.gz -C $(rdklogctrl_IPK_STAGING_DIR) .
	tar -czvf $(rdklogctrl_IPK_OUTDIR)/control.tar.gz -C $(rdklogctrl_IPK_OUTDIR) $(rdklogctrl_CONTROL_FILES)
	cd $(rdklogctrl_IPK_OUTDIR) && ar cr $(rdklogctrl_IPK_OUTPUT) $(rdklogctrl_IPK_FILES) && cd -
	rm -rf $(rdklogctrl_IPK_STAGING_DIR)
