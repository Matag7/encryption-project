# 🔐 Vigenère Cipher System

A terminal-based encryption tool written in C, implementing the Vigenère cipher algorithm with integrity verification, random key generation, and persistent file storage.

---

##  Overview

This project implements a complete Vigenère cipher system built entirely with only `<stdio.h>` and `<stdlib.h>` — no external libraries. The core components include encryption and decryption using a 26×26 Vigenère table, digital signature (checksum) for message integrity, a smart key generator, special character detection, a visual progress bar, and file-based storage.

---

##  Project Structure

```
.
├── src/
│   ├── main.c                  # Entry point and menu logic
│   ├── chiffrement.c           # Encryption module
│   ├── dechiffrement.c         # Decryption module
│   ├── checksum.c              # Integrity verification (digital signature)
│   ├── random.c                # Intelligent key generation
│   ├── fonction1_style.c       # Progress bar and terminal UI
│   ├── fonction_lecture.c      # File reading
│   └── fonction_stockage.c     # File writing and storage
├── application.sh              # Build/run script
└── README.md
```

---

##  Features

###  Encryption & Decryption
- Implements a full 26×26 Vigenère table
- Accepts alphabetic keys (uppercase or lowercase)
- Automatically truncates keys longer than the message
- Ignores spaces during encryption (with a warning)
- Rejects non-alphabetic characters in both message and key

###  Integrity Check (Checksum)
- Generates a unique `#XXXX` digital signature for each encrypted message
- Recalculates the signature at decryption time
- Displays a **red alert** in the terminal if the message has been tampered with
- Confirms integrity with a success message when the data is unmodified

###  Random Key Generation
- Generates 7-character keys with a balanced mix of uppercase and lowercase letters
- Designed to maximise complexity and resist simple pattern attacks

###  Progress Bar
- Animated progress bar (0% → 100%) displayed during encryption/decryption
- Adapts to the size of the data being processed
- Confirms completion with a success message

###  File Storage
- Save the **encrypted message** (with its checksum) to `donnees.txt`
- Save the **decrypted message** in plaintext to `donnees.txt`
- Read and display the contents of the stored file directly in the terminal
- Prevents saving if no operation has been performed yet

---

##  Getting Started

### Prerequisites

- GCC or any C99-compatible compiler
- Linux / macOS terminal (or WSL on Windows)

### Build & Run

```bash
chmod +x application.sh
./application.sh
```

Or compile manually:

```bash
gcc src/main.c src/chiffrement.c src/dechiffrement.c src/checksum.c \
    src/random.c src/fonction1_style.c src/fonction_lecture.c \
    src/fonction_stockage.c -o application
./application
```

---

##  Test Summary

All tests were conducted and passed across four categories:

| Category | Tests | Status |
|---|---|---|
| Encryption & Key Security | 1.1 → 1.5 | ✅ All OK |
| Checksum Integrity | 2.1 → 2.3 | ✅ All OK |
| Visual Interface (Progress Bar) | 3.1 → 3.2 | ✅ All OK |
| Storage & Data Persistence | 4.1 → 4.4 | ✅ All OK |

Key scenarios validated include nominal encryption/decryption, message reversibility, special character rejection, checksum generation and tampering detection, progress bar rendering, and file read/write operations.

---

##  Limitations

- Only **alphabetic characters** are encrypted. Digits and symbols are detected and flagged with a yellow warning, but are left in plaintext.
- The optional **dynamic Vigenère table** (shuffled alphabet via a table key) was scoped but not implemented in this version.

---

##  Team

| Name | Role |
|---|---|
| [Me](https://github.com/Matag7) | Project lead, `main.c`, random key generation, style |
| Anonyme | Encryption, decryption, additional features |
| Anonyme | File storage and reading |
| [Arealys](https://github.com/Arealys) | Decryption logic, additional features |

---

##  Technical Choices

The project was intentionally built using **only** `<stdio.h>` and `<stdlib.h>`. This constraint pushed the team to reimplement string manipulation functions from scratch and deepen understanding of C fundamentals such as pointers, 2D arrays, and manual memory handling.

---
