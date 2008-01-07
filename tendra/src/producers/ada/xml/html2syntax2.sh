#!/bin/bash
#
# This script convert syntax rules from Ada Reference Manual (HTML)
# into xml form. 
#

[ -f RM-P.html ] || wget http://www.adaic.org/standards/05rm/html/RM-P.html

xsltproc -o html2syntax1.tmp --html html2syntax1.xsl RM-P.html
xsltproc -o html2syntax2.tmp html2syntax2.xsl html2syntax1.tmp


begin_gramar()
{
    echo '<?xml version="1.0"?>'
    echo '<gramar>'
}

end_gramar()
{
    echo '</gramar>'
}

do_rule()
{
    echo "<rule name=\"$1\" label=\"$2:\">"
    echo "<seq>"
}

end_rule()
{
    echo "</seq>"
    echo "</rule>"
}

do_ref()
{
    if [ -z "$2" ]; then
        echo "<ref name=\"$1\"/>"
    else
        echo "<ref name=\"$1\" italic=\"$2\"/>"
    fi
}

do_keyword()
{
    case "$1" in
        *\ *)
            do_keyword "${1%% *}"
            do_keyword "${1#* }"
            ;;
        *)
            echo "<keyword text=\"$1\"/>"
            ;;
   esac
}

do_texts()
{
    case "$1" in
        \{\|*)
            echo "<list>"
            echo "<seq>"
            echo "<delim text=\"|\"/>"
            do_texts "${1:2}"
            ;;
        \{*)
            echo "<list>"
            echo "<seq>"
            do_texts "${1:1}"
            ;;
        \}*)
            echo "</seq>"
            echo "</list>"
            do_texts "${1:1}"
            ;;
        \[*)
            echo "<opt>"
            echo "<seq>"
            do_texts "${1:1}"
            ;;
        \]*)
            echo "</seq>"
            echo "</opt>"
            do_texts "${1:1}"
            ;;
        \|*)
            echo "</seq>"
            echo "<seq>"
            do_texts "${1:1}"
            ;;

        \>\>* )
            echo "<delim text=\"&gt;&gt;\"/>"
            do_texts "${1:2}"
            ;;
        \>=* )
            echo "<delim text=\"&gt;=\"/>"
            do_texts "${1:2}"
            ;;
        \<\<* )
            echo "<delim text=\"&lt;&lt;\"/>"
            do_texts "${1:2}"
            ;;
        \<=* )
            echo "<delim text=\"&lt;=\"/>"
            do_texts "${1:2}"
            ;;
        \<\>* )
            echo "<delim text=\"&lt;&gt;\"/>"
            do_texts "${1:2}"
            ;;
        =\>* )
            echo "<delim text=\"=&gt;\"/>"
            do_texts "${1:2}"
            ;;
        \*\** | /=* | :=* |  \.\.* | --* )
            echo "<delim text=\"${1:0:2}\"/>"
            do_texts "${1:2}"
            ;;
        \"*)
            echo "<delim text='${1:0:1}'/>"
            do_texts "${1:1}"
            ;;
        \<*)
            echo "<delim text='&lt;'/>"
            do_texts "${1:1}"
            ;;
        \&*)
            echo "<delim text='&amp;'/>"
            do_texts "${1:1}"
            ;;
        [A-z][a-z]*)
            word=`echo "$1"|sed -e "s/[^A-Za-z].*\$//"|tr "[A-Z]" "[a-z]"`
            rest=`echo "$1"|sed -e "s/^[A-Z][a-z]*//"`
            echo "<keyword text=\"${word}\"/>"
            do_texts "${rest}"
            ;;
        "")
            ;;
        *)
            echo "<delim text=\"${1:0:1}\"/>"
            do_texts "${1:1}"
            ;;
    esac
}

. ./html2syntax2.tmp | xmllint --format --output syntax-2005.xml -

rm *.tmp
