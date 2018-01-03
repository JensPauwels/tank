#
# Copyright (C) DPTechnics - All Rights Reserved
#
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
#
# Written by Daan Pape <Jens@dptechnics.com>, Jul 2017
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=spytank-server
PKG_RELEASE:=1

PKG_BUILD_DIR := $(KERNEL_BUILD_DIR)/$(PKG_NAME)
PKG_MAINTAINER := Jens Pauwels <jens@dptechnics.com>

PKG_BUILD_DEPENDS = wembed

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/spytank-server
  SECTION:=firmware
  CATEGORY:=Firmware
  TITLE:=Jens SpyTank Server
  DEPENDS:=+wembed
endef

define Package/spytank-server/description
  This package contains the server needed to control the spytank.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/spytank-server/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/spytank-server.init $(1)/etc/init.d/spytank-server

	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./files/spytank-server.config $(1)/etc/config/spytank-server

	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/spytank-server $(1)/usr/sbin/spytank-server
endef

$(eval $(call BuildPackage,spytank-server))
