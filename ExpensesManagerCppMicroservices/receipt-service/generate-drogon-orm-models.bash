# Read env data
export $(grep -v '^#' ../.env | xargs)

# 2. Generating src/db/__generated__/model.json
cat <<EOF > src/db/__generated__/model.json
{
  "rdbms": "postgresql",
  "host": "${POSTGRES_HOST:-127.0.0.1}",
  "port": ${POSTGRES_PORT:-5432},
  "dbname": "${POSTGRES_DB:-expense_db}",
  "user": "${POSTGRES_USER:-postgres}",
  "passwd": "${POSTGRES_PASSWORD}",
  "tables": []
}
EOF

# Drogon models classes auto generation
drogon_ctl create model src/db/__generated__

rm -f src/db/__generated__/Databasechangelog.*
rm -f src/db/__generated__/Databasechangeloglock.*