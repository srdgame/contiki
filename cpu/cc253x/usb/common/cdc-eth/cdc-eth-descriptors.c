#include "descriptors.h"
#include <cdc.h>
#include <contiki-conf.h>
#include <usb-arch.h>

#ifndef USB_ETH_ENDPOINT_INT 
#define USB_ETH_ENDPOINT_INT 0x83
#endif

#ifndef USB_ETH_ENDPOINT_DATA_IN
#define USB_ETH_ENDPOINT_DATA_IN 0x81
#endif

#ifndef USB_ETH_ENDPOINT_DATA_OUT
#define USB_ETH_ENDPOINT_DATA_OUT 0x02
#endif

const struct configuration_st {
  struct usb_st_configuration_descriptor configuration;
  struct usb_st_interface_descriptor comm;
  struct usb_cdc_header_func_descriptor header;
  struct usb_cdc_union_func_descriptor union_descr;
  struct usb_cdc_ethernet_func_descriptor ethernet;
#if 1
  struct usb_st_endpoint_descriptor ep_notification;
#endif
  struct usb_st_interface_descriptor data;
  struct usb_st_endpoint_descriptor ep_in;
  struct usb_st_endpoint_descriptor ep_out;
} BYTE_ALIGNED configuration_block =
  {
    /* Configuration */
    {
      sizeof(configuration_block.configuration),
      CONFIGURATION,
      sizeof(configuration_block),
      2,
      1,
      0,
      0x80,
      50
    },
    {
      sizeof(configuration_block.comm),
      INTERFACE,
      0,
      0,
      1,
      CDC,
       ETHERNET_NETWORKING_CONTROL_MODEL,
      0,
      0
    },
    {
      sizeof(configuration_block.header),
      CS_INTERFACE,
      CDC_FUNC_DESCR_HEADER,
      0x0110
    },
    {
      sizeof(configuration_block.union_descr),
      CS_INTERFACE,
      CDC_FUNC_DESCR_UNION,
      0, /* Master */
      {1}  /* Slave */
    },
    {
      sizeof(configuration_block.ethernet),
      CS_INTERFACE,
      CDC_FUNC_DESCR_ETHERNET,
      4,
      0, /* No statistics */
      UIP_CONF_BUFFER_SIZE - UIP_CONF_LLH_LEN + 14,
      0, /* No multicast filters */
      0 /* No wake-up filters */
    },
    {
      sizeof(configuration_block.ep_notification),
      ENDPOINT,
      USB_ETH_ENDPOINT_INT,
	  0x03, 
      8,
      100
    },
    {
      sizeof(configuration_block.data),
      INTERFACE,
      1,
      0,
      2,
      CDC_DATA,
      0,
      TRANSPARENT_PROTOCOL,
      0
    },
    {
      sizeof(configuration_block.ep_in),
      ENDPOINT,
      USB_ETH_ENDPOINT_DATA_IN,
	  0x02,
      64,
      0
    },
    {
      sizeof(configuration_block.ep_out),
      ENDPOINT,
	  USB_ETH_ENDPOINT_DATA_OUT,
      0x02,
      64,
      0
    }
          
  };

const struct usb_st_configuration_descriptor const *configuration_head =
(struct usb_st_configuration_descriptor const*)&configuration_block;
