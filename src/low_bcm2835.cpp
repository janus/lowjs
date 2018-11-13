
#include<stdint.h>
#include "low_bcm2835.h"
#include "LowBCM2835.h"
#include "bcm2835.h"

#include "low_alloc.h"
#include "low_config.h"
#include "low_main.h"
#include "low_system.h"

duk_ret_t low_bcm2835_init(duk_context *ctx){
    
    low_main_t *low = duk_get_low_context(ctx);
    LowBCM2835 *bcm = new(low_new) LowBCM2835(low);
    if(!bcm) {
        duk_generic_error(ctx, "out of memory");
    }
    bcm->Init(0);
  return 0;
}

duk_ret_t low_bcm2835_close(duk_context *ctx){
    low_main_t *low = duk_get_low_context(ctx);
    LowBCM2835 *bcm = new(low_new) LowBCM2835(low);
    if(!bcm) {
        duk_generic_error(ctx, "out of memory");
    }
    bcm->Close(0);
  return 0;
}


// SetDebug sets the debug level of the library.  A value of 1 prevents mapping
// to /dev/mem, and makes the library print out what it would do, rather than
// accessing the GPIO registers.  A value of 0, the default, causes normal
// operation.  Call this before calling Init()
duk_ret_t low_bcm2835_set_debug(duk_context *ctx){
  uint8_t debug = (uint8_t)duk_require_uint(ctx,0);
  low_main_t *low = duk_get_low_context(ctx);
  LowBCM2835 *bcm = new(low_new) LowBCM2835(low);
  if(!bcm) {
        duk_generic_error(ctx, "out of memory");
  }
  bcm->SetDebug(debug, duk_is_undefined(ctx, 1) ? 0 : 1 );
  return 0;
}


// GpioFsel sets the function select register for the given pin, which
// configures the pin as either Input or Output
duk_ret_t low_bcm2835_gpio_fsel(duk_context *ctx){
  uint8_t pin = (uint8_t)duk_require_uint(ctx, 0);
  uint8_t mode = (uint8_t)duk_require_uint(ctx, 1);
  low_main_t *low = duk_get_low_context(ctx);
  LowBCM2835 *bcm = new(low_new) LowBCM2835(low);
  if(!bcm) {
        duk_generic_error(ctx, "out of memory");
  }
  bcm->Fsel(pin, mode, duk_is_undefined(ctx, 2) ? 0 : 2 );
  return 0;
}


// GpioSet sets the specified pin output to high.
duk_ret_t low_bcm2835_gpio_set(duk_context *ctx){
  uint8_t pin = (uint8_t)duk_require_uint(ctx, 0);
  low_main_t *low = duk_get_low_context(ctx);
  LowBCM2835 *bcm = new(low_new) LowBCM2835(low);
  if(!bcm) {
        duk_generic_error(ctx, "out of memory");
  }
  bcm->SetOutPin(pin, duk_is_undefined(ctx, 1) ? 0 : 1 );
  return 0;
}

// GpioClr sets the specified pin output to low.
duk_ret_t low_bcm2835_gpio_clr(duk_context *ctx){
  uint8_t pin = (uint8_t)duk_require_uint(ctx, 0);
  low_main_t *low = duk_get_low_context(ctx);
  LowBCM2835 *bcm = new(low_new) LowBCM2835(low);
  if(!bcm) {
        duk_generic_error(ctx, "out of memory");
  }
  bcm->ClearOutPin(pin, duk_is_undefined(ctx, 1) ? 0 : 1 );
  return 0;
}

// GpioLev reads the current level on the specified pin and returns either high
// or low. Works whether or not the pin is an input or an output.
duk_ret_t low_bcm2835_gpio_lev(duk_context *ctx){
  uint8_t pin = (uint8_t)duk_require_uint(ctx, 0);
  low_main_t *low = duk_get_low_context(ctx);
  LowBCM2835 *bcm = new(low_new) LowBCM2835(low);
  if(!bcm) {
        duk_generic_error(ctx, "out of memory");
  }
  bcm->ReadPin(pin, duk_is_undefined(ctx, 1) ? 0 : 1 );
  return 0;
}

// Delay
duk_ret_t low_bcm2835_gpio_delay(duk_context *ctx){
  unsigned int millis = duk_require_uint(ctx, 0);
  bcm2835_delay(millis);
  return 0;
}
