#!/bin/bash
set -e

MODULE_DIRECTORY="$PROJECT_ROOT/module"
if [ ! -e "$MODULE_DIRECTORY/logo.png" ]; then
  exit 1;
fi

zip_name="shoujocrypt.zip"

cd $MODULE_DIRECTORY
zip -r9 "$PROJECT_ROOT/out/$zip_name" .
cd -
echo -e "Done! Check $PROJECT_ROOT/out/$zip_name"