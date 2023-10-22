// #####################################################################################################################
// # # #                              Copyright (C) 2023 DevPort Ost AB, all rights reserved. # #
// Unauthorized copying of this file, via any medium is strictly prohibited.                     #
// #                                           Proprietary and confidential. # # # # author:  Albin
// Hjalmas # # company: Systemfabriken # # contact: albin@systemfabriken.tech #
// #####################################################################################################################
//  INCLUDES
//  ###########################################################################################################
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>

// PRIVATE DECLARATIONS
// ###############################################################################################
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

// PRIVATE FUNCTION DECLARATIONS
// ######################################################################################

// PRIVATE DEFINITIONS

// ################################################################################################
// PROGRAM ENTRY
// ######################################################################################################
void main(void)
{
	LOG_DBG("Hello World!");
	k_sleep(K_FOREVER);
}

// PRIVATE FUNCTION DEFINITIONS
// #######################################################################################
#ifdef CONFIG_ASSERT
extern void assert_post_action(const char *file, unsigned int line);
void assert_post_action(const char *file, unsigned int line)
{
	LOG_ERR("ASSERTION FAILED @ %s:%d", file, line);
}
#endif
