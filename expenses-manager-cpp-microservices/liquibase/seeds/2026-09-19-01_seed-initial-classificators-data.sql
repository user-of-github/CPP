--liquibase formatted sql

--changeset user-of-github:01
INSERT INTO payment_methods (name, is_active) VALUES
    ('Debit / Credit Card', TRUE),
    ('Cash', TRUE),
    ('QR Code (Oplati / Mobile)', TRUE),
    ('Loyalty Points', TRUE);

--changeset user-of-github:02
INSERT INTO categories (name, description) VALUES
    ('Groceries', 'Supermarket foods, diary, meat, and vegetables'),
    ('Household & Cleaning', 'Cleaning supplies, home detergents, and consumables'),
    ('Drinks & Snacks', 'Water, coffee, tea, soft drinks, and sweets'),
    ('Prepared Food & Bakery', 'Ready-to-eat meals, bakery, and deli counter'),
    ('Other', 'Uncategorized daily goods');

--changeset user-of-github:03
INSERT INTO retail_chains (name) VALUES
    ('Euroopt'),
    ('HIPPO'),
    ('Green');

--changeset user-of-github:04
-- Euroopt stores
INSERT INTO concrete_shops (retail_chain_id, address, is_active)
SELECT id, 'Minsk, Montazhnikov str. 2 (Euroopt Prime)', TRUE
FROM retail_chains WHERE name = 'Euroopt';

INSERT INTO concrete_shops (retail_chain_id, address, is_active)
SELECT id, 'Minsk, Dzerzhinskogo ave. 104 (Titan Mall)', TRUE
FROM retail_chains WHERE name = 'Euroopt';

-- HIPPO stores
INSERT INTO concrete_shops (retail_chain_id, address, is_active)
SELECT id, 'Minsk, Rokossovskogo ave. 2', TRUE
FROM retail_chains WHERE name = 'HIPPO';

INSERT INTO concrete_shops (retail_chain_id, address, is_active)
SELECT id, 'Minsk, Goretskogo str. 2', TRUE
FROM retail_chains WHERE name = 'HIPPO';

-- Green stores
INSERT INTO concrete_shops (retail_chain_id, address, is_active)
SELECT id, 'Minsk, Pritytskogo str. 156 (Green City Mall)', TRUE
FROM retail_chains WHERE name = 'Green';

INSERT INTO concrete_shops (retail_chain_id, address, is_active)
SELECT id, 'Minsk, Partizanski ave. 182', TRUE
FROM retail_chains WHERE name = 'Green';