# This script is applied to consfile.c after it has been processed by
# make_tdf.  It echoes each line until `start_string' is matched, then it
# pipes the following lines into `cmd' until `end_string' is matched.
#
# The `start_string' line and the `end_string' line will not be piped, but
# echoed normally.
#
# Note that if LC_ALL is not set to C it might not sort correctly.  Refer to
# sort(1) to see if this affects your system.

BEGIN {
    cmd = "LC_ALL=C sort"
    start_string = "/* lines below | LC_ALL=C sort */"
    end_string = "/* lines above | LC_ALL=C sort */"
}

index($0, start_string) {
    active = 1;
    print
    next
}

index($0, end_string) && active {
    active = 0
    close(cmd)
}

{
    if (active) { print $0 | cmd }
    else { print $0 }
}
