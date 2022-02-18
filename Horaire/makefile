.SILENT:
CC = g++ -Wall -m64 -g

ApplicHoraire:	main.o applichorairewindow.o moc_applichorairewindow.o Horaire.o Planifiable.o Iterateur.o ListeTriee.o Liste.o Professeur.o Local.o Groupe.o Timing.o Temps.o Event.o Exception.o TimingException.o  TempsException.o Cours.o
		echo Creation de ApplicHoraire
		g++ -Wl,-O1 -o ApplicHoraire main.o applichorairewindow.o moc_applichorairewindow.o Horaire.o Planifiable.o Iterateur.o ListeTriee.o  Liste.o Professeur.o Local.o Groupe.o  Timing.o Temps.o Event.o Exception.o TimingException.o  TempsException.o Cours.o   /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread 					

main.o:	main.cpp
		echo Creation de main.o
		g++ -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o main.o main.cpp

applichorairewindow.o:	applichorairewindow.cpp applichorairewindow.h ui_applichorairewindow.h
		echo Creation de applichorairewindow.o
		g++ -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o applichorairewindow.o applichorairewindow.cpp

moc_applichorairewindow.o:	moc_applichorairewindow.cpp applichorairewindow.h
		echo Creation de moc_applichorairewindow.o
		g++ -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o moc_applichorairewindow.o moc_applichorairewindow.cpp

Horaire.o:	Horaire.h Horaire.cpp
			echo Creation de Horaire.o
			$(CC) Horaire.cpp -c

Planifiable.o:	Planifiable.h Planifiable.cpp
				echo Creation de Planifiable.o
				$(CC) Planifiable.cpp -c


Iterateur.o:	Iterateur.h Iterateur.cpp
				echo Creation de Iterateur.o
				$(CC) Iterateur.cpp -c

ListeTriee.o:	ListeTriee.h ListeTriee.cpp
				echo Creation de ListeTriee.o
				$(CC) ListeTriee.cpp -c

Liste.o:	Liste.h Liste.cpp
			echo Creation de Liste.o
			$(CC) Liste.cpp -c

Professeur.o:	Professeur.h Professeur.cpp
				echo Creation de Professeur.o
				$(CC) Professeur.cpp -c

Local.o:	Local.h Local.cpp
			echo Creation de Local.o
			$(CC) Local.cpp -c

Groupe.o:	Groupe.h Groupe.cpp
			echo Creation de Groupe.o
			$(CC) Groupe.cpp -c

Timing.o:	Timing.h Timing.cpp 
			echo Creation de Timing.o
			$(CC) Timing.cpp -c

Temps.o:	Temps.h Temps.cpp
			echo Creation de Temps.o
			$(CC) Temps.cpp -c

Event.o:	Event.h Event.cpp
			echo Creation de Event.o
			$(CC) Event.cpp -c

Exception.o:	Exception.cpp Exception.h
				echo Creation de Exception.o
				$(CC) Exception.cpp -c

TimingException.o:	TimingException.h TimingException.cpp
					echo Creation de TimingException.o
					$(CC) TimingException.cpp -c

TempsException.o:	TempsException.h TempsException.cpp
					echo Creation de TempsException.o
					$(CC) TempsException.cpp -c

Cours.o:	Cours.h Cours.cpp
			echo Creation de Cours.o
			$(CC) Cours.cpp -c



clean:
			rm *.o -f
			rm ApplicHoraire -f