/*
 * Copyright (c) 2012, Philippe Retornaz
 * Copyright (c) 2012, EPFL STI IMT LSRO1 -- Mobots group
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * \file
 *         Platform process which implements a UART-like functionality over
 *         the cc2531 dongle's USB hardware.
 *
 *         With it in place, putchar can be redirected to the USB and USB
 *         incoming traffic can be handled as input
 *
 * \author
 *         Philippe Retornaz (EPFL) - Original code
 *         George Oikonomou - <oikonomou@users.sourceforge.net>
 *           Turned this to a 'serial over USB' platform process
 */
#include "contiki.h"
/*---------------------------------------------------------------------------*/
static const struct {
  uint8_t size;
  uint8_t type;
  uint16_t langid;
} lang_id = { sizeof(lang_id), 3, 0x0409 };

static struct {
  uint8_t size;
  uint8_t type;
  uint16_t string[16];
} string_serial_nr = {
  sizeof(string_serial_nr),
  3, {
    'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A',
    'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A'
  }
};

static const struct {
  uint8_t size;
  uint8_t type;
  uint16_t string[17];
} string_manufacturer = {
  sizeof(string_manufacturer),
  3,
  {
    'T', 'e', 'x', 'a', 's', ' ',
    'I', 'n', 's', 't', 'r', 'u', 'm', 'e', 'n', 't', 's'
  }
};

static const struct {
  uint8_t size;
  uint8_t type;
  uint16_t string[17];
} string_product = {
  sizeof(string_product),
  3, {
    'C', 'C', '2', '5', '3', '1', ' ',
    'U', 'S', 'B', ' ', 'D', 'o', 'n', 'g', 'l', 'e'
  }
};
/*---------------------------------------------------------------------------*/

/* Callback to the input handler */
static int (* input_handler)(unsigned char c);
/*---------------------------------------------------------------------------*/
uint8_t *
usb_class_get_string_descriptor(uint16_t lang, uint8_t string)
{
  switch (string) {
  case 0: // LANGUAGE ID
    return (uint8_t *)&lang_id;
  case 2: // GET MANUFACTURE
    return (uint8_t *)&string_manufacturer;
  case 1: // GET PRODUCT
    return (uint8_t *)&string_product;
  case 3: // GET SERIAL
  case 4: // GET MAC ADDRESS
    return (uint8_t *)&string_serial_nr;
  default:
    return NULL;
  }
}

