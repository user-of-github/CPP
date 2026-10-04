# AGENTS.md — liquibase

Database migration layer for the ExpensesManager microservices. Shared by all services.

## Purpose

Manages PostgreSQL schema and seed data via **Liquibase 4.29** formatted-SQL migrations.

## Directory structure

```
liquibase/
  changelog-master.yaml          # Registry of all migrations (ORDER MATTERS)
  migrations/                    # Schema changes (DDL)
    YYYY-MM-DD-NN_description.sql
  seeds/                         # Test/reference data (INSERT)
    YYYY-MM-DD-NN_description.sql
```

## File naming convention

```
YYYY-MM-DD-NN_short-description.sql
```

- `YYYY-MM-DD` — date of creation
- `NN` — sequence number within the day (01, 02, ...)
- `short-description` — kebab-case, describes what the changeset does

Examples:
- `2026-09-19-01_create-base-classificators.sql`
- `2026-10-04-02_add-first-report-plsql.sql`

## Changeset format

Every file **must** start with:

```sql
--liquibase formatted sql

--changeset user-of-github:NN-description
<SQL statements here>

--comment: brief explanation of what this changeset does
```

- `user-of-github` — author ID (matches git user)
- `NN-description` — unique identifier for the changeset
- Each changeset is atomic; Liquibase tracks applied changesets in `databasechangelog` table

## Rules

1. **Register every new file in `changelog-master.yaml`** under `databaseChangeLog` → `include:` with `relativeToChangelogFile: true`.
2. **Order matters** — files are applied in the order listed in `changelog-master.yaml`.
3. **Never edit applied changesets** — Liquibase checksums them; editing breaks the chain. Add a new changeset instead.
4. **Migrations are DDL** (CREATE TABLE, ALTER TABLE, CREATE FUNCTION, etc.).
5. **Seeds are INSERT** statements for test/reference data.
6. **Comments** — use `--comment:` after the changeset header to explain intent.

## Example: adding a new migration

1. Create `liquibase/migrations/2026-10-05-01_add-users-table.sql`:
   ```sql
   --liquibase formatted sql
   
   --changeset user-of-github:01-add-users-table
   CREATE TABLE users (
       id SERIAL PRIMARY KEY,
       email VARCHAR(255) UNIQUE NOT NULL,
       created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
   );
   
   --comment: Add users table for authentication
   ```

2. Register it in `changelog-master.yaml`:
   ```yaml
   - include:
       file: migrations/2026-10-05-01_add-users-table.sql
       relativeToChangelogFile: true
   ```

3. Run `docker compose up` — Liquibase applies the new migration automatically.

## Current schema

- **Classificators**: `categories`, `payment_methods`, `retail_chains`, `concrete_shops`
- **Base entities**: `cheques`, `cheque_items`
- **Reports**: `reports_procedures_names` (registry of PL/pgSQL report procedures)
