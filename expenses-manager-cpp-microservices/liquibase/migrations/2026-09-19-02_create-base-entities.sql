--liquibase formatted sql

--changeset user-of-github:02


CREATE TABLE retail_chains (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL UNIQUE
);

COMMENT ON TABLE retail_chains IS 'Retail chains';
COMMENT ON COLUMN retail_chains.id IS 'Unique id for retail-chain';
COMMENT ON COLUMN retail_chains.name IS 'Shop title';

CREATE TABLE concrete_shops (
    id SERIAL PRIMARY KEY,
    retail_chain_id INT REFERENCES retail_chains(id) ON UPDATE CASCADE ON DELETE CASCADE,
    address VARCHAR(100) NOT NULL UNIQUE,
    is_active BOOLEAN DEFAULT TRUE
);

COMMENT ON TABLE concrete_shops IS 'Concrete shop id';
COMMENT ON COLUMN concrete_shops.id IS 'Unique id for concrete shop';
COMMENT ON COLUMN concrete_shops.retail_chain_id IS 'Id of retailing-shop-chain (line)';
COMMENT ON COLUMN concrete_shops.address IS 'Address';
COMMENT ON COLUMN concrete_shops.is_active IS 'Working or closed';
CREATE INDEX idx_concrete_shops_retail_chain_id ON concrete_shops(retail_chain_id);



CREATE TABLE cheques (
    id BIGSERIAL PRIMARY KEY,
    concrete_store_id INT REFERENCES concrete_shops(id) ON UPDATE CASCADE ON DELETE SET NULL,
    payment_method_id INT REFERENCES payment_methods(id) ON UPDATE CASCADE ON DELETE SET NULL ,
    total_amount NUMERIC(12, 2) NOT NULL CHECK (total_amount >= 0),
    receipt_date TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    created_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE NOT NULL DEFAULT CURRENT_TIMESTAMP
);

COMMENT ON TABLE cheques IS 'Shopping cheques';
COMMENT ON COLUMN cheques.id IS 'Cheque id';
COMMENT ON COLUMN cheques.concrete_store_id IS 'Store of purchase FK';
COMMENT ON COLUMN cheques.payment_method_id IS 'Payment method FK';
COMMENT ON COLUMN cheques.total_amount IS 'Total sum of purchase cost';
COMMENT ON COLUMN cheques.receipt_date IS 'Cheque date';
COMMENT ON COLUMN cheques.created_at IS 'Created at';
COMMENT ON COLUMN cheques.updated_at IS 'Updated at';



CREATE TABLE cheque_items (
    id BIGSERIAL PRIMARY KEY,
    cheque_id BIGINT NOT NULL REFERENCES cheques(id) ON DELETE CASCADE,
    category_id INT REFERENCES categories(id) ON DELETE SET NULL,
    product_name VARCHAR(255) NOT NULL,
    quantity NUMERIC(10, 3) NOT NULL DEFAULT 1.000 CHECK (quantity > 0),
    unit_price NUMERIC(12, 2) NOT NULL CHECK (unit_price >= 0),
    total_price NUMERIC(12, 2) NOT NULL CHECK (total_price >= 0)
);

COMMENT ON TABLE cheque_items IS 'Concrete bought item';
COMMENT ON COLUMN cheque_items.id IS 'Unique row id';
COMMENT ON COLUMN cheque_items.cheque_id IS 'Parent receipt (cheque)';
COMMENT ON COLUMN cheque_items.category_id IS 'Item category id';
COMMENT ON COLUMN cheque_items.product_name IS 'Item title';
COMMENT ON COLUMN cheque_items.quantity IS 'Count (or weight, if in KG..)';
COMMENT ON COLUMN cheque_items.unit_price IS 'Price per 1 item';
COMMENT ON COLUMN cheque_items.total_price IS 'Total price (quantity * unit_price)';

CREATE INDEX idx_cheque_items_cheque_id ON cheque_items(cheque_id);
CREATE INDEX idx_cheque_items_category_id ON cheque_items(category_id);
