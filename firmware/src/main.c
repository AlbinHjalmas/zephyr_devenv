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
 *     In header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) 2023 Albin Hjalmas
 * contact: albin@systemfabriken.tech
 *=================================================================================================
 * INCLUDES
 *===============================================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/net/socket.h>
#include <zephyr/net/net_mgmt.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

#define SERVER_PORT 12345
static char buf[CONFIG_NET_BUF_DATA_SIZE];

static void net_mgmt_cb(struct net_mgmt_event_callback *cb, uint32_t mgmt_event,
			struct net_if *iface)
{
	if (mgmt_event == NET_EVENT_IF_DOWN) {
		LOG_INF("Network interface went down");
		// Handle the interface down event
	} else if (mgmt_event == NET_EVENT_IF_UP) {
		LOG_INF("Network interface went up");
		// Handle the interface up event
	}
}

/*=================================================================================================
 * PROGRAM ENTRY POINT
 ================================================================================================*/
int main(void)
{
	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	int received;
	static struct net_mgmt_event_callback net_mgmt_cb_data;

	net_mgmt_init_event_callback(&net_mgmt_cb_data, net_mgmt_cb,
				     NET_EVENT_IF_DOWN | NET_EVENT_IF_UP);
	net_mgmt_add_event_callback(&net_mgmt_cb_data);

	// Initialize server address structure
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// Create socket
	LOG_INF("Creating socket...");
	server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_fd < 0) {
		LOG_ERR("Could not create socket (%i) %s", errno, strerror(errno));
		return EXIT_FAILURE;
	}

	// Bind socket
	LOG_INF("Binding socket...");
	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		LOG_ERR("Could not bind socket (%i) %s", errno, strerror(errno));
		close(server_fd);
		return EXIT_FAILURE;
	}

	// Listen for incoming connections
	LOG_INF("Listening on socket...");
	if (listen(server_fd, 5) < 0) {
		LOG_ERR("Could not listen on socket (%i) %s", errno, strerror(errno));
		close(server_fd);
		return EXIT_FAILURE;
	}

	LOG_INF("Server listening on port %d", SERVER_PORT);

	// Accept incoming connections
	while (1) {
		LOG_INF("Waiting for a client connection...");
		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
		if (client_fd < 0) {
			LOG_ERR("Could not accept connection");
			continue;
		}

		LOG_INF("Client connected");

		// Echo back data received
		do {
			received = recv(client_fd, buf, sizeof(buf), 0);
			LOG_INF("Received %d bytes", received);
			LOG_HEXDUMP_INF(buf, received, "Data received");
			if (received > 0) {
				send(client_fd, buf, received, 0);
			}
		} while (received > 0);

		close(client_fd);
		LOG_INF("Client disconnected");
	}

	// Cleanup
	close(server_fd);

	return EXIT_SUCCESS;
}

/*=================================================================================================
 * PRIVATE FUNCTION DEFINITIONS
 ================================================================================================*/
#ifdef CONFIG_ASSERT
extern void assert_post_action(const char *file, unsigned int line);
void assert_post_action(const char *file, unsigned int line)
{
	LOG_ERR("ASSERTION FAILED @ %s:%d", file, line);
}
#endif
