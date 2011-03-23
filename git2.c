#include <stdlib.h>
#include <stdio.h>

#include "libgit2/include/git2.h"

// doh ~stub
void get_master_hex(char *hex) {
    FILE *f = fopen(".git/refs/heads/master", "r");
    fgets(hex, 41, f);
    fclose(f);
}

int main (int argc, char** argv) {
    /*
    if (argc != 2) {
        printf("Usage: git2 rev-list <commit>\n");
        exit(1);
    }

    if (strcmp(argv[1], "rev-list") != 0) {
        printf("Not implemented!\n");
        exit(1);
    }
    */
    int bac = 5;
    printf("Motiejus: %d, %X\n", bac, &bac);

    git_repository *repo;
    git_repository_open(&repo, ".");
    char *hex = (char*)malloc(41*sizeof(char));
    get_master_hex(hex); // do not look what's inside

    // Start rev-list code //

    git_oid id;
    git_revwalk *walk;
    git_commit *head;
    git_commit *commit;

    git_oid_mkstr(&id, hex);
    git_commit_lookup(&head, repo, &id);

    git_revwalk_new(&walk, repo);
    git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL | GIT_SORT_REVERSE);
    git_revwalk_push(walk, &id);

    git_signature *author;
    while ((commit = git_revwalk_next(&id, walk)) != NULL) {
        char * msg = git_commit_message_short(commit);
        author = git_commit_author(commit);
        printf("%s (%s)\n", msg, author->email);
    }
    return 0;
}
