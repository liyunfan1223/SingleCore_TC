echo "Create docker image for worldserver and authserver..."
sudo docker build -t trinity:env -f Dockerfile.worldserver.dev .
echo "Create docker image for registor page..."
sudo docker build -t trinity:reg -f Dockerfile.register .
