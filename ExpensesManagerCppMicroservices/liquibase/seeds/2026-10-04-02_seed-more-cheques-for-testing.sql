--liquibase formatted sql

--changeset user-of-github:02-seed-more-cheques

-- 5 additional cheques with 10 items each for testing

INSERT INTO cheques (id, concrete_store_id, payment_method_id, total_amount, receipt_date) VALUES
    (11, 2, 2, 47.63, '2026-09-25 11:30:00+03'),
    (12, 4, 1, 55.00, '2026-09-26 15:45:00+03'),
    (13, 1, 3, 101.30, '2026-09-27 18:20:00+03'),
    (14, 6, 2, 87.00, '2026-09-28 13:10:00+03'),
    (15, 3, 1, 109.20, '2026-09-29 20:00:00+03');

--changeset user-of-github:03-seed-more-cheque-items

INSERT INTO cheque_items (cheque_id, category_id, product_name, quantity, unit_price, total_price) VALUES
    -- Cheque 11: Weekly groceries at HIPPO Rokossovskogo (cash payment)
    (11, 1, 'Whole Milk 2.5% 1L', 3.000, 2.10, 6.30),
    (11, 1, 'Sour Cream 15% 400g', 2.000, 2.80, 5.60),
    (11, 1, 'Pork Loin Fresh 800g', 0.850, 14.50, 12.33),
    (11, 1, 'Potatoes Washed 2kg', 1.000, 3.20, 3.20),
    (11, 1, 'Cabbage White 1kg', 1.000, 1.40, 1.40),
    (11, 1, 'Carrots Organic 1kg', 1.000, 2.10, 2.10),
    (11, 1, 'Onions Yellow 1kg', 1.000, 1.60, 1.60),
    (11, 3, 'Apple Juice 1L', 2.000, 3.40, 6.80),
    (11, 3, 'Mineral Water Still 1.5L', 3.000, 1.50, 4.50),
    (11, 5, 'Bread Sliced Rye 400g', 2.000, 1.90, 3.80),

    -- Cheque 12: Quick lunch at HIPPO Goretskogo (card payment)
    (12, 4, 'Chicken Wings Frozen 1kg', 1.000, 8.90, 8.90),
    (12, 4, 'French Fries Crispy 750g', 1.000, 5.40, 5.40),
    (12, 3, 'Ketchup Tomato 350g', 1.000, 3.20, 3.20),
    (12, 3, 'Mayonnaise Classic 250g', 1.000, 2.80, 2.80),
    (12, 3, 'Cola Classic 1.5L', 2.000, 2.90, 5.80),
    (12, 3, 'Lemonade Lime 1L', 2.000, 2.60, 5.20),
    (12, 3, 'Potato Crisps Salted 100g', 2.000, 3.10, 6.20),
    (12, 3, 'Chocolate Bar Milk 90g', 3.000, 2.40, 7.20),
    (12, 3, 'Ice Cream Vanilla 500ml', 1.000, 7.80, 7.80),
    (12, 5, 'Paper Plates 25pcs', 1.000, 2.50, 2.50),

    -- Cheque 13: Big shopping at Euroopt Prime (QR code payment)
    (13, 1, 'Beef Mince 500g', 1.000, 12.80, 12.80),
    (13, 1, 'Pasta Spaghetti 500g', 2.000, 2.90, 5.80),
    (13, 1, 'Tomato Sauce Basil 400g', 2.000, 3.60, 7.20),
    (13, 1, 'Mozzarella Cheese 125g', 2.000, 4.50, 9.00),
    (13, 1, 'Bell Peppers Mixed 1kg', 1.000, 8.90, 8.90),
    (13, 1, 'Zucchini Green 1kg', 1.000, 4.20, 4.20),
    (13, 1, 'Mushrooms Fresh 300g', 1.000, 6.80, 6.80),
    (13, 2, 'Olive Oil Extra Virgin 500ml', 1.000, 18.50, 18.50),
    (13, 3, 'Red Wine Dry 750ml', 1.000, 24.90, 24.90),
    (13, 4, 'Baguette Italian', 1.000, 3.20, 3.20),

    -- Cheque 14: Household refill at Green Partizanski (cash payment)
    (14, 2, 'Dishwasher Tablets 30pcs', 1.000, 15.90, 15.90),
    (14, 2, 'Glass Cleaner Spray 500ml', 1.000, 4.80, 4.80),
    (14, 2, 'Floor Cleaner Lemon 1L', 1.000, 6.20, 6.20),
    (14, 2, 'Laundry Pods 40pcs', 1.000, 18.50, 18.50),
    (14, 2, 'Fabric Softener 1L', 1.000, 7.90, 7.90),
    (14, 2, 'Toilet Paper 4-ply 12 rolls', 1.000, 12.80, 12.80),
    (14, 2, 'Kitchen Towels 3-pack', 1.000, 5.40, 5.40),
    (14, 2, 'Trash Bags 50L 30pcs', 2.000, 3.90, 7.80),
    (14, 2, 'Sponges Multi-purpose 5pcs', 1.000, 3.20, 3.20),
    (14, 5, 'Air Freshener Spray 250ml', 1.000, 4.50, 4.50),

    -- Cheque 15: Weekend treats at HIPPO Rokossovskogo (card payment)
    (15, 3, 'Coffee Beans Arabica 500g', 1.000, 19.90, 19.90),
    (15, 3, 'Tea Green Jasmine 100g', 1.000, 8.50, 8.50),
    (15, 3, 'Cookies Oatmeal 300g', 2.000, 4.20, 8.40),
    (15, 3, 'Chocolate Dark 70% 100g', 3.000, 3.80, 11.40),
    (15, 3, 'Nuts Mix Roasted 200g', 2.000, 9.90, 19.80),
    (15, 4, 'Croissant Almond', 4.000, 2.50, 10.00),
    (15, 4, 'Cake Chocolate Slice', 2.000, 5.80, 11.60),
    (15, 3, 'Sparkling Water Grapefruit 330ml', 4.000, 2.10, 8.40),
    (15, 1, 'Yogurt Greek Strawberry 200g', 3.000, 2.90, 8.70),
    (15, 5, 'Gift Bag Medium', 1.000, 2.50, 2.50);

--changeset user-of-github:04-sync-sequences-after-more-cheques
-- Sync sequences after manual ID insertion
SELECT setval('cheques_id_seq', (SELECT MAX(id) FROM cheques));
SELECT setval('cheque_items_id_seq', (SELECT MAX(id) FROM cheque_items));
