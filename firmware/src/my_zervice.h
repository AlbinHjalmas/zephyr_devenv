/*=================================================================================================
 *                _____           _                 ______    _          _ _
 *               / ____|         | |               |  ____|  | |        (_) |
 *              | (___  _   _ ___| |_ ___ _ __ ___ | |__ __ _| |__  _ __ _| | _____ _ __
 *               \___ \| | | / __| __/ _ \ '_ ` _ \|  __/ _` | '_ \| '__| | |/ / _ \ '_ \
 *               ____) | |_| \__ \ ||  __/ | | | | | | | (_| | |_) | |  | |   <  __/ | | |
 *              |_____/ \__, |___/\__\___|_| |_| |_|_|  \__,_|_.__/|_|  |_|_|\_\___|_| |_|
 *                       __/ |
 *                      |___/
 * Description:
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
ZERV_DECLARE(my_zervice, \
    ZERV_COMMAND(echo, \
        ZERV_COMMAND_PARAMS(const char *message, size_t message_length), \
        ZERV_COMMAND_RETURN(const char *response, size_t response_length)), \
    ZERV_COMMAND(add, \
        ZERV_COMMAND_PARAMS(int a, int b), \
        ZERV_COMMAND_RETURN(int sum)), \
    ZERV_COMMAND(print, \
        ZERV_COMMAND_PARAMS(const char *message, size_t message_length), \
        ZERV_COMMAND_RETURN(void), \
    ZERV_COMMAND(get_name, \
        ZERV_COMMAND_PARAMS(void), \
        ZERV_COMMAND_RETURN(const char *name, size_t name_length)));
    


/*=================================================================================================
 * PUBLIC FUNCTION DECLARATIONS
 *===============================================================================================*/

#endif /* _MY_ZERVICE_H_ */