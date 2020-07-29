#!/bin/sh
#
# Simple acceptance tests for SID input.

# Test a .sid file for validity. This is parsing and semantic analysis only; no
# verification of the generated code is performed; that can follow in the future.
#
# $1 - The expected value for $?
# $2 - The .sid file under test
test_sid() {
	../../src/sid -l test $2 2>&- >&-
	r=$?
	if [ $r -ne $1 ]; then
		echo "FAIL: $r where expecting $1 for $2"
	else
		echo "PASS: $r where expecting $1 for $2"
	fi
}

