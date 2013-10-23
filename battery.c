/* battery.c - show battery status
 * Che-Huai Lin <lzh9102@gmail.com>
 */

#include <stdio.h>
#include "config.h"

int main(int argc, char const *argv[])
{
	int bat_full, bat_now;
	FILE *f;

	/* get battery full status */
	f = fopen(PREFIX "_full", "r");
	if (!f)
		return 1;
	fscanf(f, "%d", &bat_full);
	fclose(f);

	/* get battery current status */
	f = fopen(PREFIX "_now", "r");
	if (!f)
		return 1;
	fscanf(f, "%d", &bat_now);
	fclose(f);

	printf(FORMAT, bat_now * 100 / bat_full);

	return 0;
}
