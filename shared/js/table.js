/* $Id: table.js 525 2010-08-21 00:26:46Z kate $ */

/*
 * Automatically-identified sortable tables.
 * See http://elide.org/widgets/sorting/ for details.
 *
 * Ideas for future work:
 *
 * - save table order in URI after # (or use a cookie)
 * - take <input> values as well as table cell values, during recursive serialisation of a <td>'s contents, also <img>
 * - deal with something modifying the table, and reinitialise it
 * - <td> columns reorderable by drag & drop for their higest <th>
 * - <tr> reorderable by drag and drop
 * - use the column type to infer left/right/centre alignment
 */

/*
 * Implementation:
 *
 * The main idea here is to do as little as possible during initialisation
 * (since there are often lots of tables in one document). As much as possible
 * is postponed until the user clicks a <th> to sort it; I figure delay is ok
 * there, since they're expecting something to happen.
 *
 * All xpath paths are given using explicit paths from the parent, so as to
 * avoid accidentally selecting inside subtables.
 *
 * This uses Array.sort() for sorting; reimplementing this (as some do) seemed
 * unneccessary.
 */

/*
 * TODO: omit diagonal <th>s
 * TODO: omtimise for the typical special case of no @colspan
 * TODO: nested tables
 * TODO: serialse <input>s etc
 * TODO: add a "table-sorting" class to <th>, for UI feedback
 * TODO: refactor to avoid repeated xpath queries
 * TODO: make it scale (cache column type, cache widths)
 * TODO: make it work with HTML namespaces, too
 * TODO: alternate approach: pre-render entire <tables> sorted for each column. clicking to sort just swaps them in
 * TODO: convention to prefix variables $ for DOM objects
 * TODO: namespacing: what about within DOM nodes? make a table object there, too?
 * TODO: when operating in HTML (not XHTML), the namespace needs to change
 * TODO: support <th colspan="2"/>. possibly simply another dimension to the th's arrays
 */


var Table = new (function () {
	/*
	 * This array determines how to sort each data type. Types are identified by
	 * regexp applied to each <td>'s .innerHTML in a column. Since empty cells are
	 * handled by the calling function, these regexps are never passed (and hence
	 * need not match) an empty string.
	 *
	 * Each entry here is ordered by precidence; the highest types in this array
	 * have higher precidence. The lowest entry is a "catch-all" type.
	 *
	 * The comparison functions used for sorting should return positive, negative,
	 * or 0, as per Array.sort(). They are passed the match arrays from their
	 * respective regexp, matched against the two <td>'s .innerHTML values to
	 * compare. Empty cells are handled by the calling function, and so the
	 * .cmp() callbacks are never passed an array matched from an empty string.
	 *
	 * The intention is that this array should be straightforward to extend with
	 * additional types in the future.
	 */
	/*
	 * TODO:
	 * - date/time (ISO 8601 and friends)
	 * - scientific notation
	 * - filesize (1kb etc)
	 * - Si magnitudes (1k3 3M 2da etc)
	 *
	 * See also: http://www.frequency-decoder.com/demo/table-sort-revisited/custom-sort-functions/
	 */
	var types = [
		/* IP address */ {
			re:  /^([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})$/,
			cmp: function (a, b) {
				return (a[1] << 24 | a[2] << 16 | a[3] << 8 | a[4] << 0)
				     - (a[1] << 24 | b[2] << 16 | b[3] << 8 | b[4] << 0);
			}
		},

		/* float (with separators) */ {
			re:  /^[-+]?[0-9,']*\.?[0-9,]+([eE][-+]?[0-9]+)?$/,
			cmp: function (a, b) {
				a = a[0].replace(/[,']/g, '');
				b = b[0].replace(/[,']/g, '');
				return Number(a) - Number(b);
			}
		},

		/* currency */ {
			re:  /^[#$\uA3]?[0-9.,']*\.?[0-9,]+([cp$]|UKP|GBP|USD)?$/i,
			cmp: function (a, b) {
				var ad = /^[cp]$/i.test(a[1]) ? 100 : 1;
				var bd = /^[cp]$/i.test(b[1]) ? 100 : 1;
				a = a[0].replace(/[^0-9.]/g, '');
				b = b[0].replace(/[^0-9.]/g, '');
				return Number(a) / ad - Number(b) / bd;
			}
		},

		/* DD/MM/YYYY */ {
			re:  /^([0123]?[0-9])\/(10|11|12|0?[0-9])\/(\d\d(\d\d)?)$/,
			cmp: function (a, b) {
				a = new Date(a[3], Number(a[2]) - 1, a[1]);
				b = new Date(b[3], Number(b[2]) - 1, b[1]);
				return a - b;
			}
		},

		/* MM/DD/YYYY */ {
			re:  /^(10|11|12|0?[0-9])\/([0123]?[0-9])\/(\d\d(\d\d)?)$/,
			cmp: function (a, b) {
				a = new Date(a[3], Number(a[1]) - 1, a[2]);
				b = new Date(b[3], Number(b[1]) - 1, b[2]);
				return a - b;
			}
		},

		/* string */ {
			re:  /^.*$/,
			cmp: function (a, b) {
				a = a[0].toLowerCase();
				b = b[0].toLowerCase();
				return (a > b) - (a < b);
			}
		}
	];

	/*
	 * Floor of the binary logarithm of i.
	 * This is equivalent to Math.floor(Math.log(i) / Math.log(2));
	 * Given a power of 2, this returns the 0-based index of that bit.
	 */
	function ilog2(i) {
		var l;

		l = 0;

		while (i >>= 1) {
			l++;
		}

		return l;
	}

	function serialise(node) {
		if (node.table_serialised == null) {
			node.table_serialised = node.innerHTML.replace(/\s+/g, " ").trim();
		}

		return node.table_serialised;
	}

	function hasclass(node, klass) {
		var a, c;

		c = node.getAttribute('class');
		if (c == null) {
			return;
		}

		a = c.split(/\s/);

		for (var i in a) {
			if (a[i] == klass) {
				return true;
			}
		}

		return false;
	}

	function removeclass(node, klass) {
		var a, c;

		c = node.getAttribute('class');
		if (c == null) {
			return;
		}

		a = c.split(/\s/);

		for (var i = 0; i < a.length; i++) {
			if (a[i] == klass || a[i] == '') {
				a.splice(i, 1);
				i--;
			}
		}

		if (a.length == 0) {
			node.removeAttribute('class');
		} else {
			node.setAttribute('class', a.join(' '));
		}
	}

	function addclass(node, klass) {
		var a, c;

		a = [ ];

		c = node.getAttribute('class');
		if (c != null) {
			a = c.split(/\s/);
		}

		for (var i = 0; i < a.length; i++) {
			if (a[i] == klass || a[i] == '') {
				a.splice(i, 1);
				i--;
			}
		}

		a.push(klass);

		node.setAttribute('class', a.join(' '));
	}

	/*
	 * Always returns an array, even if it's empty. The array contains DOM nodes.
	 * Modifying nodes will change the document.
	 *
	 * Examples:
	 *
	 * var a = xpath(document.documentElement, "//h:th");
	 * for (var i in a) {
	 *     a[i].style.backgroundColor = 'aliceblue';
	 * }
	 *
	 * // note xpath's 1-based indexing versus javascript's 0-based...
	 * xpath(document.documentElement, "//h:h1[1]")[0].style.color = 'red';
	 */
	function xpath(root, query) {
		var type = XPathResult.ORDERED_NODE_ITERATOR_TYPE;
		var resolver;
		var a, x, n;

		a = [ ];

		resolver = function (prefix) {
			switch (prefix) {
			case "h": return "http://www.w3.org/1999/xhtml";
	        default:  return null;
			}
		}

		x = document.evaluate(query, root, resolver, type, null);

		/* constructing an array because modifying any node invalidates the iterator */
		while ((n = x.iterateNext())) {
			a.push(n);
		}

		return a;
	}

	/*
	 * Returns 0-based index of the given <th>'s row, or -1 if it's inside a <thead>.
	 */
	function findthrow(t, th) {
		var tr;

		if (th.parentNode.localName != 'tr') {
			return null;
		}

		tr = th.parentNode;

		if (tr.parentNode.localName == 'thead') {
			return -1;
		}

		for (var i in t.rows) {
			if (t.rows[i] == tr) {
				return i;
			}
		}

		return null;
	}

	function getcolumn(t, b, r, c, body, cell) {
		var q;

		/*
		 * These are the cells who's left edge's (preceding siblings)
		 * column are < c and who's right edge's (self)
		 * column are > c.
		 * In other words, the cells which encompass the column index, c.
		 */
		q = "(.|h:" + body + "[" + (b + 1) + "])"
		  + "/h:tr[position() > " + r + "]"
		  + "/h:" + cell + "["
		  + "      sum(preceding-sibling::h:*/@colspan) + "
		  + "    count(preceding-sibling::h:*[not(@colspan)])"
		  + "    <= " + c
		  + "]["
		  + "      sum(preceding-sibling::h:*/@colspan) + "
		  + "    count(preceding-sibling::h:*[not(@colspan)]) + "
		  + "    number(count(@colspan) = 0) + sum(@colspan) > " + c
		  + "]";

		return xpath(t, q);
	}

	/*
	 * Returns an array of <td>s in the body for a table, after a given row.
	 *
	 * b - 0-based tbody index of the table body we're interested in.
	 * c - 0-based column index of the column we're interested in.
	 * r - 0-based row index of the row we're interested in cells below.
	 */
	function getcolumntd(t, b, r, c) {
		return getcolumn(t, b, r, c, "tbody", "td");
	}

	/*
	 * Returns an array of <th>s in the header for a table.
	 *
	 * c - 0-based column index of the column we're interested in.
	 */
	function getcolumnth(t, c) {
		return getcolumn(t, 0, 0, c, "thead", "th");
	}

	function countcols(t) {
		var cols;
		var a;

		cols = 0;

		/*
		 * TODO: there must be a better way to do this... this assumes that the
		 * first header row is entirely populated. A more thorough approach would
		 * be to count in all the rows and take the maximum.
		 */
		a = xpath(t, "h:tr[1]/h:th|h:thead/h:tr[1]/h:th"
		          + "|h:tr[1]/h:td|h:thead/h:tr[1]/h:td");
		for (var c in a) {
			cols += a[c].colSpan || 1;
		}

		return cols;
	}

	/*
	 * Return a mask of all type[] indexes which match the given string.
	 * Only indexes present in the 'runningmask' argument are considered for
	 * matching, and so it may be used to eliminate testing for irrelevant types.
	 */
	function guesstypetd(runningmask, s) {
		var mask;

		mask = 0;

		for (var i in types) {
			var j;

			j = 1 << i;

			if ((runningmask & j) == 0) {
				continue;
			}

			if (s == "" || types[i].re.test(s)) {
				mask |= j;
			}
		}

		return mask;
	}

	/*
	 * Return the 0-based index of the highest precidence type matching all cells
	 * in the given column, or -1 if no type matches.
	 */
	function guesstypecolumn(v) {
		var mask;

		/*
		 * For each regex that matches against a cell, add that type to a set. Then
		 * intersect all types within the set to find which we can consider
		 * appropiate for the entire column of cells. The type we decide is the
		 * highest precidence from this intersection.
		 */

		mask = ~0;

		for (var w in v) {
			mask &= guesstypetd(mask, serialise(v[w]));
		}

		/* no type matched */
		if (mask == 0) {
			return -1;
		}

		/* pick the first bit (i.e. the highest precidence) */
		mask &= ~(mask - 1);

		/* the index of the bit set (i.e. the index into types[]) */
		return ilog2(mask);
	}

	/*
	 * This function provides two mutually exclusive operations:
	 *
	 *  - Sorting unordered data; this happens on the first click.
	 *  - Reversing sorted data; this happens on subsequent clicks.
	 *
	 * Descision-making for when to reorder, and in what direction depends on the
	 * state of the current data. State is maintained in the @class list of the
	 * <th> associated with that column.
	 *
	 * The sort function reorders a column of data; this does not affect the
	 * page layout - it is the array order which is modified, not the DOM tree.
	 *
	 */
	function ordercolumn(th) {
		var o;

		o = { };

		if (hasclass(th, "table-sorted")) {
			o.sort = function (t, v) {
					v.reverse();
				};

			o.dir = hasclass(th, 'table-ascending')
				? 'table-descending'
				: 'table-ascending';
		} else {
			o.sort = function (t, v) {
				v.sort(function (a, b) {
						var as = serialise(a);
						var bs = serialise(b);

						if (as == "") return +1;
						if (bs == "") return -1;

						if (a.table_m == null) a.table_m = as.match(t.re);
						if (b.table_m == null) b.table_m = bs.match(t.re);

						return t.cmp(a.table_m, b.table_m);
					});
				};

			o.dir = 'table-ascending';
		}

		return o;
	}

	/*
	 * Reset the sortedness state of all columns, and set the sortedness state
	 * for the given column.
	 */
	function resetorder(t, th, dir) {
		var o;

		/* Reset classes for all other columns' data */
		/* TODO: only if this isn't our column; deal with that separately */
		o = xpath(t, "h:tbody/h:tr/h:td|h:tr/h:td");
		for (var w in o) {
			removeclass(o[w], "table-sorted");
		}

		/* Reset direction for all other columns' headers */
		o = xpath(t, "h:thead/h:tr/h:th|h:tr/h:th");
		for (var w in o) {
			removeclass(o[w], "table-ascending");
			removeclass(o[w], "table-descending");
			if (o[w] != th) {
				removeclass(o[w], "table-sorted");
			}
		}

		addclass(th, dir);
		addclass(th, "table-sorted");
	}

	/*
	 * Update the DOM tree to reflect the order of a given column.
	 * @class attributes are also updated accordingly.
	 */
	function renderorder(t, v) {
		var body, tr;

		tr = v[0].parentNode;
		if (tr.localName != 'tr') {
			return;
		}

		body = tr.parentNode;
		if (body.localName != 'table' && body.localName != 'tbody') {
			return;
		}

		for (var w in v) {
			addclass(v[w], "table-sorted");
			body.appendChild(v[w].parentNode);
		}
	}

	/*
	 * This little dance is an optimisation for speed; all the DOM modification is
	 * performed with the table node taken out of the document. This stops a
	 * browser from attempting to reflow the page layout every time a <tr> is added
	 * or removed.
	 *
	 * After the modifications are done, the table is swapped back in to the
	 * document. A placeholder node is used to conveniently hold its position.
	 */
	function replacenode(node, f) {
		var parent;
		var placeholder;

		parent = node.parentNode;
		if (parent == null) {
			return;
		}

		placeholder = document.createComment('placeholder');
		if (placeholder == null) {
			return;
		}

		parent.replaceChild(placeholder, node);

		f();

		parent.replaceChild(node, placeholder);
	}

	/*
	 * This is the callback from the <th>.onclick events; the entry point to cause
	 * a column to be sorted.
	 */
	this.sort = function (th, r, c) {
		var t, o, b;

		t = xpath(th, "ancestor::h:table[1]")[0];
		if (!t) {
			return;
		}

		/*
		 * The sorted vector table_v, and its associated type table_p, are
		 * cached to save recalculating these in the future. They are stored
		 * in th, simply because that is a convenient place to store them.
		 *
		 * Both arrays are indexed by the index of their respective tbody,
		 * which provides sorting separately for each tbody within a given
		 * column. A side-effect of this is that the elements in one tbody
		 * need not have the same type as elements in another tbody.
		 */
		{
			if (th.table_v == null) {
				th.table_v = [ ];
			}

			if (th.table_p == null) {
				th.table_p = [ ];
			}
		}

		o = ordercolumn(th);	/* TODO: rename ordercolumn() */

		resetorder(t, th, o.dir);

		b = xpath(t, "h:tbody").length;
		do {
			if (th.table_v[b] == null) {
				th.table_v[b] = getcolumntd(t, b, r, c);
			}

			if (th.table_v[b].length == 0) {
				continue;
			}

			if (th.table_p[b] == null) {
				th.table_p[b] = guesstypecolumn(th.table_v[b]);
			}

			if (th.table_p[b] == -1) {
				addclass(th, "table-notype");
				continue;
			}

			o.sort(types[th.table_p[b]], th.table_v[b]);

			replacenode(t, function () {
					renderorder(t, th.table_v[b]);
				});
		} while (b != null && b-- > 0);
	}

	/*
	 * Initialise a single table.
	 */
	function inittable(t) {
		var cols;

		cols = countcols(t);

		/*
		 * For each column, find the lowest <th>. If it meets various requirements
		 * (such as actually having some <td>s below it), then make it active as a
		 * clickable sorting header.
		 *
		 * TODO: reconsider; perhaps select all cells in a column, and iterate
		 * backwards to find the lowest th. then the tds below it are trivial to
		 * find; just the remaining elements.
		 */
		for (var c = 0; c < cols; c++) {
			var lowest;
			var r;

			/* find the lowest-down <th> of all the <th>s in this column */
			lowest = getcolumnth(t, c).pop();
			if (lowest == null) {
				continue;
			}

			/* discard multi-column <th>s */
			if (lowest.getAttribute("colspan") > 1) {
				continue;
			}

			r = findthrow(t, lowest);
			if (r == null) {
				continue;
			}

			/* Skip <th>s with no <td>s below them */
			if (getcolumntd(t, null, r, c).length == 0) {
				continue;
			}

			/*
			 * TODO: discard all the <th>s below the topmost <th> in the entire
			 * table (i.e. no diagonal <th>s; they'd be moved around when sorting)
			 */

			/*
			 * TODO: should probably wrap the <th> in an <a>, for UI consistency
			 * wrt accidentally selecting text. If so, .blur() it onclick?
			 * TODO: on doubleclick maybe?
			 */

			addclass(lowest, "table-sortable");
			lowest.setAttribute("onclick",
				"Table.sort(this, " + r + ", " + c + "); false");

			/* TODO: make this lowest.onclick = function (event) { ... }; instead */
		}
	}


	/* TODO: there is probably a way to automate calling this */
	this.init = function (root) {
		var a;

		/* not provided on Camino */
		if (!String.prototype.trim) {
			String.prototype.trim = function () {
				return this.replace(/^\s*/, "").replace(/\s*$/, "");
			}
		}

		/*
		 * Here we do not include tables which have cells of @rowspan > 1, due to
		 * their unsortabilty.
		 */

		a = xpath(root, "//h:table[not(h:tbody/h:tr/h:td[@rowspan > 1]) "
		              + "              and not(h:tr/h:td[@rowspan > 1])]");
		for (var i in a) {
			inittable(a[i]);
		}
	}
});

