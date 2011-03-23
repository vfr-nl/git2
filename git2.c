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



    /*
    git_odb *odb;
    git_odb_object *obj;
    git_oid *oid;

    unsigned char *data;
    const char *str_type;
    int error;

    if ((e = git_odb_open(&odb, ".git/objects")) != 0) {
        printf ("Fail on odb open: %d\n", e);
    }
    if (&odb == NULL) {
        printf("odb is null!\n");
    }

    //odb = git_repository_database(repo);
    git_oid_mkstr(&oid, "969b6084cbad1cb3f60443856b851340de30dc37");
    error = git_odb_read(&obj, odb, oid);
    */

    git_oid id;
    git_revwalk *walk;
    git_commit *head, *commit;

    git_oid_mkstr(&id, hex);
    printf("Raw 20 bytes: [%s]\n", (&id)->id);

    git_odb *odb; // fetch the object!
    odb = git_repository_database(repo);

    if (e = git_commit_lookup(&head, repo, &id) != 0) {
        printf("Error in git commit lookup: %d\n");
    }
    // Get git commit message of the commit
    char *msg = git_commit_message(head);
    printf("Commit message: %s\n", msg); // YAY!!!


    if (e = git_revwalk_new(&walk, repo)) printf("Fail: %d\n");
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
