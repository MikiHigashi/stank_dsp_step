#ifndef LTC2630_H
#define LTC2630_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
        
        
void LTC2630_write(uint16_t volt);

#endif	//LTC2630_H
/**
 End of File
*/

