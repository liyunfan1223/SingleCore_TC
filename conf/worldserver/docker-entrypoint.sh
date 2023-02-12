cd /trinity/build

CXX=g++-6 CC=gcc-6 cmake .. -DCONF_DIR=/usr/local/etc -DTOOLS=0 -DWITH_WARNINGS=0 -DCMAKE_EXPORT_COMPILE_COMMANDS=1

make -j8 && make install

cp /usr/local/etc/worldserver.conf.dist /usr/local/etc/worldserver.conf && \
cp /usr/local/etc/authserver.conf.dist /usr/local/etc/authserver.conf && \
cp /usr/local/etc/aiplayerbot.conf.dist /usr/local/etc/aiplayerbot.conf

cd /usr/local/bin

./authserver &

./worldserver