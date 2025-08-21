# 🧬 Protein Structure RMSD & Alignment Tool (C)

A simple **C program** to calculate **RMSD (Root Mean Square Deviation)** between two protein structures given in **PDB format**.  
The script also performs a **least-squares alignment** before RMSD calculation, ensuring the best structural overlap.

---

## ✨ Features
- Reads two **PDB files** and extracts only **Cα atoms**.
- Performs **centroid alignment**.
- Uses the **Kabsch algorithm** for optimal superposition.
- Computes **RMSD** between the two structures.
- Lightweight, fast, and dependency-free (pure C).

---

## 📂 Repository Structure
📦 RMSD-Align-C
┣ 📜 rmsd.c # Main source code
┣ 📜 4bfz.pdb # Example structure 1
┣ 📜 4bfu.pdb # Example structure 2
┣ 📜 README.md # Documentation


---

## ⚡ Installation & Compilation
Compile with `gcc` (use `-std=c99` flag to allow modern C loops):
```bash
gcc -std=c99 -o rmsd rmsd.c -lm

## **Run the program with two pdb filenames**

./rmsd 4bfz.pdb 4bfu.pdb

## **Example output**
Read 288 Cα atoms from 4bfz.pdb
Read 288 Cα atoms from 4bfu.pdb
Centroid of structure 1: (12.34, 8.92, 15.67)
Centroid of structure 2: (12.21, 9.05, 15.82)
Best-fit RMSD = 1.87 Å
