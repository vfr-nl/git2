#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    char *hex = (char*)malloc(41*sizeof(char));
    get_master_hex(hex); // do not look what's inside

    int e;
    // Start rev-list code //
    git_repository *repo;
    if (e = git_repository_open(&repo, ".git") != 0) {
        printf("Error code: %d" , e);
    }

    git_oid id;
    git_revwalk *walk;
    git_commit *head, *commit;

    git_oid_mkstr(&id, hex);
    //printf("Raw 20 bytes: [%s]\n", (&id)->id);

    git_odb *odb; // fetch the object!
    odb = git_repository_database(repo);

    if (e = git_commit_lookup(&head, repo, &id) != 0) {
        printf("Error in git commit lookup: %d\n");
    }
    // Get git commit message of the commit
    char *msg = git_commit_message(head);
    printf("Commit message: %s\n", msg); // YAY!!!

    if (e = git_revwalk_new(&walk, repo)) printf("Fail walker: %d\n", e);
    //git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL | GIT_SORT_REVERSE);
    if (e = git_revwalk_push(walk, &id))
        printf("Failed revwalk push: %d\n", e);

    int ret = git_revwalk_next(&id, walk);
    char *hex2 = (char*) malloc(41*sizeof(char));

    git_oid_fmt(hex2, &id);
    printf("Hex2: %40s\n", hex2);

    
    while (git_revwalk_next(&id, walk) == GIT_SUCCESS) {
        git_oid_fmt(hex2, &id);
        printf("%s\n", hex2);
    }
    return 0;
}
