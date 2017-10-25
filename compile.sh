#!/bin/bash

# Remove old main executable
echo "Removing old main executable (if any)"
rm rpccracker


# Remove all old object files if any
objects="$(ls | fgrep .o)"

echo "Removing old object files (if any)..."
for object in $objects
do
    rm $object
done


# Compile all .c scripts individually
scripts="$(ls | fgrep .c)"


echo "Creating new object files..."
for script in $scripts
do
    size=${#script}
    size=`expr $size - 1`

    substr=${script:0:$size}
    obj="${substr}o"

    gcc -c -o $obj $script
done


# Combine all compiled scripts into one executable
objs_to_compile=""
objects="$(ls | fgrep .o)"
for obj in $objects
do
    objs_to_compile="${objs_to_compile} ${obj}"
done


echo "Combining all compiled scripts into one executable..."
gcc -o rpcCracker $objs_to_compile

echo "Done!"
