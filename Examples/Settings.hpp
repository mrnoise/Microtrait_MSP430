
#ifndef EXAMPLES_SETTINGS_HPP_
#define EXAMPLES_SETTINGS_HPP_

#ifndef RUN_TESTS
//#define EXAMPLE_RUN_GPIO
//#define EXAMPLE_RUN_WDTA
//#define EXAMPLE_RUN_TIMERA
#define EXAMPLE_RUN_EUSCIA
#endif

#ifdef EXAMPLE_RUN_GPIO
#include "Examples/GPIO.hpp"
#endif

#ifdef EXAMPLE_RUN_WDTA
#include "Examples/WDTA.hpp"
#endif

#ifdef EXAMPLE_RUN_TIMERA
#include "Examples/TIMERA.hpp"
#endif

#ifdef EXAMPLE_RUN_EUSCIA
#include "Examples/EUSCIA.hpp"
#endif


#endif /* EXAMPLES_SETTINGS_HPP_ */
