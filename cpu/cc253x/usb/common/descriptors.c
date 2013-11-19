#include "descriptors.h"
#include "cdc.h"
#include "usb-arch.h"

#ifndef USB_CDC_CONF_VID
#define USB_CDC_CONF_VID 0x0451
#endif
#ifndef USB_CDC_CONF_PID
#define USB_CDC_CONF_PID 0x16A8
#endif

const struct usb_st_device_descriptor device_descriptor =
  {
    sizeof(struct usb_st_device_descriptor),
    DEVICE,
    0x0210,
    CDC,
    0,
    0,
    CTRL_EP_SIZE,
	USB_CDC_CONF_VID,
	USB_CDC_CONF_PID,
    0x0010,
    2,
    1,
    3,
    1
  };


