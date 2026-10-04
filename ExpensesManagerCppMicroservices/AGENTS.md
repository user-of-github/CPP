# AGENTS.md

Guidance for AI agents working in this repository.

## Communication style

**Always respond concisely and to the point.** Use bullet points, tables, and short sentences. Avoid verbose explanations unless explicitly requested. Minimize token usage.

## Overview

**ExpensesManagerCppMicroservices** — a set of C++ microservices for managing expenses, receipts (cheques) and generating reports.

## Microservices

| Service | Path | Purpose | Status |
|---------|------|---------|--------|
| **receipt-service** | `receipt-service/` | REST API for receipts/cheques CRUD + classificators (categories, payment methods, retail chains, shops) | Active |
| **reports-service** | `reports-service/` | Excel report generation from PostgreSQL stored procedures | Active |
| **liquibase** | `liquibase/` | Shared database migrations and seeds | Active |

## Tech stack

- **Modern C++ (C++23)**, GNU/GCC 14
- **receipt-service**: Drogon framework, Drogon ORM, Jsoncpp
- **reports-service**: Crow framework, libpqxx, libxlsxwriter
- **PostgreSQL 17**, **Liquibase 4.29** (formatted SQL migrations)
- **Docker / Docker Compose**
- **CMake** build system

## Quick start

```bash
# 1. Copy .env.example → .env and fill in credentials
cp .env.example .env

# 2. Start Postgres + Liquibase migrations + both services
docker compose --env-file .env up --build
```

## Detailed guides

- `receipt-service/AGENTS.md` — receipt-service internals, code style, conventions
- `reports-service/AGENTS.md` — reports-service architecture, report generation flow
- `liquibase/AGENTS.md` — database migration conventions
