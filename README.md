Final Project for UAF 372 class
===============================
![MainIcon](https://raw.githubusercontent.com/FizzyGalacticus/MusicPlayer/master/icons/mainWindowIcon.png)

##Requirements:
This assignment was given essentially to allow the Spring '14 UAF CS372 class play around with GUI programming, considering that most of us had never played with GUI development prior.

##Group Idea:
Our group's idea was to create a music/audio player.

##Group Members:
*	Dustin Dodson

##Former Contributors:
*	Erik Talvi
*	Matthew Parrish
*	Nate Helms
*	Nicholas Mardeusz
*	Thomas Cerny

##GUI Framework:
We originally wanted to use the Unity engine, but it does not seem to have decent support for file input. We decided to use QT instead, which proved to be a great success. Qt's framework has allowed us to quickly throw together something in the small window we had to turn in the assignment, and was easy enough to learn to continue development afterward.

###Helpful Links for QT Framework:
*	[QT Multimedia Library](http://qt-project.org/doc/qt-5/qtmultimedia-index.html)
	-	[QMediaPlayer Class](http://qt-project.org/doc/qt-5/qmediaplayer.html)
	-	[QMediaPlaylist Class](http://qt-project.org/doc/qt-5/qmediaplaylist.html)
	
*	[QDir Class](http://qt-project.org/doc/qt-4.8/qdir.html): For directory and file manipulation, namely *getting files from a directory*.

*	[QPushButton Class](http://qt-project.org/doc/qt-5/QPushButton.html): Used for our audio playback buttons as well as for MISC. options.

*	[QTabWidget](http://qt-project.org/doc/qt-5/qtabwidget.html): Used to display different tabs. Useful for having more than one playlist open at a time.

*	[QListWidget](http://qt-project.org/doc/qt-5/qlistwidget.html): Handy for displaying information about the audio tracks for each given playlist.

*	[QIcon](http://qt-project.org/doc/qt-5/qicon.html): Very easy to use icon object to use on all the things!

###Ideal Features To Implement:
*	Favorites
	-	For as long as I can remember, I have listened to a handful of favorite songs immediately before listening to other stuff. I would really like to implement a feature where favorites can be selected in a playlist and then they would be played before all other songs in that playlist. Of course this would need to be data saved with the playlists as well.
