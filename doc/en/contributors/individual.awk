# $TenDRA$

BEGIN {
	FS="|"
}

/^[^#]/{

print "<row>"
print "  <entry>" $1 " " $2 "</entry>" 
print "  <entry><email>" $3 "</email></entry>"
print "  <entry>" $4 "</entry>"
print "</row>"

}
