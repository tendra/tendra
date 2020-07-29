XSLT stylesheets for internal use as supporting utilities. These do not produce
output in document form directly useful to users. These serve to perform xpath
queries on documents; I didn't want to introduce a dependency on a CLI tool
such as XMLStarlet, when we can get by with just XSLT.

