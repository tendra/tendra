# $TenDRA$

BEGIN {
	FS="|"
}

/^[^#]/{

print "<row>"
print "  <entry>" $1 "</entry>"
print "  <entry><ulink url=\"" $2 "\">" $2 "</ulink>" 
print "  <entry>" $3 "</entry>"
print "</row>"

}
