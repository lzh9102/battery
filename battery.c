/* battery.c - show battery status
 * Che-Huai Lin <lzh9102@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "config.h"

void error_exit(const char *msg)
{
	fprintf(stderr, msg);
	exit(1);
}

/* read a non-negative integer from the file
 * returns -1 on error
 */
long read_number_from_file(const char *filename)
{
	long result = -1;
	FILE *f = fopen(filename, "r");
	if (f) {
		fscanf(f, "%ld", &result);
		fclose(f);
	}
	return result;
}

void format_remaining_time(char *buffer, int bufsize, int seconds)
{
	int hour = seconds / 3600;
	int minute = (seconds%3600) / 60;
	snprintf(buffer, bufsize, "%dh %dm", hour, minute);
}

int main(int argc, char *argv[])
{
	/* get battery status */
	long charge_full = read_number_from_file(BAT_PATH "charge_full");
	long charge_now = read_number_from_file(BAT_PATH "charge_now");
	if (charge_full < 0 || charge_now < 0)
		error_exit("battery not found");

#ifdef IS_CHARGING_FILE
	int is_charging = (int)read_number_from_file(IS_CHARGING_FILE);
	if (is_charging < 0)
		is_charging = 0;
#endif

	/* parse command-line options */
	char ch;
	int opt_short = 0;
	while ((ch = getopt(argc, argv, "s")) != -1) {
		switch (ch) {
			case 's':
				opt_short = 1;
				break;
			default:
				break;
		}
	}

	int charge_percent = charge_now * 100 / charge_full;

	if (opt_short) /* short format (for tmux, zsh, ...) */
		printf("[%d%c]\n", charge_percent, is_charging ? '+' : '-');
	else { /* detailed report */
		/* charge level and status */
		const char *status = is_charging ? "charging" : "discharging";
		printf("%d%% (%s)\n", charge_percent, status);

		/* compute remaining time if the battery is discharging */
		long current_uA = read_number_from_file(BAT_PATH "current_now");
		if (!is_charging && current_uA > 0) {
			/* time = charge(uWh) * seconds_per_hour(s/h) / current(uA) seconds */
			int remaining_seconds = charge_full * 3600 / current_uA;
			char str_remaining_time[16];
			format_remaining_time(str_remaining_time, 16, remaining_seconds);
			printf("estimated remaining time: %s\n", str_remaining_time);
		}
	}

	return 0;
}
