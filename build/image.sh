#!/bin/bash

bash $PROJECT_ROOT/src/image_payload/embed.sh
cp $PROJECT_ROOT/src/image_payload/offset $PROJECT_ROOT/module/
cp $PROJECT_ROOT/src/image_payload/payload.png $PROJECT_ROOT/module/logo.png