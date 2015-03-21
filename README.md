Final Project for UAF 372 class
===============================
![MainIcon](https://raw.githubusercontent.com/FizzyGalacticus/MusicPlayer/master/icons/mainWindowIcon.png)

##Purpose
This media player began as a group project for my CS372 (Software Construction) class. The original purpose was to have us create an application using a GUI framework, since most of us had not played around with GUI programming before. We decided to create a media player that could have a layout and features that we have wanted in existing players. 

I have since taken on this project solo, but I am looking for contributors! I am currently working on completely re-writing everything due to the spaghetti-code. All new work is currently being pushed to the "newMusicPlayer" branch.

##GUI Framework:
My group and I originally wanted to use the Unity engine, but it does not seem to have decent support for file input. We decided to use QT instead, which proved to be a great success. Qt's framework has allowed us to quickly throw together something in the small window we had to turn in the assignment, and was easy enough to learn to continue development afterward. I've so far spent the last year's worth of free time to learn more about what Qt has to offer.

###Ideal Features To Implement:
*	Favorites
	-	For as long as I can remember, I have listened to a handful of favorite songs immediately before listening to other stuff. I would really like to implement a feature where favorites can be selected in a playlist and then they would be played before all other songs in that playlist. Of course this would need to be data saved with the playlists as well.
*	Statistics
	-	A database system that keeps track of the number of times a user has listened to a particular song.
*	~~Video Playback~~
	-	~~Because why not? This honestly shouldn't take that much effort, as the player currently can play audio for video files. It just needs the video portion added.~~
*	Compatibility
	-	Capability to automatically install GStreamer (*nix) or DirectShow (Windoze) codecs, or to bundle codecs with application.

###Compiling MySQL drivers
This has proved to be quite a challenge for both Linux & Windows systems, so I though I would document my process.

First, it is necessary to build the qsqlmysql driver. From *some* posts I've read, QT5 supposedly comes with them pre-build, but I have not found sufficient evidence to support this. Make sure that you have qmake **from the Qt version of the driver that you wish to build** in your PATH. Also, you **need to have the same architecture of MySQL server installed as the version of Qt that you're building for.** A 32-bit Qt application *can* talk to a 64-bit server, but you must have the 32-bit **libmysql** library for the Qt application to talk to. 

To build, navigate to your Qt\VERSION\Src\qtbase\src\plugins\sqldrivers\mysql folder in the terminal. Then type the following command on Linux:
```Bash
qmake "INCLUDEPATH+=/PATH/TO/MYSQL/include" "LIBS+=/PATH/TO/MYSQL/lib -lmysqlclient_r" mysql.pro
make
make install
```

or on Windows:
```Bash
qmake "INCLUDEPATH+=\PATH\TO\MYSQL\include" "LIBS+=\PATH\TO\MYSQL\lib\mysqlclient" mysql.pro
make	#Whatever version of make you're using
make install
```

If everything goes well, then you shouldn't have any errors, and the drivers should have been installed into your Qt\VERSION\COMPILER\bin directory. If not, feel free to message me and I'll see if I've made an error. (*oops*)

If you by chance get an error about the main.moc having been created by an earlier version, then simply **delete** the main.moc file. Then re-run the above commands. A "make clean" might not be a bad idea either.