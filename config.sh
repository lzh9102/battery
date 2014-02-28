#!/bin/sh

echo "#ifndef _CONFIG_H_"
echo "#define _CONFIG_H_"
echo

PREFIX=/sys/class/power_supply

# guess "online" file
if [ -e $PREFIX/ACAD/online ]; then
	IS_CHARGING_FILE=$PREFIX/ACAD/online
else
	IS_CHARGING_FILE=
fi

# guess battery path (BAT0 or BAT1)
if [ -e $PREFIX/BAT0 ]; then
	PREFIX=$PREFIX/BAT0
elif [ -e $PREFIX/BAT1 ]; then
	PREFIX=$PREFIX/BAT1
else
	echo "config error: cannot find BAT0 or BAT1 in $PREFIX" > /dev/stderr
	echo "battery not found" > /dev/stderr
	exit 1
fi

# guess system file prefix (charge_ or energy_)
if [ -e $PREFIX/charge_full ]; then
	PREFIX=$PREFIX/charge
elif [ -e $PREFIX/energy_full ]; then
	PREFIX=$PREFIX/charge
else
	echo "config error: cannot find $PREFIX/charge_full or $PREFIX/energy_full" > /dev/stderr
	exit 1
fi

echo "#define PREFIX \"$PREFIX\""
if [ ! -z "$IS_CHARGING_FILE" ]; then
	echo "#define IS_CHARGING_FILE \"$IS_CHARGING_FILE\""
fi
echo
echo "#endif /* _CONFIG_H_ */"

exit 0
