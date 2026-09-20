# _CPP Microservices application_
## _Expenses-manager microservices_
___   

### Tech stack:   
- _[Modern C++ 17/20](https://isocpp.org/)_  
- _[Drogon — C++17/20-based HTTP application framework](https://drogon.org/) || [[GIT]](https://github.com/drogonframework/drogon)_  
- _[Nlohmann JSON](https://json.nlohmann.me/)_
- _[Docker, Docker-Compose](https://www.docker.com/)_  
- _[PostrgreSQL](https://www.postgresql.org/)_
- _[Liquibase](https://www.liquibase.com/) for DB migrations_  
- _[Gemini Flash](https://blog.google/innovation-and-ai/models-and-research/gemini-models/3-8-flash-and-3-8-flash-cyber/) for consultations and boilerplate code generation_

___  
### Installation:  
- Fill .env with necessary DB data (see [.env.example](./.env.example) for reference)  
- If running services locally - make sure that configuration in CLion includes environment string same as in .env file  
- If running locally make cure, you have GNU supporting C++ 20 standard, and mentioned libs above. I have GNU 14  

___  
### Hints:  
##### If no internet in Docker
- `sudo nano /etc/docker/daemon.json`
- Insert there:
```json
{
  "dns": ["8.8.8.8", "1.1.1.1"]
}
```  
- `Ctrl+O`, `Enter`, `Ctrl+X`  
- `sudo systemctl restart docker`

