# CPP Microservices application
## Expenses-manager microservices
___   

### Tech stack:  
- _[Docker, Docker-Compose](https://www.docker.com/)_  
- _[PostrgreSQL](https://www.postgresql.org/)_
- _[Liquibase](https://www.liquibase.com/)_  
- [Modern C++ 17/20](https://isocpp.org/)

### Installation:  
- Env  
##### If no internet in docker
- `sudo nano /etc/docker/daemon.json`
- Insert there:
```json
{
  "dns": ["8.8.8.8", "1.1.1.1"]
}
```  
- `Ctrl+O`, `Enter`, `Ctrl+X`  
- `sudo systemctl restart docker`

