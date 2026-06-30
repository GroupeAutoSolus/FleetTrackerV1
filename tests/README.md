# Tests

The tests folder is reserved for cross-project and system-level validation.

## Folder Responsibilities

- `firmware/`: Integration tests that exercise firmware behavior at a system level.
- `backend/`: API, ingestion, storage, and service integration tests.
- `dashboard/`: End-to-end UI and workflow tests.

Module-local firmware tests belong in `firmware/test/`.
