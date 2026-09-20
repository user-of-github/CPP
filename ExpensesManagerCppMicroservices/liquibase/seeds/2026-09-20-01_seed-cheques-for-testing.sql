--liquibase formatted sql

--changeset user-of-github:01-seed-cheques

-- I generated it with Gemini

INSERT INTO cheques (id, concrete_store_id, payment_method_id, total_amount, receipt_date) VALUES
    (1, 1, 1, 54.57, '2026-09-10 10:15:00+03'),
    (2, 5, 3, 69.20, '2026-09-11 18:30:00+03'),
    (3, 3, 2, 75.00, '2026-09-12 12:45:00+03'),
    (4, 2, 1, 76.76, '2026-09-13 19:10:00+03'),
    (5, 4, 1, 55.22, '2026-09-14 14:05:00+03'),
    (6, 6, 3, 59.70, '2026-09-15 09:20:00+03'),
    (7, 1, 1, 92.73, '2026-09-16 17:50:00+03'),
    (8, 5, 1, 66.90, '2026-09-17 13:15:00+03'),
    (9, 3, 2, 70.60, '2026-09-18 20:05:00+03'),
    (10, 2, 1, 61.80, '2026-09-19 16:40:00+03');

--changeset user-of-github:06-seed-cheque-items
INSERT INTO cheque_items (cheque_id, category_id, product_name, quantity, unit_price, total_price) VALUES
    -- Cheque 1: Groceries run at Euroopt Prime
    (1, 1, 'Fresh Milk 3.2% 1L', 2.000, 2.19, 4.38),
    (1, 1, 'Whole Wheat Bread 400g', 1.000, 1.85, 1.85),
    (1, 1, 'Eggs Large Grade A 10pcs', 1.000, 3.40, 3.40),
    (1, 1, 'Butter 82.5% 180g', 1.000, 4.15, 4.15),
    (1, 1, 'Chicken Breast Fillet 1kg', 1.250, 11.50, 14.38),
    (1, 1, 'Cheddar Cheese Block 250g', 1.000, 6.20, 6.20),
    (1, 1, 'Bananas Fresh', 1.420, 4.50, 6.39),
    (1, 1, 'Tomatoes Vine Ripe', 0.850, 7.90, 6.72),
    (1, 3, 'Mineral Sparkling Water 1.5L', 2.000, 1.60, 3.20),
    (1, 2, 'Kitchen Paper Towels 2-pack', 1.000, 3.90, 3.90),

    -- Cheque 2: Snacks and Coffee at Green City Mall
    (2, 3, 'Arabica Coffee Beans 250g', 1.000, 16.50, 16.50),
    (2, 3, 'Dark Chocolate 85% 100g', 2.000, 3.80, 7.60),
    (2, 4, 'Croissant Butter Bakery', 2.000, 2.20, 4.40),
    (2, 3, 'Orange Juice Fresh 1L', 1.000, 5.80, 5.80),
    (2, 3, 'Roasted Almonds 150g', 1.000, 8.90, 8.90),
    (2, 3, 'Green Tea Jasmine 20 bags', 1.000, 4.50, 4.50),
    (2, 4, 'Baguette French Crispy', 1.000, 1.90, 1.90),
    (2, 1, 'Greek Yogurt Plain 400g', 2.000, 2.60, 5.20),
    (2, 1, 'Fresh Blueberries 125g', 1.000, 7.50, 7.50),
    (2, 3, 'Granola Honey & Oats 375g', 1.000, 6.90, 6.90),

    -- Cheque 3: Cleaning essentials at HIPPO Rokossovskogo
    (3, 2, 'Dishwashing Liquid Citrus 500ml', 1.000, 4.20, 4.20),
    (3, 2, 'Laundry Detergent Gel 1.5L', 1.000, 22.50, 22.50),
    (3, 2, 'Multi-surface Cleaning Spray 750ml', 1.000, 7.30, 7.30),
    (3, 2, 'Microfiber Cleaning Cloths 3pcs', 1.000, 4.90, 4.90),
    (3, 2, 'Trash Bags Heavy Duty 60L 20pcs', 2.000, 3.60, 7.20),
    (3, 2, 'Toilet Paper 3-ply 8 rolls', 1.000, 9.80, 9.80),
    (3, 5, 'AA Alkaline Batteries 4-pack', 1.000, 6.50, 6.50),
    (3, 2, 'Hand Soap Liquid Antibacterial 300ml', 2.000, 3.20, 6.40),
    (3, 2, 'Sponges Heavy Duty 5-pack', 1.000, 2.80, 2.80),
    (3, 3, 'Peppermint Chewing Gum 30g', 2.000, 1.70, 3.40),

    -- Cheque 4: Dinner ingredients at Euroopt Titan Mall
    (4, 1, 'Beef Tenderloin Steak 500g', 0.650, 28.00, 18.20),
    (4, 1, 'Baby Potatoes 1kg', 1.800, 2.20, 3.96),
    (4, 1, 'Fresh Rosemary Pack', 1.000, 2.90, 2.90),
    (4, 1, 'Garlic 3-pack', 1.000, 2.10, 2.10),
    (4, 1, 'Extra Virgin Olive Oil 500ml', 1.000, 19.90, 19.90),
    (4, 1, 'Sea Salt Grinder 100g', 1.000, 5.40, 5.40),
    (4, 1, 'Black Pepper Grinder 50g', 1.000, 6.10, 6.10),
    (4, 1, 'Mixed Salad Greens 150g', 1.000, 4.30, 4.30),
    (4, 3, 'Non-Alcoholic Beer 0.5L', 4.000, 2.80, 11.20),
    (4, 4, 'Ciabatta Olive Bread', 1.000, 2.70, 2.70),

    -- Cheque 5: Weekly staples at HIPPO Goretskogo
    (5, 1, 'Oat Flakes Bio 500g', 2.000, 2.40, 4.80),
    (5, 1, 'Cottage Cheese 5% 300g', 2.000, 3.10, 6.20),
    (5, 1, 'Spaghetti Durum Wheat 500g', 2.000, 3.20, 6.40),
    (5, 1, 'Tomato Basil Pasta Sauce 350g', 2.000, 4.90, 9.80),
    (5, 1, 'Parmesan Cheese Wedge 200g', 1.000, 11.90, 11.90),
    (5, 1, 'Yellow Onions 1kg', 1.100, 1.80, 1.98),
    (5, 1, 'Carrots Washed 1kg', 1.300, 1.90, 2.47),
    (5, 1, 'Apples Gala 1kg', 1.650, 3.80, 6.27),
    (5, 3, 'Herbal Tea Chamomile 25 bags', 1.000, 3.90, 3.90),
    (5, 5, 'Shopping Reusable Bag Large', 1.000, 1.50, 1.50),

    -- Cheque 6: Breakfast run at Green Partizanski
    (6, 4, 'Pain au Chocolat Bakery', 2.000, 2.50, 5.00),
    (6, 4, 'Cinnamon Roll Glazed', 2.000, 2.80, 5.60),
    (6, 3, 'Cold Brew Coffee 330ml', 2.000, 4.50, 9.00),
    (6, 1, 'Strawberries Fresh 250g', 1.000, 8.90, 8.90),
    (6, 1, 'Sour Cream 20% 300g', 1.000, 2.40, 2.40),
    (6, 1, 'Ricotta Cheese 250g', 1.000, 5.10, 5.10),
    (6, 3, 'Energy Drink Sugar Free 250ml', 2.000, 3.20, 6.40),
    (6, 3, 'Roasted Pistachios Salted 100g', 1.000, 9.50, 9.50),
    (6, 4, 'Sesame Bagel Plain', 2.000, 1.60, 3.20),
    (6, 1, 'Salted Butter 200g', 1.000, 4.60, 4.60),

    -- Cheque 7: BBQ weekend at Euroopt Prime
    (7, 1, 'Pork Ribs Marinated 1kg', 1.600, 16.80, 26.88),
    (7, 1, 'Cumberland Sausages 400g', 2.000, 7.50, 15.00),
    (7, 1, 'BBQ Sauce Smokey Hickory 350ml', 1.000, 5.90, 5.90),
    (7, 1, 'Dijon Mustard 200g', 1.000, 3.40, 3.40),
    (7, 1, 'Sweet Corn on the Cob 2pcs', 2.000, 4.20, 8.40),
    (7, 1, 'Red Bell Peppers 1kg', 0.750, 8.20, 6.15),
    (7, 2, 'Charcoal Briquettes 2.5kg', 1.000, 9.90, 9.90),
    (7, 2, 'Firestarter Cubes 24pcs', 1.000, 3.50, 3.50),
    (7, 3, 'Lemonade Sparkling 1L', 2.000, 2.90, 5.80),
    (7, 3, 'Tortilla Corn Chips 150g', 2.000, 3.90, 7.80),

    -- Cheque 8: Healthy lunch at Green City Mall
    (8, 1, 'Fresh Atlantic Salmon Fillet 300g', 1.000, 19.80, 19.80),
    (8, 1, 'Avocado Hass Ready to Eat 2pcs', 1.000, 7.90, 7.90),
    (8, 1, 'Quinoa Organic 400g', 1.000, 6.50, 6.50),
    (8, 1, 'Baby Spinach Fresh 125g', 1.000, 3.80, 3.80),
    (8, 1, 'Cherry Tomatoes 250g', 1.000, 4.60, 4.60),
    (8, 1, 'Lemon Fresh Each', 2.000, 1.20, 2.40),
    (8, 1, 'Cucumber Greenhouse 1kg', 0.600, 4.50, 2.70),
    (8, 3, 'Coconut Water Pure 330ml', 2.000, 3.90, 7.80),
    (8, 3, 'Raw Energy Bar Cashew Date 50g', 3.000, 2.60, 7.80),
    (8, 4, 'Whole Seed Sourdough Loaf 450g', 1.000, 3.60, 3.60),

    -- Cheque 9: Home and Pantry refill at HIPPO Rokossovskogo
    (9, 1, 'Turkey Breast Sliced Deli 150g', 2.000, 4.90, 9.80),
    (9, 1, 'Gouda Cheese Sliced 150g', 2.000, 4.20, 8.40),
    (9, 1, 'Basmati Rice 800g', 1.000, 5.50, 5.50),
    (9, 1, 'Canned Tuna in Olive Oil 160g', 3.000, 4.80, 14.40),
    (9, 1, 'Green Peas Canned 400g', 2.000, 2.10, 4.20),
    (9, 1, 'Sweet Corn Canned 340g', 2.000, 2.30, 4.60),
    (9, 2, 'Toothpaste Whitening Complete 75ml', 1.000, 6.20, 6.20),
    (9, 2, 'Shampoo Daily Moisture 400ml', 1.000, 11.50, 11.50),
    (9, 2, 'Cotton Pads 120pcs', 1.000, 2.90, 2.90),
    (9, 3, 'Still Mineral Water 5L', 1.000, 3.10, 3.10),

    -- Cheque 10: Weekend snacks and sweets at Euroopt Titan Mall
    (10, 4, 'Margherita Pizza Fresh Bake 400g', 1.000, 12.50, 12.50),
    (10, 4, 'Garlic Bread with Herbs 200g', 1.000, 3.40, 3.40),
    (10, 3, 'Ice Cream Vanilla Bean 500ml', 1.000, 9.20, 9.20),
    (10, 3, 'Potato Crisps Sour Cream & Onion 140g', 2.000, 3.80, 7.60),
    (10, 3, 'Cola Zero Sugar 1.5L', 2.000, 2.60, 5.20),
    (10, 3, 'Milk Chocolate Hazelnut 90g', 2.000, 3.50, 7.00),
    (10, 1, 'Fresh Strawberries & Bananas Mix', 1.000, 6.80, 6.80),
    (10, 1, 'Whipped Cream Spray 250ml', 1.000, 5.30, 5.30),
    (10, 2, 'Wet Wipes Antibacterial 60pcs', 1.000, 2.90, 2.90),
    (10, 5, 'Paper Napkins 100pcs', 1.000, 1.90, 1.90);

--changeset user-of-github:07-sync-sequences
-- Выравниваем последовательность первичных ключей после ручного указания ID
SELECT setval('cheques_id_seq', (SELECT MAX(id) FROM cheques));
SELECT setval('cheque_items_id_seq', (SELECT MAX(id) FROM cheque_items));