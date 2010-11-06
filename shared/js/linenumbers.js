/* $Id$ */

var Linenumbers = new (function () {

	this.init = function(root) {
		var pre = root.getElementsByTagName('pre'); 
		if (pre == null) {
			return;
		}

		for (var i = 0; i < pre.length; i++) {
			var count;
			var content;

			content = pre[i].innerHTML;
			content = content.replace(/\n+$/g, '');
			content = content.replace(/\t/g, '    ');
			pre[i].innerHTML = content;

			/* IE replaces '\n' by a space; this degrades to match nothing. */
			var matches = pre[i].innerHTML.match(/\n/mg);
			if (matches == null) {
				count = 1;
			} else {
				count = matches.length + 1;
			}

			var numbers = [];
			for (var n = 1; n <= count; n++) {
				numbers.push(n);
			}
			numbers = numbers.join("\n");

			var div = root.ownerDocument.createElementNS('http://www.w3.org/1999/xhtml', 'div');
			div.appendChild(root.ownerDocument.createTextNode(numbers));
			div.setAttribute('class', 'lines');
			pre[i].appendChild(div);
			pre[i].insertBefore(div, pre[i].firstChild);
		}
	}

});

