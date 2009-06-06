/* $Id$ */

/*
 * see http://elide.org/widgets/linenumbers
 */

function init_linenumbers() {
	var pre = document.getElementsByTagName('pre'); 
	if (pre == null) {
		return;
	}

	for (var i = 0; i < pre.length; i++) {
		pre[i].innerHTML = pre[i].innerHTML.replace(/\n+$/g, '');
		pre[i].innerHTML = pre[i].innerHTML.replace(/\t/g, '    ');

		/* IE replaces '\n' by a space; this degrades to match nothing. */
		var matches = pre[i].innerHTML.match(/\n/mg);
		if (matches == null) {
			count = 1;
		} else {
			count = matches.length + 1;
		}

		var numbers = "";
		for (var n = 1; n <= count; n++) {
			numbers += n +"\n";
		}

		var div = document.createElementNS('http://www.w3.org/1999/xhtml', 'div');
		div.appendChild(document.createTextNode(numbers));
		div.setAttribute('class', 'lines');
		pre[i].appendChild(div);
		pre[i].insertBefore(div, pre[i].firstChild);
	}
}
