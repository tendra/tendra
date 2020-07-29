#!/bin/sh
#
# Simple acceptance tests for Lexi input.

# Test a .lxi file for validity. This is parsing and semantic analysis only; no
# verification of the generated code is performed; that can follow in the future.
#
# $1 - The expected value for $?
# $2 - The .lxi file under test
lxitest() {
	../src/lexi -ltest $2 2>&- >&-
	r=$?
	if [ $r -ne $1 ]; then
		echo "FAIL: $r where expecting $1 for $2"
	else
		echo "PASS: $r where expecting $1 for $2"
	fi
}

for t in pass-*.lxi; do
	lxitest 0 $t
done

for t in fail-*.lxi; do
	lxitest 1 $t
done

