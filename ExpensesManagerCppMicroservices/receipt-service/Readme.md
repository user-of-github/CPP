# Receipts (Cheques) Microservice  
___  
## Endpoints:  
### Classificators
- `GET` - `/payment-methods` - Get list of active payment methods
- `GET` - `/categories` - None - Get list of expense categories
- `GET` - `/retail-chains` - None - Get list of retail chains
- `GET` - `/shops` - Query: retail_chain_id (integer, optional) - Get list of concrete shops filtered by retail chain
- `GET` - `/shops/{id}` - Get concrete shop details by ID  
### Cheques
- `GET` - `/cheques` - Get paginated list of receipts
- `GET` - `/cheques/{id}` -  Get receipt with items by ID
- `POST` - `/cheques` - Body: `CreateChequeDto` - Create a new receipt with items
- `DELETE` - `/cheques/{id}` - Delete receipt and related items by ID  

**CreateChequeDto**  
```json
{
  "concrete_store_id": 1,
  "payment_method_id": 1,
  "total_amount": 369.80,
  "items": [
    {
      "category_id": 1,
      "product_name": "Milk 3.2%",
      "quantity": 2.000,
      "unit_price": 89.90,
      "total_price": 179.80
    }
  ]
}
```