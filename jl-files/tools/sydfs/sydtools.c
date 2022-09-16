#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <errno.h>
#include <libgen.h>

#include "kagami_mochi.h"




const char *opts_short = "k:pcCb:ef";
const struct option opts_long[] = {
	{"help",	0, NULL, 'h'},
	{"key",	1, NULL, 'k'},
	{"pack",	0, NULL, 'p'},
	{"crypt",	0, NULL, 'c'},
	{"fcrypt",	0, NULL, 'C'},
	{"blocksize",	1, NULL, 'b'},
	{"end",	0, NULL, 'e'},
	{"fill",	0, NULL, 'f'},
	NULL
};

void usage() {
	fprintf(stderr,
		"Usage: *** [OPTION]... input_file [output_dir]\n"
		"   OR: *** [OPTION]... output_file [file_type file_name]...\n"
		"Tool for dealing with SYDFS, which is a filesystem that is used as a read-only\n"
		"file storage format in JieLi's SoCs (AC69, AC52, AC46..)\n"
		"\n"
		"      --help             prints this help message\n"
		"  -k, --key=key          set the encryption key to `key` (default 0xffff)\n"
		"  -p, --pack             packs files into syd, instead of unpacking\n"
		"  -c, --crypt            de/encrypt header\n"
		"  -C, --fcrypt           de/encrypt in/output file (useful when dealing with\n"
		"                          user.app files, for example).\n"
		"  -b, --blocksize=size   set the alignment block size (default 512)\n"
		"  -e, --end              place the header at the end or expect it to be here.\n"
		"  -f, --fill             fill unused places with 1s\n"
		"\n"
		"When unpacking, it decrypts the whole file (if --fcrypt option is present), then\n"
		" it searches for the syd header, and if crc check fails, it steps for/backwards\n"
		" by the size of the header (%ld bytes)\n"
		, sizeof(struct jl_syd_head)
		);
}

int main(int argc, char **argv) {
	printf("SYDTOOL v1.1\n" // by ewogs30 (konata@acebeca0.net)\n" //FAKE!
	       "Compiled %s -- %s\n", __DATE__, __TIME__);

	/* ========= get arguments ========= */
	uint16_t cryptkey=0xffff;
	int action=0, flags=0, blocksize=512;

	while (1) {
		int opt = getopt_long(argc, argv, opts_short, opts_long, NULL);
		if (opt == -1) break;

		switch (opt) {
		case '?':
			usage();
			return -1;
		case 'h':
			usage();
			return 0;
		case 'k':
			cryptkey = strtol(optarg, NULL, 0);
			break;
		case 'b':
			blocksize = strtol(optarg, NULL, 0);
			break;
		case 'p':
			action = 1;
			break;
		case 'c':
			flags |= 1;
			break;
		case 'C':
			flags |= 2;
			break;
		case 'e':
			flags |= 4;
			break;
		case 'f':
			flags |= 8;
			break;
		}
	}

	char **sargv = argv + optind;
	int sargc = argc - optind;

	if (sargc == 0) {
		fprintf(stderr, "Error: input/output file name is required.\n");
		return -2;
	}

	printf("cryptkey=%x, flags=%d, action=%d, blocksize=%d\n", cryptkey, flags, action, blocksize);

	/* ================================================================== */
	FILE *sydfp;
	void *sydptr;
	size_t sydsize;
	struct jl_syd_head *sydhead;
	struct jl_syd_entry *sydentry;

	if (action == 0) { 
		/* unpack */
		char dirpaths[1024];
		char *dirpath = "./";
		if (sargc >= 2) dirpath = sargv[1];

		/* ---- Load the file ---- */
		sydfp = fopen(sargv[0], "rb");
		if (!sydfp) {
			fprintf(stderr, "Error: failed to open file `%s` for reading! errno: %d\n", sargv[0], errno);
			return errno;
		}

		fseek(sydfp, 0, SEEK_END);
		sydsize = ftell(sydfp);
		fseek(sydfp, 0, SEEK_SET);

		sydptr = malloc(sydsize);
		if (!sydptr) {
			fprintf(stderr, "Error: failed to allocate %ld bytes for syd data! errno: %d\n", sydsize, errno);
			fclose(sydfp);
			return errno;
		}

		sydsize = fread(sydptr, 1, sydsize, sydfp);
		fclose(sydfp);

		if (sydsize < sizeof(struct jl_syd_head)) {
			fprintf(stderr, "Error: file is too small!\n");
			free(sydptr);
			return -2;
		}

		/* ========================================= */

		if (flags & 2) jl_crypt_dyn(sydptr, sydsize, cryptkey, 0);

		if (flags & 4) sydhead = sydptr + sydsize - 32; // at the end
		else           sydhead = sydptr;                // at the start

		uint16_t crccalc;

		// find the syd header...
		while (1) {
			if (sydhead < sydptr || sydhead >= (sydptr + sydsize)) break;

			if (flags & 1) jl_crypt(sydhead, sizeof(struct jl_syd_head), cryptkey); // decrypt it

			crccalc = jl_crc16(&sydhead->crc16_list, sizeof(struct jl_syd_head) - 2, 0);
			if (crccalc == sydhead->crc16_head) {
				size_t hdrsize = sydsize - ((void*)sydhead - sydptr);
				sydentry = sydhead + 1;

				// check for validity of header's data (file count)
				if (sydhead->file_count <= ((hdrsize - sizeof(struct jl_syd_head)) / sizeof(struct jl_syd_entry))) {
					crccalc = jl_crc16(sydentry, sydhead->file_count * sizeof(struct jl_syd_entry), 0);

					if (crccalc == sydhead->crc16_list) {crccalc = 1; break;} // FOUND!
					crccalc = 0;
				}
			}

			// go forwards/backwards
			if (flags & 4) sydhead--;
			else           sydhead++;

			if (flags & 1) jl_crypt(sydhead, sizeof(struct jl_syd_head), cryptkey); // encrypt it back, to preserve accidentaly-crypted data
		}

		if (crccalc == 1) {
			printf("Found at 0x%lx!\n", ((void*)sydhead - sydptr));

			printf("Header:\n"
			       "  crc16_head: 0x%04x\n"
			       "  crc16_list: 0x%04x\n"
			       "  info1:      0x%08x\n"
			       "  info2:      0x%08x\n"
			       "  file_count: %d\n"
			       "  version1:   0x%08x\n"
			       "  version2:   0x%08x\n"
			       "  chiptype1:  0x%08x\n"
			       "  chiptype2:  0x%08x\n"
			       "\n",
				sydhead->crc16_head, sydhead->crc16_list, sydhead->info1, sydhead->info2, 
				sydhead->file_count, sydhead->version1, sydhead->version2, 
				sydhead->chiptype1, sydhead->chiptype2
				);

			for (int i = 0; i < sydhead->file_count; i++) {
				if (flags & 1) jl_crypt(&sydentry[i], sizeof(struct jl_syd_entry), cryptkey);

				printf("=> `%-15s`: #%d - type:%02x, @%08x, size: %d, crc: %04x\n", 
				sydentry[i].name, sydentry[i].num, sydentry[i].file_type, sydentry[i].addr, sydentry[i].size, sydentry[i].crc16);

				if ((sydentry[i].addr + sydentry[i].size) >= sydsize) {
					fprintf(stderr, "Error: this file have too ambigous address and/or size!\n");
					break;
				}

				if (sydentry[i].crc16 != jl_crc16(sydptr + sydentry[i].addr, sydentry[i].size, 0))
					printf("Warning: this file has invalid crc! This file may be corrupted.\n");

				// write out this file
				sprintf(dirpaths, "%s%s", dirpath, sydentry[i].name);
				sydfp = fopen(dirpaths, "wb");
				if (!sydfp) {
					fprintf(stderr, "Error: could not open `%s` for writing! errno: %d\n", dirpaths, errno);
					break;
				}

				fwrite(sydptr + sydentry[i].addr, 1, sydentry[i].size, sydfp);
				fclose(sydfp);
			}
		} else fprintf(stderr, "Error: couldn't find syd header!\n");

		free(sydptr);
	} else if (action == 1) {
		/* pack */
		uint16_t crccalc;
		size_t filesize, filepos, sydpos;
		int nfiles = sargc / 2;
		sydsize = sydpos = 0;

		int hdrsize = sizeof(struct jl_syd_head) + sizeof(struct jl_syd_entry) * nfiles;
		if (blocksize) hdrsize += blocksize - (hdrsize % blocksize);

		if (flags & 4) filepos = 0;
		else           filepos = hdrsize;

		sydhead = malloc(hdrsize);
		if (!sydhead) {
			fprintf(stderr, "Error: failed to allocate %d bytes for header! errno: %d\n", hdrsize, errno);
			return errno;
		}
		if (flags & 8) memset(sydhead, 0xff, hdrsize);

		sydentry = sydhead + 1;
		sydhead->file_count = nfiles;

		sydptr = malloc(0);
		if (!sydptr) {
			fprintf(stderr, "Error: allocation of 0 bytes somehow failed !!! errno: %d\n", errno);
			free(sydhead);
			return errno;
		}

		for (int i = 0; i < nfiles; i++) {
			sydfp = fopen(sargv[1 + i*2], "rb");
			if (!sydfp) {
				fprintf(stderr, "Error: failed to open file `%s` for reading! errno: %d\n", sargv[1 + i*2], errno);
				break;
			}
			fseek(sydfp, 0, SEEK_END);
			filesize = ftell(sydfp);
			fseek(sydfp, 0, SEEK_SET);

			sydsize += filesize;
			if (filesize && blocksize) sydsize += blocksize - sydsize % blocksize;

			sydptr = realloc(sydptr, sydsize);
			if (!sydptr) {
				fprintf(stderr, "Error: failed to extend syd data size to %d bytes! errno: %d\n", sydsize, errno);
				fclose(sydfp);
				free(sydhead);
				return errno;
			}

			filesize = fread(sydptr + sydpos, 1, filesize, sydfp);
			fclose(sydfp);

			if (flags & 8) memset(sydptr + sydpos + filesize, 0xff, sydsize - filesize - sydpos);

			sydentry[i].crc16 = jl_crc16(sydptr + sydpos, filesize, 0);
			sydentry[i].file_type = (sargc - 1 - i*2 > 1)?strtol(sargv[2 + i*2], NULL, 0):0;
			sydentry[i].addr = filepos;
			sydentry[i].size = filesize;
			sydentry[i].num = i;
			strcpy(sydentry[i].name, basename(sargv[1 + i*2]));

			printf("=> `%-15s`: #%d - type:%02x, @%08x, size: %d, crc: %04x\n", 
				sydentry[i].name, sydentry[i].num, sydentry[i].file_type, sydentry[i].addr, sydentry[i].size, sydentry[i].crc16);

			if (flags & 1) jl_crypt(&sydentry[i], sizeof(struct jl_syd_entry), cryptkey);

			filepos += filesize; sydpos += filesize;
			if (filesize && blocksize) {
				filepos += blocksize - filesize % blocksize;
				sydpos += blocksize - filesize % blocksize;
			}
		}

		sydhead->crc16_list = jl_crc16(sydentry, sizeof(struct jl_syd_entry) * sydhead->file_count, 0);
		sydhead->crc16_head = jl_crc16(&sydhead->crc16_list, sizeof(struct jl_syd_head) - 2, 0);
		if (flags & 1) jl_crypt(sydhead, sizeof(struct jl_syd_head), cryptkey);

		// write the file!
		sydfp = fopen(sargv[0], "wb");
		if (!sydfp) {
			fprintf(stderr, "Error: failed to open file `%s` for writing! errno: %d\n", sargv[0], errno);
			free(sydptr);
			free(sydhead);
			return errno;
		}
		
		if (flags & 2) {
			jl_crypt_dyn(sydptr, sydsize, cryptkey,  flags&4 ? 0       : hdrsize);
			jl_crypt_dyn(sydhead, hdrsize, cryptkey, flags&4 ? sydsize : 0      );
		}
		
		if (flags & 4) {
			fwrite(sydptr, 1, sydsize, sydfp);
			fwrite(sydhead, 1, hdrsize, sydfp);
		} else {
			fwrite(sydhead, 1, hdrsize, sydfp);
			fwrite(sydptr, 1, sydsize, sydfp);
		}
		
		fclose(sydfp);
		
		free(sydptr);
		free(sydhead);
	}

	return 0;
}
