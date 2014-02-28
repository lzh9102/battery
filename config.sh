#!/bin/sh

echo "#ifndef _CONFIG_H_"
echo "#define _CONFIG_H_"
echo

PREFIX=/sys/class/power_supply

# guess "online" file (whether the AC adapter is plugged in)
if [ -e $PREFIX/ACAD/online ]; then
	IS_CHARGING_FILE=$PREFIX/ACAD/online
else
	IS_CHARGING_FILE=
fi

# guess battery path (BAT{index})
for index in `seq 0 9`; do
	if [ -e $PREFIX/BAT${index}/ ]; then
		BAT_PATH=$PREFIX/BAT${index}/
		break
	fi
done
if [ -z "$BAT_PATH" ]; then
	echo "config error: cannot find BAT0 or BAT1 in $PREFIX" > /dev/stderr
	echo "battery not found" > /dev/stderr
	exit 1
fi

echo "#define BAT_PATH \"$BAT_PATH\""
if [ ! -z "$IS_CHARGING_FILE" ]; then
	echo "#define IS_CHARGING_FILE \"$IS_CHARGING_FILE\""
fi
echo
echo "#endif /* _CONFIG_H_ */"

exit 0
