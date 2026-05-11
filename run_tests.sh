#!/bin/bash
OUTPUT_FILE="test_output.txt"
echo "Running tests..." > $OUTPUT_FILE
for test in ./bin/test-*; do
    echo "=== $test ===" >> $OUTPUT_FILE
    $test >> $OUTPUT_FILE 2>&1
    echo "" >> $OUTPUT_FILE
done
echo "All tests completed. Output saved to $OUTPUT_FILE"