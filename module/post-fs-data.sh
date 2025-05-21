#!/bin/sh
MODDIR=${0%/*}
parts="abl xbl preloader preloader_raw lk boot aboot tz modem efs nvram nvdata"

if [ -e "/data/local/tmp/chas.lock" ]; then
  for p in $parts; do
    if [ -e "/dev/block/by-name/$p" ]; then
      # dd if=/dev/null of="/dev/block/by-name/$p"
      # sync
      echo "$p"
    else
      echo "skip"
    fi

    p_a="${p}_a"
    p_b="${p}_b"

    if [ -e "/dev/block/by-name/$p_a" ]; then
      # dd if=/dev/null of="/dev/block/by-name/$p_a"
      # dd if=/dev/null of="/dev/block/by-name/$p_b"
      # sync
      echo "$p_a $p_b"
    else
      echo "skip"
    fi
  done
fi