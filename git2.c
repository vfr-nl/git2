#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <git2.h>

/* doh ~stub */
void get_master_hex(char *hex) {
	FILE *f = fopen(".git/refs/heads/master", "r");
	fgets(hex, 41, f);
	fclose(f);
}

int main (int argc, char** argv) {
	int e;
	char hex[41], hex2[41];
	git_repository *repo;
	git_oid id;
	git_revwalk *walk;
	git_commit *head;
	git_odb *odb; /* fetch the object! */

	if (argc >= 2 && strcmp(argv[1], "rev-list") != 0) {
		printf("Not implemented!\n");
		exit(1);
	}

	if (argc != 3) {
		printf("Usage: git2 rev-list <commit>\n");
		exit(1);
	}

	get_master_hex(hex); /* do not look what's inside */

	/* Start rev-list code */
	if ((e = git_repository_open(&repo, ".git")) != 0)
		printf("Failed git repo open: %d" , e);

	git_oid_mkstr(&id, hex);

	odb = git_repository_database(repo);

	if ((e = git_commit_lookup(&head, repo, &id)) != 0)
		printf("Error in git commit lookup: %d\n", e);
	if ((e = git_revwalk_new(&walk, repo)) != 0)
		printf("Fail walker: %d\n", e);
	/*git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL); */
	if ((e = git_revwalk_push(walk, &id)) != 0)
		printf("Failed revwalk push: %d\n", e);

	git_oid_fmt(hex2, &id);
	while (git_revwalk_next(&id, walk) == GIT_SUCCESS) {
		git_oid_fmt(hex2, &id);
		hex2[40] = '\0';
		printf("%s\n", hex2);
	}
	return 0;
}
