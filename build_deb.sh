#!/bin/sh
make clean
./bootstrap
./configure --prefix=/usr
make

checkinstall \
		--install=no \
		--backup=no \
		--strip=yes \
		--stripso=yes \
		--nodoc \
		--pkgversion="0.9" \
		--pkggroup="system" \
		--requires="libboost-program-options1.55.0, liblog4cplus-1.0-4, libcec3, liblockdev1, libboost-system1.55.0, libboost-thread1.55.0, libstdc++6" \
		--pkgname="libcec-daemon" \
		--maintainer='KingBonecrusher' \
		--provides='libcec-daemon' \
		--pkgsource="https://github.com/KingBonecrusher/libcec-daemon"



