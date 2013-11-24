DEFINES+=PROJECT_CONF_H=\"project-conf.h\"

# We need uIPv6, therefore we also need banking
HAVE_BANKING=1
UIP_CONF_IPV6=1
UIP_CONF_RPL=1

CONTIKI_PROJECT = crosso-dev

all: $(CONTIKI_PROJECT)

APPS = serial-shell
CONTIKI = ../..

include $(CONTIKI)/Makefile.include
