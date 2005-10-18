# $TenDRA$


# Generate our header.

echo "<!DOCTYPE refentry PUBLIC \"-//FreeBSD//DTD DocBook V4.1-Based Extension//EN\"["
echo "<!ENTITY % man PUBLIC \"-//FreeBSD//ENTITIES DocBook Manual Page Entities//EN\">"
echo "%man;"
echo "<!ENTITY % doc PUBLIC \"-//FreeBSD//ENTITIES DocBook Document Entities//EN\">"
echo "%doc;"


case $1 in
	*680x0*)
		echo "<!ENTITY % ref.man.680x0-common SYSTEM \"tmp/680x0-common.sgml_tmp\"> %ref.man.680x0-common;"
		echo "<!ENTITY trans \"hptrans\">"
	;;
	*80x86*)
		echo "<!ENTITY % ref.man.80x86-common SYSTEM \"tmp/80x86-common.sgml_tmp\"> %ref.man.80x86-common;"
		echo "<!ENTITY trans \"trans386\">"
	;;
	*alpha*)
		echo "<!ENTITY % ref.man.alpha-common SYSTEM \"tmp/alpha-common.sgml_tmp\"> %ref.man.alpha-common;"
		echo "<!ENTITY trans \"alphatrans\">"
	;;
	*hppa*)
		echo "<!ENTITY % ref.man.hppa-common SYSTEM \"tmp/hppa-common.sgml_tmp\"> %ref.man.hppa-common;"
		echo "<!ENTITY trans \"hppatrans\">"
	;;
	*mips*)
		echo "<!ENTITY % ref.man.mips-common SYSTEM \"tmp/mips-common.sgml_tmp\"> %ref.man.mips-common;"
		echo "<!ENTITY trans \"mipstrans\">"
	;;
	*power*)
		echo "<!ENTITY % ref.man.power-common SYSTEM \"tmp/power-common.sgml_tmp\"> %ref.man.power-common;"
		echo "<!ENTITY trans \"powertrans\">"
	;;
	*ppc601*)
		echo "<!ENTITY % ref.man.power-common SYSTEM \"tmp/power-common.sgml_tmp\"> %ref.man.power-common;"
		echo "<!ENTITY % ref.man.ppc601-common SYSTEM \"tmp/ppc601-common.sgml_tmp\"> %ref.man.ppc601-common;"
		echo "<!ENTITY trans \"powertrans\">"
	;;
	*sparc*)
		echo "<!ENTITY % ref.man.sparc-common SYSTEM \"tmp/sparc-common.sgml_tmp\"> %ref.man.sparc-common;"
		echo "<!ENTITY trans \"sparctrans\">"
	;;
esac



if [ -f "../manpages/$1/manpage.sgml" ]; then
	echo "]>"
	echo "<refentry id=\"$1\">"
	sed -e 's/\\/&&/g' ../manpages/$1/manpage.sgml
elif [ -f "../manpages/trans/$1/manpage.sgml" ]; then
	echo "<!ENTITY % ref.man.options SYSTEM \"tmp/options.sgml_tmp\"> %ref.man.options;"
	echo "<!ENTITY % ref.man.common SYSTEM \"tmp/common.sgml_tmp\"> %ref.man.common;"
	echo "]>"
	echo "<refentry id=\"trans-$1\">"
	sed -e 's/\\/&&/g' ../manpages/trans/$1/manpage.sgml
fi


echo "</refentry>"
