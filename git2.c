#include <stdlib.h>
#include <stdio.h>

#include "libgit2/include/git2.h"

int main (int argc, char** argv) {

    git_repository *repo;
    git_repository_open(&repo, ".");

    printf("I've been loaded!\n");
    return 0;
}
