include conf/machine/include/ibm-power10-cpu.inc
OBMC_MACHINE_FEATURES += 'op-fsi'
PREFERRED_PROVIDER_virtual/obmc-host-ctl = "p9-host-start"
