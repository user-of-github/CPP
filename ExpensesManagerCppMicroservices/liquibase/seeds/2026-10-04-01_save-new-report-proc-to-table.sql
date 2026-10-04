--liquibase formatted sql

--changeset user-of-github:03-seed-first-report-procedure
INSERT INTO reports_procedures_names (id, title, procedure_name)
VALUES (1, 'Category Spending Report', 'get_monthly_category_report');