
Debian
====================
This directory contains files used to package zcored/zcore-qt
for Debian-based Linux systems. If you compile zcored/zcore-qt yourself, there are some useful files here.

## zcore: URI support ##


zcore-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install zcore-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your zcoreqt binary to `/usr/bin`
and the `../../share/pixmaps/zcore128.png` to `/usr/share/pixmaps`

zcore-qt.protocol (KDE)

