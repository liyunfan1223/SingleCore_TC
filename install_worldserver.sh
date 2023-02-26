apt update -y && apt upgrade -y

apt install build-essential software-properties-common -y && \
add-apt-repository ppa:ubuntu-toolchain-r/test -y && \
apt update -y && \
apt install p7zip git vim gcc-6 g++-6 -y

apt install cmake make libmysqlclient-dev libssl-dev libbz2-dev libreadline-dev libncurses-dev libboost-all-dev mysql-client -y

mkdir build && cd build

CXX=g++-6 CC=gcc-6 cmake .. -DCONF_DIR=/usr/local/etc -DTOOLS=0 -DWITH_WARNINGS=0

make -j4 && make install

cp /usr/local/etc/worldserver.conf.dist /usr/local/etc/worldserver.conf && \
cp /usr/local/etc/authserver.conf.dist /usr/local/etc/authserver.conf && \
cp /usr/local/etc/aiplayerbot.conf.dist /usr/local/etc/aiplayerbot.conf

cd ..

7zr x static/data.7z -o/usr/local && rm data.7z

mkdir /usr/local/logs && chmod 777 /usr/local/logs -R

cd /usr/local/bin
