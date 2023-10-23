/*=================================================================================================
 *                _____           _                 ______    _          _ _
 *               / ____|         | |               |  ____|  | |        (_) |
 *              | (___  _   _ ___| |_ ___ _ __ ___ | |__ __ _| |__  _ __ _| | _____ _ __
 *               \___ \| | | / __| __/ _ \ '_ ` _ \|  __/ _` | '_ \| '__| | |/ / _ \ '_ \
 *               ____) | |_| \__ \ ||  __/ | | | | | | | (_| | |_) | |  | |   <  __/ | | |
 *              |_____/ \__, |___/\__\___|_| |_| |_|_|  \__,_|_.__/|_|  |_|_|\_\___|_| |_|
 *                       __/ |
 *                      |___/
 *
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) 2023 Systemfabriken AB
 * contact: albin@systemfabriken.tech
 *===============================================================================================*/
#ifndef _MY_ZERVICE_H_
#define _MY_ZERVICE_H_

/*=================================================================================================
 * INCLUDES
 *===============================================================================================*/
#include <zephyr/zerv/zerv.h>

/*=================================================================================================
 * PUBLIC MACROS
 *===============================================================================================*/

ZERV_CMD_REGISTER(my_zervice, echo, ZERV_CMD_PARAM(const char *message, size_t length),
		  ZERV_CMD_RETURN(const char *message, size_t length));
ZERV_CMD_REGISTER(my_zervice, sum, ZERV_CMD_PARAM(int a, int b), ZERV_CMD_RETURN(int sum));
ZERV_CMD_REGISTER(my_zervice, print_hello, EMPTY, EMPTY);

/*=================================================================================================
 * PUBLIC FUNCTION DECLARATIONS
 *===============================================================================================*/

#endif /* _MY_ZERVICE_H_ */