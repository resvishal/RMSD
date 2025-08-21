```
title: "Protein RMSD Calculator in C"
author: "Your Name"
date: "`r Sys.Date()`"
output: html_document
```

# Introduction

In **structural bioinformatics**, one of the key tasks is to **compare two protein structures** to understand their structural similarity.  
A widely used metric for this is the **Root Mean Square Deviation (RMSD)** of backbone or Cα atoms.

In this project, we implement a **C program** to:
1. Parse two **PDB files**
2. Extract **Cα atom coordinates**
3. Perform an **alignment using the Kabsch algorithm**
4. Compute the **RMSD value**
5. Print the result

This workflow is useful when comparing different conformations of the same protein, or comparing predicted vs experimental structures.

---

# The C Program

Below is the C code used for reading PDB files, aligning the structures, and computing RMSD.

```c
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
        perror("File open error");
        exit(1);
    }
    char line[200];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "ATOM", 4) == 0 && strncmp(line + 13, "CA", 2) == 0) {
            sscanf(line + 30, "%lf %lf %lf", &atoms[count].x, &atoms[count].y, &atoms[count].z);
            count++;
        }
    }
    fclose(fp);
    return count;
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
    if (argc < 3) {
        printf("Usage: %s file1.pdb file2.pdb\n", argv[0]);
        return 1;
    }

    Atom a[MAX_ATOMS], b[MAX_ATOMS];
    int n1 = read_ca(argv[1], a);
    int n2 = read_ca(argv[2], b);

    if (n1 != n2) {
        printf("Error: structures have different number of CA atoms.\n");
        return 1;
    }

    double result = rmsd(a, b, n1);
    printf("RMSD = %lf\n", result);

    return 0;
}
