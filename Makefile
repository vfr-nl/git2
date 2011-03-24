git2: git2.c libgit2.a
git2.c:
	gcc -static src/git2.c -I. -L. -lgit2 -ogit2 -Wall -pedantic

libgit2: libgit2.a

libgit2.a:
	cd libgit2; ./waf configure build-static; cp build/static/libgit2.a ../
