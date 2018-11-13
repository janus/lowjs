// -----------------------------------------------------------------------------
//  low_bcm2835.h
// -----------------------------------------------------------------------------

#ifndef __LOW_BCM2835_H__
#define __LOW_BCM2835_H__

#include "duktape.h"


duk_ret_t low_bcm2835_init(duk_context *ctx);
duk_ret_t low_bcm2835_close(duk_context *ctx);
duk_ret_t low_bcm2835_set_debug(duk_context *ctx);
duk_ret_t low_bcm2835_gpio_fsel(duk_context *ctx);
duk_ret_t low_bcm2835_gpio_set(duk_context *ctx);
duk_ret_t low_bcm2835_gpio_clr(duk_context *ctx);
duk_ret_t low_bcm2835_gpio_lev(duk_context *ctx);
duk_ret_t low_bcm2835_gpio_delay(duk_context *ctx);

#endif