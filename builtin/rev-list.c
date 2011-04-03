#include <stdio.h>
#include <stdlib.h>

#include <git2.h>

static const char rev_list_usage[] =
"git rev-list [OPTION] <commit-id>... [ -- paths... ]\n"
"  limiting output:\n"
"    --max-count=<n>\n"
"    --max-age=<epoch>\n"
"    --min-age=<epoch>\n"
"    --sparse\n"
"    --no-merges\n"
"    --remove-empty\n"
"    --all\n"
"    --branches\n"
"    --tags\n"
"    --remotes\n"
"    --stdin\n"
"    --quiet\n"
"  ordering output:\n"
"    --topo-order\n"
"    --date-order\n"
"    --reverse\n"
"  formatting output:\n"
"    --parents\n"
"    --children\n"
"    --objects | --objects-edge\n"
"    --unpacked\n"
"    --header | --pretty\n"
"    --abbrev=<n> | --no-abbrev\n"
"    --abbrev-commit\n"
"    --left-right\n"
"  special purpose:\n"
"    --bisect\n"
"    --bisect-vars\n"
"    --bisect-all"
;


/* doh ~stub */
static void get_master_hex(char *hex) {
	FILE *f = fopen(".git/refs/heads/master", "r");
	fgets(hex, 41, f);
	fclose(f);
}


int cmd_rev_list(int argc, const char **argv)
{
//	int i;

	int e;
	char hex[41], hex2[41];
	git_repository *repo;
	git_oid id;
	git_revwalk *walk;
	git_commit *head;
//	git_odb *odb; /* fetch the object! */

	if (argc != 1) {
		printf(rev_list_usage);
		printf("\n");
	}

	/* Start rev-list code */
	if ((e = git_repository_open(&repo, ".git")) != 0)
		printf("Failed git repo open: %d\n" , e);

	get_master_hex(hex); /* do not look what's inside */
	git_oid_mkstr(&id, hex);

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

	//odb = git_repository_database(repo);

	//struct rev_info revs;
	//struct rev_list_info info;
	//int bisect_list = 0;
	//int bisect_show_vars = 0;
	//int bisect_find_all = 0;
	//int quiet = 0;

	//git_config(git_default_config, NULL);
	//init_revisions(&revs, prefix);
	//revs.abbrev = DEFAULT_ABBREV;
	//revs.commit_format = CMIT_FMT_UNSPECIFIED;
	//argc = setup_revisions(argc, argv, &revs, NULL);

	//memset(&info, 0, sizeof(info));
	//info.revs = &revs;
	//if (revs.bisect)
	//	bisect_list = 1;

	//quiet = DIFF_OPT_TST(&revs.diffopt, QUICK);
	//for (i = 1 ; i < argc; i++) {
	//	const char *arg = argv[i];
	
	//	if (!strcmp(arg, "--header")) {
	//		revs.verbose_header = 1;
	//		continue;
	//	}
	//	if (!strcmp(arg, "--timestamp")) {
	//		info.show_timestamp = 1;
	//		continue;
	//	}
	//	if (!strcmp(arg, "--bisect")) {
	//		bisect_list = 1;
	//		continue;
	//	}
	//	if (!strcmp(arg, "--bisect-all")) {
	//		bisect_list = 1;
	//		bisect_find_all = 1;
	//		info.bisect_show_flags = BISECT_SHOW_ALL;
	//		revs.show_decorations = 1;
	//		continue;
	//	}
	//	if (!strcmp(arg, "--bisect-vars")) {
	//		bisect_list = 1;
	//		bisect_show_vars = 1;
	//		continue;
	//	}
	//	usage(rev_list_usage);

	//}
	//if (revs.commit_format != CMIT_FMT_UNSPECIFIED) {
	//	/* The command line has a --pretty  */
	//	info.hdr_termination = '\n';
	//	if (revs.commit_format == CMIT_FMT_ONELINE)
	//		info.header_prefix = "";
	//	else
	//		info.header_prefix = "commit ";
	//}
	//else if (revs.verbose_header)
	//	/* Only --header was specified */
	//	revs.commit_format = CMIT_FMT_RAW;

	//if ((!revs.commits &&
	//     (!(revs.tag_objects||revs.tree_objects||revs.blob_objects) &&
	//      !revs.pending.nr)) ||
	//    revs.diff)
	//	usage(rev_list_usage);

	//save_commit_buffer = (revs.verbose_header ||
	//		      revs.grep_filter.pattern_list ||
	//		      revs.grep_filter.header_list);
	//if (bisect_list)
	//	revs.limited = 1;

	//if (prepare_revision_walk(&revs))
	//	die("revision walk setup failed");
	//if (revs.tree_objects)
	//	mark_edges_uninteresting(revs.commits, &revs, show_edge);

	//if (bisect_list) {
	//	int reaches = reaches, all = all;

	//	revs.commits = find_bisection(revs.commits, &reaches, &all,
	//				      bisect_find_all);

	//	if (bisect_show_vars)
	//		return show_bisect_vars(&info, reaches, all);
	//}

	//traverse_commit_list(&revs,
	//		     quiet ? finish_commit : show_commit,
	//		     quiet ? finish_object : show_object,
	//		     &info);

	//if (revs.count) {
	//	if (revs.left_right)
	//		printf("%d\t%d\n", revs.count_left, revs.count_right);
	//	else
	//		printf("%d\n", revs.count_left + revs.count_right);
	//}

	//return 0;
}