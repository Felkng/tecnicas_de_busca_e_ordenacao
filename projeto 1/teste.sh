#!/bin/bash

# Check if a filename is provided as an argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

filename="$1"

# Check if the file exists
if [ ! -e "$filename" ]; then
    echo "File not found: $filename"
    exit 1
fi

# Use sed to replace tabs with spaces (4 spaces in this example)
sed -i 's/    / /g' "$filename"

echo "Tabs replaced with spaces in $filename"
