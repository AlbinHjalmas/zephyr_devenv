#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/zerv/zerv.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

ZERV_COMMAND_REGISTER(my_zervice, echo, ZERV_CMD_PARAMS(const char *message, size_t length),
		      ZERV_CMD_RETURN(const char *message, size_t length));

int main(void)
{
	ZERV_CALL(my_zervice, echo, rc, p_response, "Hello World!");

	if (rc != 0) {
		LOG_ERR("Failed to call echo command, rc: %d", rc);
		return -1;
	}

	LOG_DBG("Hello World!");
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
