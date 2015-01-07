/* Copyright (c) 2015, Vsevolod Stakhov
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *       * Redistributions of source code must retain the above copyright
 *         notice, this list of conditions and the following disclaimer.
 *       * Redistributions in binary form must reproduce the above copyright
 *         notice, this list of conditions and the following disclaimer in the
 *         documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/types.h>
#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

#include "asignify.h"
#include "cli.h"

int quiet = 0;

static void
usage(const char *error)
{
	if (error)
		fprintf(stderr, "%s\n", error);

	fprintf(stderr, "usage:"
	    "\tasignify [-q] %s\n"
	    "\tasignify [-q] %s\n"
	    "\tasignify [-q] %s\n"
	    "\tasignify [-q] %s\n",
	    cli_verify_help(), cli_check_help(), cli_sign_help(), cli_generate_help());

	exit(EXIT_FAILURE);
}

int
main(int argc, char **argv)
{
	int ch, ret = -1;
	static struct option long_options[] = {
		{"quiet",   no_argument,       0,  'q' },
		{"help", 	no_argument,       0,  'h' },
		{"version",	no_argument,       0,  'v' },
		{0,         0,                 0,  0 }
	};


	while ((ch = getopt_long(argc, argv, "qhv", long_options, NULL)) != -1) {
		switch (ch) {
		case 'q':
			quiet = 1;
			break;
		case 'h':
		case 'v':
		default:
			usage(NULL);
			break;
		}
	}
	argc -= optind;
	argv += optind;

	/* Read command as the next argument */
	if (argc == 0) {
		usage("must specify at least one command");
	}

	if (strcasecmp(argv[0], "check") == 0) {
		ret = cli_check(argc - 1, argv + 1);
	}
	else if (strcasecmp(argv[0], "verify") == 0) {
		ret = cli_verify(argc - 1, argv + 1);
	}
	else if (strcasecmp(argv[0], "sign") == 0) {
		ret = cli_sign(argc - 1, argv + 1);
	}
	else if (strcasecmp(argv[0], "generate") == 0) {
		ret = cli_generate(argc - 1, argv + 1);
	}
	else if (strcasecmp(argv[0], "help") == 0) {
		usage(NULL);
	}

	if (ret == 0) {
		usage(NULL);
	}
	else if (ret == -1) {
		exit(EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
