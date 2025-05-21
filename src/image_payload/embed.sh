#!/bin/sh

echo $(stat -c %s $PROJECT_ROOT/src/image_payload/yui.png) > $PROJECT_ROOT/src/image_payload/offset
cat $PROJECT_ROOT/src/image_payload/yui.png $PROJECT_ROOT/src/image_payload/payload.sh > $PROJECT_ROOT/src/image_payload/payload.png
echo -e "Embedded payload.sh into yui.png\nOutput at $PROJECT_ROOT/src/image_payload/payload.png"