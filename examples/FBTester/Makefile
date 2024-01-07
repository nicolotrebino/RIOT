
# name of your application
APPLICATION = FBTester

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

include $(RIOTBASE)/tests/sys/Makefile.sys_common

# Set to 1 to disable the feedback scheduling module
NOFB ?= 0

ifneq (1,$(NOFB))
  USEMODULE += sched_feedback
endif
USEMODULE += ztimer_msec

# microbit qemu failing currently
TEST_ON_CI_BLACKLIST += microbit

include $(RIOTBASE)/Makefile.include

# Increase time between feedback calls so prints are not interrupted for
# slow CPU's
ifneq (,$(filter ztimer_usec,$(USEMODULE)))
  CFLAGS += -DSCHED_FB_TIMEOUT=100*1000
else
ifneq (,$(filter ztimer_msec,$(USEMODULE)))
  CFLAGS += -DSCHED_FB_TIMEOUT=100
endif
endif
