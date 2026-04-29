# Contributing to Lokr

Thank you for your interest in contributing to **Lokr** — a minimal, security-focused password manager written in C.

Please read this document carefully before opening any issue or pull request.

---

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [How to Contribute](#how-to-contribute)
- [Pull Request Rules](#pull-request-rules)
- [Commit Style](#commit-style)
- [Code Style](#code-style)
- [Reporting Bugs](#reporting-bugs)
- [Suggesting Features](#suggesting-features)

---

## Code of Conduct

Be respectful. Contributions are reviewed by humans. Keep discussions technical, focused, and professional.

---

## Getting Started

1. **Fork** the repository and clone your fork locally.
2. Make sure you have the required dependencies:
   - `gcc` or `clang`
   - `libsodium` (dev headers)
   - `make`
3. Create a dedicated branch for your change — never work directly on main:
```sh
git checkout -b fix/Lokr-open-null-deref
# or
git checkout -b feat/entry-search-by-label

```
Branch names should follow the same prefix convention as commits: fix/, feat/, docs/, refactor/, test/.
4. Build the project:
   ```sh
   make
   ```

Or Recommended way :
   ```sh
mkdir build && cd build
cmake ..
cmake --build .
   ```

---

## How to Contribute

- Browse open [issues](../../issues) for something to work on.
- If you want to fix something not listed, **open an issue first** and describe what you intend to do. Wait for acknowledgment before starting work.
- Small, focused contributions are strongly preferred over large sweeping changes.

---

## Pull Request Rules

> These rules are strictly enforced. PRs that do not follow them will be closed without review.

### ✦ One thing per PR — no exceptions

Every pull request must do **exactly one of the following**:

- Fix one specific bug
- Add one specific feature
- Improve one specific area of the codebase (refactor, docs, tests)

**Do not** bundle multiple fixes, multiple features, or unrelated changes in a single PR. If you have three things to contribute, open three separate PRs.

### ✦ Be precise

Your PR description must clearly state:

- **What** the change does (one sentence)
- **Why** it is needed (one or two sentences)
- **How** it was tested

Vague descriptions like *"misc fixes"*, *"improvements"*, or *"cleaned up some stuff"* will result in the PR being closed immediately.

### ✦ PR Checklist

Before submitting, verify that:

- [ ] The PR touches only what it claims to touch
- [ ] The code compiles cleanly with no warnings (`-Wall -Wextra`)
- [ ] All existing tests pass (`make`)
- [ ] New behavior is covered by a test where applicable
- [ ] No unrelated files are modified (whitespace-only changes, unrelated headers, etc.)
- [ ] The commit history is clean (see [Commit Style](#commit-style))

---

## Commit Style

Use short, imperative commit messages:

```
fix: null dereference in vault_open() when path is empty
feat: add entry search by label in CLI
docs: clarify Argon2id parameter rationale in README
refactor: extract base64 encode/decode into util module
test: add roundtrip test for crypto_secretbox blob layout
```

Prefix format: `fix:` / `feat:` / `docs:` / `refactor:` / `test:` / `chore:`

Keep each commit focused. Do not mix formatting changes with logic changes in the same commit.

---

## Code Style

- Follow the existing code style — consistency matters more than personal preference.
- Use `snake_case` for all identifiers.
- Keep functions small and single-purpose.
- Avoid dynamic memory allocation unless strictly necessary; always pair `malloc` with a corresponding `free` and check for `NULL`.
- Sensitive memory (keys, plaintext passwords) must be wiped with `sodium_memzero()` before being freed or going out of scope.
- Do not introduce external dependencies without prior discussion in an issue.

---

## Reporting Bugs

Open an issue and include:

- A short, descriptive title
- Steps to reproduce
- Expected vs actual behavior
- Output of `gcc --version` and `pkg-config --modversion libsodium`
- Relevant compiler warnings or runtime output

---

## Suggesting Features

Open an issue tagged `enhancement` and describe:

- The problem the feature solves
- The proposed behavior
- Any security implications you are aware of

Features that weaken the cryptographic design of Lokr (e.g., weaker KDF parameters, optional encryption) will not be accepted.

---

*When in doubt: keep it small, keep it precise, keep it secure.*
