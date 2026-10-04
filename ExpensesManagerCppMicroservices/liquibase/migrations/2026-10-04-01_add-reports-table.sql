--liquibase formatted sql

--changeset user-of-github:01-create-reports-procedures
CREATE TABLE reports_procedures_names (
    id SERIAL PRIMARY KEY,
    title VARCHAR(100) NOT NULL,
    procedure_name VARCHAR(100) NOT NULL
);

COMMENT ON TABLE reports_procedures_names IS 'Registry of available report stored procedures';
COMMENT ON COLUMN reports_procedures_names.title IS 'Report title';
COMMENT ON COLUMN reports_procedures_names.procedure_name IS 'PL/pgSQL procedure name in Postgres DB';