#!/bin/sh
#
# Simple acceptance tests for SID input.
# $Id$

. ../sidact.sh

for t in pass-*.sid; do
	test_sid 0 $t
done

for t in fail-*.sid; do
	test_sid 1 $t
done

