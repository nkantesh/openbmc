pkg_postinst:${PN}:append() {
  mkdir -p $D$systemd_system_unitdir/obmc-host-crash@0.target.wants
  mkdir -p $D$systemd_system_unitdir/obmc-host-timeout@0.target.wants
  mkdir -p $D$systemd_system_unitdir/obmc-host-startmin@0.target.wants
  mkdir -p $D$systemd_system_unitdir/obmc-host-stop@0.target.wants

	# The obmc-host-crash target is repurposed for the memory preserving reboot
	# feature when it is enabled. If not enabled, then install the standard
	# debug collector checkstop service for basic error reporting
	if [ "${@bb.utils.filter('DISTRO_FEATURES', 'mpreboot', d)}" != mpreboot ]; then
		LINK="$D$systemd_system_unitdir/obmc-host-crash@0.target.wants/openpower-debug-collector-checkstop@0.service"
		TARGET="../openpower-debug-collector-checkstop@.service"
		ln -s $TARGET $LINK
	fi

	LINK="$D$systemd_system_unitdir/obmc-host-timeout@0.target.wants/openpower-debug-collector-watchdog@0.service"
	TARGET="../openpower-debug-collector-watchdog@.service"
	ln -s $TARGET $LINK

	if [ "${@bb.utils.filter('OBMC_MACHINE_FEATURES', 'phal', d)}" != 'phal' ]; then
		LINK="$D$systemd_system_unitdir/obmc-host-timeout@0.target.wants/openpower-debug-collector-watchdog-timeout@0.service"
		TARGET="../openpower-debug-collector-watchdog-timeout@.service"
		ln -s $TARGET $LINK
	fi
  if [ "${@bb.utils.filter('PACKAGECONFIG', 'openpower_dump_collection', d)}" == openpower_dump_collection ]; then
         LINK="$D$systemd_system_unitdir/obmc-host-startmin@0.target.wants/org.open_power.Dump.Manager.service"
         TARGET="../org.open_power.Dump.Manager.service"
         ln -s $TARGET $LINK
  fi

  LINK="$D$systemd_system_unitdir/obmc-host-stop@0.target.wants/clear_hostdumps_poweroff.service"
  TARGET="../clear_hostdumps_poweroff.service"
  ln -s $TARGET $LINK
}

pkg_prerm:${PN}:append() {
	if [ "${@bb.utils.filter('DISTRO_FEATURES', 'mpreboot', d)}" != mpreboot ]; then
		LINK="$D$systemd_system_unitdir/obmc-host-crash@0.target.wants/openpower-debug-collector-checkstop@0.service"
		rm $LINK
	fi
	LINK="$D$systemd_system_unitdir/obmc-host-timeout@0.target.wants/openpower-debug-collector-watchdog@0.service"
	rm $LINK
	if [ "${@bb.utils.filter('OBMC_MACHINE_FEATURES', 'phal', d)}" != 'phal' ]; then
		LINK="$D$systemd_system_unitdir/obmc-host-timeout@0.target.wants/openpower-debug-collector-watchdog-timeout@0.service"
		rm $LINK
	fi
  if [ "${@bb.utils.filter('DISTRO_FEATURES', 'mpreboot', d)}" != mpreboot ]; then
          LINK="$D$systemd_system_unitdir/obmc-host-startmin@0.target.wants/org.open_power.Dump.Manager.service"
          rm $LINK
  fi
  LINK="$D$systemd_system_unitdir/obmc-host-stop@0.target.wants/clear_hostdumps_poweroff.service"
  rm $LINK
}
