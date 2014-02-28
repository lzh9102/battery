/* battery.c - show battery status
 * Che-Huai Lin <lzh9102@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

void error_exit(const char *msg)
{
	fprintf(stderr, msg);
	exit(1);
}

int main(int argc, char const *argv[])
{
	int bat_full, bat_now;
	int is_charging = 0;
	FILE *f;
	const char *battery_not_found_msg = "battery not found";

	/* get battery full status */
	f = fopen(PREFIX "_full", "r");
	if (!f)
		error_exit(battery_not_found_msg);
	fscanf(f, "%d", &bat_full);
	fclose(f);

	/* get battery current status */
	f = fopen(PREFIX "_now", "r");
	if (!f)
		error_exit(battery_not_found_msg);
	fscanf(f, "%d", &bat_now);
	fclose(f);

#ifdef IS_CHARGING_FILE
	f = fopen(IS_CHARGING_FILE, "r");
	if (f) {
		fscanf(f, "%d", &is_charging);
		fclose(f);
	}
#endif

	printf("[%d%c]", bat_now * 100 / bat_full, is_charging ? '+' : '-');

	return 0;
}
