#pragma once

#include_next <mcuconf.h>

#undef ADC_USE_WAIT
#undef ADC_USE_MUTUAL_EXCLUSION
#define ADC_USE_WAIT TRUE
#define ADC_USE_MUTUAL_EXCLUSION TRUE