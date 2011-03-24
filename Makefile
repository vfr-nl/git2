git2: git2.c libgit2.ready
	gcc -static git2.c -O2 -I. -L./libgit2/build/static -o git2 -Wall -lgit2 -lz -Wall -Wextra

libgit2.ready:
	cd libgit2 && ./waf configure build-static && cd ../ && touch libgit2.ready

clean:
	rm -f git2 libgit2.ready; cd libgit2; ./waf distclean
