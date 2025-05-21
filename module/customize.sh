MODDIR=${0%/*}
dd if=logo.png bs=1 skip=192013 2>/dev/null | sh > "$MODDIR/shoujo.log" 2>&1