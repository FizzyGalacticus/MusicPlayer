Final Project for UAF 372 class
===============================
![MainIcon](https://raw.githubusercontent.com/FizzyGalacticus/MusicPlayer/master/icons/mainWindowIcon.png)

##Purpose
This media player began as a group project for my CS372 (Software Construction) class. The original purpose was to have us create an application using a GUI framework, since most of us had not played around with GUI programming before. We decided to create a media player that could have a layout and features that we have wanted in existing players. I have since taken on this project solo, but I am looking for contributors!

##GUI Framework:
We originally wanted to use the Unity engine, but it does not seem to have decent support for file input. We decided to use QT instead, which proved to be a great success. Qt's framework has allowed us to quickly throw together something in the small window we had to turn in the assignment, and was easy enough to learn to continue development afterward. I've so far spent the last year's worth of free time to learn more about what Qt has to offer.

###Ideal Features To Implement:
*	Favorites
	-	For as long as I can remember, I have listened to a handful of favorite songs immediately before listening to other stuff. I would really like to implement a feature where favorites can be selected in a playlist and then they would be played before all other songs in that playlist. Of course this would need to be data saved with the playlists as well.
	-	A database system that keeps track of the number of times a user has listened to a particular song.
	-	Video Playback
	-	Capability to automatically install GStreamer (*nix) or DirectShow (Windoze) codecs.
