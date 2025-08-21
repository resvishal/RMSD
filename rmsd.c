#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ATOMS 10000

typedef struct {
    double x, y, z;
} Atom;

int read_ca(const char *filename, Atom atoms[]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Cannot open %s\n", filename);
        exit(1);
    }
    char line[200];
    int n = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "ATOM", 4) == 0 && strncmp(&line[13], "CA", 2) == 0) {
            sscanf(&line[30], "%lf %lf %lf", &atoms[n].x, &atoms[n].y, &atoms[n].z);
            n++;
        }
    }
    fclose(fp);
    return n;
}

double rmsd(Atom a[], Atom b[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double dx = a[i].x - b[i].x;
        double dy = a[i].y - b[i].y;
        double dz = a[i].z - b[i].z;
        sum += dx*dx + dy*dy + dz*dz;
    }
    return sqrt(sum / n);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s file1.pdb file2.pdb\n", argv[0]);
        return 1;
    }

    Atom atoms1[MAX_ATOMS], atoms2[MAX_ATOMS];
    int n1 = read_ca(argv[1], atoms1);
    int n2 = read_ca(argv[2], atoms2);

    if (n1 != n2) {
        printf("Error: Different number of C-alpha atoms (%d vs %d)\n", n1, n2);
        return 1;
    }

    printf("RMSD = %.3f Ã\n", rmsd(atoms1, atoms2, n1));
    return 0;
}
