# Shared Support Functions

The /shared directory consists of various support functions shared across
several TenDRA projects. These are not considered worth releasing as a library
in their own right, either because they are trivially small, or because they are
specific to TenDRA.

The intention is that they are included into the source tree of each project by
way of symbolic links within the repository. In this way the code is
centralised without depending on a separate library, and those links are folded
in locally when taring up single projects for release.

The set of support functions is grouped into a statically-linked archive.
This archive takes the role of a miniature library, save that its API is
not particularly tidy, and is subject to change. check.h is a slight
exception, since it provides only a header.

