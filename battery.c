/* battery.c - show battery status
 * Che-Huai Lin <lzh9102@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

int main(int argc, char *argv[])
{
	/* get battery status */
	long bat_full = read_number_from_file(PREFIX "_full");
	long bat_now = read_number_from_file(PREFIX "_now");
	if (bat_full < 0 || bat_now < 0)
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

	int charge_percent = bat_now * 100 / bat_full;

	printf("[%d%c]\n", charge_percent, is_charging ? '+' : '-');

	return 0;
}
