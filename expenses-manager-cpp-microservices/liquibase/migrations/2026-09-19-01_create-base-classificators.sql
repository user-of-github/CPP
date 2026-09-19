--liquibase formatted sql

--changeset user-of-github:01

CREATE TABLE payment_methods (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    is_active BOOLEAN NOT NULL DEFAULT TRUE
);

COMMENT ON TABLE payment_methods IS 'Classificator of available payment methods (cash, card, QR..)';
COMMENT ON COLUMN payment_methods.id IS 'Unique id of payment method';
COMMENT ON COLUMN payment_methods.name IS 'Name/description';
COMMENT ON COLUMN payment_methods.is_active IS 'Is active';


CREATE TABLE categories (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL UNIQUE,
    description TEXT
);

COMMENT ON TABLE categories IS 'Classificator of goods/expenses categories';
COMMENT ON COLUMN categories.id IS 'Unique id for category';
COMMENT ON COLUMN categories.name IS 'Category title';
COMMENT ON COLUMN categories.description IS 'Category description';
