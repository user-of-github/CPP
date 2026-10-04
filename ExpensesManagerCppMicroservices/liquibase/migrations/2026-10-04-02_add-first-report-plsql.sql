--liquibase formatted sql

--changeset user-of-github:01-create-category-report-proc endDelimiter:/
CREATE OR REPLACE FUNCTION get_monthly_category_report()
RETURNS TABLE (
    "Category" VARCHAR,
    "Items Count" BIGINT,
    "Total Spent" NUMERIC
) AS $$
BEGIN
    RETURN QUERY
    SELECT
        COALESCE(c.name, 'Uncategorized')::VARCHAR AS "Category",
        COUNT(ci.id)::BIGINT AS "Items Count",
        ROUND(COALESCE(SUM(ci.total_price), 0.0), 2) AS "Total Spent"
    FROM cheque_items ci
    JOIN cheques ch ON ci.cheque_id = ch.id
    LEFT JOIN categories c ON ci.category_id = c.id
    GROUP BY c.name
    ORDER BY 3 DESC;
END;
$$ LANGUAGE plpgsql;
/