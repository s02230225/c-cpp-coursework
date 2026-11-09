#include "mv.h"
int copy_permissions(const char *src, const char *dest) {
    struct stat st;
    if (stat(src, &st) == -1) {
        perror("stat");
        return 1;
    }
    if (chmod(dest, st.st_mode) == -1){
        perror("chmod");
        return 1;
    }
    return 0;
}

int move(const char *old_file, const char *new_file) {
    if (rename(old_file, new_file)!=0){
	perror("mv");
	return 1;
    }
    return 0;
}

int mymv(int argc, char *argv[]) {
    if (!(argc==3)) {
        fprintf(stderr, "Usage: %s <old_file> <new_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
	if (strcmp(argv[1], argv[2])==0){
		fprintf(stderr, "mv: '%s' and '%s' are the same file\n", argv[1], argv[2]);
		return 1;
	}
   struct stat fileStat;
    const char *old_file = argv[1];
    const char *new_file = argv[2];
    char cwd[MAX_LINE_LENGTH/2];
    char fullPath[MAX_LINE_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) == NULL){
	    perror("getcwd");
	    return 0;
    }
    snprintf(fullPath, sizeof(fullPath), "%s/%s", cwd, old_file);
    if (stat(fullPath, &fileStat) < 0) {
	    perror("stat");
            return 0;
    }
    move(old_file, new_file);
    printf("Size: %ld\n", fileStat.st_size);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    mymv(argc, argv);
    return 0;
}
