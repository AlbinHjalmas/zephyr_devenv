#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/zerv/zerv.h>

#include "my_zervice.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
	ZERV_CALL(my_zervice, echo, rc, p_response, "Hello World!");

	if (rc != 0) {
		LOG_ERR("Failed to call echo command, rc: %d", rc);
		return -1;
	}

	ZERV_CALL(my_zervice, sum, rc2, p_response2, 1, 2);

	if (rc2 != 0) {
		LOG_ERR("Failed to call sum command, rc: %d", rc);
		return -1;
	}

	LOG_DBG("Sum: %d", p_response2->sum);

	ZERV_CALL(my_zervice, print_hello, rc3, p_response3);

	if (rc3 != 0) {
		LOG_ERR("Failed to call print_hello command, rc: %d", rc);
		return -1;
	}

	LOG_DBG("p_response3: %p", p_response3);

	k_sleep(K_FOREVER);

	return 0;
}

#ifdef CONFIG_ASSERT
extern void assert_post_action(const char *file, unsigned int line);
void assert_post_action(const char *file, unsigned int line)
{
	LOG_ERR("ASSERTION FAILED @ %s:%d", file, line);
}
#endif
